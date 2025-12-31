#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vec-c.h>

#include "dsp_fr.h"
#include "fr_weight_dsp.h"

#include "custom_printf.h"

// 打印开关，1开启，0关闭
#define ENABLE_TENSOR_PRINT 0

// 自动字符串化参数名的宏
#if ENABLE_TENSOR_PRINT
#define print_uint8tensor(tensor) print_uint8tensor_impl(#tensor, (tensor))
#else
#define print_uint8tensor(tensor) ((void)0)
#endif

int buffer_conv_1024[1024];
uint8_t buffer_conv_u8[1024];

int total_memory = 0;



unsigned int TIMER0_START(){
	//return 0;
	// _out(_cpm, (unsigned int)100000000, 0x200C);
	// uint32_t cfg = _in(_cpm, 0x2000);
	// cfg |= (1<<16);
	// cfg |= (1<<19);
	// _out(_cpm, cfg, 0x2000);
	// return _in(_cpm, 0x2008);
//    DSP_LOG("TIMER0_START is not implemented yet!\n");
}


unsigned int TIMER0_END(){
//	return 0;
	// unsigned int end =  _in(_cpm, 0x2008);
	// return end;
//    DSP_LOG("TIMER0_END is not implemented yet!\n");
}

void print_uint8tensor_impl(const char *name, struct Uint8Tensor *input)
{
    if (input == NULL || input->data_location == NULL) {
        DSP_LOG("[%s] ERROR: Tensor is NULL or data_location is NULL\n", name);
        return;
    }

    int total_elements = input->height * input->width * input->channel;
    int print_limit = 128;
    int print_elements = (total_elements > print_limit) ? print_limit : total_elements;
    const char *type_str = (input->type == 1) ? "int8" : "uint8";
    
    DSP_LOG("\n========== Tensor: %s ==========\n", name);
    DSP_LOG("Shape: [height=%u, width=%u, channel=%u]\n", input->height, input->width, input->channel);
    DSP_LOG("Type: %s\n", type_str);
    DSP_LOG("Total elements: %d\n", total_elements);
    if (total_elements > print_limit) {
        DSP_LOG("Printing first %d elements (limited):\n", print_limit);
    } else {
        DSP_LOG("Data content:\n");
    }
    
    if (input->type == 1) {
        // int8_t type
        int8_t *data = (int8_t *)input->data_location;
        char line_buf[128];
        int pos = 0;
        line_buf[0] = '\0';

        for (int i = 0; i < print_elements; i++) {
            if (pos > 100) {
                DSP_LOG("%s\n", line_buf);
                pos = 0;
                line_buf[0] = '\0';
            }

            pos += snprintf(line_buf + pos, sizeof(line_buf) - pos, "%d", data[i]);

            if ((i + 1) % input->channel == 0) {
                DSP_LOG("%s\n", line_buf);
                pos = 0;
                line_buf[0] = '\0';
            } else if ((i + 1) % 16 == 0) {
                pos += snprintf(line_buf + pos, sizeof(line_buf) - pos, " | ");
            } else {
                pos += snprintf(line_buf + pos, sizeof(line_buf) - pos, " ");
            }
        }
        if (pos > 0) {
            DSP_LOG("%s\n", line_buf);
        }
    } else {
        // uint8_t type
        uint8_t *data = input->data_location;
        char line_buf[128];
        int pos = 0;
        line_buf[0] = '\0';

        for (int i = 0; i < print_elements; i++) {
            if (pos > 100) {
                DSP_LOG("%s\n", line_buf);
                pos = 0;
                line_buf[0] = '\0';
            }

            pos += snprintf(line_buf + pos, sizeof(line_buf) - pos, "%3u", data[i]);

            if ((i + 1) % input->channel == 0) {
                DSP_LOG("%s\n", line_buf);
                pos = 0;
                line_buf[0] = '\0';
            } else if ((i + 1) % 16 == 0) {
                pos += snprintf(line_buf + pos, sizeof(line_buf) - pos, " | ");
            } else {
                pos += snprintf(line_buf + pos, sizeof(line_buf) - pos, " ");
            }
        }
        if (pos > 0) {
            DSP_LOG("%s\n", line_buf);
        }
    }
    DSP_LOG("========================================\n\n");
}

void lookup(struct Uint8Tensor *input, struct Uint8Tensor *output, struct LookupParameter *lookup_params){
    uint32_t start_time = TIMER0_START();

	
	int flag = (lookup_params->output_type == 1);
    int h = output->height;
    int w = output->width;
    int c = output->channel;

    int total_len = h * w * c;
    uint8_t *in_ptr = input->data_location;
    uint8_t *out_ptr = output->data_location;
    uint8_t *table = lookup_params->table;

    for(int i = 0; i < total_len; i++){
        uint8_t index = in_ptr[i];
        uint8_t value = table[index];
        out_ptr[i] = flag ? ((int8_t)value) : value;
    }

	uint32_t end_time = TIMER0_END();
//    DSP_LOG("lookup , %f M MACs, time cost is %f M cycles\n", 1.0f*(total_len)/1000000, 1.0f*(start_time - end_time)/1000000);
}

void concat(struct Uint8Tensor *input1, struct Uint8Tensor *input2, struct Uint8Tensor *output, struct ConcatParams *concat_params){
    
	uint32_t start_time = TIMER0_START();
    int h = output->height;
    int w = output->width;
    int c = output->channel;
    int scale1 = concat_params->scale1;
    int scale2 = concat_params->scale2;
    int offset1 = concat_params->offset1;
    int offset2 = concat_params->offset2;
    
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            for(int k=0;k<c/2;k++){
                // output->data_location[i*w*c + j*c + k] = ((input1->data_location[i*w*c/2 + j*c/2 + k]*scale1) +(1 << (offset1 - 1))) >> offset1;
                // output->data_location[i*w*c + j*c + c/2 + k] = ((input2->data_location[i*w*c/2 + j*c/2 + k]*scale2) +(1 << (offset2 - 1))) >> offset2;
                int temp = 0;
                int temp_input1 = 0, temp_input2 = 0;
                if(input1->type == 1) 
                    temp_input1 = (int8_t)input1->data_location[i*w*c/2 + j*c/2 + k];
                else
                    temp_input1 = (uint8_t)input1->data_location[i*w*c/2 + j*c/2 + k];
                
                if(offset1 > 0) 
                    temp = (((temp_input1*scale1) +(1 << (offset1 - 1))) >> offset1);
                else
                    temp = (temp_input1*scale1);
                
                output->data_location[i*w*c + j*c + k] = (uint8_t)temp;
                
                if(input2->type == 1)
                    temp_input2 = (int8_t)input2->data_location[i*w*c/2 + j*c/2 + k];
                else
                    temp_input2 = (uint8_t)input2->data_location[i*w*c/2 + j*c/2 + k];

                if(offset2 > 0)
                    temp = (((temp_input2*scale2) +(1 << (offset2 - 1))) >> offset2);
                else
                    temp = ((temp_input2*scale2));

                output->data_location[i*w*c + j*c + c/2 + k] = (uint8_t)temp;
                
            }
        }
    }

	uint32_t end_time = TIMER0_END();
//    DSP_LOG("concat, %f M MACs, time cost is %f M cycles\n", 1.0*(output->channel*output->width*output->height)/1000000, 1.0*(start_time - end_time)/1000000);

}

void build_output(struct Uint8Tensor *output, unsigned char type){
//	static int i = 0;
    total_memory += (output->channel)*(output->width)*(output->height);
    output->data_location = (uint8_t *)malloc(sizeof(uint8_t)*(output->channel)*(output->width)*(output->height));
//    DSP_LOG("total_memory %d, alloc size %d\n", total_memory, (output->channel)*(output->width)*(output->height));
}

void release_input(struct Uint8Tensor *input){
    total_memory -= (input->channel)*(input->width)*(input->height);
    free(input->data_location);
//    DSP_LOG("total_memory %d, free size %d\n", total_memory, (input->channel)*(input->width)*(input->height));
    return;
}


void conv_fr_split(struct Uint8Tensor *input, struct Uint8Tensor *output, struct Structure *conv_params, struct ConvParameter *weight){
    // 后续用交织的方式做处理，会得到更大的效果
    uint32_t start_time = TIMER0_START();
	
	int shift = conv_params->offset;
    int input_w = input->width;
    int input_c = input->channel;
    int input_h = input->height;
    int output_c = output->channel;
    int max=127,min=-128;

    int8_t temp_memory_in[192] = {0};
    int8_t temp_memory_out[192] = {0};
    int index_out_from_in[192] = {0};

    for(int i=0;i<output_c;i++){
        index_out_from_in[i] = (uint8_t)(weight->weight[i]);
    }



    for(int i=0;i<input_h;i++){
        for(int j=0;j<input_w;j++){
            memcpy(temp_memory_in, input->data_location + i*input_w*input_c + j*input_c, input_c);
            for(int k=0;k<output_c;k++){
                int result = ((temp_memory_in[index_out_from_in[k]]*127 + (1<<(shift-1))) >> shift);
                if(result > max){
                    result = max;
                }else if(result < min){
                    result = min;
                }
                temp_memory_out[k] = (int8_t)result;
            }
            memcpy(output->data_location + i*input_w*output_c + j*output_c,temp_memory_out,output_c);
        }
    }

	uint32_t end_time = TIMER0_END();
    // DSP_LOG("split_conv, %f M MACs, time cost is %f M cycles\n", 1.0*(input->channel*output->channel*output->width*output->height)/1000000, 1.0*(start_time - end_time)/1000000);
}





void conv1x1xn_dsp(struct Uint8Tensor *input, struct Uint8Tensor *output, struct Structure *conv_params, struct ConvParameter *weight){
	uint32_t start_time = TIMER0_START();

    int bias_offset = conv_params->bias_offset;
    int bias_offset_per_channel_flag = conv_params->bias_offset_per_channel;
    int8_t *weight_ptr1 = (int8_t *)weight->weight;
	int o_c = output->channel;
    int i_c = input->channel;

    assert(input->channel == 24 || (input->channel %16 == 0)); 
	assert(conv_params->offset_per_channel);




    for(int vec_part = 0; vec_part < (o_c+15)/ 16; vec_part ++ ){

    	int calcu_oc = 16;
		if(output->channel == 24 && vec_part == 1) calcu_oc = 8;

		short temp_weight0[16] = {0};
		short4xN_t weight_out[i_c];
		for(int i=0;i<i_c;i++){
			for(int j=0;j<calcu_oc;j++){
				temp_weight0[j] = weight_ptr1[(16*vec_part +j)*(i_c) + i];
			}
			weight_out[i] = *(short4xN_t*)temp_weight0;
		}

		int bias_local[16] = {0};
		for(int s=0;s<calcu_oc;s++){
			if(bias_offset_per_channel_flag){
				bias_local[s] = (weight->bias[vec_part*16 + s] << weight->bias_offset_per_channel[vec_part*16 + s]) + (1<<(weight->offset_per_channel[vec_part*16 + s]-1));
			}
			else{
				bias_local[s] = (weight->bias[vec_part*16 + s] << bias_offset)+ (1<<(weight->offset_per_channel[vec_part*16 + s]-1));
			}
		}

		int4xN_t bias_vec = *(int4xN_t*)bias_local;

		unsigned int temp_shift_lo[8] ={0};
		unsigned int temp_shift_hi[8] ={0};
		for(int i=0;i<8;i++){
			temp_shift_lo[i] = (unsigned int)weight->offset_per_channel[vec_part*16 + i];
		}
		for(int i=0;i<8;i++){
			temp_shift_hi[i] = (unsigned int)weight->offset_per_channel[vec_part*16 + i + 8];
		}
		uint2xN_t shift_vec_lo = *(uint2xN_t*)temp_shift_lo;
		uint2xN_t shift_vec_hi = *(uint2xN_t*)temp_shift_hi;

		unsigned char tmp_kernel[1024] = {0};
		int tmp_input1 = 0;
		int tmp_input2 = 0;
		int tmp_input3 = 0;
		int tmp_input4 = 0;

		int count0 = 0;



		for(int i=0;i<output->height;i++){
			for(int j=0;j<output->width;j++){
				memcpy(tmp_kernel, input->data_location+count0,  i_c);
				count0 += i_c;

				int4xN_t temp_result1 = {0};
				int4xN_t temp_result2 = {0};
				int4xN_t temp_result3 = {0};
				int4xN_t temp_result4 = {0};


				for(int ii=0; ii<i_c; ii += 16){

					memcpy(&tmp_input1, tmp_kernel + ii, 4);
					memcpy(&tmp_input2, tmp_kernel + ii + 4, 4);
					memcpy(&tmp_input3, tmp_kernel + ii + 8, 4);
					memcpy(&tmp_input4, tmp_kernel + ii + 12, 4);

					temp_result1 = _vmac5((weight_out[ii + 0]),(weight_out[ii + 1]),(weight_out[ii + 2]),(weight_out[ii + 3]), tmp_input1,temp_result1);
					temp_result2 = _vmac5((weight_out[ii + 4]),(weight_out[ii + 5]),(weight_out[ii + 6]),(weight_out[ii + 7]), tmp_input2,temp_result2);
					if(ii+8 == i_c) continue;
					temp_result3 = _vmac5((weight_out[ii + 8]),(weight_out[ii + 9]),(weight_out[ii + 10]),(weight_out[ii + 11]), tmp_input3,temp_result3);
					temp_result4 = _vmac5((weight_out[ii + 12]),(weight_out[ii + 13]),(weight_out[ii + 14]),(weight_out[ii + 15]), tmp_input4,temp_result4);

				}


				temp_result1 = (temp_result1 + bias_vec + temp_result2 + temp_result3 +temp_result4);

				int2xN_t vec_lo = _vunpack_lo(temp_result1);
				int2xN_t vec_hi = _vunpack_hi(temp_result1);
				int4xN_t temp_result5 = _vpack(_vshiftr(vec_lo,shift_vec_lo),_vshiftr(vec_hi,shift_vec_hi));
				char4xN_t temp1 = _vcastc4n(_sat,_vcasts4n(_sat,temp_result5));

				int position000 = i*(output->width*o_c) + j*o_c + vec_part*16;
				memcpy(output->data_location+position000,&temp1,calcu_oc);
			}
		}
    }

    uint32_t end_time = TIMER0_END();
//	DSP_LOG("1x1_conv_dsp, %f M MACs, time cost is %f M cycles\n", 1.0*(i_c*o_c*output->width*output->height)/1000000, 1.0*(start_time - end_time)/1000000);
}

