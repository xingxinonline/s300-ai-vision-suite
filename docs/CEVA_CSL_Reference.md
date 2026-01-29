# CEVA CSL (Core Support Library) 参考手册

> 基于 dsp_csl 头文件整理，用于 CEVA SensPro250 DSP 开发

## 1. CSL 概述

### 1.1 什么是 CSL？

**CSL (Core Support Library)** 是 CEVA 提供的底层硬件抽象库，提供：
- 硬件寄存器访问
- 定时器管理
- 性能分析计数器
- DMA 驱动
- 中断控制
- 内存管理

### 1.2 主要模块

| 模块       | 头文件              | 功能         |
| ---------- | ------------------- | ------------ |
| CSL Core   | `ceva_csl.h`        | 库初始化入口 |
| Timers     | `ceva_timers.h`     | 定时器管理   |
| Profiler   | `ceva_profiler.h`   | 性能计数器   |
| DMA Driver | `dma_driver.h`      | DMA 数据传输 |
| ICU        | `ceva_icu.h`        | 中断控制器   |
| Memory Map | `ceva_memory_map.h` | 内存映射定义 |

---

## 2. CSL 初始化

### 2.1 CSL_start

```c
#include "ceva_csl.h"

// 在 CEVA DSP 上直接调用
E_csl_status status = CSL_start();
if (status != CSL_SUCCESS) {
    // 初始化失败处理
}
```

### 2.2 状态码

```c
typedef enum {
    CSL_SUCCESS = 0,           // 成功
    CSL_ALLOCATION_FAILURE,    // 资源分配失败
    CSL_ERROR,                 // 一般错误
    // ... 其他状态码
} E_csl_status;
```

---

## 3. 定时器 (Timers)

### 3.1 定时器配置结构

```c
typedef union {
    struct {
        uint32_t ts       : 2;  // Time Scale: 时钟分频
        uint32_t cm       : 3;  // Count Mode: 计数模式
        uint32_t es       : 1;  // Event Source
        uint32_t tp       : 1;  // Timer_OUT Polarity
        uint32_t tm       : 2;  // Timer_OUT Mode
        uint32_t trest_en : 1;  // Timer Reset Enable
        uint32_t cas      : 1;  // Cascade Mode
        uint32_t          : 5;  // Reserved
        uint32_t res      : 1;  // Restart
        uint32_t pc       : 1;  // Pause Count
        uint32_t ct       : 1;  // Clear Timer_OUT
        uint32_t ru       : 1;  // Read-time Update
        uint32_t bpen     : 1;  // Debug Enable
        uint32_t          : 11; // Reserved
    } fields;
    uint32_t value;
} T_TIMERx_CFG;
```

### 3.2 时钟分频选项

```c
typedef enum {
    TIMER_CFG_TS_CLK_DIV_1  = 0,  // 不分频
    TIMER_CFG_TS_CLK_DIV_2  = 1,  // 2分频
    TIMER_CFG_TS_CLK_DIV_4  = 2,  // 4分频
    TIMER_CFG_TS_CLK_DIV_16 = 3   // 16分频
} E_timer_cfg_ts;
```

### 3.3 计数模式

```c
typedef enum {
    TIMER_CFG_CM_SINGLE_COUNT = 0,  // 单次计数
    TIMER_CFG_CM_AUTO_RESTART = 1,  // 自动重启
    TIMER_CFG_CM_FREE_RUNNING = 2,  // 自由运行
    TIMER_CFG_CM_EVENT_COUNT  = 3   // 事件计数
} E_timer_cfg_cm;
```

### 3.4 定时器 API

```c
// 分配32位定时器
T_csl_allocation_id TIMER_allocate32(T_TIMERx_CFG timer_config);

// 分配64位定时器（级联模式）
T_csl_allocation_id TIMER_allocate64(T_TIMERx_CFG timer_config);

// 释放定时器
E_csl_status TIMER_deallocate(T_csl_allocation_id timer_id);

// 重置定时器计数
E_csl_status TIMER_reset(T_csl_allocation_id timer_id, uint64_t timer_sc);

// 恢复计数
E_csl_status TIMER_resume(T_csl_allocation_id timer_id);

// 暂停计数
E_csl_status TIMER_pause(T_csl_allocation_id timer_id);

// 读取32位计数值
uint32_t TIMER_read32(T_csl_allocation_id timer_id);

// 读取64位计数值（仅级联模式）
uint64_t TIMER_read64(T_csl_allocation_id timer_id);
```

### 3.5 使用示例：性能测量

