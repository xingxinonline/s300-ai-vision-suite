# CEVA SensPro250 硬件验证参考手册

> 基于实际硬件测试结果，2026-01-28 (v6.0 - 向量类型分类修正)

## 1. 硬件架构确认

### 1.1 产品规格 (SP250, N=4)

| 参数             | 值                | 说明                     |
| ---------------- | ----------------- | ------------------------ |
| 产品型号         | **SP250**         | 通过 int2xN_t 元素数确认 |
| N 值             | **4**             | 向量宽度系数             |
| 向量寄存器宽度   | **256 bits**      | 单寄存器                 |
| VCU              | 1× VCU0 + 1× LVCU | 最多2条向量指令/周期     |
| 浮点支持         | ❌ 禁用            | 无 SP/HP 浮点            |
| 非线性指令       | ✅ 启用            | _vsigmoid, _vtanh 可用   |
| 累加器 (v24-v31) | 8个 × 512 bits    | 固定宽度累加器           |

### 1.2 向量类型分类 (关键理解！)

**类型命名规则**: 前缀数字是向量倍数标识，不是元素数！

#### Half Vector (半寄存器, 128 bits)
| 类型         | sizeof() | 元素数 | 元素大小 |
| ------------ | -------- | ------ | -------- |
| `char4xN_t`  | 16 bytes | 16     | 8-bit    |
| `short2xN_t` | 16 bytes | 8      | 16-bit   |

#### Full Vector (单寄存器, 256 bits) ← 用于检测产品！
| 类型           | sizeof()     | 元素数 | 元素大小 |
| -------------- | ------------ | ------ | -------- |
| `char8xN_t`    | 32 bytes     | 32     | 8-bit    |
| `short4xN_t`   | 32 bytes     | 16     | 16-bit   |
| **`int2xN_t`** | **32 bytes** | **8**  | 32-bit   |

#### Dual Vector (双寄存器, 512 bits) ← 跨2个寄存器！
| 类型         | sizeof() | 元素数 | 元素大小 |
| ------------ | -------- | ------ | -------- |
| `short8xN_t` | 64 bytes | 32     | 16-bit   |
| `int4xN_t`   | 64 bytes | 16     | 32-bit   |

**⚠️ 重要修正 (2026-01-28)**:
- 之前误以为 `int4xN_t` 是 Full Vector，实际是 **Dual Vector**
- 使用 `int2xN_t` (8元素) 判断产品型号更准确
- SP250: int2xN_t=8个, SP500: int2xN_t=16个

### 1.3 内存配置

**内存地址映射图:**

```
DSP 内部视角 (CEVA核心)          外部视角 (AXI总线/DMA)
=====================          =======================
DTCM: 0x00000000 (256KB)  <-->  0x44800000
PTCM: 0x00000000 (128KB)  <-->  0x44A00000  (不同总线)

External SRAM (连续512KB):
  SRAM0: 0x44000000 (256KB)
  SRAM1: 0x44040000 (256KB)

PSRAM: 0x80000000 (8MB)   <-->  0x80000000
```

| 区域      | 大小   | 内部地址   | 外部地址   | 说明                   |
| --------- | ------ | ---------- | ---------- | ---------------------- |
| **DTCM**  | 256 KB | 0x00000000 | 0x44800000 | 数据TCM (最快)         |
| **PTCM**  | 128 KB | 0x00000000 | 0x44A00000 | 程序TCM (不同总线)     |
| **SRAM0** | 256 KB | -          | 0x44000000 | 外部SRAM               |
| **SRAM1** | 256 KB | -          | 0x44040000 | 外部SRAM (与SRAM0连续) |
| **PSRAM** | 8 MB   | -          | 0x80000000 | 外部PSRAM (XIP)        |

**⚠️ PSRAM 重要限制**: 
- **不支持 8-bit 读写！**
- 最小访问宽度: **16-bit**
- 使用 `uint16_t*` 或 `uint32_t*` 访问

