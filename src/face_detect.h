
#ifndef FACE_DETECT_H
#define FACE_DETECT_H

typedef signed short int16_t;
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned char u8;

typedef struct FaceRect_
{
    float score;
    int x1;
    int y1;
    int x2;
    int y2;
    float lm[10];
} FaceRect;


#ifndef MIN
    #define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
    #define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

void show_bgr(u8 *bgr_buffer, int width, int height);
void add_faces(u8 *image_layer, FaceRect faces[], int facecount);

//input image, it must be RGB (three-channel) image
int objectdetect_cnn(const unsigned char *rgb_image_data, int width, int height, FaceRect *faces);

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;

struct Structure
{
    unsigned short num_output;
    unsigned char kernel_h;
    unsigned char kernel_w;
    unsigned char pad_h;
    unsigned char pad_w;
    unsigned char stride_h;
    unsigned char stride_w;
    unsigned char bias_flag;
    unsigned char depth_wise_flag;
    unsigned char nonlinear;
    unsigned char pooling_method;
    unsigned char offset;
    unsigned char offset_per_channel;
    unsigned char bias_offset;
    unsigned char bias_offset_per_channel;
};

struct Tensor
{
    unsigned short height;
    unsigned short width;
    unsigned short channel;
    int *data_location;
    unsigned char type; // 0 for uint8, 1 for int8
};

struct Uint8Tensor
{
    unsigned short height;
    unsigned short width;
    unsigned short channel;
    uint8_t *data_location;
    unsigned char type; // 0 for uint8, 1 for int8
};

struct FloatTensor
{
    unsigned short height;
    unsigned short width;
    unsigned short channel;
    float *data_location;
    unsigned char type; // 0 for uint8, 1 for int8
};

struct ConvParameter
{
    int16_t shape_weight[4];
    int16_t shape_bias;
    int16_t shape_offset;
    int16_t shape_bias_offset;
    const int8_t *weight;
    const int16_t *bias;
    const int8_t *offset_per_channel;
    const int8_t *bias_offset_per_channel;
};

FaceRect faces_result[3];

void conv(struct Uint8Tensor *input, struct Uint8Tensor *output, struct Structure *conv_params, struct ConvParameter *weight);

void pooling(struct Uint8Tensor *input, struct Uint8Tensor *output, struct Structure *pooling_params);

int fd_run(struct FloatTensor *result, const unsigned char *bgr_data);
int face_detect(const uint16_t *bgr565_image);
void cropAndConvertImage(const uint16_t *srcImage, uint8_t *dstImage, int srcWidth, int srcHeight, int cropHeight);

// 新增：当预处理已在接收图像阶段完成时，直接用160x120x3(RGB888)做推理
int face_detect_rgb(const uint8_t *rgb_image_160x120);

// 细化计时统计（供外部读取）
extern volatile uint32_t g_perf_preprocess_ms; // 前处理耗时 (BGR565→RGB888)
extern volatile uint32_t g_perf_infer_ms;      // 推理耗时 (48层CNN)
extern volatile uint32_t g_perf_softmax_ms;    // softmax耗时  
extern volatile uint32_t g_perf_decode_ms;     // priorbox解码耗时
extern volatile uint32_t g_perf_nms_ms;        // NMS耗时 (含IOU计算)

#endif

