# 开发笔记

零散记录一些调试过程中发现的问题和解决方法。

---

## 2026-01-28 (续) - 向量类型分类大修正

### 关键发现：int4xN_t 是 Dual Vector，不是 Full Vector！

之前一直以为 SP250 的向量宽度是 512 bits（因为 int4xN_t 有 16 个元素）。
经过仔细分析 CEVA 架构手册和编译器头文件后发现：

| 类型     | 实际分类        | 寄存器占用             |
| -------- | --------------- | ---------------------- |
| int2xN_t | Full Vector     | **1个** 256-bit 寄存器 |
| int4xN_t | **Dual Vector** | **2个** 256-bit 寄存器 |

**证据**:
1. `senspro.tdf` 配置: `<attributes name="Vector Width" value="256"/>`
2. 编译器 target: `--target=senspro250-unknown-unknown-elf`
3. vec-c.h 选择: `#elif defined(__senspro250__) #include "N4_SENSPROVecCV1.h"`

**N4 头文件中的类型定义**:
```c
typedef int int2xN_t __attribute__((ext_vector_type(8)));   // Full: 8个 = 256 bits
typedef int int4xN_t __attribute__((ext_vector_type(16)));  // Dual: 16个 = 512 bits
```

### 正确的产品检测方法

用 `int2xN_t`（Full Vector）而不是 `int4xN_t`（Dual Vector）来判断产品：

```c
int count = sizeof(int2xN_t) / sizeof(int);
// SP50=2, SP100=4, SP250=8, SP500/1000=16
```

### 测试验证结果

```
int2xN_t (Full Vector) has 8 int32 elements
Vector register width: 256 bits
>>> Detected: SP250 <<<
(N=4, Vector Width=256 bits)

Verification:
  int4xN_t (Dual) = 16 elements = 2 x int2xN_t (Full)
  Dual Vector width: 512 bits = 2 x 256 bits
  [PASS] Dual = 2 x Full confirmed
```

### 性能影响

之前的性能估算需要修正：

| 参数            | 之前理解（错误） | 修正后（正确） |
| --------------- | ---------------- | -------------- |
| 向量宽度        | 512 bits         | **256 bits**   |
| 16x16 MAC/cycle | 128              | **64**         |
| 理论峰值 (int8) | 102 GMAC/s       | **51 GMAC/s**  |

### VCU 配置

根据手册和 TDF 配置：
- **VCU0**: 1个（主向量单元，支持乘法、MAC、非线性）
- **VCU1**: 无（只有 SP1000 有2个 VCU）
- **LVCU**: 1个（轻量向量单元，加减、逻辑、移位）
- 每周期最多 **2条向量指令**

---

## 2026-01-28

### Timer API 不工作

CSL 的 Timer 接口调用后没反应，读出来的值不动。可能是寄存器映射或时钟使能的问题。

**解决**: 用 WATCHDOG 计时器替代。

```c
WATCHDOG_set_threshold(1, 0xFFFFFFFE);
WATCHDOG_enable();
uint32_t start = WATCHDOG_get_counter_value();
// ... 被测代码 ...
uint32_t end = WATCHDOG_get_counter_value();
WATCHDOG_disable();

// 注意: WATCHDOG 计数器每 16 个 DSP 周期加 1
uint32_t cycles = (end - start) * 16;
```

### PSRAM 8-bit 访问失败

用 `char*` 读写 PSRAM (0x80000000) 会出错，数据不对。

**原因**: PSRAM 控制器不支持 8-bit burst，最小 16-bit。

**解决**: 用 `uint16_t*` 或 `uint32_t*` 访问。

### AXI DMA 通道号

一开始用通道 0，DMA 不动。

**原因**: 通道号是 1~8，不是 0~7。

**解决**: `dsp_hw_dma_memcpy(1, ...)` 而不是 `dsp_hw_dma_memcpy(0, ...)`。

### PTCM 外部地址只能写

想用 PDMA 把代码搬到 PTCM，然后从外部地址读回来验证。结果读出来全是垃圾。

**原因**: PTCM 外部地址 0x44Axxxxx 是只写的，AXI 总线读取返回的是无意义数据。

**解决**: 
1. 不做数据验证，只检查传输有没有超时
2. 或者直接跳转执行来验证功能

### QMAN sync point 死锁

调用 `QMAN_sync_point()` 后程序卡死。

**原因**: 不确定，可能是队列配置或任务状态的问题。

**临时方案**: 不用 QMAN，直接调 DDMA API + 轮询。

```c
// 别用这个
// QMAN_sync_point();

// 用这个
DMSS_execute_ddma_task(...);
while (DMSS_is_ddma_busy()) { }
```