```c
#include "ceva_csl.h"

void measure_performance(void) {
    // 配置定时器：自由运行模式，不分频
    T_TIMERx_CFG timer_cfg = {0};
    timer_cfg.fields.cm = TIMER_CFG_CM_FREE_RUNNING;
    timer_cfg.fields.ts = TIMER_CFG_TS_CLK_DIV_1;
    
    // 分配定时器
    T_csl_allocation_id timer_id = TIMER_allocate32(timer_cfg);
    
    // 重置并启动
    TIMER_reset(timer_id, 0);
    TIMER_resume(timer_id);
    
    // === 被测量的代码 ===
    my_function();
    // ====================
    
    // 读取周期数
    uint32_t cycles = TIMER_read32(timer_id);
    
    // 暂停并释放
    TIMER_pause(timer_id);
    TIMER_deallocate(timer_id);
    
    rt_kprintf("Cycles: %u\n", cycles);
}
```

---

## 4. 性能分析器 (Profiler)

### 4.1 概述

SensPro250 提供8个可配置的性能计数器 (PROF_CNT0-7) 加一个自由运行计数器 (FRCC)。

### 4.2 计数器事件类型 (SensPro)

| 事件                               | 值  | 描述             |
| ---------------------------------- | --- | ---------------- |
| `PROF_COUNTER_EVENT_FRCC`          | 1   | 自由运行周期计数 |
| `PROF_COUNTER_EVENT_CORE_LS`       | 4   | 轻睡眠周期       |
| `PROF_COUNTER_EVENT_WAIT_CNT`      | 80  | 等待周期         |
| `PROF_COUNTER_EVENT_RAW_WAIT`      | 88  | RAW 等待周期     |
| `PROF_COUNTER_EVENT_NOP_PACKET`    | 94  | NOP 包计数       |
| `PROF_COUNTER_EVENT_BR_TO_ISR`     | 95  | 进入 ISR 次数    |
| `PROF_COUNTER_EVENT_RET_FROM_ISR`  | 96  | 退出 ISR 次数    |
| `PROF_COUNTER_EVENT_ISR_CYCLE_CNT` | 97  | ISR 中非等待周期 |
| `PROF_COUNTER_EVENT_PMSS_HIT_CNT`  | 64  | 程序缓存命中     |
| `PROF_COUNTER_EVENT_PMSS_MISS_CNT` | 65  | 程序缓存未命中   |

### 4.3 内存访问事件

| 事件                                  | 值  | 描述               |
| ------------------------------------- | --- | ------------------ |
| `PROF_COUNTER_EVENT_LD_LS0_TCM_CNT`   | 7   | LS0 TCM 加载       |
| `PROF_COUNTER_EVENT_LD_LS1_TCM_CNT`   | 8   | LS1 TCM 加载       |
| `PROF_COUNTER_EVENT_ST_TCM_CNT`       | 16  | TCM 存储           |
| `PROF_COUNTER_EVENT_EDP_R_CNT`        | 33  | EDP 读突发         |
| `PROF_COUNTER_EVENT_EDP_W_CNT`        | 36  | EDP 写突发         |
| `PROF_COUNTER_EVENT_VLD_LS0_INST_EXT` | 119 | 向量加载到外部存储 |
| `PROF_COUNTER_EVENT_VST_INST_EXT`     | 121 | 向量存储到外部存储 |

### 4.4 向量/DMA 相关事件 (V1.2+)

| 事件                                  | 值  | 描述                   |
| ------------------------------------- | --- | ---------------------- |
| `PROF_COUNTER_EVENT_VPLD_STALL_CYC`   | 122 | vpld bank竞争周期      |
| `PROF_COUNTER_EVENT_VPST_STALL_CYC`   | 123 | vpst bank竞争周期      |
| `PROF_COUNTER_EVENT_IDM_CONT_CYC_ALL` | 124 | IDM bank竞争周期(全部) |
| `PROF_COUNTER_EVENT_IDM_CONT_CYC_DMA` | 125 | IDM bank竞争周期(DMA)  |
| `PROF_COUNTER_EVENT_VLD_NALGN_CYC`    | 126 | vld非对齐等待周期      |
| `PROF_COUNTER_EVENT_VST_NALGN_CYC`    | 127 | vst非对齐等待周期      |

### 4.5 计数器控制

```c
// 计数器掩码
typedef enum {
    PROF_COUNTER_MASK_FRCC = 0x00010001U,
    PROF_COUNTER_MASK_CNT0 = 0x00020002U,
    PROF_COUNTER_MASK_CNT1 = 0x00040004U,
    // ...
    PROF_COUNTER_MASK_ALL  = 0x01ff01ffU
} E_profiler_counter_mask;

// 常用 API
void PROFILER_reset(E_profiler_counter_mask mask);
void PROFILER_pause(E_profiler_counter_mask mask);
void PROFILER_resume(E_profiler_counter_mask mask);
uint32_t PROFILER_read(E_profiler_counter_number counter);
```

---

## 5. DMA 驱动

### 5.1 DMA 状态码

```c
typedef enum {
    DMA_STATUS_OK = 0,
    DMA_STATUS_ERROR_PARAMS,
    DMA_STATUS_ERROR_QUEUE_FULL,
    DMA_STATUS_ERROR_NOT_READY,
    // ...
} dma_status_e;
```