### 1.3 时钟配置 (动态读取)

通过 RCC 寄存器读取 PLL 配置计算实际时钟：

```c
// PLL 公式:
// FOUTVCO = HSE * FBDIV / REFDIV
// FOUTPOSTDIV = FOUTVCO / (POSTDIV1 * POSTDIV2)
// DSP_CLK = FOUTPOSTDIV / 2

// 寄存器读取
uint32_t refdiv = (DSP_PLL_CRL >> 24) & 0x3F;
uint32_t fbdiv = DSP_PLL_CRL2 & 0xFFF;
uint32_t postdiv1 = (DSP_PLL_CRL2 >> 12) & 0x7;
uint32_t postdiv2 = (DSP_PLL_CRL2 >> 15) & 0x7;
```

常用频率配置：
| 频率    | REFDIV | FBDIV | POSTDIV1 | POSTDIV2 |
| ------- | ------ | ----- | -------- | -------- |
| 384 MHz | 1      | 64    | 2        | 1        |
| 400 MHz | 1      | 100   | 3        | 1        |
| 600 MHz | 1      | 100   | 2        | 1        |
| 800 MHz | 3      | 200   | 1        | 1        |

### 1.4 AXI DMA

- **通道数**: 8 channels
- **基地址**: 0x44088000
- **功能**: Memory-to-Memory, LLI支持
- **传输宽度**: 8/16/32/64 bits

---

## 2. 向量指令验证结果

### 2.1 _vmac - 向量乘累加 ✅ 已验证

**签名**:
```c
int4xN_t _vmac(char4xN_t a, short4xN_t b, int4xN_t acc);
int4xN_t _vmac(uchar4xN_t a, short4xN_t b, int4xN_t acc);
int4xN_t _vmac(short4xN_t a, short4xN_t b, int4xN_t acc);
```

**⚠️ 重要**: 第二个参数必须是 `short4xN_t`，不能是 `char4xN_t`！

**行为确认**:
```
acc[k] = acc[k] + a[k] * b[k]   // for k = 0..15
```

**这是逐元素操作，不是点积！** 无跨通道累加。

**通道映射测试结果**:
```
a[0]=1, b[0]=1, others=0 → acc[0]=1, 其他=0
a[4]=1, b[4]=1, others=0 → acc[4]=1, 其他=0
a[8]=1, b[8]=1, others=0 → acc[8]=1, 其他=0
```

**有符号/无符号测试**:
```
input=200 (0xC8), weight=1:
- char4xN_t  (signed):   result = -56 (正确解释为有符号)
- uchar4xN_t (unsigned): result = 200 (正确解释为无符号)
```

### 2.2 _vmax - 向量最大值 ✅ 已验证

**签名**:
```c
char8xN_t _vmax(char8xN_t a, char8xN_t b);
short4xN_t _vmax(short4xN_t a, short4xN_t b);
```

**行为确认**:
```
out[k] = max(a[k], b[k])   // for all k
```

逐元素取最大值，测试全部通过。

### 2.3 _vshiftr - 向量算术右移 ✅ 已验证

**签名**:
```c
short4xN_t _vshiftr(short4xN_t a, int shift);
int4xN_t _vshiftr(int4xN_t a, int shift);
```

**行为确认**:
```
out[k] = a[k] >> shift   // 算术右移，保留符号
```

测试结果:
- `256 >> 4 = 16` ✅
- `1024 >> 4 = 64` ✅  
- `-256 >> 4 = -16` ✅ (符号扩展正确)

### 2.4 _vmax4 - 4输入向量最大值 ⚠️ 需进一步研究

**签名**:
```c
char8xN_t _vmax4(char8xN_t a, char8xN_t b, char8xN_t c, char8xN_t d, unsigned char mode);
short4xN_t _vmax4(short4xN_t a, short4xN_t b, short4xN_t c, short4xN_t d, unsigned char mode);
```

