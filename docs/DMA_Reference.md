# DMA 子系统参考手册

> 基于 SensPro250 实际测试整理

## 概述

SensPro250 有多个 DMA 引擎，各有各的用法：

| DMA 类型    | 用途            | 接口    | 状态     |
| ----------- | --------------- | ------- | -------- |
| **DDMA**    | 数据传输 (主力) | CSL API | ✅ 稳定   |
| **PDMA**    | 程序加载到 PTCM | CSL API | ✅ 正常   |
| **AXI DMA** | 通用传输        | 寄存器  | ✅ 正常   |
| **QMAN**    | 任务队列调度    | CSL API | ⚠️ 不稳定 |

## 1. DDMA (Data DMA)

DDMA 是最常用的数据搬运接口，直接调用 CSL API 就行。

### 核心 API

```c
#include "ceva_dmss.h"

// 配置并启动 DDMA 传输
DMSS_execute_ddma_task(
    uint32_t internal_addr,  // DSP 内部地址 (DTCM)
    uint32_t external_addr,  // 外部 AXI 地址
    uint32_t config,         // 传输配置
    uint32_t size            // 字节数 (1D) 或打包参数 (2D)
);

// 等待完成
while (DMSS_is_ddma_busy()) { }
```

### 配置宏

**1D 线性传输:**
```c
DDMA_CONFIG_LINEAR_UPLOAD    // 内部 → 外部
DDMA_CONFIG_LINEAR_DOWNLOAD  // 外部 → 内部
DDMA_CONFIG_LINEAR_INTERNAL  // 内部 → 内部
```

**2D 块传输:**
```c
DDMA_CONFIG_2D_UPLOAD(src_stride, dst_stride, count)
DDMA_CONFIG_2D_DOWNLOAD(src_stride, dst_stride, count)
```

参数说明:
- `src_stride`: 源行间隔 (字节)
- `dst_stride`: 目标行间隔 (字节)
- `count`: 行数

### 使用示例

**1D 上传 (DTCM → SRAM):**
```c
#define DTCM_INTERNAL  0x00008000
#define SRAM_ADDR      0x44020000

DMSS_execute_ddma_task(
    DTCM_INTERNAL,
    SRAM_ADDR,
    DDMA_CONFIG_LINEAR_UPLOAD,
    256  // 256 bytes
);
while (DMSS_is_ddma_busy()) { }
```

**2D 下载 (PSRAM → DTCM):**
```c
// 从 640 宽图像中取 32×8 的块
#define SRC_STRIDE  640   // 源图像宽度
#define DST_STRIDE  32    // 目标行宽
#define HEIGHT      8     // 行数
#define WIDTH       32    // 每行字节数

uint32_t size_param = (HEIGHT << 16) | WIDTH;
uint32_t config = DDMA_CONFIG_2D_DOWNLOAD(SRC_STRIDE, DST_STRIDE, HEIGHT);

DMSS_execute_ddma_task(
    DTCM_INTERNAL,
    PSRAM_ADDR,
    config,
    size_param
);
while (DMSS_is_ddma_busy()) { }
```

### 性能数据

在 400 MHz 下测得:

| 操作      | 大小 | 周期数 | 吞吐量    |
| --------- | ---- | ------ | --------- |
| SRAM→DTCM | 256B | ~200   | ~512 MB/s |
| DTCM→SRAM | 256B | ~200   | ~512 MB/s |
| 2D 块传输 | 32×8 | ~300   | ~340 MB/s |

实际吞吐受内存带宽和总线争用影响。

---

## 2. PDMA (Program DMA)

PDMA 专门用来把代码加载到 PTCM。

### 核心 API

```c
#include "mss.h"
#include "ceva_pmss.h"

// 加载程序到 PTCM
mss_load_internal_program(
    uint32_t internal_addr,  // PTCM 内部地址
    uint32_t external_addr,  // 源地址 (SRAM/PSRAM)
    uint32_t size            // 字节数
);

// 等待完成
while (PMSS_is_pdma_busy()) { }

// 中断处理
if (mss_has_pdma_interrupt_pending()) {
    mss_clear_pdma_interrupt_pending();
}
```

### 注意事项

