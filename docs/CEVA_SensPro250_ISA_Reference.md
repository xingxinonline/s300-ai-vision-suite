# CEVA SensPro250 指令集参考手册

> 基于官方文档整理，用于DSP固件开发参考
> **2026-01-28 更新**: 修正向量宽度为 256-bit (非 512-bit)

## 1. 架构概述

### 1.1 向量处理单元

CEVA SensPro250 是一款专为AI/ML和信号处理优化的向量DSP：

- **产品型号**: SP250 (N=4)
- **向量寄存器宽度**: **256位** (单寄存器，经硬件验证)
- **Dual Vector 宽度**: 512位 (跨2个寄存器)
- **向量处理单元**: 1× VCU0 + 1× LVCU (最多2条向量指令/周期)
- **SIMD 宽度** (Full Vector): 8× int32 或 16× int16 或 32× int8
- **支持数据类型**:
  - `char` (8-bit): 16个元素/半寄存器 (4xN) 或 32个/全寄存器 (8xN)
  - `short` (16-bit): 8个元素/半寄存器 (2xN) 或 16个/全寄存器 (4xN)
  - `int` (32-bit): 8个元素/全寄存器 (2xN) 或 16个/双寄存器 (4xN)
  - ❌ 浮点已禁用 (本硬件配置)

### 1.2 向量数据类型 (Vec-C) - 经硬件验证

**⚠️ 重要修正**: 类型命名中的数字是倍数标识，不是元素数！

#### Half Vector (半寄存器, 128 bits)
| 类型          | sizeof() | 元素数 | 说明 |
| ------------- | -------- | ------ | ---- |
| `char4xN_t`   | 16 bytes | 16     | 16×8-bit |
| `short2xN_t`  | 16 bytes | 8      | 8×16-bit |

#### Full Vector (单寄存器, 256 bits) ← 用于产品检测
| 类型          | sizeof() | 元素数 | 说明 |
| ------------- | -------- | ------ | ---- |
| `char8xN_t`   | 32 bytes | 32     | 32×8-bit |
| `short4xN_t`  | 32 bytes | 16     | 16×16-bit |
| **`int2xN_t`**| **32 bytes** | **8** | **8×32-bit** |

#### Dual Vector (双寄存器, 512 bits) ← 跨2个寄存器！
| 类型          | sizeof() | 元素数 | 说明 |
| ------------- | -------- | ------ | ---- |
| `short8xN_t`  | 64 bytes | 32     | 32×16-bit |
| `int4xN_t`    | 64 bytes | 16     | 16×32-bit |

> **注意**: `int4xN_t` 是 **Dual Vector**，需要两个寄存器。使用 `int2xN_t` 判断产品型号更准确。

---

## 2. 向量乘累加指令 (VMAC系列)

### 2.1 VMAC - 基本向量乘累加

**功能**: 对两个向量进行逐元素乘法并累加到累加器

**操作**:
```
res[k] += A[k] * B[k]   // 对所有k
```

**Vec-C 内建函数**:
```c
// 经硬件验证的签名 (3参数版本):
int4xN_t _vmac(char4xN_t a, short4xN_t b, int4xN_t acc);   // char * short
int4xN_t _vmac(uchar4xN_t a, short4xN_t b, int4xN_t acc);  // uchar * short
int4xN_t _vmac(short4xN_t a, short4xN_t b, int4xN_t acc);  // short * short
```

**⚠️ 实测结论**: 
- 第二个参数必须是 `short4xN_t`，不能用 `char4xN_t`
- 这是逐元素操作: `acc[k] += a[k] * b[k]`，**不是**点积！
- 没有跨通道累加，每个通道独立计算
- 16 个输入元素产生 16 个独立的累加结果

**验证示例**:
```c
char4xN_t input = {0};   // 16 x int8
short4xN_t weight = {0}; // 16 x int16
int4xN_t acc = 0;        // 16 x int32

input[0] = 3;  weight[0] = 5;   // 只设置第0通道
acc = _vmac(input, weight, acc);
// 结果: acc[0] = 15, acc[1..15] = 0  (逐元素，非规约)
```