第5个参数 `mode` 控制比较模式，具体用法待研究。
当 `mode=0` 时输出全是 -128，行为异常。

### 2.5 _vmac5 - 5点乘累加 ✅ 已验证

**签名** (经编译器头文件验证):
```c
int4xN_t _vmac5(short4xN_t a, short4xN_t b, short4xN_t c, short4xN_t d,
                unsigned int packed_input, int4xN_t acc);
```

**⚠️ 原文档签名错误**: 输入不是 `char4xN_t`，而是 `short4xN_t`！

**行为确认**:
```
acc[k] += a[k]*e0 + b[k]*e1 + c[k]*e2 + d[k]*e3
```

其中 `e0-e3` 是从 `packed_input` 提取的4个8位值。

**测试结果**:
```
a[0]=1, b[0]=2, c[0]=3, d[0]=4
packed_input = 0x01010101  // e0=e1=e2=e3=1
acc[0] = 1*1 + 2*1 + 3*1 + 4*1 = 10 ✅
```

### 2.6 _vconv - 向量卷积 ✅ 已验证

**签名** (经编译器头文件验证):
```c
int32 _vconv(char8xN_t a, char8xN_t b, char8xN_t c, char8xN_t d,
             unsigned char inE, unsigned short inF, int32 acc);
```

**⚠️ 关键发现**:
- `int32` 是**向量类型** (32 × int = 1024位)，不是标量！
- `inE` 必须是**立即数常量** (0-3)，不能用变量传递
- `inF` 也必须是立即数常量

**测试结果** (2026-01-28 验证):
```
输入: a[i]=i, b[i]=1, c[i]=2, d[i]=3

inE=0, inF=0: acc[0-3] = {0, 0, 0, 0}  (无输出)
inE=1, inF=0: acc[0-3] = {0, 0, 0, 0}  (无输出)
inE=2, inF=0: acc[0-3] = {0, 0, 0, 0}  (无输出)
inE=3, inF=0: acc[0-3] = {0, 0, 0, 0}  (无输出)

inE=0, inF=1: acc[0-3] = {0, 3, 6, 9}  ✅ 有效输出！
```

**行为分析**:
- `inF=1` 激活卷积操作
- 输出 `{0, 3, 6, 9}` = `{a[0]*d, a[1]*d, a[2]*d, a[3]*d}` = `{0×3, 1×3, 2×3, 3×3}`
- 推测：`inF` 选择使用哪个向量作为乘数

### 2.7 _vcorr3x3 - 3x3 相关运算 ✅ 已验证

**签名** (经编译器头文件验证):
```c
void _vcorr3x3(char8xN_t A, char8xN_t B, char8xN_t C, char8xN_t D,
               short8xN_t& acc, char8xN_t& out);
```

**功能**: 3x3滑动窗口卷积专用指令

**操作**:
```
res[k] += A[k]*D[0] + A[k+1]*D[1] + A[k+2]*D[2] +
          B[k]*D[3] + B[k+1]*D[4] + B[k+2]*D[5] +
          C[k]*D[6] + C[k+1]*D[7] + C[k+2]*D[8]
```

**测试结果** (2026-01-28 验证):
```
输入 3x3 块:         Kernel D[0-8]:
row_a: [1, 2, 3]     [1, 1, 1, 1, 1, 1, 1, 1, 1]
row_b: [4, 5, 6]
row_c: [7, 8, 9]

_vcorr3x3 输出:
acc[0] = 45 = 1+2+3+4+5+6+7+8+9  ✅ (窗口位置0)
acc[1] = 33 = 2+3+0+5+6+0+8+9+0  ✅ (窗口位置1)
acc[2] = 18 = 3+0+0+6+0+0+9+0+0  ✅ (窗口位置2)
```

**滑动窗口确认**: 指令正确实现了3x3卷积的滑动行为。

### 2.8 _vmac9 - 8点乘累加 ✅ 已验证