void conv_fr1x1xn(struct Uint8Tensor *input, struct Uint8Tensor *output, struct Structure *conv_params, struct ConvParameter *weight){
	
	uint32_t start_time = TIMER0_START();
    int32_t bias_local[1024] = {0};

    int bias_offset = conv_params->bias_offset;
    int bias_offset_per_channel_flag = conv_params->bias_offset_per_channel;

    if(conv_params->bias_flag){
        for(int s=0;s<output->channel;s++){
            if(bias_offset_per_channel_flag){
                bias_local[s] = ((int32_t)weight->bias[s] << weight->bias_offset_per_channel[s]);
            }
            else{
                bias_local[s] = ((int32_t)weight->bias[s] << bias_offset);
            }
        }
    }else{
		assert(input->channel == output->channel);
    }


    
	
    memset(buffer_conv_1024,0,1024*4);
    uint8_t tmp_kernel[1024] = {0};

    int *position_result = buffer_conv_1024;
    int step3 = input->width*input->channel;
    int channel_sum = 0, weight_index = 0;


    for(int i=0;i<output->height;i++){
        for(int j=0;j<output->width;j++){
            memcpy(tmp_kernel, input->data_location+i*(step3) + j * input->channel, input->channel);

            for(int k=0;k<output->channel;k++){
                channel_sum = 0;
                weight_index = k*input->channel;
                for(int f=0;f<input->channel;f++)
                    channel_sum += (int8_t)tmp_kernel[f] * (int8_t)weight->weight[weight_index+f];
                position_result[k] = channel_sum;
            }


            
            for(int s=0;s<output->channel;s++){
                position_result[s] += bias_local[s];
                int shift = (conv_params->offset_per_channel)?weight->offset_per_channel[s]:conv_params->offset;
                position_result[s] = ((position_result[s] + (1<<(shift-1))) >> shift);
            }

            int max=127,min=-128;
            int position000 = i*(output->width*output->channel) + j*(output->channel);

            for(int s=0;s<output->channel;s++){
                int kk = position000 + s;
                if(position_result[s] > max){
                    output->data_location[kk] = max;
                }else if(position_result[s] < min){
                    output->data_location[kk] = min;
                }else{
                    output->data_location[kk] = position_result[s];
                }
            }
        }
    }

    uint32_t end_time = TIMER0_END();
//    DSP_LOG("1x1_conv, %f M MACs, time cost is %f M cycles\n", 1.0*(input->channel*output->channel*output->width*output->height)/1000000, 1.0*(start_time - end_time)/1000000);
}
void conv_fr1x1xn_psram(struct Uint8Tensor *input, struct Uint8Tensor *output, struct Structure *conv_params, struct ConvParameter *weight){
	
	uint32_t start_time = TIMER0_START();
    int32_t bias_local[1024] = {0};

    int bias_offset = conv_params->bias_offset;
    int bias_offset_per_channel_flag = conv_params->bias_offset_per_channel;

    if(conv_params->bias_flag){
        for(int s=0;s<output->channel;s++){
            if(bias_offset_per_channel_flag){
                bias_local[s] = ((int32_t)weight->bias[s] << weight->bias_offset_per_channel[s]);
            }
            else{
                bias_local[s] = ((int32_t)weight->bias[s] << bias_offset);
            }
        }
    }else{
		assert(input->channel == output->channel);
    }
    memset(buffer_conv_1024,0,1024*4);
    uint8_t tmp_kernel[1024] = {0};
    uint8_t temp_buf[1024] = {0};

    int *position_result = buffer_conv_1024;
    int step3 = input->width*input->channel;
    int channel_sum = 0, weight_index = 0;


    for(int i=0;i<output->height;i++){
        for(int j=0;j<output->width;j++){
            memcpy(tmp_kernel, input->data_location+i*(step3) + j * input->channel, input->channel);
            DSP_LOG("tmp_psram_addr cpy start\n");
            for(int k=0;k<output->channel;k++){
                channel_sum = 0;
                weight_index = k*input->channel;
                uint32_t *temp_addr = (uint32_t *)temp_buf;
                uint32_t *tmp_psram_addr = (uint32_t *)(0x80000000 + weight_index);
                for (size_t i = 0; i < 256; i++)
                {
                    /* code */
                    temp_addr[i] = tmp_psram_addr[i];
                }
                for(int f=0;f<input->channel;f++)
                    channel_sum += (int8_t)tmp_kernel[f] * (int8_t)temp_buf[f];
                position_result[k] = channel_sum;
            }
            DSP_LOG("tmp_psram_addr cpy finish\n");

            
            for(int s=0;s<output->channel;s++){
                position_result[s] += bias_local[s];
                int shift = (conv_params->offset_per_channel)?weight->offset_per_channel[s]:conv_params->offset;
                position_result[s] = ((position_result[s] + (1<<(shift-1))) >> shift);
            }

            int max=127,min=-128;
            int position000 = i*(output->width*output->channel) + j*(output->channel);

            for(int s=0;s<output->channel;s++){
                int kk = position000 + s;
                if(position_result[s] > max){
                    output->data_location[kk] = max;
                }else if(position_result[s] < min){
                    output->data_location[kk] = min;
                }else{
                    output->data_location[kk] = position_result[s];
                }
            }




        }
    }



    uint32_t end_time = TIMER0_END();
//    DSP_LOG("1x1_conv, %f M MACs, time cost is %f M cycles\n", 1.0*(input->channel*output->channel*output->width*output->height)/1000000, 1.0*(start_time - end_time)/1000000);
}



void conv_fr_rgb(struct Uint8Tensor *input, struct Uint8Tensor *output, struct Structure *conv_params, struct ConvParameter *weight){

//	static int i = 0;
    uint32_t start_time = TIMER0_START();
    int position_h = 0;
    int position_w = 0;

    int kernel_h = conv_params->kernel_h;
    int kernel_w = conv_params->kernel_w;
    int bias_offset = conv_params->bias_offset;
    int bias_offset_per_channel_flag = conv_params->bias_offset_per_channel;

//    DSP_LOG("conv_fr_rgb %d \n", i++);

    memset(buffer_conv_u8,0,sizeof(buffer_conv_u8));
    memset(buffer_conv_1024,0,1024*4);

//    DSP_LOG("conv_fr_rgb %d \n", i++);

    uint8_t *tmp_kernel = buffer_conv_u8;

    int *position_result = buffer_conv_1024;

    int step1 = kernel_h * kernel_w * input->channel;
    int step2 = kernel_w*input->channel;
    int step3 = input->width*input->channel;

    int16_t weight_local[step1*output->channel];
    for(int i=0;i<step1*output->channel;i++){
        weight_local[i] = weight->weight[i];
    }

//    DSP_LOG("conv_fr_rgb %d \n", i++);


    int bias_local[64] = {0};
    for(int s=0;s<output->channel;s++){
        if(bias_offset_per_channel_flag){
            bias_local[s] = (weight->bias[s] << weight->bias_offset_per_channel[s]);
        }
        else{
            bias_local[s] = (weight->bias[s] << bias_offset);
        }
    }

//    DSP_LOG("conv_fr_rgb %d \n", i++);


    for(int i=0;i<output->height;i++){
        for(int j=0;j<output->width;j++){   
            memset(tmp_kernel, 0, 27);
            for(int s=0;s<3;s++){
                for(int t=0;t<3;t++){
//                	DSP_LOG("conv_fr_rgb i=%d j=%d s=%d t=%d \n", i, j, s, t);
                    position_h = i * conv_params->stride_h + s - conv_params->pad_h;
                    position_w = j * conv_params->stride_w + t - conv_params->pad_w;
                    
                    if(position_h < 0 || position_w < 0 || position_h >= input->height || position_w >= input->width){
                        continue;
                    }
                    else{
                        int data_index = position_h*(step3) + position_w * input->channel;
//                        DSP_LOG("tmp_kernel addr %p\n", tmp_kernel);
                        memcpy(tmp_kernel + s*9 + t*3,input->data_location+data_index,3);
                    }

                }
            }

            
            for(int s=0;s<output->channel;s++){
                int temp = 0;
                int ssss = 27*s;
                for(int t=0;t<step1;t++){
                    temp += (int8_t)(tmp_kernel[t]) * (int8_t)weight->weight[ssss+t];
                }
                position_result[s] = temp;
            } 
            
            int position000 = i*(output->width*output->channel) + j*(output->channel);

            for(int s=0;s<output->channel;s++){
                position_result[s] = position_result[s] + bias_local[s];
                int shift = weight->offset_per_channel[s];
                position_result[s] = ((position_result[s] + (1<<(shift-1))) >> shift);
                position_result[s] = (position_result[s]>-128)?position_result[s]:-128;
                output->data_location[position000 + s] = (position_result[s]<127)?position_result[s]:127;
            }
        }
    }
	uint32_t end_time = TIMER0_END();
//    DSP_LOG("rgb_conv, %f M MACs, time cost is %f M cycles\n", 1.0*(9*input->channel*output->channel*output->width*output->height)/1000000, 1.0*(start_time - end_time)/1000000);
}




void conv_rgb_dsp(struct Uint8Tensor *input, struct Uint8Tensor *output, struct Structure *conv_params, struct ConvParameter *weight){

    uint32_t start_time = TIMER0_START();
	int o_c = output->channel;

	assert(output->channel == 24);
    short temp_weight[32] = {0};
    short4xN_t weight_vec[56];

    for (int j=0;j<27;j++){//27
        for(int i=0;i<24;i++){//24
            temp_weight[i] = weight->weight[i*27+j];
        }
        weight_vec[j] = *(short4xN_t*)(temp_weight);
		weight_vec[27+j] = *(short4xN_t*)(temp_weight+16);
    }

	int bias_offset = conv_params->bias_offset;
    int bias_offset_per_channel_flag = conv_params->bias_offset_per_channel;
    int bias_local[24] = {0};
	for(int s=0;s<output->channel;s++){
		if(bias_offset_per_channel_flag){
			bias_local[s] = (weight->bias[s] << weight->bias_offset_per_channel[s]) + (1<<(weight->offset_per_channel[s]-1));
		}
		else{
			bias_local[s] = (weight->bias[s] << bias_offset)+ (1<<(weight->offset_per_channel[s]-1));
		}
	}

	int4xN_t bias_vec0 = *(int4xN_t*)bias_local;
	int4xN_t bias_vec1 = *(int4xN_t*)(bias_local+16);

	unsigned int temp_shift_lo[8] ={0};
	unsigned int temp_shift_hi[8] ={0};
	for(int i=0;i<8;i++){
		temp_shift_lo[i] = (unsigned int)weight->offset_per_channel[i];
	}
	for(int i=8;i<16;i++){
		temp_shift_hi[i-8] = (unsigned int)weight->offset_per_channel[i];
	}
    uint2xN_t shift_vec_lo0 = *(uint2xN_t*)temp_shift_lo;
    uint2xN_t shift_vec_hi0 = *(uint2xN_t*)temp_shift_hi;

	for(int i=16;i<24;i++){
		temp_shift_lo[i] = (unsigned int)weight->offset_per_channel[i];
	}
    uint2xN_t shift_vec_lo1 = *(uint2xN_t*)temp_shift_lo;

	char tmp_kernel[28] = {0};
	int input_step0 = input->width*input->channel;

	for(int i=0;i<output->height;i++){
        for(int j=0;j<output->width;j++){
			memset(tmp_kernel, 0, 28);
			memset(tmp_kernel, 0, 28);
            if(i == 0 && j == 0){
                for(int s=1;s<3;s++){
                    for(int t=1;t<3;t++){
                        int position_h = s - conv_params->pad_h;
                        int position_w = t - conv_params->pad_w;
                        int data_index = position_h*(input_step0) + position_w * input->channel;
                        memcpy(tmp_kernel + s*9 + t*3,input->data_location+data_index,3);
                    }
                }
            }else if(i == 0 && j != 0){
                int position_h1 = 1 - conv_params->pad_h;
                int position_h2 = 2 - conv_params->pad_h;
                int position_w = j * conv_params->stride_w - conv_params->pad_w;
                int data_index1 = position_h1*(input_step0) + position_w * input->channel;
                int data_index2 = position_h2*(input_step0) + position_w * input->channel;
                memcpy(tmp_kernel + 9,input->data_location+data_index1,9);
                memcpy(tmp_kernel + 18,input->data_location+data_index2,9);

            }else if(i != 0 && j == 0){
                int position_h1 = i * conv_params->stride_h + 0 - conv_params->pad_h;
                int position_h2 = i * conv_params->stride_h + 1 - conv_params->pad_h;
                int position_h3 = i * conv_params->stride_h + 2 - conv_params->pad_h;
                int position_w = 1 - conv_params->pad_w;

                int data_index = position_h1*(input_step0) + position_w * input->channel;
                memcpy(tmp_kernel + 3,input->data_location+data_index,6);
                data_index = position_h2*(input_step0) + position_w * input->channel;
                memcpy(tmp_kernel + 12,input->data_location+data_index,6);
                data_index = position_h3*(input_step0) + position_w * input->channel;
                memcpy(tmp_kernel + 21,input->data_location+data_index,6);

            }else{
                int position_h1 = i * conv_params->stride_h + 0 - conv_params->pad_h;
                int position_h2 = i * conv_params->stride_h + 1 - conv_params->pad_h;
                int position_h3 = i * conv_params->stride_h + 2 - conv_params->pad_h;
                int position_w = j * conv_params->stride_w + 0 - conv_params->pad_w;
                int data_index = position_h1*(input_step0) + position_w * input->channel;
                memcpy(tmp_kernel + 0,input->data_location+data_index,9);
                data_index = position_h2*(input_step0) + position_w * input->channel;
                memcpy(tmp_kernel + 9,input->data_location+data_index,9);
                data_index = position_h3*(input_step0) + position_w * input->channel;
                memcpy(tmp_kernel + 18,input->data_location+data_index,9);
            }

			int4xN_t temp_result0 = bias_vec0;
			int4xN_t temp_result1 = bias_vec1;
			for(int k=0;k<27;k++){
				temp_result0 = _vmac(weight_vec[k],tmp_kernel[k],temp_result0);
				temp_result1 = _vmac(weight_vec[27+k],tmp_kernel[k],temp_result1);

			}

			int2xN_t vec_lo = _vunpack_lo(temp_result0);
			int2xN_t vec_hi = _vunpack_hi(temp_result0);
			int4xN_t temp_result5 = _vpack(_vshiftr(vec_lo,shift_vec_lo0),_vshiftr(vec_hi,shift_vec_hi0));
			short4xN_t temp0 = _vcasts4n(_sat,temp_result5);
			char4xN_t temp1 = _vcastc4n(_sat, temp0);
			int position000 = i*(output->width*output->channel) + j*(output->channel);
            memcpy(output->data_location+position000,&temp1,16);

			vec_lo = _vunpack_lo(temp_result1);
			temp_result5 = _vpack(_vshiftr(vec_lo,shift_vec_lo1),_vshiftr(vec_hi,shift_vec_hi0));
			temp0 = _vcasts4n(_sat,temp_result5);
			temp1 = _vcastc4n(_sat, temp0);
			position000 = i*(output->width*output->channel) + j*(output->channel) + 16;
            memcpy(output->data_location+position000,&temp1,8);



		}
    }
	uint32_t end_time = TIMER0_END();
//    DSP_LOG("rgb_conv, %f M MACs, time cost is %f M cycles\n", 1.0*(9*input->channel*output->channel*output->width*output->height)/1000000, 1.0*(start_time - end_time)/1000000);
}