---

### 2.2 VMAC5 - 5点乘累加 ✅ 已验证

**功能**: 4个向量分别乘以打包标量，累加到32位累加器

**操作** (经硬件验证):
```
acc[k] += a[k]*e0 + b[k]*e1 + c[k]*e2 + d[k]*e3
```

其中 e0-e3 是从 `packed_input` 中提取的4个8位值

**Vec-C 内建函数** (经编译器头文件验证):
```c
// 正确签名 - short4xN_t 输入, int4xN_t 累加器:
int4xN_t _vmac5(short4xN_t a, short4xN_t b, short4xN_t c, short4xN_t d,
                unsigned int packed_input, int4xN_t acc);

// 其他变体:
uint4xN_t _vmac5(ushort4xN_t a, ushort4xN_t b, ushort4xN_t c, ushort4xN_t d,
                 unsigned int packed_input, uint4xN_t acc);
```

**⚠️ 重要修正**: 原文档标注的 `char4xN_t` 输入是错误的！
- 输入必须是 `short4xN_t` (16位)
- 累加器是 `int4xN_t` (32位)，不是 `short4xN_t`

**参数说明**:
- `a, b, c, d`: 4个向量 (short4xN_t, 16个16位元素)
- `packed_input`: 打包的4个8位值 `{e3, e2, e1, e0}`
- `acc`: 32位累加器向量 (int4xN_t)

**验证示例**:
```c
a[0]=1, b[0]=2, c[0]=3, d[0]=4
packed_input = 0x01010101  // e0=e1=e2=e3=1

acc = _vmac5(a, b, c, d, packed_input, acc);
// 结果: acc[0] = 1*1 + 2*1 + 3*1 + 4*1 = 10 ✓
```

**使用场景**: 1x1卷积，每次处理4个输入通道对16个输出通道的贡献

---

### 2.3 VMAC9 - 8点乘累加 ✅ 已验证

**功能**: 8点乘累加，用于3x3卷积优化

**Vec-C 内建函数** (经编译器头文件验证):
```c
// 简化版 (单累加器):
int4xN_t _vmac9(char8xN_t inA, char8xN_t inB, char8xN_t inC, char8xN_t inD,
                ushort4xN_t inE, unsigned char inF, int4xN_t accG);

// 完整版 (双累加器):
void _vmac9(char8xN_t inA, char8xN_t inB, char8xN_t inC, char8xN_t inD,
            ushort4xN_t inE, unsigned char inF, unsigned char inG,
            int4xN_t& inoutH, short4xN_t& inoutI);
```

**参数说明**:
- `inA, inB, inC, inD`: 4个输入向量 (char8xN_t = 32×8bit)
- `inE`: 系数向量 (ushort4xN_t = 16×16bit)
- `inF`: 模式控制 (必须是立即数 0-3)
- `accG`: 32位累加器 (int4xN_t = 16×32bit)

**验证示例** (2026-01-28):
```c
A[i] = i+1, B[i] = i+2, C[i] = i+3, D[i] = i+4
E[i] = 1 (全1系数)

mode=0: acc[0-7] = {84, 92, 100, 108, 116, 124, 132, 140}
mode=1: acc[0-7] = {92, 100, 108, 116, 124, 132, 140, 148}
// mode=1 相比 mode=0 整体偏移 +8
```

**使用场景**: 3x3卷积核的高效计算

---

### 2.4 VCORR3X3 - 3x3相关运算 ⭐

**功能**: 专为3x3滑动窗口卷积设计的指令

**操作**:
```
res[k] += A[k]*D[0] + B[k]*D[1] + C[k]*D[2] + 
          A[k+1]*D[3] + B[k+1]*D[4] + C[k+1]*D[5] + 
          A[k+2]*D[6] + B[k+2]*D[7] + C[k+2]*D[8]
```

**参数**:
- `A, B, C`: 3行输入数据向量
- `D`: 9个3x3卷积核系数
- `W`: 累加器 (short向量)
- `O`: 输出 (char向量)