**签名** (经编译器头文件验证):
```c
int4xN_t _vmac9(char8xN_t inA, char8xN_t inB, char8xN_t inC, char8xN_t inD,
                ushort4xN_t inE, unsigned char inF, int4xN_t accG);
```

**功能**: 用于3x3卷积的高效MAC指令，可同时处理多个位置的加权求和。

**参数**:
- `inA, inB, inC, inD` - 4个输入向量 (char8xN_t = 32×8bit)
- `inE` - 系数向量 (ushort4xN_t = 16×16bit)
- `inF` - 模式控制 (0-3，必须是立即数)
- `accG` - 累加器 (int4xN_t = 16×32bit)

**测试结果** (2026-01-28 验证):
```
输入: A[i]=i+1, B[i]=i+2, C[i]=i+3, D[i]=i+4
系数: E[i]=1 (全1)

mode=0: acc[0-7] = {84, 92, 100, 108, 116, 124, 132, 140}
mode=1: acc[0-7] = {92, 100, 108, 116, 124, 132, 140, 148}
```

**行为分析**:
- 不同mode产生不同的偏移输出
- mode=1 相比 mode=0 整体偏移 +8
- 适用于3x3卷积核的高效计算

### 2.9 _vsigmoid - 向量Sigmoid激活函数 ✅ 已验证

**签名**:
```c
int2xN_t _vsigmoid(int2xN_t inA);
short2xN_t _vsigmoid(short2xN_t inA);
```

**功能**: AI神经网络的Sigmoid激活函数，硬件加速实现。

**数据格式**:
- 输入: **Q4.12** 定点数 (范围 [-8, 8))
  - 1.0 = 4096, -1.0 = -4096
- 输出: **Q1.15** 定点数 (范围 [0, 1))
  - 0.5 = 16384, 1.0 = 32768

**测试结果** (2026-01-28 验证):
```
sigmoid(x) = 1 / (1 + e^(-x))

输入 (Q4.12)     输出 (Q1.15)      实际值
-------------------------------------------
x = 0    (0)     → 16384           ≈ 0.500 ✅
x = 1    (4096)  → 23959           ≈ 0.731 ✅
x = -1   (-4096) → 8808            ≈ 0.269 ✅
x = 2    (8192)  → 28865           ≈ 0.881 ✅
x = -2   (-8192) → 3902            ≈ 0.119 ✅
x = 4    (16384) → 32179           ≈ 0.982 ✅
x = -4   (-16384)→ 588             ≈ 0.018 ✅
x ≈ 8    (32767) → 32756           ≈ 0.9996 ✅
```

**精度验证**: 与标准 sigmoid 函数高度吻合。

### 2.10 _vtanh - 向量双曲正切激活函数 ✅ 已验证

**签名**:
```c
int2xN_t _vtanh(int2xN_t inA);
short2xN_t _vtanh(short2xN_t inA);
```

**功能**: AI神经网络的Tanh激活函数。

**数据格式**:
- 输入: **Q4.12** 定点数 (范围 [-8, 8))
- 输出: **Q1.15** 定点数 (范围 [-1, 1))

**测试结果** (2026-01-28 验证):
```
tanh(x) = (e^x - e^(-x)) / (e^x + e^(-x))

输入 (Q4.12)     输出 (Q1.15)      实际值
-------------------------------------------
x = 0    (0)     → 4               ≈ 0.000 ✅
x = 1    (4096)  → 24982           ≈ 0.762 ✅
x = -1   (-4096) → -24982          ≈ -0.762 ✅
x = 2    (8192)  → 31595           ≈ 0.964 ✅
x = -2   (-8192) → -31595          ≈ -0.964 ✅
x = 4    (16384) → 32747           ≈ 0.999 ✅
x = -4   (-16384)→ -32747          ≈ -0.999 ✅
x = 0.5  (2048)  → 15174           ≈ 0.463 ✅
```

**对称性验证**: tanh(1) + tanh(-1) = 0 ✅

