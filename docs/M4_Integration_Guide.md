# M4 集成指南 - DSP 检测结果处理

本文档描述 M4 MCU 如何处理 DSP 发送的人脸检测结果。
当前 DSP demo 仅输出检测框与关键点；`track_id`、`vx`、`vy`、`speed`、`kf_confidence`、`selected_idx` 等字段仅为协议兼容保留字段，M4 侧应忽略其业务语义。

## 1. 通信协议

### 1.1 数据流

```
┌─────────┐  检测数据  ┌─────────┐  邮箱通信  ┌─────────┐  显示
│  摄像头  │ ──────────► │   DSP   │ ─────────► │   M4    │ ────────► LCD
└─────────┘             └─────────┘            └─────────┘
                         人脸检测
                         + 结果过滤
```

### 1.2 邮箱消息格式

DSP 通过邮箱 FIFO 发送 `DetectionResult_t` 结构体：

```c
typedef struct {
    uint32_t magic;              // = 0x44455446 ("DETF")
    uint32_t version;            // = 0x0202 (v2.2)
    uint32_t frame_id;           // 帧计数器
    uint32_t timestamp;          // DSP 时间戳（毫秒）
    uint32_t count;              // 检测到的目标数量 (0-10)
    int32_t  selected_idx;       // 兼容保留字段，当前固定为 -1
    DetectionBox_t boxes[MAX_DETECTIONS];  // 检测框（最多10个）
} DetectionResult_t;  // 总大小: 704 字节
```

### 1.3 检测框结构体

```c
typedef struct __attribute__((packed)) {
    float    score;              // 检测置信度 [0.0, 1.0]
    int32_t  x1, y1;             // 左上角坐标
    int32_t  x2, y2;             // 右下角坐标
    float    lm[10];             // 5个关键点 (x0,y0,x1,y1,...,x4,y4)
    uint8_t  type;               // 检测类型 (1=人脸, 2=行人, 3=手势)
    uint8_t  track_id;           // 兼容保留字段，当前固定填 0
    int8_t   vx;                 // 兼容保留字段，当前固定填 0
    int8_t   vy;                 // 兼容保留字段，当前固定填 0
    uint8_t  speed;              // 兼容保留字段，当前固定填 0
    uint8_t  kf_confidence;      // 兼容保留字段，当前固定填 0
    uint8_t  reserved[2];        // 预留字段
} DetectionBox_t;  // 总大小: 68 字节
```

## 2. 兼容字段说明

当前人脸 demo 中，这些字段只用于保持与既有 CM4 结构体布局兼容：

| 字段            | 类型    | 范围        | 说明                                  |
| --------------- | ------- | ----------- | ------------------------------------- |
| `track_id`      | uint8_t | 固定 0      | 兼容保留字段，当前不分配目标 ID       |
| `vx`            | int8_t  | 固定 0      | 兼容保留字段，当前不输出速度          |
| `vy`            | int8_t  | 固定 0      | 兼容保留字段，当前不输出速度          |
| `speed`         | uint8_t | 固定 0      | 兼容保留字段，当前不输出速度幅值      |
| `kf_confidence` | uint8_t | 固定 0      | 兼容保留字段，当前不输出滤波置信度    |
| `selected_idx`  | int32_t | 固定 -1     | 兼容保留字段，当前不指定主目标        |

M4 端只需要依赖以下字段：
- `magic`
- `version`
- `frame_id`
- `timestamp`
- `count`
- `boxes[i].score`
- `boxes[i].x1/y1/x2/y2`
- `boxes[i].lm[10]`

## 3. 历史渲染扩展

以下箭头渲染内容是旧版扩展设想，当前纯检测 demo 不启用，也不作为联调前置条件。

## 4. 箭头渲染算法（历史保留）

### 3.1 何时绘制箭头

满足以下条件时绘制速度箭头：
- `speed >= ARROW_MIN_SPEED`（建议值：10）
- 目标在屏幕上可见
- `kf_confidence > 0`

### 3.2 箭头参数配置