**Shift选项**:
| 选项     | A偏移 | B偏移 | C偏移 | 用途     |
| -------- | ----- | ----- | ----- | -------- |
| shift0   | 0     | 0     | 0     | 默认     |
| shift3   | 3     | 3     | 3     | 列偏移3  |
| shift6   | 6     | 6     | 6     | 列偏移6  |
| shift036 | 0     | 3     | 6     | 斜向滑动 |
| shift003 | 0     | 0     | 3     | 特殊模式 |
| shift366 | 3     | 6     | 6     | 特殊模式 |

**SP250限制**: 只有前14个元素被计算，其余保持不变

**使用场景**: 
- 2D空间卷积（边缘检测、模糊等）
- 需要滑动窗口的3x3卷积操作

---

## 3. 向量卷积指令 (VCONV) ✅ 已验证

### 3.1 VCONV - 向量卷积

**功能**: 专用卷积运算，将4个char向量规约到32元素int向量

**Vec-C 内建函数** (经编译器头文件验证):
```c
// 正确签名:
int32 _vconv(char8xN_t a, char8xN_t b, char8xN_t c, char8xN_t d,
             unsigned char inE, unsigned short inF, int32 acc);
```

**⚠️ 重要发现**:
- `int32` 是**向量类型**: 32个int元素 (1024位)，不是标量！
- `inE` 必须是**立即数常量** (0-3)，不能用变量
- `inF` 也必须是立即数常量
- `char8xN_t` = 32个char元素 (256位)

**参数说明**:
- `a, b, c, d`: 4个char8xN_t向量 (32×8位 = 256位每个)
- `inE`: 控制字节 (立即数 0-3)
- `inF`: 控制short (立即数)
- `acc`: int32向量累加器 (32×32位 = 1024位)

**验证示例**:
```c
char8xN_t a, b, c, d;
int32 acc = {0};

acc = _vconv(a, b, c, d, 0, 0, acc);  // inE, inF 必须是常量
// 结果: acc 是 32 个 int 元素的向量
```

**使用场景**: 专用图像卷积运算，需研究控制参数含义

---

## 4. 向量比较和选择指令

### 4.1 VMAX - 向量最大值 ✅ 已验证

**功能**: 逐元素取两个向量的最大值

**Vec-C 内建函数**:
```c
char8xN_t _vmax(char8xN_t a, char8xN_t b);
short4xN_t _vmax(short4xN_t a, short4xN_t b);
int2xN_t _vmax(int2xN_t a, int2xN_t b);
```

**操作**: `out[k] = max(a[k], b[k])`

### 4.2 VMIN - 向量最小值 ✅ 已验证

**功能**: 逐元素取向量的最小值

**Vec-C 内建函数**:
```c
// 2路最小值
short4xN_t _vmin(short4xN_t a, short4xN_t b);
int2xN_t _vmin(int2xN_t a, int2xN_t b);
char8xN_t _vmin(char8xN_t a, char8xN_t b);

// 3路最小值
short4xN_t _vmin(short4xN_t a, short4xN_t b, short4xN_t c);

// 4路最小值 (带mask)
short4xN_t _vmin4(short4xN_t a, short4xN_t b, short4xN_t c, short4xN_t d, unsigned char mask);
```

**⚠️ 注意**: `_vmin` 和 `_vmin4` **不支持** `int4xN_t` 类型！

**mask位定义** (4路版本):
- bit 0: 向量A参与
- bit 1: 向量B参与
- bit 2: 向量C参与
- bit 3: 向量D参与

**验证示例**:
```c
A[0]=100, B[0]=50, C[0]=80, D[0]=60

_vmin(A, B)           → 50  = min(100, 50)
_vmin(A, B, C)        → 50  = min(100, 50, 80)
_vmin4(A,B,C,D, 0xF)  → 50  = min(100, 50, 80, 60)
_vmin4(A,B,C,D, 0x5)  → 80  = min(100, 80)  // 只有A和C参与
```

### 4.3 VMAX4 - 4元素取最大