### _vmac 签名

官方文档写的是 `_vmac(char, char, int)`，实际上第二个参数必须是 `short4xN_t`。

正确签名:
```c
int4xN_t _vmac(char4xN_t a, short4xN_t b, int4xN_t acc);
```

而且这是逐元素操作，不是点积。`acc[k] += a[k] * b[k]`，没有跨通道累加。

### 向量类型元素个数

`char4xN_t` 不是 4 个元素，是 16 个。命名里的 "4" 是历史遗留，不用管。

实际:
- `char4xN_t`: 16 个 8-bit = 128 bit
- `short4xN_t`: 16 个 16-bit = 256 bit  
- `int4xN_t`: 16 个 32-bit = 512 bit

所以向量寄存器是 512-bit 的。

### AI激活函数定点格式

`_vsigmoid` 和 `_vtanh` 使用特殊的定点格式：

- 输入: **Q4.12** (4位整数 + 12位小数)
  - 范围: [-8.0, 8.0)
  - 1.0 = 4096, -1.0 = -4096

- 输出: **Q1.15** (1位整数 + 15位小数)
  - 范围: [-1.0, 1.0) 或 [0, 1.0)
  - 0.5 = 16384, 1.0 = 32768

转换公式:
```c
// 浮点 → Q4.12 (输入)
int q412 = (int)(float_val * 4096.0f);

// Q1.15 → 浮点 (输出)
float result = (float)q115 / 32768.0f;
```

### _vmin / _vmin4 不支持 int4xN_t

编译报错 `no matching function for call to '_vmin'`。

原因: `_vmin` 和 `_vmin4` 不支持 `int4xN_t` 类型。

支持的类型:
- `short4xN_t` / `ushort4xN_t`
- `char8xN_t` / `uchar8xN_t`
- `int2xN_t` / `uint2xN_t`

解决: 用 `short4xN_t` 代替 `int4xN_t`。

### _vlut 调用方式

`_vlut` 返回值需要赋值，不是 void 函数:

```c
// 正确
vec_out = _vlut(vec_table, vec_idx, vec_out);

// 错误 (结果丢失)
_vlut(vec_table, vec_idx, vec_out);
```

---

## 性能数字备忘

(@ 400 MHz)

| 项目              | 数值         |
| ----------------- | ------------ |
| 向量点积加速      | 5.7×         |
| DTCM 写延迟       | 2 cyc/word   |
| DTCM 读延迟       | 4 cyc/word   |
| SRAM 读延迟       | 14 cyc/word  |
| PSRAM 读延迟      | 112 cyc/word |
| AXI DMA SRAM↔SRAM | 1219 MB/s    |
| PDMA 大块传输     | 1706 MB/s    |
| PSRAM DMA 读      | 108 MB/s     |
| PSRAM DMA 写      | 122 MB/s     |

### 指令性能

| 指令          | 周期数 (估算) | 备注         |
| ------------- | ------------- | ------------ |
| `_vmac`       | ~1 cycle      | 16-wide SIMD |
| `_vsigmoid`   | ~1-2 cycles   | 硬件加速LUT  |
| `_vtanh`      | ~1-2 cycles   | 硬件加速LUT  |
| `_vintrasumi` | ~8 cycles     | 归约操作     |
| `_vlut`       | ~1 cycle      | 并行查表     |
| `_vmin4`      | ~1 cycle      | 4路比较      |

---

## 坑汇总

1. Timer 不工作 → 用 WATCHDOG
2. PSRAM 不支持 8-bit → 用 16/32-bit
3. PTCM 外部只写 → 别读
4. QMAN sync 会死 → 用 DDMA 直接 API
5. AXI DMA 通道 1-8 → 不是 0-7
6. `_vmac` 要 short → 不是 char
7. `_vmac` 是逐元素 → 不是点积
8. `_vmin` 不支持 int4xN_t → 用 short4xN_t
9. `_vsigmoid` 输入 Q4.12 → 不是普通整数
10. `DTCM_ALIGNED_32` 需要定义 → `__attribute__((aligned(32)))`

---

## 已验证指令统计

截至 2026-01-28:

| 类别         | 指令数 | 状态   |
| ------------ | ------ | ------ |
| 基础运算     | 5      | ✅ 正常 |
| 卷积/MAC扩展 | 4      | ✅ 正常 |
| AI激活函数   | 3      | ✅ 正常 |
| 数据操作     | 1      | ✅ 正常 |
| **总计**     | **13** | 12正常 |

异常: `_vmax4` mode=0 输出 -128

---

*持续更新*
*最后更新: 2026-01-28*