1. **单向传输**: 只能从外部加载到 PTCM，不能反过来
2. **PTCM 外部地址只写**: 0x44Axxxxx 无法读取，写入后只能通过执行来验证
3. **对齐要求**: 地址和大小都要 32 字节对齐
4. **最大传输**: `MSS_MAX_PDMA_TRANSFER_SIZE`

### 性能数据

| 大小  | 周期数 | 吞吐量     |
| ----- | ------ | ---------- |
| 32B   | ~400   | ~32 MB/s   |
| 256B  | ~80    | ~1280 MB/s |
| 2048B | ~480   | ~1706 MB/s |

小块传输启动开销明显，大块传输吞吐可达 1.7 GB/s。

---

## 3. AXI DMA

通用的内存间 DMA，通过寄存器控制。

### 寄存器定义

基地址: `0x62400000`

每个通道偏移 `0x100 × channel`，通道号 **1~8**（不是 0~7）。

```c
// 通道 N 的寄存器
#define DMA_SRC_ADDR(ch)   (0x62400000 + 0x100*(ch) + 0x00)
#define DMA_DST_ADDR(ch)   (0x62400000 + 0x100*(ch) + 0x04)
#define DMA_SIZE(ch)       (0x62400000 + 0x100*(ch) + 0x08)
#define DMA_CTRL(ch)       (0x62400000 + 0x100*(ch) + 0x0C)
#define DMA_STATUS(ch)     (0x62400000 + 0x100*(ch) + 0x10)
```

### 封装函数

```c
void dsp_hw_dma_memcpy(uint32_t channel, void* src, void* dst, uint32_t size);
int dsp_hw_dma_wait(uint32_t channel);  // 返回 0 成功，-1 超时
```

### 示例

```c
dsp_hw_dma_init();

// 通道 1 传输 4KB
dsp_hw_dma_memcpy(1, (void*)0x44020000, (void*)0x44030000, 4096);
if (dsp_hw_dma_wait(1) != 0) {
    // 超时处理
}
```

### 性能数据

4096 字节传输 @ 400 MHz:

| 路径         | 吞吐量    |
| ------------ | --------- |
| SRAM → SRAM  | 1204 MB/s |
| PSRAM → SRAM | 108 MB/s  |
| SRAM → PSRAM | 122 MB/s  |

---

## 4. QMAN (Queue Manager)

QMAN 用任务队列管理 DMA，理论上更高效，但目前 sync point 机制不太稳定。

### 当前状态

- `QMAN_sync_point()` 调用后会阻塞
- 单任务模式可以工作
- 多任务链和同步点有问题

### 临时方案

直接用 DDMA API，不走 QMAN:

```c
// 不用这个
// dma_init_manager();
// dma_add_task(...);
// QMAN_sync_point();

// 用这个
DMSS_execute_ddma_task(...);
while (DMSS_is_ddma_busy()) { }
```

后续需要进一步调试 QMAN。

---

## DMA 选型建议

| 场景         | 推荐 DMA | 理由             |
| ------------ | -------- | ---------------- |
| 权重加载     | DDMA     | 大块连续数据     |
| 图像分块读取 | DDMA 2D  | 支持 stride      |
| 代码热替换   | PDMA     | 唯一能写 PTCM    |
| 双缓冲       | DDMA     | 可同时计算和搬运 |
| 通用 memcpy  | AXI DMA  | 简单直接         |

---

## 常见问题

### Q: PDMA 传输后怎么验证？

PTCM 外部地址 (0x44Axxxxx) 只能写不能读。验证方法:
1. 传输完成无超时即认为成功
2. 实际执行加载的代码来验证功能

### Q: AXI DMA 通道号怎么选？

通道 1~8 都可以，功能一样。多通道可以并行传输。

### Q: DDMA 和 AXI DMA 有什么区别？

- DDMA: CSL 封装，自动处理 burst/alignment，支持 2D
- AXI DMA: 底层寄存器操作，更灵活但需要自己处理细节

### Q: 为什么 QMAN 会卡死？

`QMAN_sync_point()` 等待所有任务完成，如果任务配置有问题或者队列状态异常就会死等。目前建议用轮询 `DMSS_is_ddma_busy()` 替代。

---

*基于实际硬件测试，2026-01-28*