### 2.11 _vintrasumi - 向量内求和 ✅ 已验证

**签名**:
```c
int _vintrasumi(int2xN_t inA);           // 返回 int
short _vintrasums(int2xN_t inA);         // 返回 short (截断)
unsigned int _vintrasumui(uint2xN_t inA); // 无符号版本
```

**功能**: 将向量内所有元素求和，输出标量结果。用于神经网络池化层、特征统计等。

**测试结果** (2026-01-28 验证):
```
输入: [1, 2, 3, 4, 5, 6, 7, 8] (int2xN_t = 8×32bit)

_vintrasumi 输出: 36 ✅ (1+2+3+4+5+6+7+8 = 36)
_vintrasums 输出: 36 ✅

测试2: 全部元素=100
_vintrasumi 输出: 800 ✅ (100×8 = 800)
```

**应用场景**:
- Global Average Pooling
- 向量点积后的水平求和
- 特征统计（均值计算）

### 2.12 _vlut - 向量查找表 ✅ 已验证

**签名**:
```c
int2xN_t _vlut(int2xN_t inA, uint2xN_t inB, int2xN_t inoutC);
// 多种类型重载: ushort4xN_t, uchar4xN_t 等
```

**功能**: 向量查找表操作，核心运算 `Z[i] = A[B[i]]`。

**应用场景**:
- Activation LUT (查表实现激活函数)
- 颜色空间转换 (Color LUT)
- 量化表查找

**测试结果** (2026-01-28 验证):
```
Table:   [0, 10, 20, 30, 40, 50, 60, 70]  (table[i] = i×10)
Indices: [0,  1,  2,  3,  7,  5,  4,  6]

Expected: [0, 10, 20, 30, 70, 50, 40, 60]
Result:   [0, 10, 20, 30, 70, 50, 40, 60] ✅
```

**完全匹配**: 查找表功能正确实现。

### 2.13 _vmin / _vmin4 - 向量最小值 ✅ 已验证

**签名**:
```c
// 2-way minimum
short4xN_t _vmin(short4xN_t A, short4xN_t B);
int2xN_t _vmin(int2xN_t A, int2xN_t B);
char8xN_t _vmin(char8xN_t A, char8xN_t B);

// 3-way minimum
short4xN_t _vmin(short4xN_t A, short4xN_t B, short4xN_t C);

// 4-way minimum with mask
short4xN_t _vmin4(short4xN_t A, short4xN_t B, short4xN_t C, short4xN_t D, unsigned char mask);
```

**⚠️ 注意**: 不支持 `int4xN_t` 类型！仅支持 short4xN_t, int2xN_t, char8xN_t 及其无符号版本。

**测试结果** (2026-01-28 验证):
```
A[0]=100, B[0]=50, C[0]=80, D[0]=60

_vmin(A, B):
  Result: [50, 52, 54, 56] ✅ (正确取最小值)

_vmin(A, B, C):
  Result[0]: 50 ✅ = min(100, 50, 80)

_vmin4(A, B, C, D, 0xF):  // 全部4个向量参与
  Result[0]: 50 ✅ = min(100, 50, 80, 60)

_vmin4(A, B, C, D, 0x5):  // mask=0b0101, 只有A和C参与
  Result[0]: 80 ✅ = min(100, 80)
```

**mask位定义** (与 _vmax4 相同):
- bit 0: 向量A参与
- bit 1: 向量B参与
- bit 2: 向量C参与
- bit 3: 向量D参与

---

## 3. 性能测量结果

### 3.1 计时方法

**CSL Timer API 无法工作**，需使用 WATCHDOG 计数器：

```c
WATCHDOG_set_threshold(1, 0xFFFFFFFE);
WATCHDOG_enable();
uint32_t start = WATCHDOG_get_counter_value();

// ... 测量代码 ...

uint32_t end = WATCHDOG_get_counter_value();
WATCHDOG_disable();

// 重要: 实际周期数 = 16 × WDOGCNT
uint32_t cycles = (end - start) * 16;
```