void conv_dp_dsp(struct Uint8Tensor *input, struct Uint8Tensor *output, struct Structure *conv_params, struct ConvParameter *weight){
	uint32_t start_time = TIMER0_START();

	int i_c = input->channel;
	int o_c = output->channel;
	
	assert(i_c == o_c);
	assert(i_c == 24 || i_c == 48 || i_c == 96);
	assert(conv_params->kernel_h == 3);
	assert(conv_params->kernel_w == 3);
	assert(conv_params->pad_h == 1);
	assert(conv_params ->depth_wise_flag == 1);
	assert(conv_params->nonlinear == 0);

	int stride = conv_params->stride_h;
	int padding = conv_params->pad_h;
	int input_step0 = input->width*input->channel;


	for(int v = 0; v < (o_c+15)/ 16; v++){

		int calcu_oc = 16;
		if(o_c == 24 && v == 1) calcu_oc = 8;

		short temp_weight[16] = {0};
		int bias_local[16] = {0};
		short4xN_t weight_vec[9];

		for (int j=0;j<9;j++){
			for(int i=0;i<calcu_oc;i++){
				temp_weight[i] = (short)weight->weight[j*i_c + i + 16*v];
			}
			weight_vec[j] = *(short4xN_t*)temp_weight;
		}

//注意stride的处理，目标地址在源地址*stride-padding 开始 比如目标地址是1，源地址就是1*2-1 = 1 开始，123这三个

		int bias_offset = conv_params->bias_offset;
		int bias_offset_per_channel_flag = conv_params->bias_offset_per_channel;


		for(int s=0;s<calcu_oc;s++){
			if(bias_offset_per_channel_flag){
				bias_local[s] = (weight->bias[v*16 + s] << weight->bias_offset_per_channel[v*16 + s]) + (1<<(weight->offset_per_channel[v*16 + s]-1));
			}
			else{
				bias_local[s] = (weight->bias[v*16 + s] << bias_offset)+ (1<<(weight->offset_per_channel[v*16 + s]-1));
			}
		}

		int4xN_t bias_vec = *(int4xN_t*)bias_local;

		unsigned int temp_shift_lo[8] ={0};
		unsigned int temp_shift_hi[8] ={0};
		for(int i=0;(i<8 && v*16 + i < i_c);i++){
			temp_shift_lo[i] = (unsigned int)weight->offset_per_channel[v*16 + i];
		}
		for(int i=0;(i<8 && v*16 + i + 8 < i_c);i++){
			temp_shift_hi[i] = (unsigned int)weight->offset_per_channel[v*16 + i + 8];
		}
		uint2xN_t shift_vec_lo = *(uint2xN_t*)temp_shift_lo;
		uint2xN_t shift_vec_hi = *(uint2xN_t*)temp_shift_hi;


		

		for(int i=0;i<output->height;i++){
			for(int j=0;j<output->width;j++){
				int4xN_t temp_result1 = {0};
				int4xN_t temp_result2 = {0};
				int4xN_t temp_result3 = {0};
				if(input->type == 1){
					if(!(i == 0 || i == output->height-1 || j == 0 || j == output->width-1)){
						for(int s=0;s<3;s++){
							int ss = i*stride - padding + s;
							int step_temp = ss*(input_step0) + v*16;

							temp_result1 = _vmac( *(char4xN_t*)(input->data_location + step_temp + (j* stride + 0 - padding)*  i_c ),(weight_vec[s*3]), temp_result1);
							temp_result2 = _vmac( *(char4xN_t*)(input->data_location + step_temp + (j* stride + 1 - padding)  *  i_c),(weight_vec[s*3+1]), temp_result2);
							temp_result3 = _vmac( *(char4xN_t*)(input->data_location + step_temp + (j* stride + 2 - padding) *  i_c),(weight_vec[s*3+2]), temp_result3);

						}
						temp_result1 = temp_result1 + temp_result2 +temp_result3;
					}
					else{
						for(int s=0;s<3;s++){
							int ss = i*stride - padding + s;
							if( ss < 0 ||ss >= input->height )
								continue;
							int step_temp = ss*(input_step0) + v*16;
							for(int t=0;t<3;t++){
								int tt = j* stride - padding + t;
								if( tt <0 ||tt >= input->width)
									continue;
								temp_result1 = _vmac( *(char4xN_t*)(input->data_location + step_temp + tt *  i_c),(weight_vec[s*3+t]), temp_result1);


							}
						}
					}
				}else{
					if(!(i == 0 || i == output->height-1 || j == 0 || j == output->width-1)){
						for(int s=0;s<3;s++){
							int ss = i*stride - padding + s;
							int step_temp = ss*(input_step0) + v*16;

							temp_result1 = _vmac( *(uchar4xN_t*)(input->data_location + step_temp + (j* stride + 0 - padding)*  i_c ),(weight_vec[s*3]), temp_result1);
							temp_result2 = _vmac( *(uchar4xN_t*)(input->data_location + step_temp + (j* stride + 1 - padding)  *  i_c),(weight_vec[s*3+1]), temp_result2);
							temp_result3 = _vmac( *(uchar4xN_t*)(input->data_location + step_temp + (j* stride + 2 - padding) *  i_c),(weight_vec[s*3+2]), temp_result3);

						}
						temp_result1 = temp_result1 + temp_result2 +temp_result3;
					}
					else{
						for(int s=0;s<3;s++){
							int ss = i*stride - padding + s;
							if( ss < 0 ||ss >= input->height )
								continue;
							int step_temp = ss*(input_step0) + v*16;
							for(int t=0;t<3;t++){
								int tt = j* stride - padding + t;
								if( tt <0 ||tt >= input->width)
									continue;
								temp_result1 = _vmac( *(uchar4xN_t*)(input->data_location + step_temp + tt *  i_c),(weight_vec[s*3+t]), temp_result1);


							}
						}
					}

				}


				temp_result1 += (bias_vec);


				int2xN_t vec_lo = _vunpack_lo(temp_result1);
				int2xN_t vec_hi = _vunpack_hi(temp_result1);

				int4xN_t temp_result5 = _vpack(_vshiftr(vec_lo,shift_vec_lo),_vshiftr(vec_hi,shift_vec_hi));
				int position000 = i*(output->width*o_c) + j*(o_c) + v*16;

				if(conv_params->nonlinear == 1){
					uchar4xN_t temp1 = _vcastuc4n(_sat,_vcasts4n(_sat,temp_result5));
					memcpy(output->data_location+position000,&temp1,calcu_oc);
				}
				else{
					char4xN_t temp1 = _vcastc4n(_sat,_vcasts4n(_sat,temp_result5));
					memcpy(output->data_location+position000,&temp1,calcu_oc);
				}




			}
		}
	}
	uint32_t end_time = TIMER0_END();

//	DSP_LOG("dp_dsp_conv, %f M MACs, time cost is %f M cycles\n", 1.0*(9*input->channel*output->width*output->height)/1000000, 1.0*(start_time - end_time)/1000000);


}


void conv_fr(struct Uint8Tensor *input, struct Uint8Tensor *output, struct Structure *conv_params, struct ConvParameter *weight){
    //中间过程先存放为int32,如果后面需要转int8或者uint8,再强制转
	uint32_t start_time = TIMER0_START();

    int position_h = 0;
    int position_w = 0;
    
    int kernel_h = conv_params->kernel_h;
    int kernel_w = conv_params->kernel_w;
    int bias_flag = conv_params->bias_flag;
    
    int offset_per_channel_flag = conv_params->offset_per_channel;
    int bias_offset = conv_params->bias_offset;
    int bias_offset_per_channel_flag = conv_params->bias_offset_per_channel;

	assert(conv_params->depth_wise_flag);

    //这用来存放卷积的中间值
    int *tmp_kernel = NULL;
    if(!(conv_params->depth_wise_flag))
        tmp_kernel = (int*)malloc(output->channel * kernel_h * kernel_w * input->channel*sizeof(int));
    else
        tmp_kernel = (int*)malloc(kernel_h * kernel_w * input->channel*sizeof(int));
    
	


    int *position_result = (int*)malloc(output->channel*sizeof(int));
    for(int i=0;i<output->channel;i++) position_result[i] = 0;


    for(int i=0;i<output->height;i++){
        for(int j=0;j<output->width;j++){   

            //if it is not depth wise conv 这个对应的就是全卷积
            if(!(conv_params->depth_wise_flag)){
                //先生成全卷积的内核对应的一片内存
                int size_kernel = output->channel * kernel_h * kernel_w * input->channel;
                for(int k=0;k<size_kernel;k++){
                    tmp_kernel[k] = 0;
                }

                for(int s=0;s<kernel_h;s++){
                    for(int t=0;t<kernel_w;t++){
                        position_h = i * conv_params->stride_h + s - conv_params->pad_h;
                        position_w = j * conv_params->stride_w + t - conv_params->pad_w;
                        
                        if(position_h < 0 || position_w < 0 || position_h >= input->height || position_w >= input->width){
                            continue;
                        }

                        else{
                            for(int m=0;m<output->channel;m++){
                                for(int n=0;n<input->channel;n++){
                                    if(input->type == 1)
                                        tmp_kernel[m*(kernel_h * kernel_w * input->channel) + s*(kernel_w*input->channel) + t*input->channel + n] = (int8_t)input->data_location[position_h*(input->width*input->channel) + position_w * input->channel + n];
                                    else
                                        tmp_kernel[m*(kernel_h * kernel_w * input->channel) + s*(kernel_w*input->channel) + t*input->channel + n] = (uint8_t)input->data_location[position_h*(input->width*input->channel) + position_w * input->channel + n];
                                }
                            }
                        }
                    }
                }
                //然后用这个内存做点乘后放到对应位置
                for(int s=0;s<output->channel;s++){
                    int temp = 0;
                    for(int t=0;t<kernel_h*kernel_w*input->channel;t++){
                        int index = s*kernel_h*kernel_w*input->channel + t;
                        temp += tmp_kernel[index] * weight->weight[index];
                    }
                    position_result[s] = temp;
                } 
            }
            //这里对应的是depthwise卷积
            else{
                memset(tmp_kernel,0,sizeof(int)*output->channel * kernel_h * kernel_w);
                //既是depthwise卷积，那么输入channel一定和输出channel相同
                //assert(input->channel == output->channel);
                for(int s=0;s<kernel_h;s++){
                    for(int t=0;t<kernel_w;t++){
                        position_h = i * conv_params->stride_h + s - conv_params->pad_h;
                        position_w = j * conv_params->stride_w + t - conv_params->pad_w;
                        if(position_h < 0 || position_w < 0 || position_h >= input->height || position_w >= input->width){
                        }
                        else{
                            for(int n=0;n<input->channel;n++){
                                if(input->type == 1)
                                    tmp_kernel[s*(kernel_w*input->channel) + t*(input->channel) + n] = (int8_t)input->data_location[position_h*(input->width*input->channel) + position_w * input->channel + n];
                                else
                                    tmp_kernel[s*(kernel_w*input->channel) + t*(input->channel) + n] = (uint8_t)input->data_location[position_h*(input->width*input->channel) + position_w * input->channel + n];
                                
                            }
                        }
                        
                    }
                    //DSP_LOG("\n");
                }
                
                //然后用这个内存做点乘后放到对应位置
                for(int s=0;s<output->channel;s++){
                    int temp = 0;
                    for(int t=0;t<kernel_h*kernel_w;t++){
                        int index = t*(output->channel) + s;
                        temp += tmp_kernel[index] * weight->weight[index];
                    }
                    position_result[s] = temp;
                    //DSP_LOG("%d,",position_result[s]);
                }
                
            }
            if(bias_flag){
                if(bias_offset_per_channel_flag){
                    for(int s=0;s<output->channel;s++){
                        position_result[s] = position_result[s] + (weight->bias[s] << weight->bias_offset_per_channel[s]);
                    }
                }
                else{
                    for(int s=0;s<output->channel;s++){
                        position_result[s] = position_result[s] + (weight->bias[s] << bias_offset);
                    }
                }
            }
            //relu
            if(conv_params->nonlinear == 1){
                for(int s=0;s<output->channel;s++){
                    position_result[s] = (position_result[s]>0)?position_result[s]:0;
                }
            }  
            // for(int s=0;s<output->channel;s++){
            //     DSP_LOG("%d,",position_result[s]);
            // }
            // DSP_LOG("\n");

            if(offset_per_channel_flag){
                for(int s=0;s<output->channel;s++){
                    int shift = weight->offset_per_channel[s];
                    position_result[s] = ((position_result[s] + (1<<(shift-1))) >> shift);
                }
            }else{
                for(int s=0;s<output->channel;s++){
                    int shift = conv_params->offset;
                    position_result[s] = ((position_result[s] + (1<<(shift-1))) >> shift);
                }
            }


            int min = 0,max=255;
            if(output->type == 1){
                min = -128;
                max = 127;
            }

            //把输出按照逐channel的方式写到输出
            for(int s=0;s<output->channel;s++){
                
                int temp0 = position_result[s];

                if (temp0 > max) 
                    temp0 = max;
                else if(temp0 < min) 
                    temp0 = min;
                
                output->data_location[i*(output->width*output->channel) + j*(output->channel) + s] = (int8_t)temp0;
            }

        }
    }
    free(tmp_kernel);
    free(position_result); 

	uint32_t end_time = TIMER0_END();
//    DSP_LOG("fr_conv, %f M MACs, time cost is %f M cycles\n", 1.0*(9*output->channel*output->width*output->height)/1000000, 1.0*(start_time - end_time)/1000000);

}



