# DSP 人脸检测算法优化总结

> 平台: CEVA SensPro250 @ 400MHz  
> 日期: 2026年1月29日  
> 分支: feat/dsp-testbench

## 1. 完整管线性能概览

### 1.1 端到端时间分解

| 阶段             | 功能                      | 耗时      | 占比  |
| ---------------- | ------------------------- | --------- | ----- |
| **前处理 (pre)** | BGR565→RGB888 转换 + 裁剪 | 6 ms      | 12.2% |
| **推理 (inf)**   | 48层神经网络前向传播      | 39 ms     | 79.6% |
| **Softmax (sm)** | 置信度归一化              | 2 ms      | 4.1%  |
| **解码 (dec)**   | PriorBox 解码             | 0 ms      | ~0%   |
| **NMS**          | 非极大值抑制              | 0 ms      | ~0%   |
| **总计 (det)**   | 检测完整流程              | **49 ms** | 100%  |

### 1.2 推理层优化成果

| 指标                | 优化前   | 优化后   | 提升       |
| ------------------- | -------- | -------- | ---------- |
| **L0 (conv_rgb)**   | 3.915 ms | 3.462 ms | **-11.6%** |
| **L8 (conv1x1xn)**  | 4.067 ms | 3.652 ms | **-10.2%** |
| **L10 (conv1x1xn)** | 4.067 ms | 3.652 ms | **-10.2%** |
| **推理总时间**      | 34.27 ms | 33.65 ms | **-1.8%**  |

## 2. 前处理分析

### 2.1 当前实现

```c
// BGR565 到 RGB888 转换 (160×120 = 19200 像素)
void cropAndConvertImage(const uint16_t *srcImage, uint8_t *dstImage, 
                         int srcWidth, int srcHeight, int cropHeight)
{
    for (int y = 0; y < dstHeight; ++y) {
        for (int x = 0; x < dstWidth; ++x) {
            uint16_t bgr565 = srcImage[y * srcWidth + x];
            BGR565ToRGB888(bgr565, &r, &g, &b);  // 逐像素转换
            dstImage[dstIndex + 0] = r;
            dstImage[dstIndex + 1] = g;
            dstImage[dstIndex + 2] = b;
        }
    }
}
```

### 2.2 性能分析

- **当前耗时**: 6ms (19200 像素)
- **每像素耗时**: 312 cycles
- **主要开销**: 位域提取 + 移位 + 函数调用

### 2.3 潜在优化方向

| 优化方案                      | 预期效果 | 实现难度 |
| ----------------------------- | -------- | -------- |
| 查表法替代位运算              | -30~50%  | 低       |
| SIMD 向量化 (一次处理 4 像素) | -60~80%  | 中       |
| DMA + CPU 并行                | -50%     | 高       |

## 3. 后处理分析

### 3.1 Softmax (2ms)

```c
void my_softmax(struct FloatTensor *result) {
    // 对每个锚点计算 exp 和归一化
    // 使用 Newton-Raphson 迭代的快速平方根
}
```

**优化状态**: 已使用快速 `my_sqrt_f32` 替代标准库

### 3.2 PriorBox 解码 (0ms)

- 使用预计算的 anchor 参数
- 浮点运算已优化

### 3.3 NMS (0ms)

- 候选框数量少时几乎无开销
- 已实现基本的 IoU 快速计算

## 4. 推理层优化详情

### 3.1 conv1x1xn 优化 (L8/L10)

**问题分析**：
- 原实现循环顺序：`for(vec_part) { for(pixel) }`
- 对于 64→64 卷积，每像素的 64 字节输入被读取 4 次
- 权重预处理在每个 vec_part 开始时重复执行

**优化方案**：
```c
// 优化版：64->64 专用快速路径
if(i_c == 64 && o_c == 64) {
    // 1. 预加载所有 4 组权重 (~8KB)
    short4xN_t weight_all[4][64];
    for(int vp = 0; vp < 4; vp++) {
        // 权重重组 + bias/shift 预处理
    }
    
    // 2. 像素循环在外层，每像素只读一次输入
    for(int p = 0; p < total_pixels; p++) {
        // 缓存 64 字节输入
        unsigned int in_cache[16];
        
        // 处理 4 个 vec_part
        for(int vp = 0; vp < 4; vp++) {
            // 16 次 _vmac5 展开
        }
    }
}
```

**关键优化点**：
1. **循环重排**：像素循环外移，减少 4× 输入内存访问
2. **权重预加载**：一次性加载所有权重到寄存器/栈
3. **输入缓存**：使用 `in_cache[16]` 缓存 64 字节输入

**效果**：4.067ms → 3.652ms (-10.2%)

### 3.2 conv_rgb 优化 (L0)

**问题分析**：
- 4 个分支处理边界条件 (i==0, j==0 等)
- 每个像素调用 `memset(28)` 清零 + 多次 `memcpy`
- 7 次 `_vmac5` 循环未展开

**优化方案**：
```c
// 优化版：分离边界和主体区域
for(int i = 0; i < output->height; i++) {
    for(int j = 0; j < output->width; j++) {
        int need_padding = /* 边界检测 */;
        
        if(!need_padding) {
            // 快速路径：直接指针读取 3×3×3 = 27 字节
            unsigned char *row0 = in_data + ...;
            unsigned char *row1 = row0 + input_step;
            unsigned char *row2 = row1 + input_step;
            
            // 7 次 _vmac5 完全展开
            acc = _vmac5(weight_vec[0], ..., _pack(row0[0], row0[1]), ...);
            // ... (共 7 次)
        } else {
            // 慢速路径：边界像素，需要 padding 处理
        }
        
        // 直接向量存储
        *(uchar4xN_t*)(out_data + ...) = temp1;
    }
}
```