### 5.2 DMA 初始化

```c
#include "dma_driver.h"

// 初始化 DMA 管理器
dma_status_e status = dma_init_manager();
```

### 5.3 传输限制 (扩展描述符模式)

| 参数            | 最大值         |
| --------------- | -------------- |
| Tile Height     | 65535 (16-bit) |
| Tile Width      | 65535 bytes    |
| 1D Size         | 4MB - 1        |
| Internal Stride | 65535 bytes    |
| External Stride | 65535 bytes    |

### 5.4 基本 DMA 传输

```c
// 创建描述符
dma_desc_t desc;

// 2D 传输配置
dma_create_2d_desc(&desc,
    src_addr,       // 源地址
    dst_addr,       // 目标地址
    width,          // 每行字节数
    height,         // 行数
    src_stride,     // 源步长
    dst_stride      // 目标步长
);

// 入队描述符
dma_enqueue_desc(queue_id, &desc);

// 等待完成
dma_wait_completion(queue_id);
```

---

## 6. 编译器属性宏

### 6.1 内存段控制

```c
// 代码段
#define PRAGMA_CSECT(name)  __attribute__ ((section (name)))

// 数据段（不加载）
#define PRAGMA_DSECT_NO_LOAD(name) __attribute__ ((section (".DSECT " name)))

// 数据段（加载）
#define PRAGMA_DSECT_LOAD(name) __attribute__ ((section (".DSECT " name)))
```

### 6.2 对齐控制

```c
#define ALIGN(var, imm) var __attribute__ ((aligned (imm)))

// 使用示例
ALIGN(int buffer[256], 32);  // 32字节对齐
```

### 6.3 循环优化

```c
// 软件流水
#define DSP_CEVA_SWP              _Pragma("ceva_swp")

// 循环展开
#define DSP_CEVA_UNROLL(x)        _Pragma("dsp_ceva_unroll = x")

// 最小迭代次数提示
#define DSP_CEVA_TRIP_COUNT_MIN(x) _Pragma("dsp_ceva_trip_count_min = x")

// 使用示例
DSP_CEVA_TRIP_COUNT_MIN(4)
DSP_CEVA_UNROLL(4)
for (int i = 0; i < n; i++) {
    // ...
}
```

---

## 7. 平台检测宏

```c
// 检测 CEVA DSP 环境
#ifdef CEVA
    // 在 DSP 上运行
#endif

// 检测 SensPro
#ifdef SENSPRO
    // SensPro 系列
#endif

// 检测具体型号
#ifdef VECC_SENSPRO
    #define PLATFORM_STR "CEVA-SENSPRO"
#endif
```

---

## 8. 常用配置

### 8.1 IDM (Internal Data Memory) 配置

```c
// IDM 相关的性能计数器可用于监控：
// - Bank 竞争
// - DMA/Core 访问冲突
// - 向量加载/存储效率
```

### 8.2 QMAN (Queue Manager) 支持

```c
#ifdef CSL_QMAN_SUPPORTED
    // QMAN 可用
    // 支持异常处理
    #define QMAN_SUPPORTS_EXCPTN_HANDLE
    // 支持暂停
    #define QMAN_SUPPORTS_PAUSE
#endif
```

---

## 附录A: 文件包含关系

```
ceva_csl.h
├── ceva_hw_conf.h
├── ceva_csl_defs.h
│   └── cevaxm.h
├── ceva_assert.h
├── ceva_profiler.h
├── ceva_memory_map.h
├── ceva_dcu.h
├── ceva_dmss.h
├── ceva_pmss.h
├── ceva_hw_exceptions.h
├── ceva_mcci.h
├── ceva_timers.h (if CSL_TIMERS_SUPPORTED)
├── ceva_icu.h (if CSL_ICU_SUPPORTED)
└── ceva_qman.h (if CSL_QMAN_SUPPORTED)
```

---

## 附录B: 快速参考

### 性能测量代码模板

```c
#include "ceva_csl.h"

#define TIMER0_START() \
    T_TIMERx_CFG _t_cfg = {0}; \
    _t_cfg.fields.cm = TIMER_CFG_CM_FREE_RUNNING; \
    T_csl_allocation_id _t_id = TIMER_allocate32(_t_cfg); \
    TIMER_reset(_t_id, 0); \
    TIMER_resume(_t_id);

#define TIMER0_END(var) \
    var = TIMER_read32(_t_id); \
    TIMER_pause(_t_id); \
    TIMER_deallocate(_t_id);

// 使用
void test() {
    uint32_t cycles;
    TIMER0_START();
    // ... 被测代码 ...
    TIMER0_END(cycles);
    rt_kprintf("Cycles: %u\n", cycles);
}
```

---

*文档版本: 1.0*  
*最后更新: 2026-01-28*