**功能**: 在向量的每4个相邻元素中取最大值

**Vec-C 内建函数**:
```c
char4xN_t _vmax4(char4xN_t a);
char8xN_t _vmax4(char8xN_t a, char8xN_t b, char8xN_t c, char8xN_t d, unsigned char mode);
```

**使用场景**: Max Pooling 2x2 的一部分

⚠️ **警告**: `mode=0` 时输出异常 (-128)，需进一步研究

---

## 5. AI/神经网络激活函数 ✅ 已验证

### 5.1 VSIGMOID - 向量Sigmoid激活

**功能**: 硬件加速的Sigmoid激活函数

**Vec-C 内建函数**:
```c
int2xN_t _vsigmoid(int2xN_t inA);
short2xN_t _vsigmoid(short2xN_t inA);
```

**数据格式**:
- 输入: **Q4.12** 定点数 (范围 [-8, 8), 1.0 = 4096)
- 输出: **Q1.15** 定点数 (范围 [0, 1), 0.5 = 16384)

**验证示例**:
```c
sigmoid(0)   = 16384 (0.500)
sigmoid(1)   = 23959 (0.731)
sigmoid(-1)  = 8808  (0.269)
sigmoid(4)   = 32179 (0.982)
```

### 5.2 VTANH - 向量Tanh激活

**功能**: 硬件加速的双曲正切激活函数

**Vec-C 内建函数**:
```c
int2xN_t _vtanh(int2xN_t inA);
short2xN_t _vtanh(short2xN_t inA);
```

**数据格式**: 同 `_vsigmoid`

**验证示例**:
```c
tanh(0)   = 4      (≈0)
tanh(1)   = 24982  (0.762)
tanh(-1)  = -24982 (-0.762)  // 对称性验证
```

### 5.3 VINTRASUM - 向量内求和

**功能**: 将向量所有元素求和，输出标量

**Vec-C 内建函数**:
```c
int _vintrasumi(int2xN_t inA);           // 返回 int
short _vintrasums(int2xN_t inA);         // 返回 short
unsigned int _vintrasumui(uint2xN_t inA); // 无符号版本
```

**验证示例**:
```c
input = [1, 2, 3, 4, 5, 6, 7, 8]  // int2xN_t
_vintrasumi(input) = 36  // 1+2+3+4+5+6+7+8 = 36
```

**应用场景**: Global Average Pooling, 点积后水平求和

### 5.4 VLUT - 向量查找表

**功能**: 向量化查找表操作

**Vec-C 内建函数**:
```c
int2xN_t _vlut(int2xN_t table, uint2xN_t indices, int2xN_t inoutC);
// 多种类型重载
```

**操作**: `Z[i] = Table[Indices[i]]`

**验证示例**:
```c
Table   = [0, 10, 20, 30, 40, 50, 60, 70]
Indices = [0, 1, 2, 3, 7, 5, 4, 6]
Result  = [0, 10, 20, 30, 70, 50, 40, 60]  // 正确!
```

**应用场景**: 激活函数查表、颜色LUT、量化表

---

## 5. 向量类型转换指令

### 5.1 类型转换

```c
// int8 -> short (扩展低16位)
short4xN_t _vunpack_lo(char4xN_t a);

// int8 -> short (扩展高16位)  
short4xN_t _vunpack_hi(char4xN_t a);

// 两个short向量打包为一个char向量
char4xN_t _vpack(short4xN_t lo, short4xN_t hi);

// 有符号->无符号转换
uchar4xN_t _vcastuc4n(char4xN_t a);

// 无符号->有符号转换
char4xN_t _vcastc4n(uchar4xN_t a);
```

### 5.2 移位指令

```c
// 算术右移
int4xN_t _vshiftr(int4xN_t a, int shift);
short4xN_t _vshiftr(short4xN_t a, int shift);

// 逻辑左移
int4xN_t _vshiftl(int4xN_t a, int shift);
```

---

## 6. 向量加载/存储指令

### 6.1 对齐加载

```c
// 对齐加载 (地址必须32字节对齐)
char4xN_t vec = *(char4xN_t*)aligned_ptr;
```