**关键优化点**：
1. **快速/慢速路径分离**：98.7% 像素 (159×119) 走快速路径
2. **消除 memset/memcpy**：主体区域直接指针访问
3. **循环展开**：7 次 `_vmac5` 完全展开
4. **向量存储**：使用 `*(uchar4xN_t*)` 替代 `memcpy`

**效果**：3.915ms → 3.462ms (-11.6%)

## 5. 热点层分析

通过添加分层计时，识别出三个主要热点层：

| 层  | 算子类型       | 输入尺寸 | 通道  | 耗时   | 占推理比 |
| --- | -------------- | -------- | ----- | ------ | -------- |
| L0  | conv_rgb (3×3) | 160×120  | 3→16  | 3.46ms | 10.3%    |
| L8  | conv1x1xn      | 40×30    | 64→64 | 3.65ms | 10.8%    |
| L10 | conv1x1xn      | 40×30    | 64→64 | 3.65ms | 10.8%    |

三层合计占推理时间的 **31.9%**。

## 6. 代码清理

- 删除注释掉的 `Timer0_init()` 函数
- 简化 `printUint8Tensor` / `printfloatTensor` 为空实现
- 删除注释掉的旧版 `pooling()` 函数 (~45 行)
- 简化层计时输出，只打印热点层 (L0, L8, L10) 和总时间

## 7. 栈空间调整

`conv1x1xn` 优化需要约 8.6KB 栈空间用于权重预加载：

| 变量                | 大小    |
| ------------------- | ------- |
| `weight_all[4][64]` | 8,192 B |
| `bias_all[4]`       | 256 B   |
| `shift_*_all[4]`    | 256 B   |
| `in_cache[16]`      | 64 B    |

如使用栈分配，需修改链接脚本 `testbench_dsp.ld`：
```
__stack_size = DEFINED(__stack_size) ? __stack_size : 16k;  // 原 4k
```

当前实现使用栈分配，需要 16KB 栈空间。

## 8. 未来优化方向

### 8.1 前处理优化

| 优化方案        | 描述                                 | 预期收益 |
| --------------- | ------------------------------------ | -------- |
| **SIMD 向量化** | 一次处理 4 像素的 BGR565→RGB888 转换 | -60~80%  |
| **查表法**      | 预计算 5/6 位到 8 位的映射表         | -30~50%  |
| **DMA 并行**    | DMA 传输与 CPU 计算重叠              | -50%     |

### 8.2 推理优化

| 优化方案           | 描述                        | 预期收益 |
| ------------------ | --------------------------- | -------- |
| **DMA 预取**       | 异步加载下一批像素数据      | -10~20%  |
| **权重放置**       | 热点层权重放到 DTCM         | -5~10%   |
| **其他 conv1x1xn** | 扩展 64→64 快速路径到更多层 | -3~5%    |
| **depthwise_conv** | 类似循环重排技术            | -5~10%   |

### 8.3 后处理优化

| 优化方案          | 描述           | 预期收益       |
| ----------------- | -------------- | -------------- |
| **定点 Softmax**  | 避免浮点运算   | -50% (2ms→1ms) |
| **SIMD exp 近似** | 向量化指数函数 | -30%           |

## 9. 性能统计打印

每次调用 `face_detect()` 后，系统会自动输出完整的性能统计：

```
========== DSP Face Detection Performance ==========
[Pre-process ] BGR565->RGB888: 6 ms
[Inference   ] 48-layer CNN  : 39 ms
[Post-process] Softmax       : 2 ms
[Post-process] Decode        : 0 ms
[Post-process] NMS(+IOU)     : 0 ms
----------------------------------------------------
[Summary] Pre=6  Infer=39  Post=2 (Total=47 ms)
[FPS] Theory: 21 fps | Actual(~95%): 19 fps
====================================================
```

### 9.1 全局变量说明

| 变量名                 | 类型       | 说明                       |
| ---------------------- | ---------- | -------------------------- |
| `g_perf_preprocess_ms` | `uint32_t` | 前处理耗时 (BGR565→RGB888) |
| `g_perf_infer_ms`      | `uint32_t` | 推理耗时 (48层CNN)         |
| `g_perf_softmax_ms`    | `uint32_t` | Softmax 耗时               |
| `g_perf_decode_ms`     | `uint32_t` | PriorBox 解码耗时          |
| `g_perf_nms_ms`        | `uint32_t` | NMS 耗时 (含 IOU 计算)     |

### 9.2 帧率计算

- **理论帧率**: `1000 / 总耗时(ms)` fps
- **实际帧率**: 理论帧率 × 95% (考虑系统开销)

## 10. 文件变更清单

| 文件                               | 变更类型 | 说明                                |
| ---------------------------------- | -------- | ----------------------------------- |
| `src/face_detect.c`                | 修改     | conv1x1xn、conv_rgb 优化 + 性能统计 |
| `src/face_detect.h`                | 修改     | 新增 g_perf_preprocess_ms 声明      |
| `Debug/testbench_dsp.ld`           | 修改     | 栈空间调整 (可选)                   |
| `docs/DSP_OPTIMIZATION_SUMMARY.md` | 新增     | 本文档                              |

## 11. 验证

优化后人脸检测功能正常：
- 检测框正确显示
- 兼容字段保持固定值
- 无误检/漏检

---

*Generated by AI optimization session*