### 3.2 向量 vs 标量性能 (256元素点积)

| 实现       | 周期数   | 每元素周期 | 说明           |
| ---------- | -------- | ---------- | -------------- |
| 标量       | 4384     | 17.12      | 循环+乘法+累加 |
| 向量       | 496      | 1.93       | 使用 _vmac     |
| **加速比** | **8.8x** | -          | 接近理论16x    |

### 3.3 内存访问性能

| 操作          | 周期数 (256次) | 每次周期 | 说明           |
| ------------- | -------------- | -------- | -------------- |
| 顺序读 (SRAM) | 3600           | 14.06    | 外部SRAM延迟   |
| 顺序写 (SRAM) | 544            | 2.12     | 写入缓冲       |
| Stride-4读    | 912/64         | 14.25    | 跨步访问同延迟 |
| 向量加载      | 16/4           | 4.00     | 32 bytes/load  |

**关键发现**:
- 外部SRAM读延迟约 14 周期
- 写入比读取快 7x (写缓冲)
- 向量加载非常高效: 4 cycles/32bytes = **3.07 GB/s @ 384MHz**

### 3.4 基本操作性能

| 操作         | 周期/元素 | 说明         |
| ------------ | --------- | ------------ |
| memfill      | 2.12      | 标量写入     |
| dot_product  | 17.25     | 标量MAC      |
| vector _vmac | ~1.93     | 16-wide SIMD |

---

## 4. 开发建议

### 4.1 向量化最佳实践

1. **优先使用向量指令** - 8.8x 加速显著
2. **注意 _vmac 签名** - 第2参数必须是 short4xN_t
3. **_vmac 是逐元素操作** - 点积需要后续水平累加
4. **数据对齐** - 32字节对齐获得最佳性能

### 4.2 内存访问优化

1. **减少外部SRAM读取** - 14周期/读 是瓶颈
2. **利用写缓冲** - 写入比读取快7倍
3. **使用向量加载** - 4周期/32字节非常高效
4. **数据预取** - 隐藏内存延迟

### 4.3 CSL 使用注意

1. **Timer API 不工作** - 使用 WATCHDOG 计时
2. **支持的CSL模块**:
   - CSL_TIMERS_SUPPORTED ✅ (但不工作)
   - CSL_ICU_SUPPORTED ✅
   - CSL_QMAN_SUPPORTED ✅ (sync point 有问题)
   - CSL_PROFILER_SUPPORTED ❌

---

## 5. DMA 子系统验证 (2026-01-28)

### 5.1 DDMA (Data DMA) ✅ 已验证

直接 API 调用，稳定可靠。

```c
DMSS_execute_ddma_task(internal, external, config, size);
while (DMSS_is_ddma_busy()) { }
```

配置宏:
- `DDMA_CONFIG_LINEAR_UPLOAD` - 内部→外部
- `DDMA_CONFIG_LINEAR_DOWNLOAD` - 外部→内部
- `DDMA_CONFIG_2D_UPLOAD/DOWNLOAD(src_stride, dst_stride, count)` - 2D传输

1D/2D 传输均测试通过。

### 5.2 PDMA (Program DMA) ✅ 已验证

用于加载代码到 PTCM。

```c
mss_load_internal_program(ptcm_addr, src_addr, size);
while (PMSS_is_pdma_busy()) { }
```

性能 (@ 400 MHz):

| 大小   | 吞吐量    |
| ------ | --------- |
| 32 B   | 32 MB/s   |
| 256 B  | 1280 MB/s |
| 2048 B | 1706 MB/s |

**坑**: PTCM 外部地址 (0x44Axxxxx) 只能写不能读！

### 5.3 AXI DMA ✅ 已验证

8 通道寄存器操作 DMA，通道号 **1~8** (不是 0~7)。