### 6.2 非对齐加载

```c
// 使用 _vld 进行非对齐加载
char4xN_t _vld(void* ptr);
```

### 6.3 存储

```c
// 对齐存储
*(char4xN_t*)aligned_ptr = vec;

// 向量存储
_vst(ptr, vec);
```

---

## 7. 深度卷积优化策略

### 7.1 当前实现分析

对于 `conv_dp` (3x3 深度卷积):
- 每个通道有独立的3x3核
- 16个通道并行处理
- 使用9次 `_vmac` 完成一个输出位置

### 7.2 优化方案对比

| 方案        | 描述         | 适用性             |
| ----------- | ------------ | ------------------ |
| 9x _vmac    | 当前实现     | ✓ 正确，可优化     |
| vmac9       | 8点MAC       | ✗ 设计用于FC层     |
| vcorr3x3    | 3x3滑动窗口  | ✗ 设计用于空间卷积 |
| 输入预加载  | 减少内存访问 | ✓ 已实现           |
| 3累加器并行 | 行级并行     | ✓ 已实现           |

### 7.3 结论

对于**深度可分离卷积**（每通道独立核），当前使用 `_vmac` 的实现是最合适的。
`vcorr3x3` 和 `vmac9` 设计用于不同的计算模式。

---

## 8. 已验证指令汇总

| 指令          | 类型    | 状态     | 验证日期   |
| ------------- | ------- | -------- | ---------- |
| `_vmac`       | 基础MAC | ✅ 已验证 | 2026-01-28 |
| `_vmac5`      | 高级MAC | ✅ 已验证 | 2026-01-28 |
| `_vmac9`      | 高级MAC | ✅ 已验证 | 2026-01-28 |
| `_vmax`       | 比较    | ✅ 已验证 | 2026-01-28 |
| `_vmin`       | 比较    | ✅ 已验证 | 2026-01-28 |
| `_vmin4`      | 比较    | ✅ 已验证 | 2026-01-28 |
| `_vshiftr`    | 移位    | ✅ 已验证 | 2026-01-28 |
| `_vconv`      | 卷积    | ✅ 已验证 | 2026-01-28 |
| `_vcorr3x3`   | 卷积    | ✅ 已验证 | 2026-01-28 |
| `_vsigmoid`   | AI激活  | ✅ 已验证 | 2026-01-28 |
| `_vtanh`      | AI激活  | ✅ 已验证 | 2026-01-28 |
| `_vintrasumi` | 归约    | ✅ 已验证 | 2026-01-28 |
| `_vlut`       | 查找表  | ✅ 已验证 | 2026-01-28 |
| `_vmax4`      | 比较    | ⚠️ 异常   | 2026-01-28 |

**总计**: 14个指令测试，13个正常，1个异常

---

## 附录A: 汇编语法约定

| 符号      | 含义                   |
| --------- | ---------------------- |
| `.c8n`    | char向量 (8-bit x N)   |
| `.uc8n`   | unsigned char向量      |
| `.s4n`    | short向量 (16-bit x N) |
| `.us4n`   | unsigned short向量     |
| `.i2n`    | int向量 (32-bit x N)   |
| `.ui2n`   | unsigned int向量       |
| `vA~`     | vA的下一个连续寄存器   |
| `#uimmF2` | 2位无符号立即数        |

## 附录B: Q格式定点数说明

| 格式  | 范围              | 1.0 表示 | 用途                  |
| ----- | ----------------- | -------- | --------------------- |
| Q4.12 | [-8, 8)           | 4096     | _vsigmoid/_vtanh 输入 |
| Q1.15 | [-1, 1) 或 [0, 1) | 32768    | _vsigmoid/_vtanh 输出 |

转换公式:
```c
// 浮点 → Q4.12
int q412 = (int)(float_val * 4096.0f);

// Q1.15 → 浮点
float result = (float)q115 / 32768.0f;
```

---

*文档版本: 2.0*  
*最后更新: 2026-01-28*
*已验证指令: 13个*
