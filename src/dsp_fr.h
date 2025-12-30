typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;


struct Structure{
    uint16_t num_output;
    uint8_t kernel_h;
    uint8_t kernel_w;
    uint8_t pad_h;
    uint8_t pad_w;
    uint8_t stride_h;
    uint8_t stride_w;
    uint8_t bias_flag;
    uint8_t depth_wise_flag;
    uint8_t nonlinear;
    uint8_t pooling_method;
    uint8_t offset;
    uint8_t offset_per_channel;
    uint8_t bias_offset;
    uint8_t bias_offset_per_channel;
};


struct ConvParameter{
    int16_t shape_weight[4];
    int16_t shape_bias;
    int16_t shape_offset;
    int16_t shape_bias_offset;  
    const int8_t* weight;   
    const int16_t* bias;
    const int8_t* offset_per_channel;
    const int8_t* bias_offset_per_channel;
};

struct LookupParameter{
    int16_t shape_weight[3];
    uint8_t input_type;
    uint8_t output_type;
    uint8_t *table;
};

struct ConcatParams{
    uint8_t in_shape1;
    uint8_t in_shape2;
    uint8_t in_shape3;
    uint8_t in_shape4;
    uint8_t in_shape5;
    uint8_t in_shape6;

    uint8_t type1;
    uint8_t type2;

    uint16_t scale1;
    uint16_t scale2;

    uint8_t offset1;
    uint8_t offset2;

    uint8_t out_shape1;
    uint8_t out_shape2;
    uint8_t out_shape3;
    uint8_t type3;
};

struct Uint8Tensor{
    uint16_t height;
    uint16_t width;
    uint16_t channel;
    uint8_t* data_location;
    uint8_t type; // 0 for uint8, 1 for int8
};