```c
// 配置参数
#define ARROW_MIN_SPEED       10    // 绘制箭头的最小速度
#define ARROW_SCALE           3     // 速度到长度的乘数
#define ARROW_HEAD_RATIO      0.3f  // 箭头头部尺寸比例
#define ARROW_WIDTH_BASE      2     // 基础线宽
#define ARROW_WIDTH_SCALE     0.1f  // 线宽随速度的缩放系数
```

### 3.3 M4 端 C 语言实现

```c
#include <math.h>

typedef struct {
    int16_t x1, y1;  // 线段起点（箭头尾部）
    int16_t x2, y2;  // 线段终点（箭头顶端）
    int16_t hx1, hy1, hx2, hy2;  // 箭头两翼点
    uint8_t width;   // 线宽
    uint8_t valid;   // 1 = 应该绘制箭头
} ArrowParams_t;

/**
 * @brief 根据速度计算箭头渲染参数
 * 
 * @param cx      边界框中心 X 坐标
 * @param cy      边界框中心 Y 坐标
 * @param vx      X 方向速度（像素/帧）
 * @param vy      Y 方向速度（像素/帧）
 * @param speed   速度大小 (0-255)
 * @param out     输出的箭头参数
 */
void calculate_arrow(int16_t cx, int16_t cy, 
                     int16_t vx, int16_t vy, 
                     uint8_t speed,
                     ArrowParams_t *out)
{
    // 速度过低时跳过
    if (speed < ARROW_MIN_SPEED) {
        out->valid = 0;
        return;
    }
    
    // 箭头尾部位于检测框中心
    out->x1 = cx;
    out->y1 = cy;
    
    // 箭头顶端：沿速度方向延伸
    out->x2 = cx + (int16_t)(vx * ARROW_SCALE);
    out->y2 = cy + (int16_t)(vy * ARROW_SCALE);
    
    // 计算箭头头部
    float dx = (float)(out->x2 - out->x1);
    float dy = (float)(out->y2 - out->y1);
    float len = sqrtf(dx * dx + dy * dy);
    
    if (len < 5.0f) {
        out->valid = 0;
        return;
    }
    
    // 单位向量
    float ux = dx / len;
    float uy = dy / len;
    
    // 箭头头部长度
    float head_len = len * ARROW_HEAD_RATIO;
    
    // 计算箭头两翼
    float bx = out->x2 - ux * head_len;
    float by = out->y2 - uy * head_len;
    float wing_len = head_len * 0.5f;
    
    out->hx1 = (int16_t)(bx - uy * wing_len);
    out->hy1 = (int16_t)(by + ux * wing_len);
    out->hx2 = (int16_t)(bx + uy * wing_len);
    out->hy2 = (int16_t)(by - ux * wing_len);
    
    // 线宽随速度增加
    out->width = ARROW_WIDTH_BASE + (uint8_t)(speed * ARROW_WIDTH_SCALE);
    out->valid = 1;
}
```

### 3.4 箭头绘制示例

```c
void draw_velocity_arrow(LCD_TypeDef *lcd, const DetectionBox_t *box)
{
    // 仅为选中目标绘制箭头
    if (box->speed < ARROW_MIN_SPEED) {
        return;
    }
    
    ArrowParams_t arrow;
    int16_t cx = (box->x1 + box->x2) / 2;
    int16_t cy = (box->y1 + box->y2) / 2;
    
    calculate_arrow(cx, cy, box->vx, box->vy, box->speed, &arrow);
    
    if (arrow.valid) {
        // 根据速度选择颜色
        uint16_t color;
        if (box->speed > 150) {
            color = COLOR_RED;        // 高速：红色
        } else if (box->speed > 80) {
            color = COLOR_YELLOW;     // 中速：黄色
        } else {
            color = COLOR_GREEN;      // 低速：绿色
        }
        
        // 绘制箭头主体
        lcd_draw_line(lcd, arrow.x1, arrow.y1, arrow.x2, arrow.y2, 
                      color, arrow.width);
        
        // 绘制箭头头部
        lcd_draw_line(lcd, arrow.x2, arrow.y2, arrow.hx1, arrow.hy1, 
                      color, arrow.width);
        lcd_draw_line(lcd, arrow.x2, arrow.y2, arrow.hx2, arrow.hy2, 
                      color, arrow.width);
    }
}
```

## 4. 历史扩展示例