// Simple square root approximation (Newton's method)
static float dsp_sqrtf(float number) {
    if (number <= 0.0f) return 0.0f;
    float x = number;
    float y = 1.0f;
    float e = 0.00001f; // Precision
    while (x - y > e) {
        x = (x + y) / 2.0f;
        y = number / x;
    }
    return x;
}

int fr_run(int8_t* result, uint8_t *rgb_data){
	struct Structure structure_conv1 = {24, 3, 3, 1, 1, 2, 2, 1, 0, 0, 0, 0, 1, 0, 1};
	struct Structure structure_conv2 = {24, 3, 3, 1, 1, 2, 2, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv3 = {24, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv4 = {24, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv5 = {24, 3, 3, 1, 1, 2, 2, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv6 = {24, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split1_sec1 = {24, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_split1_sec2 = {24, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv8 = {24, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv9 = {24, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv10 = {24, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split2_sec1 = {24, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 6, 0, 0, 0};
	struct Structure structure_split2_sec2 = {24, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv12 = {24, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv13 = {24, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv14 = {24, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split3_sec1 = {24, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_split3_sec2 = {24, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv16 = {24, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv17 = {24, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv18 = {24, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv19 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv20 = {48, 3, 3, 1, 1, 2, 2, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv21 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv22 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv23 = {48, 3, 3, 1, 1, 2, 2, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv24 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split4_sec1 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_split4_sec2 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 6, 0, 0, 0};
	struct Structure structure_conv26 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1};
	struct Structure structure_conv27 = {48, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv28 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split5_sec1 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_split5_sec2 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv30 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv31 = {48, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv32 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split6_sec1 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_split6_sec2 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv34 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv35 = {48, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv36 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split7_sec1 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_split7_sec2 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv38 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv39 = {48, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv40 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split8_sec1 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 6, 0, 0, 0};
	struct Structure structure_split8_sec2 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv42 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv43 = {48, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv44 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split9_sec1 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_split9_sec2 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv46 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv47 = {48, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv48 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split10_sec1 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_split10_sec2 = {48, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv50 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv51 = {48, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv52 = {48, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv53 = {96, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv54 = {96, 3, 3, 1, 1, 2, 2, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv55 = {96, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv56 = {96, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv57 = {96, 3, 3, 1, 1, 2, 2, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv58 = {96, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split11_sec1 = {96, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_split11_sec2 = {96, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv60 = {96, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1};
	struct Structure structure_conv61 = {96, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv62 = {96, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split12_sec1 = {96, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_split12_sec2 = {96, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv64 = {96, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv65 = {96, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv66 = {96, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_split13_sec1 = {96, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_split13_sec2 = {96, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv68 = {96, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv69 = {96, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv70 = {96, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv71 = {192, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0};
	struct Structure structure_conv72 = {1024, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1};
	struct Structure structure_conv73 = {1024, 5, 5, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1};
	struct Structure structure_conv74 = {1024, 3, 3, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv1d1 = {128, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0};
	struct Structure structure_conv_bn1 = {128, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 7, 0, 0, 0};
	struct ConvParameter weight_conv1 = {{24, 3, 3, 3},24,24,24,fr_conv1_weight,fr_conv1_bias,fr_conv1_offset,fr_conv1_bias_offset};
	struct LookupParameter params_prelu1 = {{56,56,24},1,1,fr_prelu1_lookup};
	struct ConvParameter weight_conv2 = {{1, 3, 3, 24},24,24,24,fr_conv2_weight,fr_conv2_bias,fr_conv2_offset,NULL};
	struct ConvParameter weight_conv3 = {{24, 1, 1, 24},24,24,24,fr_conv3_weight,fr_conv3_bias,fr_conv3_offset,NULL};
	struct LookupParameter params_prelu2 = {{28,28,24},1,0,fr_prelu2_lookup};
	struct ConvParameter weight_conv4 = {{24, 1, 1, 24},24,24,24,fr_conv4_weight,fr_conv4_bias,fr_conv4_offset,NULL};
	struct LookupParameter params_prelu3 = {{56,56,24},1,1,fr_prelu3_lookup};
	struct ConvParameter weight_conv5 = {{1, 3, 3, 24},24,24,24,fr_conv5_weight,fr_conv5_bias,fr_conv5_offset,NULL};
	struct ConvParameter weight_conv6 = {{24, 1, 1, 24},24,24,24,fr_conv6_weight,fr_conv6_bias,fr_conv6_offset,NULL};
	struct LookupParameter params_prelu4 = {{28,28,24},1,1,fr_prelu4_lookup};
	struct ConcatParams params_concat1 = {28,28,24,28,28,24,0,1,117,1,8,0,28,28,48,1};
	struct ConvParameter weight_split1_sec1 = {{24, 1, 1, 48},0,24,24,split_index11,NULL,NULL,NULL};
	struct ConvParameter weight_split1_sec2 = {{24, 1, 1, 48},0,24,24,split_index12,NULL,NULL,NULL};
	struct ConvParameter weight_conv8 = {{24, 1, 1, 24},24,24,24,fr_conv8_weight,fr_conv8_bias,fr_conv8_offset,NULL};
	struct LookupParameter params_prelu5 = {{28,28,24},1,1,fr_prelu5_lookup};
	struct ConvParameter weight_conv9 = {{1, 3, 3, 24},24,24,24,fr_conv9_weight,fr_conv9_bias,fr_conv9_offset,NULL};
	struct ConvParameter weight_conv10 = {{24, 1, 1, 24},24,24,24,fr_conv10_weight,fr_conv10_bias,fr_conv10_offset,NULL};
	struct LookupParameter params_prelu6 = {{28,28,24},1,1,fr_prelu6_lookup};
	struct ConcatParams params_concat2 = {28,28,24,28,28,24,1,1,1,222,0,8,28,28,48,1};
	struct ConvParameter weight_split2_sec1 = {{24, 1, 1, 48},0,24,24,split_index11,NULL,NULL,NULL};
	struct ConvParameter weight_split2_sec2 = {{24, 1, 1, 48},0,24,24,split_index12,NULL,NULL,NULL};
	struct ConvParameter weight_conv12 = {{24, 1, 1, 24},24,24,24,fr_conv12_weight,fr_conv12_bias,fr_conv12_offset,NULL};
	struct LookupParameter params_prelu7 = {{28,28,24},1,1,fr_prelu7_lookup};
	struct ConvParameter weight_conv13 = {{1, 3, 3, 24},24,24,24,fr_conv13_weight,fr_conv13_bias,fr_conv13_offset,NULL};
	struct ConvParameter weight_conv14 = {{24, 1, 1, 24},24,24,24,fr_conv14_weight,fr_conv14_bias,fr_conv14_offset,NULL};
	struct LookupParameter params_prelu8 = {{28,28,24},1,1,fr_prelu8_lookup};
	struct ConcatParams params_concat3 = {28,28,24,28,28,24,1,1,189,245,8,8,28,28,48,1};
	struct ConvParameter weight_split3_sec1 = {{24, 1, 1, 48},0,24,24,split_index11,NULL,NULL,NULL};
	struct ConvParameter weight_split3_sec2 = {{24, 1, 1, 48},0,24,24,split_index12,NULL,NULL,NULL};
	struct ConvParameter weight_conv16 = {{24, 1, 1, 24},24,24,24,fr_conv16_weight,fr_conv16_bias,fr_conv16_offset,NULL};
	struct LookupParameter params_prelu9 = {{28,28,24},1,1,fr_prelu9_lookup};
	struct ConvParameter weight_conv17 = {{1, 3, 3, 24},24,24,24,fr_conv17_weight,fr_conv17_bias,fr_conv17_offset,NULL};
	struct ConvParameter weight_conv18 = {{24, 1, 1, 24},24,24,24,fr_conv18_weight,fr_conv18_bias,fr_conv18_offset,NULL};
	struct LookupParameter params_prelu10 = {{28,28,24},1,1,fr_prelu10_lookup};
	struct ConcatParams params_concat4 = {28,28,24,28,28,24,1,1,1,166,0,8,28,28,48,1};
	struct ConvParameter weight_conv19 = {{48, 1, 1, 48},0,48,48,index19,NULL,NULL,NULL};
	struct ConvParameter weight_conv20 = {{1, 3, 3, 48},48,48,48,fr_conv20_weight,fr_conv20_bias,fr_conv20_offset,NULL};
	struct ConvParameter weight_conv21 = {{48, 1, 1, 48},48,48,48,fr_conv21_weight,fr_conv21_bias,fr_conv21_offset,NULL};
	struct LookupParameter params_prelu11 = {{14,14,48},1,1,fr_prelu11_lookup};
	struct ConvParameter weight_conv22 = {{48, 1, 1, 48},48,48,48,fr_conv22_weight,fr_conv22_bias,fr_conv22_offset,NULL};
	struct LookupParameter params_prelu12 = {{28,28,48},1,0,fr_prelu12_lookup};
	struct ConvParameter weight_conv23 = {{1, 3, 3, 48},48,48,48,fr_conv23_weight,fr_conv23_bias,fr_conv23_offset,NULL};
	struct ConvParameter weight_conv24 = {{48, 1, 1, 48},48,48,48,fr_conv24_weight,fr_conv24_bias,fr_conv24_offset,NULL};
	struct LookupParameter params_prelu13 = {{14,14,48},1,1,fr_prelu13_lookup};
	struct ConcatParams params_concat5 = {14,14,48,14,14,48,1,1,1,189,0,8,14,14,96,1};
	struct ConvParameter weight_split4_sec1 = {{48, 1, 1, 96},0,48,48,split_index21,NULL,NULL,NULL};
	struct ConvParameter weight_split4_sec2 = {{48, 1, 1, 96},0,48,48,split_index22,NULL,NULL,NULL};
	struct ConvParameter weight_conv26 = {{48, 1, 1, 48},48,48,48,fr_conv26_weight,fr_conv26_bias,fr_conv26_offset,fr_conv26_bias_offset};
	struct LookupParameter params_prelu14 = {{14,14,48},1,1,fr_prelu14_lookup};
	struct ConvParameter weight_conv27 = {{1, 3, 3, 48},48,48,48,fr_conv27_weight,fr_conv27_bias,fr_conv27_offset,NULL};
	struct ConvParameter weight_conv28 = {{48, 1, 1, 48},48,48,48,fr_conv28_weight,fr_conv28_bias,fr_conv28_offset,NULL};
	struct LookupParameter params_prelu15 = {{14,14,48},1,1,fr_prelu15_lookup};
	struct ConcatParams params_concat6 = {14,14,48,14,14,48,1,1,1,213,0,8,14,14,96,1};
	struct ConvParameter weight_split5_sec1 = {{48, 1, 1, 96},0,48,48,split_index21,NULL,NULL,NULL};
	struct ConvParameter weight_split5_sec2 = {{48, 1, 1, 96},0,48,48,split_index22,NULL,NULL,NULL};
	struct ConvParameter weight_conv30 = {{48, 1, 1, 48},48,48,48,fr_conv30_weight,fr_conv30_bias,fr_conv30_offset,NULL};
	struct LookupParameter params_prelu16 = {{14,14,48},1,1,fr_prelu16_lookup};
	struct ConvParameter weight_conv31 = {{1, 3, 3, 48},48,48,48,fr_conv31_weight,fr_conv31_bias,fr_conv31_offset,NULL};
	struct ConvParameter weight_conv32 = {{48, 1, 1, 48},48,48,48,fr_conv32_weight,fr_conv32_bias,fr_conv32_offset,NULL};
	struct LookupParameter params_prelu17 = {{14,14,48},1,1,fr_prelu17_lookup};
	struct ConcatParams params_concat7 = {14,14,48,14,14,48,1,1,1,218,0,8,14,14,96,1};
	struct ConvParameter weight_split6_sec1 = {{48, 1, 1, 96},0,48,48,split_index21,NULL,NULL,NULL};
	struct ConvParameter weight_split6_sec2 = {{48, 1, 1, 96},0,48,48,split_index22,NULL,NULL,NULL};
	struct ConvParameter weight_conv34 = {{48, 1, 1, 48},48,48,48,fr_conv34_weight,fr_conv34_bias,fr_conv34_offset,NULL};
	struct LookupParameter params_prelu18 = {{14,14,48},1,1,fr_prelu18_lookup};
	struct ConvParameter weight_conv35 = {{1, 3, 3, 48},48,48,48,fr_conv35_weight,fr_conv35_bias,fr_conv35_offset,NULL};
	struct ConvParameter weight_conv36 = {{48, 1, 1, 48},48,48,48,fr_conv36_weight,fr_conv36_bias,fr_conv36_offset,NULL};
	struct LookupParameter params_prelu19 = {{14,14,48},1,1,fr_prelu19_lookup};
	struct ConcatParams params_concat8 = {14,14,48,14,14,48,1,1,1,252,0,8,14,14,96,1};
	struct ConvParameter weight_split7_sec1 = {{48, 1, 1, 96},0,48,48,split_index21,NULL,NULL,NULL};
	struct ConvParameter weight_split7_sec2 = {{48, 1, 1, 96},0,48,48,split_index22,NULL,NULL,NULL};
	struct ConvParameter weight_conv38 = {{48, 1, 1, 48},48,48,48,fr_conv38_weight,fr_conv38_bias,fr_conv38_offset,NULL};
	struct LookupParameter params_prelu20 = {{14,14,48},1,1,fr_prelu20_lookup};
	struct ConvParameter weight_conv39 = {{1, 3, 3, 48},48,48,48,fr_conv39_weight,fr_conv39_bias,fr_conv39_offset,NULL};
	struct ConvParameter weight_conv40 = {{48, 1, 1, 48},48,48,48,fr_conv40_weight,fr_conv40_bias,fr_conv40_offset,NULL};
	struct LookupParameter params_prelu21 = {{14,14,48},1,1,fr_prelu21_lookup};
	struct ConcatParams params_concat9 = {14,14,48,14,14,48,1,1,254,1,8,0,14,14,96,1};
	struct ConvParameter weight_split8_sec1 = {{48, 1, 1, 96},0,48,48,split_index21,NULL,NULL,NULL};
	struct ConvParameter weight_split8_sec2 = {{48, 1, 1, 96},0,48,48,split_index22,NULL,NULL,NULL};
	struct ConvParameter weight_conv42 = {{48, 1, 1, 48},48,48,48,fr_conv42_weight,fr_conv42_bias,fr_conv42_offset,NULL};
	struct LookupParameter params_prelu22 = {{14,14,48},1,1,fr_prelu22_lookup};
	struct ConvParameter weight_conv43 = {{1, 3, 3, 48},48,48,48,fr_conv43_weight,fr_conv43_bias,fr_conv43_offset,NULL};
	struct ConvParameter weight_conv44 = {{48, 1, 1, 48},48,48,48,fr_conv44_weight,fr_conv44_bias,fr_conv44_offset,NULL};
	struct LookupParameter params_prelu23 = {{14,14,48},1,1,fr_prelu23_lookup};
	struct ConcatParams params_concat10 = {14,14,48,14,14,48,1,1,164,1,8,0,14,14,96,1};
	struct ConvParameter weight_split9_sec1 = {{48, 1, 1, 96},0,48,48,split_index21,NULL,NULL,NULL};
	struct ConvParameter weight_split9_sec2 = {{48, 1, 1, 96},0,48,48,split_index22,NULL,NULL,NULL};
	struct ConvParameter weight_conv46 = {{48, 1, 1, 48},48,48,48,fr_conv46_weight,fr_conv46_bias,fr_conv46_offset,NULL};
	struct LookupParameter params_prelu24 = {{14,14,48},1,1,fr_prelu24_lookup};
	struct ConvParameter weight_conv47 = {{1, 3, 3, 48},48,48,48,fr_conv47_weight,fr_conv47_bias,fr_conv47_offset,NULL};
	struct ConvParameter weight_conv48 = {{48, 1, 1, 48},48,48,48,fr_conv48_weight,fr_conv48_bias,fr_conv48_offset,NULL};
	struct LookupParameter params_prelu25 = {{14,14,48},1,1,fr_prelu25_lookup};
	struct ConcatParams params_concat11 = {14,14,48,14,14,48,1,1,236,1,8,0,14,14,96,1};
	struct ConvParameter weight_split10_sec1 = {{48, 1, 1, 96},0,48,48,split_index21,NULL,NULL,NULL};
	struct ConvParameter weight_split10_sec2 = {{48, 1, 1, 96},0,48,48,split_index22,NULL,NULL,NULL};
	struct ConvParameter weight_conv50 = {{48, 1, 1, 48},48,48,48,fr_conv50_weight,fr_conv50_bias,fr_conv50_offset,NULL};
	struct LookupParameter params_prelu26 = {{14,14,48},1,1,fr_prelu26_lookup};
	struct ConvParameter weight_conv51 = {{1, 3, 3, 48},48,48,48,fr_conv51_weight,fr_conv51_bias,fr_conv51_offset,NULL};
	struct ConvParameter weight_conv52 = {{48, 1, 1, 48},48,48,48,fr_conv52_weight,fr_conv52_bias,fr_conv52_offset,NULL};
	struct LookupParameter params_prelu27 = {{14,14,48},1,1,fr_prelu27_lookup};
	struct ConcatParams params_concat12 = {14,14,48,14,14,48,1,1,171,1,8,0,14,14,96,1};
	struct ConvParameter weight_conv53 = {{96, 1, 1, 96},0,96,96,index53,NULL,NULL,NULL};
	struct ConvParameter weight_conv54 = {{1, 3, 3, 96},96,96,96,fr_conv54_weight,fr_conv54_bias,fr_conv54_offset,NULL};
	struct ConvParameter weight_conv55 = {{96, 1, 1, 96},96,96,96,fr_conv55_weight,fr_conv55_bias,fr_conv55_offset,NULL};
	struct LookupParameter params_prelu28 = {{7,7,96},1,1,fr_prelu28_lookup};
	struct ConvParameter weight_conv56 = {{96, 1, 1, 96},96,96,96,fr_conv56_weight,fr_conv56_bias,fr_conv56_offset,NULL};
	struct LookupParameter params_prelu29 = {{14,14,96},1,0,fr_prelu29_lookup};
	struct ConvParameter weight_conv57 = {{1, 3, 3, 96},96,96,96,fr_conv57_weight,fr_conv57_bias,fr_conv57_offset,NULL};
	struct ConvParameter weight_conv58 = {{96, 1, 1, 96},96,96,96,fr_conv58_weight,fr_conv58_bias,fr_conv58_offset,NULL};
	struct LookupParameter params_prelu30 = {{7,7,96},1,1,fr_prelu30_lookup};
	struct ConcatParams params_concat13 = {7,7,96,7,7,96,1,1,254,1,8,0,7,7,192,1};
	struct ConvParameter weight_split11_sec1 = {{96, 1, 1, 192},0,96,96,split_index31,NULL,NULL,NULL};
	struct ConvParameter weight_split11_sec2 = {{96, 1, 1, 192},0,96,96,split_index32,NULL,NULL,NULL};
	struct ConvParameter weight_conv60 = {{96, 1, 1, 96},96,96,96,fr_conv60_weight,fr_conv60_bias,fr_conv60_offset,fr_conv60_bias_offset};
	struct LookupParameter params_prelu31 = {{7,7,96},1,1,fr_prelu31_lookup};
	struct ConvParameter weight_conv61 = {{1, 3, 3, 96},96,96,96,fr_conv61_weight,fr_conv61_bias,fr_conv61_offset,NULL};
	struct ConvParameter weight_conv62 = {{96, 1, 1, 96},96,96,96,fr_conv62_weight,fr_conv62_bias,fr_conv62_offset,NULL};
	struct LookupParameter params_prelu32 = {{7,7,96},1,1,fr_prelu32_lookup};
	struct ConcatParams params_concat14 = {7,7,96,7,7,96,1,1,224,1,8,0,7,7,192,1};
	struct ConvParameter weight_split12_sec1 = {{96, 1, 1, 192},0,96,96,split_index31,NULL,NULL,NULL};
	struct ConvParameter weight_split12_sec2 = {{96, 1, 1, 192},0,96,96,split_index32,NULL,NULL,NULL};
	struct ConvParameter weight_conv64 = {{96, 1, 1, 96},96,96,96,fr_conv64_weight,fr_conv64_bias,fr_conv64_offset,NULL};
	struct LookupParameter params_prelu33 = {{7,7,96},1,1,fr_prelu33_lookup};
	struct ConvParameter weight_conv65 = {{1, 3, 3, 96},96,96,96,fr_conv65_weight,fr_conv65_bias,fr_conv65_offset,NULL};
	struct ConvParameter weight_conv66 = {{96, 1, 1, 96},96,96,96,fr_conv66_weight,fr_conv66_bias,fr_conv66_offset,NULL};
	struct LookupParameter params_prelu34 = {{7,7,96},1,0,fr_prelu34_lookup};
	struct ConcatParams params_concat15 = {7,7,96,7,7,96,1,0,1,126,0,8,7,7,192,1};
	struct ConvParameter weight_split13_sec1 = {{96, 1, 1, 192},0,96,96,split_index31,NULL,NULL,NULL};
	struct ConvParameter weight_split13_sec2 = {{96, 1, 1, 192},0,96,96,split_index32,NULL,NULL,NULL};
	struct ConvParameter weight_conv68 = {{96, 1, 1, 96},96,96,96,fr_conv68_weight,fr_conv68_bias,fr_conv68_offset,NULL};
	struct LookupParameter params_prelu35 = {{7,7,96},1,1,fr_prelu35_lookup};
	struct ConvParameter weight_conv69 = {{1, 3, 3, 96},96,96,96,fr_conv69_weight,fr_conv69_bias,fr_conv69_offset,NULL};
	struct ConvParameter weight_conv70 = {{96, 1, 1, 96},96,96,96,fr_conv70_weight,fr_conv70_bias,fr_conv70_offset,NULL};
	struct LookupParameter params_prelu36 = {{7,7,96},1,0,fr_prelu36_lookup};
	struct ConcatParams params_concat16 = {7,7,96,7,7,96,1,0,1,126,0,8,7,7,192,1};
	struct ConvParameter weight_conv71 = {{192, 1, 1, 192},0,192,192,index71,NULL,NULL,NULL};
	struct ConvParameter weight_conv72 = {{1024, 1, 1, 192},1024,1024,1024,fr_conv72_weight,fr_conv72_bias,fr_conv72_offset,fr_conv72_bias_offset};
	struct LookupParameter params_prelu37 = {{7,7,1024},1,1,fr_prelu37_lookup};
	struct ConvParameter weight_conv73 = {{1, 5, 5, 1024},1024,1024,1024,fr_conv73_weight,fr_conv73_bias,fr_conv73_offset,fr_conv73_bias_offset};
	struct LookupParameter params_prelu38 = {{3,3,1024},1,1,fr_prelu38_lookup};
	struct ConvParameter weight_conv74 = {{1, 3, 3, 1024},1024,1024,1024,fr_conv74_weight,fr_conv74_bias,fr_conv74_offset,NULL};
	struct LookupParameter params_prelu39 = {{1,1,1024},1,0,fr_prelu39_lookup};
	struct ConvParameter weight_conv1d1 = {{128, 1, 1, 1024},128,128,128,fr_conv1d1_weight,fr_conv1d1_bias,fr_conv1d1_offset,NULL};
	struct ConvParameter weight_conv_bn1 = {{128, 1, 1, 128},128,128,128,fr_conv_bn1_weight,fr_conv_bn1_bias,NULL,NULL};
	struct Uint8Tensor blob1 = {112, 112, 3,NULL,1};
	struct Uint8Tensor conv_blob1 = {56, 56, 24,NULL,1};
	struct Uint8Tensor prelu_blob1 = {56, 56, 24,NULL,1};
	struct Uint8Tensor conv_blob2 = {28, 28, 24,NULL,1};
	struct Uint8Tensor conv_blob3 = {28, 28, 24,NULL,1};
	struct Uint8Tensor prelu_blob2 = {28, 28, 24,NULL,0};
	struct Uint8Tensor conv_blob4 = {56, 56, 24,NULL,1};
	struct Uint8Tensor prelu_blob3 = {56, 56, 24,NULL,1};
	struct Uint8Tensor conv_blob5 = {28, 28, 24,NULL,1};
	struct Uint8Tensor conv_blob6 = {28, 28, 24,NULL,1};
	struct Uint8Tensor prelu_blob4 = {28, 28, 24,NULL,1};
	struct Uint8Tensor concat_blob1 = {28, 28, 48,NULL,1};
	struct Uint8Tensor split1_sec_blob1 = {28, 28, 24,NULL,1};
	struct Uint8Tensor split1_sec_blob2 = {28, 28, 24,NULL,1};
	struct Uint8Tensor conv_blob8 = {28, 28, 24,NULL,1};
	struct Uint8Tensor prelu_blob5 = {28, 28, 24,NULL,1};
	struct Uint8Tensor conv_blob9 = {28, 28, 24,NULL,1};
	struct Uint8Tensor conv_blob10 = {28, 28, 24,NULL,1};
	struct Uint8Tensor prelu_blob6 = {28, 28, 24,NULL,1};
	struct Uint8Tensor concat_blob2 = {28, 28, 48,NULL,1};
	struct Uint8Tensor split2_sec_blob1 = {28, 28, 24,NULL,1};
	struct Uint8Tensor split2_sec_blob2 = {28, 28, 24,NULL,1};
	struct Uint8Tensor conv_blob12 = {28, 28, 24,NULL,1};
	struct Uint8Tensor prelu_blob7 = {28, 28, 24,NULL,1};
	struct Uint8Tensor conv_blob13 = {28, 28, 24,NULL,1};
	struct Uint8Tensor conv_blob14 = {28, 28, 24,NULL,1};
	struct Uint8Tensor prelu_blob8 = {28, 28, 24,NULL,1};
	struct Uint8Tensor concat_blob3 = {28, 28, 48,NULL,1};
	struct Uint8Tensor split3_sec_blob1 = {28, 28, 24,NULL,1};
	struct Uint8Tensor split3_sec_blob2 = {28, 28, 24,NULL,1};
	struct Uint8Tensor conv_blob16 = {28, 28, 24,NULL,1};
	struct Uint8Tensor prelu_blob9 = {28, 28, 24,NULL,1};
	struct Uint8Tensor conv_blob17 = {28, 28, 24,NULL,1};
	struct Uint8Tensor conv_blob18 = {28, 28, 24,NULL,1};
	struct Uint8Tensor prelu_blob10 = {28, 28, 24,NULL,1};
	struct Uint8Tensor concat_blob4 = {28, 28, 48,NULL,1};
	struct Uint8Tensor conv_blob19 = {28, 28, 48,NULL,1};
	struct Uint8Tensor conv_blob20 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob21 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob11 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob22 = {28, 28, 48,NULL,1};
	struct Uint8Tensor prelu_blob12 = {28, 28, 48,NULL,0};
	struct Uint8Tensor conv_blob23 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob24 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob13 = {14, 14, 48,NULL,1};
	struct Uint8Tensor concat_blob5 = {14, 14, 96,NULL,1};
	struct Uint8Tensor split4_sec_blob1 = {14, 14, 48,NULL,1};
	struct Uint8Tensor split4_sec_blob2 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob26 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob14 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob27 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob28 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob15 = {14, 14, 48,NULL,1};
	struct Uint8Tensor concat_blob6 = {14, 14, 96,NULL,1};
	struct Uint8Tensor split5_sec_blob1 = {14, 14, 48,NULL,1};
	struct Uint8Tensor split5_sec_blob2 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob30 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob16 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob31 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob32 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob17 = {14, 14, 48,NULL,1};
	struct Uint8Tensor concat_blob7 = {14, 14, 96,NULL,1};
	struct Uint8Tensor split6_sec_blob1 = {14, 14, 48,NULL,1};
	struct Uint8Tensor split6_sec_blob2 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob34 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob18 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob35 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob36 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob19 = {14, 14, 48,NULL,1};
	struct Uint8Tensor concat_blob8 = {14, 14, 96,NULL,1};
	struct Uint8Tensor split7_sec_blob1 = {14, 14, 48,NULL,1};
	struct Uint8Tensor split7_sec_blob2 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob38 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob20 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob39 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob40 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob21 = {14, 14, 48,NULL,1};
	struct Uint8Tensor concat_blob9 = {14, 14, 96,NULL,1};
	struct Uint8Tensor split8_sec_blob1 = {14, 14, 48,NULL,1};
	struct Uint8Tensor split8_sec_blob2 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob42 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob22 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob43 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob44 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob23 = {14, 14, 48,NULL,1};
	struct Uint8Tensor concat_blob10 = {14, 14, 96,NULL,1};
	struct Uint8Tensor split9_sec_blob1 = {14, 14, 48,NULL,1};
	struct Uint8Tensor split9_sec_blob2 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob46 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob24 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob47 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob48 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob25 = {14, 14, 48,NULL,1};
	struct Uint8Tensor concat_blob11 = {14, 14, 96,NULL,1};
	struct Uint8Tensor split10_sec_blob1 = {14, 14, 48,NULL,1};
	struct Uint8Tensor split10_sec_blob2 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob50 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob26 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob51 = {14, 14, 48,NULL,1};
	struct Uint8Tensor conv_blob52 = {14, 14, 48,NULL,1};
	struct Uint8Tensor prelu_blob27 = {14, 14, 48,NULL,1};
	struct Uint8Tensor concat_blob12 = {14, 14, 96,NULL,1};
	struct Uint8Tensor conv_blob53 = {14, 14, 96,NULL,1};
	struct Uint8Tensor conv_blob54 = {7, 7, 96,NULL,1};
	struct Uint8Tensor conv_blob55 = {7, 7, 96,NULL,1};
	struct Uint8Tensor prelu_blob28 = {7, 7, 96,NULL,1};
	struct Uint8Tensor conv_blob56 = {14, 14, 96,NULL,1};
	struct Uint8Tensor prelu_blob29 = {14, 14, 96,NULL,0};
	struct Uint8Tensor conv_blob57 = {7, 7, 96,NULL,1};
	struct Uint8Tensor conv_blob58 = {7, 7, 96,NULL,1};
	struct Uint8Tensor prelu_blob30 = {7, 7, 96,NULL,1};
	struct Uint8Tensor concat_blob13 = {7, 7, 192,NULL,1};
	struct Uint8Tensor split11_sec_blob1 = {7, 7, 96,NULL,1};
	struct Uint8Tensor split11_sec_blob2 = {7, 7, 96,NULL,1};
	struct Uint8Tensor conv_blob60 = {7, 7, 96,NULL,1};
	struct Uint8Tensor prelu_blob31 = {7, 7, 96,NULL,1};
	struct Uint8Tensor conv_blob61 = {7, 7, 96,NULL,1};
	struct Uint8Tensor conv_blob62 = {7, 7, 96,NULL,1};
	struct Uint8Tensor prelu_blob32 = {7, 7, 96,NULL,1};
	struct Uint8Tensor concat_blob14 = {7, 7, 192,NULL,1};
	struct Uint8Tensor split12_sec_blob1 = {7, 7, 96,NULL,1};
	struct Uint8Tensor split12_sec_blob2 = {7, 7, 96,NULL,1};
	struct Uint8Tensor conv_blob64 = {7, 7, 96,NULL,1};
	struct Uint8Tensor prelu_blob33 = {7, 7, 96,NULL,1};
	struct Uint8Tensor conv_blob65 = {7, 7, 96,NULL,1};
	struct Uint8Tensor conv_blob66 = {7, 7, 96,NULL,1};
	struct Uint8Tensor prelu_blob34 = {7, 7, 96,NULL,0};
	struct Uint8Tensor concat_blob15 = {7, 7, 192,NULL,1};
	struct Uint8Tensor split13_sec_blob1 = {7, 7, 96,NULL,1};
	struct Uint8Tensor split13_sec_blob2 = {7, 7, 96,NULL,1};
	struct Uint8Tensor conv_blob68 = {7, 7, 96,NULL,1};
	struct Uint8Tensor prelu_blob35 = {7, 7, 96,NULL,1};
	struct Uint8Tensor conv_blob69 = {7, 7, 96,NULL,1};
	struct Uint8Tensor conv_blob70 = {7, 7, 96,NULL,1};
	struct Uint8Tensor prelu_blob36 = {7, 7, 96,NULL,0};
	struct Uint8Tensor concat_blob16 = {7, 7, 192,NULL,1};
	struct Uint8Tensor conv_blob71 = {7, 7, 192,NULL,1};
	struct Uint8Tensor conv_blob72 = {7, 7, 1024,NULL,1};
	struct Uint8Tensor prelu_blob37 = {7, 7, 1024,NULL,1};
	struct Uint8Tensor conv_blob73 = {3, 3, 1024,NULL,1};
	struct Uint8Tensor prelu_blob38 = {3, 3, 1024,NULL,1};
	struct Uint8Tensor conv_blob74 = {1, 1, 1024,NULL,1};
	struct Uint8Tensor prelu_blob39 = {1, 1, 1024,NULL,0};
	struct Uint8Tensor conv1d_blob1 = {1, 1, 128,NULL,1};
	struct Uint8Tensor conv_bn_blob1 = {1, 1, 128,NULL,1};
	//load_input(&blob1,"blob1");
    
    int inputlength = blob1.channel*blob1.height*blob1.width;
    blob1.data_location= (uint8_t*)rgb_data;
    
    // DSP_LOG("Before rgb_data change (first 128 bytes):\n");
    // {
    //     char line_buf[128];
    //     int pos = 0;
    //     line_buf[0] = '\0';
    //     for (int i = 0; i < 128 && i < inputlength; i++) {
    //         pos += snprintf(line_buf + pos, sizeof(line_buf) - pos, "%02X ", rgb_data[i]);
    //         if ((i + 1) % 16 == 0) {
    //             DSP_LOG("%s\n", line_buf);
    //             pos = 0;
    //             line_buf[0] = '\0';
    //         }
    //     }
    //     if (pos > 0) DSP_LOG("%s\n", line_buf);
    // }

    for(int i=0;i<inputlength;i++)
        blob1.data_location[i] = rgb_data[i]-127;

    // DSP_LOG("After rgb_data change (first 128 bytes):\n");
    // {
    //     char line_buf[128];
    //     int pos = 0;
    //     line_buf[0] = '\0';
    //     for (int i = 0; i < 128 && i < inputlength; i++) {
    //         pos += snprintf(line_buf + pos, sizeof(line_buf) - pos, "%02X ", blob1.data_location[i]);
    //         if ((i + 1) % 16 == 0) {
    //             DSP_LOG("%s\n", line_buf);
    //             pos = 0;
    //             line_buf[0] = '\0';
    //         }
    //     }
    //     if (pos > 0) DSP_LOG("%s\n", line_buf);
    // }

    print_uint8tensor(&blob1);
	build_output(&conv_blob1, 1);
	//conv_rgb_dsp(&blob1, &conv_blob1, &structure_conv1, &weight_conv1);
    // uint32_t start_cycles = get_cycles_start();
	conv_fr_rgb(&blob1, &conv_blob1, &structure_conv1, &weight_conv1);
    // uint32_t end_cycles = get_cycles_end();

    // DSP_LOG("conv_fr_rgb cycles: %u\n", end_cycles - start_cycles);
	print_uint8tensor(&conv_blob1);

	//release_input(&blob1);

	build_output(&prelu_blob1, 1);
    // start_cycles = get_cycles_start();
	lookup(&conv_blob1, &prelu_blob1, &params_prelu1);
    // end_cycles = get_cycles_end();

    // DSP_LOG("lookup cycles: %u\n", end_cycles - start_cycles);
	release_input(&conv_blob1);
    print_uint8tensor(&prelu_blob1);


	build_output(&conv_blob2, 1);
	conv_dp_dsp(&prelu_blob1, &conv_blob2, &structure_conv2, &weight_conv2);
    print_uint8tensor(&conv_blob2);

    
	build_output(&conv_blob3, 1);
	conv1x1xn_dsp(&conv_blob2, &conv_blob3, &structure_conv3, &weight_conv3);
	release_input(&conv_blob2);

	build_output(&prelu_blob2, 0);
	lookup(&conv_blob3, &prelu_blob2, &params_prelu2);
	release_input(&conv_blob3);

	build_output(&conv_blob4, 1);
	conv1x1xn_dsp(&prelu_blob1, &conv_blob4, &structure_conv4, &weight_conv4);
	release_input(&prelu_blob1);




	build_output(&prelu_blob3, 1);
	lookup(&conv_blob4, &prelu_blob3, &params_prelu3);
	release_input(&conv_blob4);

	build_output(&conv_blob5, 1);
	conv_dp_dsp(&prelu_blob3, &conv_blob5, &structure_conv5, &weight_conv5);

	release_input(&prelu_blob3);
	build_output(&conv_blob6, 1);
	conv1x1xn_dsp(&conv_blob5, &conv_blob6, &structure_conv6, &weight_conv6);

	release_input(&conv_blob5);

	build_output(&prelu_blob4, 1);
	lookup(&conv_blob6, &prelu_blob4, &params_prelu4);
	release_input(&conv_blob6);

	build_output(&concat_blob1, 1);
	concat(&prelu_blob2, &prelu_blob4, &concat_blob1, &params_concat1);
	release_input(&prelu_blob2);

	release_input(&prelu_blob4);

	build_output(&split1_sec_blob1, 1);
	conv_fr_split(&concat_blob1, &split1_sec_blob1, &structure_split1_sec1, &weight_split1_sec1);

	build_output(&split1_sec_blob2, 1);
	conv_fr_split(&concat_blob1, &split1_sec_blob2, &structure_split1_sec2, &weight_split1_sec2);

	release_input(&concat_blob1);

	build_output(&conv_blob8, 1);
	conv1x1xn_dsp(&split1_sec_blob2, &conv_blob8, &structure_conv8, &weight_conv8);

	release_input(&split1_sec_blob2);

	build_output(&prelu_blob5, 1);
	lookup(&conv_blob8, &prelu_blob5, &params_prelu5);
	release_input(&conv_blob8);

	build_output(&conv_blob9, 1);
	conv_dp_dsp(&prelu_blob5, &conv_blob9, &structure_conv9, &weight_conv9);

	release_input(&prelu_blob5);

	build_output(&conv_blob10, 1);
	conv1x1xn_dsp(&conv_blob9, &conv_blob10, &structure_conv10, &weight_conv10);

	release_input(&conv_blob9);

	build_output(&prelu_blob6, 1);
	lookup(&conv_blob10, &prelu_blob6, &params_prelu6);
	release_input(&conv_blob10);

	build_output(&concat_blob2, 1);
	concat(&split1_sec_blob1, &prelu_blob6, &concat_blob2, &params_concat2);
	release_input(&split1_sec_blob1);

	release_input(&prelu_blob6);

	build_output(&split2_sec_blob1, 1);
	conv_fr_split(&concat_blob2, &split2_sec_blob1, &structure_split2_sec1, &weight_split2_sec1);

	build_output(&split2_sec_blob2, 1);
	conv_fr_split(&concat_blob2, &split2_sec_blob2, &structure_split2_sec2, &weight_split2_sec2);

	release_input(&concat_blob2);

	build_output(&conv_blob12, 1);
	conv1x1xn_dsp(&split2_sec_blob2, &conv_blob12, &structure_conv12, &weight_conv12);

	release_input(&split2_sec_blob2);

	build_output(&prelu_blob7, 1);
	lookup(&conv_blob12, &prelu_blob7, &params_prelu7);
	release_input(&conv_blob12);

	build_output(&conv_blob13, 1);
	conv_dp_dsp(&prelu_blob7, &conv_blob13, &structure_conv13, &weight_conv13);

	release_input(&prelu_blob7);

	build_output(&conv_blob14, 1);
	conv1x1xn_dsp(&conv_blob13, &conv_blob14, &structure_conv14, &weight_conv14);

	release_input(&conv_blob13);

	build_output(&prelu_blob8, 1);
	lookup(&conv_blob14, &prelu_blob8, &params_prelu8);
	release_input(&conv_blob14);

	build_output(&concat_blob3, 1);
	concat(&split2_sec_blob1, &prelu_blob8, &concat_blob3, &params_concat3);
	release_input(&split2_sec_blob1);

	release_input(&prelu_blob8);

	build_output(&split3_sec_blob1, 1);
	conv_fr_split(&concat_blob3, &split3_sec_blob1, &structure_split3_sec1, &weight_split3_sec1);

	build_output(&split3_sec_blob2, 1);
	conv_fr_split(&concat_blob3, &split3_sec_blob2, &structure_split3_sec2, &weight_split3_sec2);

	release_input(&concat_blob3);

	build_output(&conv_blob16, 1);
	conv1x1xn_dsp(&split3_sec_blob2, &conv_blob16, &structure_conv16, &weight_conv16);

	release_input(&split3_sec_blob2);

	build_output(&prelu_blob9, 1);
	lookup(&conv_blob16, &prelu_blob9, &params_prelu9);
	release_input(&conv_blob16);

	build_output(&conv_blob17, 1);
	conv_dp_dsp(&prelu_blob9, &conv_blob17, &structure_conv17, &weight_conv17);

	release_input(&prelu_blob9);

	build_output(&conv_blob18, 1);
	conv1x1xn_dsp(&conv_blob17, &conv_blob18, &structure_conv18, &weight_conv18);

	release_input(&conv_blob17);

	build_output(&prelu_blob10, 1);
	lookup(&conv_blob18, &prelu_blob10, &params_prelu10);
	release_input(&conv_blob18);

	build_output(&concat_blob4, 1);
	concat(&split3_sec_blob1, &prelu_blob10, &concat_blob4, &params_concat4);
	release_input(&split3_sec_blob1);

	release_input(&prelu_blob10);

	build_output(&conv_blob19, 1);
	conv_fr_split(&concat_blob4, &conv_blob19, &structure_conv19, &weight_conv19);

	release_input(&concat_blob4);

	build_output(&conv_blob20, 1);
	conv_dp_dsp(&conv_blob19, &conv_blob20, &structure_conv20, &weight_conv20);

	build_output(&conv_blob21, 1);
	conv1x1xn_dsp(&conv_blob20, &conv_blob21, &structure_conv21, &weight_conv21);

	release_input(&conv_blob20);

	build_output(&prelu_blob11, 1);
	lookup(&conv_blob21, &prelu_blob11, &params_prelu11);
	release_input(&conv_blob21);

	build_output(&conv_blob22, 1);
	conv1x1xn_dsp(&conv_blob19, &conv_blob22, &structure_conv22, &weight_conv22);

	release_input(&conv_blob19);

	build_output(&prelu_blob12, 0);
	lookup(&conv_blob22, &prelu_blob12, &params_prelu12);
	release_input(&conv_blob22);

	build_output(&conv_blob23, 1);
	conv_dp_dsp(&prelu_blob12, &conv_blob23, &structure_conv23, &weight_conv23);

	release_input(&prelu_blob12);

	build_output(&conv_blob24, 1);
	conv1x1xn_dsp(&conv_blob23, &conv_blob24, &structure_conv24, &weight_conv24);

	release_input(&conv_blob23);

	build_output(&prelu_blob13, 1);
	lookup(&conv_blob24, &prelu_blob13, &params_prelu13);
	release_input(&conv_blob24);

	build_output(&concat_blob5, 1);
	concat(&prelu_blob11, &prelu_blob13, &concat_blob5, &params_concat5);
	release_input(&prelu_blob11);

	release_input(&prelu_blob13);

	build_output(&split4_sec_blob1, 1);
	conv_fr_split(&concat_blob5, &split4_sec_blob1, &structure_split4_sec1, &weight_split4_sec1);

	build_output(&split4_sec_blob2, 1);
	conv_fr_split(&concat_blob5, &split4_sec_blob2, &structure_split4_sec2, &weight_split4_sec2);

	release_input(&concat_blob5);

	build_output(&conv_blob26, 1);
	conv1x1xn_dsp(&split4_sec_blob2, &conv_blob26, &structure_conv26, &weight_conv26);

	release_input(&split4_sec_blob2);

	build_output(&prelu_blob14, 1);
	lookup(&conv_blob26, &prelu_blob14, &params_prelu14);
	release_input(&conv_blob26);

	build_output(&conv_blob27, 1);
	conv_dp_dsp(&prelu_blob14, &conv_blob27, &structure_conv27, &weight_conv27);

	release_input(&prelu_blob14);

	build_output(&conv_blob28, 1);
	conv1x1xn_dsp(&conv_blob27, &conv_blob28, &structure_conv28, &weight_conv28);

	release_input(&conv_blob27);

	build_output(&prelu_blob15, 1);
	lookup(&conv_blob28, &prelu_blob15, &params_prelu15);
	release_input(&conv_blob28);

	build_output(&concat_blob6, 1);
	concat(&split4_sec_blob1, &prelu_blob15, &concat_blob6, &params_concat6);
	release_input(&split4_sec_blob1);

	release_input(&prelu_blob15);

	build_output(&split5_sec_blob1, 1);
	conv_fr_split(&concat_blob6, &split5_sec_blob1, &structure_split5_sec1, &weight_split5_sec1);

	build_output(&split5_sec_blob2, 1);
	conv_fr_split(&concat_blob6, &split5_sec_blob2, &structure_split5_sec2, &weight_split5_sec2);

	release_input(&concat_blob6);

	build_output(&conv_blob30, 1);
	conv1x1xn_dsp(&split5_sec_blob2, &conv_blob30, &structure_conv30, &weight_conv30);

	release_input(&split5_sec_blob2);

	build_output(&prelu_blob16, 1);
	lookup(&conv_blob30, &prelu_blob16, &params_prelu16);
	release_input(&conv_blob30);

	build_output(&conv_blob31, 1);
	conv_dp_dsp(&prelu_blob16, &conv_blob31, &structure_conv31, &weight_conv31);

	release_input(&prelu_blob16);

	build_output(&conv_blob32, 1);
	conv1x1xn_dsp(&conv_blob31, &conv_blob32, &structure_conv32, &weight_conv32);

	release_input(&conv_blob31);

	build_output(&prelu_blob17, 1);
	lookup(&conv_blob32, &prelu_blob17, &params_prelu17);
	release_input(&conv_blob32);

	build_output(&concat_blob7, 1);
	concat(&split5_sec_blob1, &prelu_blob17, &concat_blob7, &params_concat7);
	release_input(&split5_sec_blob1);

	release_input(&prelu_blob17);

	build_output(&split6_sec_blob1, 1);
	conv_fr_split(&concat_blob7, &split6_sec_blob1, &structure_split6_sec1, &weight_split6_sec1);

	build_output(&split6_sec_blob2, 1);
	conv_fr_split(&concat_blob7, &split6_sec_blob2, &structure_split6_sec2, &weight_split6_sec2);

	release_input(&concat_blob7);

	build_output(&conv_blob34, 1);
	conv1x1xn_dsp(&split6_sec_blob2, &conv_blob34, &structure_conv34, &weight_conv34);

	release_input(&split6_sec_blob2);

	build_output(&prelu_blob18, 1);
	lookup(&conv_blob34, &prelu_blob18, &params_prelu18);
	release_input(&conv_blob34);

	build_output(&conv_blob35, 1);
	conv_dp_dsp(&prelu_blob18, &conv_blob35, &structure_conv35, &weight_conv35);

	release_input(&prelu_blob18);

	build_output(&conv_blob36, 1);
	conv1x1xn_dsp(&conv_blob35, &conv_blob36, &structure_conv36, &weight_conv36);

	release_input(&conv_blob35);

	build_output(&prelu_blob19, 1);
	lookup(&conv_blob36, &prelu_blob19, &params_prelu19);
	release_input(&conv_blob36);

	build_output(&concat_blob8, 1);
	concat(&split6_sec_blob1, &prelu_blob19, &concat_blob8, &params_concat8);
	release_input(&split6_sec_blob1);

	release_input(&prelu_blob19);

	build_output(&split7_sec_blob1, 1);
	conv_fr_split(&concat_blob8, &split7_sec_blob1, &structure_split7_sec1, &weight_split7_sec1);

	build_output(&split7_sec_blob2, 1);
	conv_fr_split(&concat_blob8, &split7_sec_blob2, &structure_split7_sec2, &weight_split7_sec2);

	release_input(&concat_blob8);

	build_output(&conv_blob38, 1);
	conv1x1xn_dsp(&split7_sec_blob2, &conv_blob38, &structure_conv38, &weight_conv38);

	release_input(&split7_sec_blob2);

	build_output(&prelu_blob20, 1);
	lookup(&conv_blob38, &prelu_blob20, &params_prelu20);
	release_input(&conv_blob38);

	build_output(&conv_blob39, 1);
	conv_dp_dsp(&prelu_blob20, &conv_blob39, &structure_conv39, &weight_conv39);

	release_input(&prelu_blob20);

	build_output(&conv_blob40, 1);
	conv1x1xn_dsp(&conv_blob39, &conv_blob40, &structure_conv40, &weight_conv40);

	release_input(&conv_blob39);

	build_output(&prelu_blob21, 1);
	lookup(&conv_blob40, &prelu_blob21, &params_prelu21);
	release_input(&conv_blob40);

	build_output(&concat_blob9, 1);
	concat(&split7_sec_blob1, &prelu_blob21, &concat_blob9, &params_concat9);
	release_input(&split7_sec_blob1);

	release_input(&prelu_blob21);

	build_output(&split8_sec_blob1, 1);
	conv_fr_split(&concat_blob9, &split8_sec_blob1, &structure_split8_sec1, &weight_split8_sec1);

	build_output(&split8_sec_blob2, 1);
	conv_fr_split(&concat_blob9, &split8_sec_blob2, &structure_split8_sec2, &weight_split8_sec2);

	release_input(&concat_blob9);

	build_output(&conv_blob42, 1);
	conv1x1xn_dsp(&split8_sec_blob2, &conv_blob42, &structure_conv42, &weight_conv42);

	release_input(&split8_sec_blob2);

	build_output(&prelu_blob22, 1);
	lookup(&conv_blob42, &prelu_blob22, &params_prelu22);
	release_input(&conv_blob42);

	build_output(&conv_blob43, 1);
	conv_dp_dsp(&prelu_blob22, &conv_blob43, &structure_conv43, &weight_conv43);

	release_input(&prelu_blob22);

	build_output(&conv_blob44, 1);
	conv1x1xn_dsp(&conv_blob43, &conv_blob44, &structure_conv44, &weight_conv44);

	release_input(&conv_blob43);

	build_output(&prelu_blob23, 1);
	lookup(&conv_blob44, &prelu_blob23, &params_prelu23);
	release_input(&conv_blob44);

	build_output(&concat_blob10, 1);
	concat(&split8_sec_blob1, &prelu_blob23, &concat_blob10, &params_concat10);
	release_input(&split8_sec_blob1);

	release_input(&prelu_blob23);

	build_output(&split9_sec_blob1, 1);
	conv_fr_split(&concat_blob10, &split9_sec_blob1, &structure_split9_sec1, &weight_split9_sec1);

	build_output(&split9_sec_blob2, 1);
	conv_fr_split(&concat_blob10, &split9_sec_blob2, &structure_split9_sec2, &weight_split9_sec2);

	release_input(&concat_blob10);

	build_output(&conv_blob46, 1);
	conv1x1xn_dsp(&split9_sec_blob2, &conv_blob46, &structure_conv46, &weight_conv46);

	release_input(&split9_sec_blob2);

	build_output(&prelu_blob24, 1);
	lookup(&conv_blob46, &prelu_blob24, &params_prelu24);
	release_input(&conv_blob46);

	build_output(&conv_blob47, 1);
	conv_dp_dsp(&prelu_blob24, &conv_blob47, &structure_conv47, &weight_conv47);

	release_input(&prelu_blob24);

	build_output(&conv_blob48, 1);
	conv1x1xn_dsp(&conv_blob47, &conv_blob48, &structure_conv48, &weight_conv48);

	release_input(&conv_blob47);

	build_output(&prelu_blob25, 1);
	lookup(&conv_blob48, &prelu_blob25, &params_prelu25);
	release_input(&conv_blob48);

	build_output(&concat_blob11, 1);
	concat(&split9_sec_blob1, &prelu_blob25, &concat_blob11, &params_concat11);
	release_input(&split9_sec_blob1);

	release_input(&prelu_blob25);

	build_output(&split10_sec_blob1, 1);
	conv_fr_split(&concat_blob11, &split10_sec_blob1, &structure_split10_sec1, &weight_split10_sec1);

	build_output(&split10_sec_blob2, 1);
	conv_fr_split(&concat_blob11, &split10_sec_blob2, &structure_split10_sec2, &weight_split10_sec2);

	release_input(&concat_blob11);

	build_output(&conv_blob50, 1);
	conv1x1xn_dsp(&split10_sec_blob2, &conv_blob50, &structure_conv50, &weight_conv50);

	release_input(&split10_sec_blob2);

	build_output(&prelu_blob26, 1);
	lookup(&conv_blob50, &prelu_blob26, &params_prelu26);
	release_input(&conv_blob50);

	build_output(&conv_blob51, 1);
	conv_dp_dsp(&prelu_blob26, &conv_blob51, &structure_conv51, &weight_conv51);

	release_input(&prelu_blob26);

	build_output(&conv_blob52, 1);
	conv1x1xn_dsp(&conv_blob51, &conv_blob52, &structure_conv52, &weight_conv52);

	release_input(&conv_blob51);

	build_output(&prelu_blob27, 1);
	lookup(&conv_blob52, &prelu_blob27, &params_prelu27);
	release_input(&conv_blob52);

	build_output(&concat_blob12, 1);
	concat(&split10_sec_blob1, &prelu_blob27, &concat_blob12, &params_concat12);
	release_input(&split10_sec_blob1);

	release_input(&prelu_blob27);

	build_output(&conv_blob53, 1);
	conv_fr_split(&concat_blob12, &conv_blob53, &structure_conv53, &weight_conv53);

	release_input(&concat_blob12);

	build_output(&conv_blob54, 1);
	conv_dp_dsp(&conv_blob53, &conv_blob54, &structure_conv54, &weight_conv54);

	build_output(&conv_blob55, 1);
	conv1x1xn_dsp(&conv_blob54, &conv_blob55, &structure_conv55, &weight_conv55);

	release_input(&conv_blob54);

	build_output(&prelu_blob28, 1);
	lookup(&conv_blob55, &prelu_blob28, &params_prelu28);
	release_input(&conv_blob55);

	build_output(&conv_blob56, 1);
	conv1x1xn_dsp(&conv_blob53, &conv_blob56, &structure_conv56, &weight_conv56);

	release_input(&conv_blob53);

	build_output(&prelu_blob29, 0);
	lookup(&conv_blob56, &prelu_blob29, &params_prelu29);
	release_input(&conv_blob56);

	build_output(&conv_blob57, 1);
	conv_dp_dsp(&prelu_blob29, &conv_blob57, &structure_conv57, &weight_conv57);

	release_input(&prelu_blob29);

	build_output(&conv_blob58, 1);
	conv1x1xn_dsp(&conv_blob57, &conv_blob58, &structure_conv58, &weight_conv58);

	release_input(&conv_blob57);

	build_output(&prelu_blob30, 1);
	lookup(&conv_blob58, &prelu_blob30, &params_prelu30);
	release_input(&conv_blob58);

	build_output(&concat_blob13, 1);
	concat(&prelu_blob28, &prelu_blob30, &concat_blob13, &params_concat13);
	release_input(&prelu_blob28);

	release_input(&prelu_blob30);

	build_output(&split11_sec_blob1, 1);
	conv_fr_split(&concat_blob13, &split11_sec_blob1, &structure_split11_sec1, &weight_split11_sec1);

	build_output(&split11_sec_blob2, 1);
	conv_fr_split(&concat_blob13, &split11_sec_blob2, &structure_split11_sec2, &weight_split11_sec2);

	release_input(&concat_blob13);

	build_output(&conv_blob60, 1);
	conv1x1xn_dsp(&split11_sec_blob2, &conv_blob60, &structure_conv60, &weight_conv60);

	release_input(&split11_sec_blob2);

	build_output(&prelu_blob31, 1);
	lookup(&conv_blob60, &prelu_blob31, &params_prelu31);
	release_input(&conv_blob60);

	build_output(&conv_blob61, 1);
	conv_dp_dsp(&prelu_blob31, &conv_blob61, &structure_conv61, &weight_conv61);

	release_input(&prelu_blob31);

	build_output(&conv_blob62, 1);
	conv1x1xn_dsp(&conv_blob61, &conv_blob62, &structure_conv62, &weight_conv62);

	release_input(&conv_blob61);

	build_output(&prelu_blob32, 1);
	lookup(&conv_blob62, &prelu_blob32, &params_prelu32);
	release_input(&conv_blob62);

	build_output(&concat_blob14, 1);
	concat(&split11_sec_blob1, &prelu_blob32, &concat_blob14, &params_concat14);
	release_input(&split11_sec_blob1);

	release_input(&prelu_blob32);

	build_output(&split12_sec_blob1, 1);
	conv_fr_split(&concat_blob14, &split12_sec_blob1, &structure_split12_sec1, &weight_split12_sec1);

	build_output(&split12_sec_blob2, 1);
	conv_fr_split(&concat_blob14, &split12_sec_blob2, &structure_split12_sec2, &weight_split12_sec2);

	release_input(&concat_blob14);

	build_output(&conv_blob64, 1);
	conv1x1xn_dsp(&split12_sec_blob2, &conv_blob64, &structure_conv64, &weight_conv64);

	release_input(&split12_sec_blob2);

	build_output(&prelu_blob33, 1);
	lookup(&conv_blob64, &prelu_blob33, &params_prelu33);
	release_input(&conv_blob64);

	build_output(&conv_blob65, 1);
	conv_dp_dsp(&prelu_blob33, &conv_blob65, &structure_conv65, &weight_conv65);

	release_input(&prelu_blob33);

	build_output(&conv_blob66, 1);
	conv1x1xn_dsp(&conv_blob65, &conv_blob66, &structure_conv66, &weight_conv66);

	release_input(&conv_blob65);

	build_output(&prelu_blob34, 0);
	lookup(&conv_blob66, &prelu_blob34, &params_prelu34);
	release_input(&conv_blob66);

	build_output(&concat_blob15, 1);
	concat(&split12_sec_blob1, &prelu_blob34, &concat_blob15, &params_concat15);
	release_input(&split12_sec_blob1);

	release_input(&prelu_blob34);

	build_output(&split13_sec_blob1, 1);
	conv_fr_split(&concat_blob15, &split13_sec_blob1, &structure_split13_sec1, &weight_split13_sec1);

	build_output(&split13_sec_blob2, 1);
	conv_fr_split(&concat_blob15, &split13_sec_blob2, &structure_split13_sec2, &weight_split13_sec2);

	release_input(&concat_blob15);

	build_output(&conv_blob68, 1);
	conv1x1xn_dsp(&split13_sec_blob2, &conv_blob68, &structure_conv68, &weight_conv68);

	release_input(&split13_sec_blob2);

	build_output(&prelu_blob35, 1);
	lookup(&conv_blob68, &prelu_blob35, &params_prelu35);
	release_input(&conv_blob68);

	build_output(&conv_blob69, 1);
	conv_dp_dsp(&prelu_blob35, &conv_blob69, &structure_conv69, &weight_conv69);

	release_input(&prelu_blob35);

	build_output(&conv_blob70, 1);
	conv1x1xn_dsp(&conv_blob69, &conv_blob70, &structure_conv70, &weight_conv70);

	release_input(&conv_blob69);

	build_output(&prelu_blob36, 0);
	lookup(&conv_blob70, &prelu_blob36, &params_prelu36);
	release_input(&conv_blob70);

	build_output(&concat_blob16, 1);
	concat(&split13_sec_blob1, &prelu_blob36, &concat_blob16, &params_concat16);
	release_input(&split13_sec_blob1);

	release_input(&prelu_blob36);

	build_output(&conv_blob71, 1);
	conv_fr_split(&concat_blob16, &conv_blob71, &structure_conv71, &weight_conv71);

	release_input(&concat_blob16);

	build_output(&conv_blob72, 1);
	conv1x1xn_dsp(&conv_blob71, &conv_blob72, &structure_conv72, &weight_conv72);

	release_input(&conv_blob71);

	build_output(&prelu_blob37, 1);

	lookup(&conv_blob72, &prelu_blob37, &params_prelu37);

	release_input(&conv_blob72);

	build_output(&conv_blob73, 1);

	conv_fr(&prelu_blob37, &conv_blob73, &structure_conv73, &weight_conv73);

	release_input(&prelu_blob37);

	build_output(&prelu_blob38, 1);
	lookup(&conv_blob73, &prelu_blob38, &params_prelu38);
	release_input(&conv_blob73);

	build_output(&conv_blob74, 1);
	conv_fr(&prelu_blob38, &conv_blob74, &structure_conv74, &weight_conv74);
	print_uint8tensor(&conv_blob74);

	release_input(&prelu_blob38);

	build_output(&prelu_blob39, 0);
	lookup(&conv_blob74, &prelu_blob39, &params_prelu39);
    print_uint8tensor(&prelu_blob39);
	release_input(&conv_blob74);

	build_output(&conv1d_blob1, 1);

//    uint32_t start_cycles = get_cycles_start();
	// conv_fr1x1xn(&prelu_blob39, &conv1d_blob1, &structure_conv1d1, &weight_conv1d1);
	conv_fr1x1xn_psram(&prelu_blob39, &conv1d_blob1, &structure_conv1d1, &weight_conv1d1);
//    uint32_t end_cycles = get_cycles_end();

//    DSP_LOG("Conv1x1xN cycles: %u\n", end_cycles - start_cycles);

	print_uint8tensor(&conv1d_blob1);
	release_input(&prelu_blob39);

	build_output(&conv_bn_blob1, 1);

	conv_fr1x1xn(&conv1d_blob1, &conv_bn_blob1, &structure_conv_bn1, &weight_conv_bn1);

	release_input(&conv1d_blob1);
	print_uint8tensor(&conv_bn_blob1);
		
    // Calculate L2 Norm and Normalize
    float sum_sq = 0.0f;
    float temp_float[128];
    float scale = 0.010845917096839575f;

    // 1. Dequantize to float and calculate sum of squares
	for(int i=0;i<128;i++){
       temp_float[i] = (float)scale * (int8_t)conv_bn_blob1.data_location[i];
       sum_sq += temp_float[i] * temp_float[i];
    }

    // 2. Calculate Norm
    float norm = dsp_sqrtf(sum_sq);
    float inv_norm = (norm > 1e-6f) ? (1.0f / norm) : 0.0f;

    // 3. Normalize, Quantize and output
    for(int i=0;i<128;i++){
        float normalized_val = temp_float[i] * inv_norm;
        // Scale by 127 to maximize int8 range
        float quantized_val = normalized_val * 127.0f;
        
        // Clamp and cast
        if (quantized_val >= 127.0f) quantized_val = 127.0f;
        if (quantized_val <= -128.0f) quantized_val = -128.0f;
        
        // Rounding
        result[i] = (int8_t)(quantized_val > 0 ? quantized_val + 0.5f : quantized_val - 0.5f);
    }

    DSP_LOG("Normalized result (first 10): %d %d %d %d %d %d %d %d %d %d\n", 
        result[0], result[1], result[2], result[3], result[4], 
        result[5], result[6], result[7], result[8], result[9]);
		

	release_input(&conv_bn_blob1);
	return 0;
}



int face_recognition(){

    int8_t result_vev[128] = {0};

    DSP_LOG("run into running processer\r\n");

    fr_run(result_vev , input_image);
    DSP_LOG("run out running processer\r\n");

    DSP_LOG("%d\n",result_vev[111]);
    

}