```c
dsp_hw_dma_memcpy(channel, src, dst, size);
dsp_hw_dma_wait(channel);
```

性能 (4KB 传输 @ 400 MHz):

| 路径       | 吞吐量    |
| ---------- | --------- |
| SRAM↔SRAM  | 1219 MB/s |
| PSRAM→SRAM | 108 MB/s  |
| SRAM→PSRAM | 122 MB/s  |

### 5.4 QMAN ⚠️ 暂不可用

`QMAN_sync_point()` 会阻塞死锁，原因待查。

临时方案: 用 DDMA 直接 API + 轮询 `DMSS_is_ddma_busy()`。

---

## 6. 已验证指令汇总

| 指令          | 状态     | 类型       | 备注                                 |
| ------------- | -------- | ---------- | ------------------------------------ |
| `_vmac`       | ✅ 已验证 | 基础MAC    | 逐元素MAC，第2参数必须是short4xN_t   |
| `_vmax`       | ✅ 已验证 | 基础比较   | 逐元素最大值                         |
| `_vmin`       | ✅ 已验证 | 基础比较   | 2/3路逐元素最小值                    |
| `_vmin4`      | ✅ 已验证 | 基础比较   | 4路最小值，支持mask控制              |
| `_vshiftr`    | ✅ 已验证 | 基础算术   | 算术右移，保留符号                   |
| `_vmac5`      | ✅ 已验证 | 高级MAC    | 4向量×packed标量累加，acc[0]=10      |
| `_vmac9`      | ✅ 已验证 | 高级MAC    | 8点MAC，用于3x3卷积优化              |
| `_vconv`      | ✅ 已验证 | 卷积       | inF=1激活，输出{0,3,6,9}             |
| `_vcorr3x3`   | ✅ 已验证 | 卷积       | 3x3滑动窗口，acc[0]=45，滑动行为正确 |
| `_vsigmoid`   | ✅ 已验证 | AI激活函数 | Q4.12→Q1.15，sigmoid(0)=0.5          |
| `_vtanh`      | ✅ 已验证 | AI激活函数 | Q4.12→Q1.15，对称性验证通过          |
| `_vintrasumi` | ✅ 已验证 | 归约       | 向量内求和→标量，1+...+8=36          |
| `_vlut`       | ✅ 已验证 | 查找表     | Z[i]=A[B[i]]，查表正确               |
| `_vmax4`      | ⚠️ 异常   | 基础比较   | mode=0输出-128，参数待研究           |

### 按功能分类

**基础运算 (5个)**:
- `_vmac` - 逐元素乘累加
- `_vmax` / `_vmin` - 逐元素最大/最小
- `_vmin4` - 4路最小值 (带mask)
- `_vshiftr` - 算术右移

**卷积/MAC扩展 (4个)**:
- `_vmac5` - 5点MAC (4向量×4标量)
- `_vmac9` - 8点MAC (用于3x3卷积)
- `_vconv` - 向量卷积 (多模式)
- `_vcorr3x3` - 3x3相关运算

**AI/神经网络 (3个)**:
- `_vsigmoid` - Sigmoid激活
- `_vtanh` - Tanh激活
- `_vintrasumi` - 向量内求和

**数据操作 (1个)**:
- `_vlut` - 向量查找表

## 7. 待测试项目

- [ ] `_vmax4` - 研究mode参数含义 (mode≠0?)
- [ ] `_vpack` / `_vunpack` - 数据打包解包
- [ ] `_vadd` / `_vsub` - 向量加减
- [ ] `_vmul` - 向量乘法
- [ ] `_vabs` - 向量绝对值
- [ ] `_vclip` - 向量裁剪
- [ ] `_vintramax` / `_vintramin` - 向量内最大/最小值
- [ ] ICU 中断控制
- [ ] QMAN 任务调度 (排查 sync point)

---

*文档版本: 5.0*
*最后更新: 2026-01-28*
*已验证指令数: 13个 (12个正常, 1个异常)*