### 4.1 当前推荐处理流程

```c
void process_detection_result(const DetectionResult_t *result)
{
    // 1. 验证数据有效性
    if (result->magic != DETECTION_MAGIC) {
        return;  // 无效数据
    }
    
    if (result->version != 0x0202) {
        // 版本不匹配，可能需要更新协议
        log_warning("协议版本不匹配: 0x%04X", result->version);
    }
    
    // 2. 当前 demo 不依赖 selected_idx，直接绘制所有有效框
    for (uint32_t i = 0; i < result->count; i++) {
        draw_bounding_box(&result->boxes[i], COLOR_GREEN);
    }
}
```

### 4.2 历史扩展说明

以下丢失处理、速度箭头和目标 ID 示例来自旧版扩展设想。当前纯检测 demo 中：

1. `selected_idx` 固定为 `-1`
2. `track_id`、`vx`、`vy`、`speed`、`kf_confidence` 固定为 0
3. M4 端应以 `count` 和 `boxes[0..count-1]` 为唯一有效输入

```c
static uint8_t s_lost_count = 0;
#define MAX_LOST_DISPLAY  10  // 丢失后最多继续显示10帧

void handle_target_lost(const DetectionResult_t *result)
{
    if (result->selected_idx >= 0) {
        s_lost_count = 0;
        return;  // 目标存在
    }
    
    s_lost_count++;
    
    if (s_lost_count <= MAX_LOST_DISPLAY) {
        // 使用上一帧的目标显示预测框
        draw_predicted_box(last_target, COLOR_YELLOW);  // 虚线黄色框
        display_status("目标丢失中...");
    } else {
        // 彻底丢失
        clear_tracking_display();
        display_status("搜索目标...");
    }
}
```

## 5. 数据结构大小说明

### 5.1 协议版本 v2.2 结构体大小

| 结构体              | 大小     | 说明                         |
| ------------------- | -------- | ---------------------------- |
| `DetectionBox_t`    | 68 字节  | 包含速度字段的检测框         |
| `DetectionResult_t` | 704 字节 | 完整检测结果（含10个检测框） |

### 5.2 编译时断言

M4 端应添加编译时断言确保结构体大小匹配：

```c
// 确保与 DSP 端结构体大小一致
_Static_assert(sizeof(DetectionBox_t) == 68, "DetectionBox_t 大小不匹配");
_Static_assert(sizeof(DetectionResult_t) == 704, "DetectionResult_t 大小不匹配");
```

## 6. 调试建议

### 6.1 UART 日志格式

当前 face demo 重点关注以下日志：
- `[DSP-CTRL]` - 控制面握手、状态迁移、心跳
- `[DSP:RAW]` - 原始检测分数
- `[DSP:REJECT]` - 被 DSP 侧过滤的检测框
- `[DSP:FILTER]` - 原始框数量与有效框数量对比

### 6.2 常见问题排查

| 问题             | 可能原因                       | 解决方案                         |
| ---------------- | ------------------------------ | -------------------------------- |
| 边框位置错误     | 坐标系不匹配                   | 检查 DSP 与 M4 的坐标空间定义    |
| 有检测但不显示   | `count` 为 0 或框被本地过滤    | 查看 `[DSP:REJECT]` 与阈值配置   |
| 握手后无结果     | 未进入 `RUNNING` 状态          | 检查 `[DSP-CTRL]` 状态迁移日志   |
| 结构体大小不匹配 | 编译器对齐不一致               | 使用 `__attribute__((packed))`   |

### 6.3 性能指标

- 检测结果渲染时延应由 LCD 刷新链路主导
- DSP 侧状态上报周期默认为每 32 帧一次
- 纯检测链路不再包含目标关联与速度估计开销

## 7. 版本历史

| 版本 | 日期       | 更改内容                                    |
| ---- | ---------- | ------------------------------------------- |
| v2.2 | 2026-01-30 | 保留兼容字段布局，当前 demo 仅输出纯检测    |
| v2.1 | 2026-01-29 | 历史版本曾扩展兼容字段                      |
| v2.0 | 2026-01-20 | 历史版本曾尝试目标关联                      |
| v1.0 | 2026-01-01 | 初始版本                                    |
