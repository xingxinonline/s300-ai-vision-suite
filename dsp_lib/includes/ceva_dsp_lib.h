/*************************************************************************************\
* Copyright (C) CEVA(R) Inc. All rights reserved                                      *
*                                                                                     *
* This information embodies materials and concepts, which are proprietary and         *
* confidential to CEVA Inc., and is made available solely pursuant to the terms       *
* of a written license agreement, or NDA, or another written agreement, as            *
* applicable ("CEVA Agreement"), with CEVA Inc. or any of its subsidiaries ("CEVA").  *
*                                                                                     *
* This information can be used only with the written permission from CEVA, in         *
* accordance with the terms and conditions stipulated in the CEVA Agreement, under    *
* which the information has been supplied and solely as expressly permitted for       *
* the purpose specified in the CEVA Agreement.                                        *
*                                                                                     *
* This information is made available exclusively to licensees or parties that have    *
* received express written authorization from CEVA to download or receive the         *
* information and have agreed to the terms and conditions of the CEVA Agreement.      *
*                                                                                     *
* IF YOU HAVE NOT RECEIVED SUCH EXPRESS AUTHORIZATION AND AGREED TO THE CEVA          *
* AGREEMENT, YOU MAY NOT DOWNLOAD, INSTALL OR USE THIS INFORMATION.                   *
*                                                                                     *
* The information contained in this document is subject to change without notice      *
* and does not represent a commitment on any part of CEVA. Unless specifically        *
* agreed otherwise in the CEVA Agreement, CEVA make no warranty of any kind with      *
* regard to this material, including, but not limited to implied warranties of        *
* merchantability and fitness for a particular purpose whether arising out of law,    *
* custom, conduct or otherwise.                                                       *
*                                                                                     *
* While the information contained herein is assumed to be accurate, CEVA assumes no   *
* responsibility for any errors or omissions contained herein, and assumes no         *
* liability for special, direct, indirect or consequential damage, losses, costs,     *
* charges, claims, demands, fees or expenses, of any nature or kind, which are        *
* incurred in connection with the furnishing, performance or use of this material.    *
*                                                                                     *
* This document contains proprietary information, which is protected by U.S. and      *
* international copyright laws. All rights reserved. No part of this document may     *
* be reproduced, photocopied, or translated into another language without the prior   *
* written consent of CEVA.                                                            *
\*************************************************************************************/

#ifndef _CEVA_DSP_LIB_H
#define _CEVA_DSP_LIB_H

#include <ceva_typedef.h>

#ifdef WIN32
#define __attribute__(x)
#endif /* WIN32 */

//**********************************************************
//********************* Variables **************************
//**********************************************************
#if ( defined( _OOB ) || defined( WIN32 ) || defined( _ASM_OPT ) || defined( _VECC ) )
extern const int16_t CEVA_DSP_LIB_cos_sin_fft_16[];
extern const int32_t CEVA_DSP_LIB_cos_sin_fft_32[];
extern const float CEVA_DSP_LIB_FLOAT_cos_sin[];

#if ((CEVA_DSP_LIB_MAX_FFT==32) || (CEVA_DSP_LIB_MAX_FFT==64) || (CEVA_DSP_LIB_MAX_FFT==128) || (CEVA_DSP_LIB_MAX_FFT==256) || (CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const int16_t twi_table_16_rfft_32[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==64) || (CEVA_DSP_LIB_MAX_FFT==128) || (CEVA_DSP_LIB_MAX_FFT==256) || (CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const int16_t twi_table_16_rfft_64[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==128) || (CEVA_DSP_LIB_MAX_FFT==256) || (CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const int16_t twi_table_16_rfft_128[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==256) || (CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const int16_t twi_table_16_rfft_256[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const int16_t twi_table_16_rfft_512[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==1024))
extern const int16_t twi_table_16_rfft_1024[];
#endif

#if ((CEVA_DSP_LIB_MAX_FFT==32) || (CEVA_DSP_LIB_MAX_FFT==64) || (CEVA_DSP_LIB_MAX_FFT==128) || (CEVA_DSP_LIB_MAX_FFT==256) || (CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const int32_t twi_table_32_rfft_32[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==64) || (CEVA_DSP_LIB_MAX_FFT==128) || (CEVA_DSP_LIB_MAX_FFT==256) || (CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const int32_t twi_table_32_rfft_64[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==128) || (CEVA_DSP_LIB_MAX_FFT==256) || (CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const int32_t twi_table_32_rfft_128[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==256) || (CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const int32_t twi_table_32_rfft_256[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const int32_t twi_table_32_rfft_512[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==1024))
extern const int32_t twi_table_32_rfft_1024[];
#endif

#if ((CEVA_DSP_LIB_MAX_FFT==32) || (CEVA_DSP_LIB_MAX_FFT==64) || (CEVA_DSP_LIB_MAX_FFT==128) || (CEVA_DSP_LIB_MAX_FFT==256) || (CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const float twi_table_float_rfft_32[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==64) || (CEVA_DSP_LIB_MAX_FFT==128) || (CEVA_DSP_LIB_MAX_FFT==256) || (CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const float twi_table_float_rfft_64[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==128) || (CEVA_DSP_LIB_MAX_FFT==256) || (CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const float twi_table_float_rfft_128[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==256) || (CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const float twi_table_float_rfft_256[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==512) || (CEVA_DSP_LIB_MAX_FFT==1024))
extern const float twi_table_float_rfft_512[];
#endif
#if ((CEVA_DSP_LIB_MAX_FFT==1024))
extern const float twi_table_float_rfft_1024[];
#endif

// bit reverse tables
extern const int16_t bitrev_16_1024[];
extern const int16_t bitrev_32_1024[];

extern const int16_t bitrev1024[];
#elif defined( _VECC_EXPN )
#ifdef __HFP__
extern const float float_real_twiddles[];
extern const float float_imagine_twiddles[];
extern const int bit_reverse_256[];
extern const int bit_reverse_512[];
extern const int bit_reverse_1024[];
extern const int bit_reverse_2048[];
#endif /* __HFP__ */
#endif /* ( defined( _OOB ) || defined( WIN32 ) || defined( _ASM_OPT ) ) */

//**********************************************************
//************** Functions Decelerations *******************
//**********************************************************
#define MAT_INDEX(R,C,Ncol)          ((C) + (R)*(Ncol))
#define HERMITIAN_UP_INDEX(R,C,Ncol) ((C)+((Ncol)-1)*(R) - ((R)*((R)-1)>>1))

#if ( defined( _OOB ) || defined( WIN32 ) || defined( _ASM_OPT ) )
// Math
//~~~~~~~~~~~~~~~~~~~
// div
int16_t CEVA_DSP_LIB_DIV_INTEGER_INT16( int16_t x, int16_t y );
int32_t CEVA_DSP_LIB_DIV_INTEGER_INT32( int32_t x, int32_t y );
int16_t CEVA_DSP_LIB_DIV16_SS( int16_t var1, int16_t var2 );
int32_t CEVA_DSP_LIB_DIV32_SS( int32_t var1, int32_t var2 );
int32_t CEVA_DSP_LIB_DIV32_SHIFTED_INT32( int32_t var1, int32_t var2, int32_t shift_val );

// pow
int32_t CEVA_DSP_LIB_POW2_INT32( int32_t arg_in, int16_t arg_exp_in, int16_t *arg_exp_out );
float_32 CEVA_DSP_LIB_FLOAT_POW2( float_32 arg );
int32_t CEVA_DSP_LIB_POW10_INT32( int32_t arg_in, int16_t arg_exp_in, int16_t *arg_exp_out );
float_32 CEVA_DSP_LIB_FLOAT_POW10( float_32 arg );
int32_t CEVA_DSP_LIB_POW_INT32( int32_t arg_in_X, int16_t arg_exp_in_X, int32_t arg_in_Y, int16_t arg_exp_in_Y, int16_t *arg_exp_out );
float_32 CEVA_DSP_LIB_FLOAT_POW( float_32 arg_X, float_32 arg_Y );

// sqrt
uint16_t CEVA_DSP_LIB_SQRT_INT16( uint16_t operand_be1, uint32_t rnd_flag );
uint16_t CEVA_DSP_LIB_SQRT_INT32( uint32_t operand_be1, uint32_t rnd_flag );
float_32 CEVA_DSP_LIB_FLOAT_SQRT( float_32 a );

// Inverse sqrt
int16_t CEVA_DSP_LIB_ISQRT16( int16_t arg_in );
int32_t CEVA_DSP_LIB_ISQRT32( int32_t arg_in );
float CEVA_DSP_LIB_FLOAT_ISQRT( float arg_in );

// log
int32_t CEVA_DSP_LIB_LOG2_INT32( int32_t arg_in, int16_t arg_exp_in, int16_t *arg_exp_out );
float_32 CEVA_DSP_LIB_FLOAT_LOG2( float_32 inp );
int32_t CEVA_DSP_LIB_LOG10_INT32( int32_t arg_in, int16_t arg_exp_in, int16_t *arg_exp_out );
float_32 CEVA_DSP_LIB_FLOAT_LOG10( float_32 inp );
int32_t CEVA_DSP_LIB_LOGN_INT32( int32_t arg_in, int16_t arg_exp_in, int16_t *arg_exp_out );
float_32 CEVA_DSP_LIB_FLOAT_LOGN( float_32 inp );

// Sigmoid
int32_t CEVA_DSP_LIB_SIGMOID( int32_t x );
float_32 CEVA_DSP_LIB_FLOAT_SIGMOID( float_32 arg );

// Trigonometry
//~~~~~~~~~~~~~~~~~~~
// cos
int16_t CEVA_DSP_LIB_COS_INT16( int16_t arg );
int32_t CEVA_DSP_LIB_COS_INT32( int32_t arg );

// Sin
int16_t CEVA_DSP_LIB_SIN_INT16( int16_t arg );
int32_t CEVA_DSP_LIB_SIN_INT32( int32_t arg );
float_32 CEVA_DSP_LIB_FLOAT_SIN( float_32 arg );

// cossin
void  CEVA_DSP_LIB_COSSIN_Q15( int16_t* p_inp, int16_t* p_cossin, int N );

// tan
int16_t CEVA_DSP_LIB_TAN_INT16( int16_t arg );
int32_t CEVA_DSP_LIB_TAN_INT32( int32_t arg );
float_32 CEVA_DSP_LIB_FLOAT_TAN( float_32 arg );

// tanh
float_32 CEVA_DSP_LIB_FLOAT_TANH( float_32 arg );
    
// atan    
int16_t CEVA_DSP_LIB_ATAN_INT16( int16_t arg );
int32_t CEVA_DSP_LIB_ATAN_INT32( int32_t arg );

// atan2
int16_t  CEVA_DSP_LIB_ATAN2_INT16( int16_t Y, int16_t X );
int32_t  CEVA_DSP_LIB_ATAN2_INT32( int32_t Y, int32_t X );

// Vectors
//~~~~~~~~~~~~~~~~~~~
void CEVA_DSP_LIB_VEC_ADD16( int16_t *a, int16_t *b, uint32_t N, int16_t *c );
void CEVA_DSP_LIB_VEC_ADD32( int32_t *a, int32_t *b, uint32_t N, int32_t *c );
void CEVA_DSP_LIB_VEC_SUB16( int16_t *a, int16_t *b, uint32_t N, int16_t *c );
void CEVA_DSP_LIB_VEC_SUB32( int32_t *a, int32_t *b, uint32_t N, int32_t *c );
void CEVA_DSP_LIB_VEC_NEG16( int16_t *a, uint32_t N, int16_t *c );
void CEVA_DSP_LIB_VEC_NEG32( int32_t *a, uint32_t N, int32_t *c );
int16_t CEVA_DSP_LIB_VEC_MAX_ABS16( int16_t *a, uint32_t N );
int32_t CEVA_DSP_LIB_VEC_MAX_ABS32( int32_t *a, uint32_t N );
int16_t CEVA_DSP_LIB_VEC_MAX_ABS16_WITH_INDEX( uint32_t *ind, int16_t *buf, uint32_t size_buf, uint32_t first_index );
int32_t CEVA_DSP_LIB_VEC_MAX_ABS32_WITH_INDEX( uint32_t *ind, int32_t *buf, uint32_t size_buf, uint32_t first_index );
int16_t CEVA_DSP_LIB_VEC_MAX16( int16_t *buf, uint32_t size_buf );
int16_t CEVA_DSP_LIB_VEC_MAX16_WITH_INDEX( uint32_t *ind, int16_t *buf, uint32_t size_buf, uint32_t first_index );
int32_t CEVA_DSP_LIB_VEC_MAX32( int32_t *buf, uint32_t size_buf );
int32_t CEVA_DSP_LIB_VEC_MAX32_WITH_INDEX( uint32_t *ind, int32_t *buf, uint32_t size_buf, uint32_t first_index );
int16_t CEVA_DSP_LIB_VEC_MIN16( int16_t *buf, uint32_t size_buf );
int16_t CEVA_DSP_LIB_VEC_MIN16_WITH_INDEX( uint32_t *ind, int16_t *buf, uint32_t size_buf, uint32_t first_index );
int32_t CEVA_DSP_LIB_VEC_MIN32( int32_t *buf, uint32_t size_buf );
int32_t CEVA_DSP_LIB_VEC_MIN32_WITH_INDEX( uint32_t *ind, int32_t *buf, uint32_t size_buf, uint32_t first_index );
void CEVA_DSP_LIB_VEC_MUL_Q15( int16_t *a, int16_t *b, uint32_t N, int16_t *c );
void CEVA_DSP_LIB_VEC_MUL_Q31( int32_t *a, int32_t *b, uint32_t N, int32_t *c );
int32_t CEVA_DSP_LIB_VEC_DOT_Q15( int16_t *a, int16_t *b, uint32_t N );
int32_t CEVA_DSP_LIB_VEC_DOT_Q31( int32_t *a, int32_t *b, uint32_t N );
int32_t CEVA_DSP_LIB_VEC_DOT_Q15X7( int16_t *a, int8_t *b, uint32_t N );
int32_t CEVA_DSP_LIB_VEC_DOT_Q31X15( int32_t *a, int16_t *b, uint32_t N );
cint32_t CEVA_DSP_LIB_VEC_CX_DOT_Q15( cint16_t* A, cint16_t* B, uint32_t N );
cint32_t CEVA_DSP_LIB_VEC_CX_DOT_Q31( cint32_t *a, cint32_t *b, uint32_t N );
void CEVA_DSP_LIB_VEC_SHF16( int16_t *inp, int32_t shift_val, uint32_t size_buf, int16_t *out );
void CEVA_DSP_LIB_VEC_SHF16_NO_SAT( int16_t *inp, int32_t shift_val, uint32_t size_buf, int16_t *out );
void CEVA_DSP_LIB_VEC_SHF32( int32_t *inp, int32_t shift_val, uint32_t size_buf, int32_t *out );
void CEVA_DSP_LIB_VEC_SHF32_NO_SAT( int32_t *inp, int32_t shift_val, uint32_t size_buf, int32_t *out );
void CEVA_DSP_LIB_FLOAT_VEC_ABS( float_32 *a, uint32_t N, float_32 *c );
void CEVA_DSP_LIB_FLOAT_VEC_NEG( float_32 *a, uint32_t N, float_32 *c );
void CEVA_DSP_LIB_FLOAT_VEC_ADD( float_32 *a, float_32 *b, uint32_t N, float_32 *c );
void CEVA_DSP_LIB_FLOAT_VEC_SUB( float_32 *a, float_32 *b, uint32_t N, float_32 *c );
void CEVA_DSP_LIB_FLOAT_VEC_MUL( float_32 *a, float_32 *b, uint32_t N, float_32 *c );
float_32 CEVA_DSP_LIB_FLOAT_VEC_DOT( float_32 *a, float_32 *b, uint32_t N );
void CEVA_DSP_LIB_FLOAT_VEC_DOT_CX( cfloat *A, cfloat *B, uint32_t N, cfloat *C );
void CEVA_DSP_LIB_FLOAT_VEC_DOT_CX_CONJ( cfloat *A, cfloat *B, uint32_t N, cfloat *C );
float_32 CEVA_DSP_LIB_FLOAT_VEC_MAX( float_32 *a, uint32_t N );
float_32 CEVA_DSP_LIB_FLOAT_VEC_MIN( float_32 *a, uint32_t N );
float_32 CEVA_DSP_LIB_FLOAT_VEC_MAX_ABS( float_32 *a, uint32_t N );
float_32 CEVA_DSP_LIB_FLOAT_VEC_MAX_WITH_INDEX( uint32_t *ind, float_32 *buf, uint32_t size_buf );
float_32 CEVA_DSP_LIB_FLOAT_VEC_MIN_WITH_INDEX( uint32_t *ind, float_32 *buf, uint32_t size_buf );
float_32 CEVA_DSP_LIB_FLOAT_VEC_MAX_ABS_WITH_INDEX( uint32_t *ind, float_32 *buf, uint32_t size_buf, uint32_t first_index );

void CEVA_DSP_LIB_FLOAT_VEC_MUL( float_32 *a, float_32 *b, uint32_t N, float_32 *c );
void CEVA_DSP_LIB_FLOAT_VEC_MUL_CONST( float_32 *a, float_32 b, int32_t N, float_32 *c );
void CEVA_DSP_LIB_FLOAT_VEC_MUL_CX( cfloat *A, cfloat *B, uint32_t N, cfloat *C );
void CEVA_DSP_LIB_FLOAT_VEC_MUL_CX_CONST( cfloat *A, cfloat *B, uint32_t N, cfloat *C );
void CEVA_DSP_LIB_FLOAT_VEC_MUL_CX_CONJ( cfloat *A, cfloat *B, uint32_t N, cfloat *C );
void CEVA_DSP_LIB_FLOAT_VEC_INTPOL( float_32 *A, float_32 *B, uint32_t N, float_32 a, float_32 b, float_32 *C );
void CEVA_DSP_LIB_FLOAT_VEC_INTPOL_CX( cfloat *A, cfloat *B, uint32_t N, float_32 a, float_32 b, cfloat *C );

// Matrics
//~~~~~~~~~~~~~~~~~~~
void CEVA_DSP_LIB_MAT_CX_ADD16( cint16_t *A, cint16_t *B, uint32_t Nrow, uint32_t Ncol, cint16_t *C );
void CEVA_DSP_LIB_MAT_CX_ADD32( cint32_t *A, cint32_t *B, uint32_t Nrow, uint32_t Ncol, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_SUB16( cint16_t *A, cint16_t *B, uint32_t Nrow, uint32_t Ncol, cint16_t *C );
void CEVA_DSP_LIB_MAT_CX_SUB32( cint32_t *A, cint32_t *B, uint32_t Nrow, uint32_t Ncol, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_MUL_TRANS_Q15( cint16_t *A, uint32_t Nrow, uint32_t Ncol, cint16_t *C );
void CEVA_DSP_LIB_MAT_CX_MUL_TRANS_Q31( cint32_t *A, uint32_t Nrow, uint32_t Ncol, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_TRANS_Q15( cint16_t *A, uint32_t M, uint32_t N, cint16_t *C );
void CEVA_DSP_LIB_MAT_CX_TRANS_Q31( cint32_t *A, uint32_t M, uint32_t N, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_MUL_CONJ_Q15( cint16_t *A, cint16_t *B, uint32_t N, uint32_t M, uint32_t L, cint16_t *C );
void CEVA_DSP_LIB_MAT_CX_MUL_CONJ_Q31( cint32_t *A, cint32_t *B, uint32_t N, uint32_t M, uint32_t L, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_TRANS_MUL_Q15( cint16_t *A, uint32_t Nrow, uint32_t Ncol, cint16_t *C );
void CEVA_DSP_LIB_MAT_CX_TRANS_MUL_Q31( cint32_t *A, uint32_t Nrow, uint32_t Ncol, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_CONJ_MUL_Q15( cint16_t *A, cint16_t *B, uint32_t N, uint32_t M, uint32_t L, cint16_t *C );
void CEVA_DSP_LIB_MAT_CX_CONJ_MUL_Q31( cint32_t *A, cint32_t *B, uint32_t N, uint32_t M, uint32_t L, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_MUL_Q15( cint16_t *A, cint16_t *B, uint32_t N, uint32_t M, uint32_t L, cint16_t *C );
void CEVA_DSP_LIB_MAT_CX_MUL_Q31( cint32_t *A, cint32_t *B, uint32_t N, uint32_t M, uint32_t L, cint32_t *C );
void CEVA_DSP_LIB_FLOAT_MAT_CX_CONJ( cfloat *A, uint32_t N, uint32_t M, cfloat *C );
void CEVA_DSP_LIB_FLOAT_MAT_MUL( float_32 *A, float_32 *B, uint32_t N, uint32_t M, uint32_t L, float_32 *C );
void CEVA_DSP_LIB_FLOAT_MAT_CX_MUL( cfloat *A, cfloat *B, uint32_t N, uint32_t M, uint32_t L, cfloat *C );
void CEVA_DSP_LIB_FLOAT_MAT_TRANS( float_32 *A, uint32_t N, uint32_t M, float_32 *C );
void CEVA_DSP_LIB_FLOAT_MAT_CX_TRANS( cfloat *A, uint32_t N, uint32_t M, cfloat *C );
void CEVA_DSP_LIB_FLOAT_MAT_CX_CONJ_MUL( cfloat *A, cfloat *B, uint32_t N, uint32_t M, uint32_t L, cfloat *C );
void CEVA_DSP_LIB_FLOAT_MAT_CX_MUL_CONJ( cfloat *A, cfloat *B, uint32_t N, uint32_t M, uint32_t L, cfloat *C );
void CEVA_DSP_LIB_FLOAT_MAT_VEC_MUL( float_32 *A, float_32 *B, uint32_t N, uint32_t M, float_32 *C );
void CEVA_DSP_LIB_FLOAT_MAT_CX_VEC_CX_MUL( cfloat *A, cfloat *B, uint32_t N, uint32_t M, cfloat *C );

// Data
//~~~~~~~~~~~~~~~~~~~
void CEVA_DSP_LIB_BLOCKCOPY( int8_t *src, int8_t *dst, int32_t size );
void CEVA_DSP_LIB_BYTESWAP( int16_t *src, int16_t *dst, int32_t size );

// Signal Processing
//~~~~~~~~~~~~~~~~~~~
// FFT
void CEVA_DSP_LIB_INT16_FFT( int32_t log2_buf_len, int16_t *in_buf16, int16_t *out_buf,int16_t const *twi_table,
                             int16_t const *last_stage_twi_table, int16_t const *bitrev_tbl, int16_t *temp_buf,
                             int8_t *ScaleShift, int32_t br );
void CEVA_DSP_LIB_CX16_FFT( int32_t log2_buf_len, int16_t *in_buf16, int16_t *out_buf, int16_t const *twi_table, 
                            int16_t const *bitrev_tbl, int16_t *temp_buf, int8_t *ScaleShift, int32_t br );
void CEVA_DSP_LIB_INT32_FFT( int32_t log2_buf_len, int32_t *in_buf, int32_t *out_buf, int32_t const *twi_table,
                             int32_t const *last_stage_twi_table, int16_t const *bitrev_tbl, int32_t *temp_buf,
                             int32_t br );                            
void CEVA_DSP_LIB_CX32_FFT( int32_t log2_buf_len, int32_t *in_buf, int32_t *out_buf, int32_t const *twi_table,
                            int16_t const *bitrev_tbl, int32_t *temp_buf, int32_t br );
void CEVA_DSP_LIB_FLOAT_FFT_REAL( int32_t log2_buf_len, float_32 *in_buf, float_32 *out_buf, float_32 const *twi_table,
	                              float_32 const *last_stage_twi_table, int16_t const *bitrev_tbl, float_32 *temp_buf,
                                  int32_t br );                            
void CEVA_DSP_LIB_FLOAT_FFT_CX( int32_t log2_buf_len, float_32 *in_buf, float_32 *out_buf, float_32 const *twi_table,
                                int16_t const *bitrev_tbl, float_32 *temp_buf, int32_t br );

// IFFT
void CEVA_DSP_LIB_INT16_IFFT( int32_t log2_buf_len, int16_t *in_buf16, int16_t *out_buf, int16_t const *twi_table,
                              int16_t const *last_stage_twi_table, int16_t const *bitrev_tbl, int16_t *temp_buf,
                              int8_t *ScaleShift, int32_t bitrev );
void CEVA_DSP_LIB_CX16_IFFT( int32_t log2_buf_len, int16_t *in_buf16, int16_t *out_buf, int16_t const *twi_table,
                             int16_t const *bitrev_tbl, int16_t *temp_buf, int8_t *ScaleShift, int32_t br );
void CEVA_DSP_LIB_INT32_IFFT( int32_t log2_buf_len, int32_t *in_buf, int32_t *out_buf, int32_t const *twi_table,
                              int32_t const *last_stage_twi_table, int16_t const *bitrev_tbl, int32_t *temp_buf,
                              int32_t bitrev );
void CEVA_DSP_LIB_CX32_IFFT( int32_t log2_buf_len, int32_t *in_buf, int32_t *out_buf, int32_t const *twi_table,
                             int16_t const *bitrev_tbl, int32_t *temp_buf, int32_t br );
void CEVA_DSP_LIB_FLOAT_FFT_REAL_INV( int32_t log2_buf_len, float_32 *in_buf, float_32 *out_buf, float_32 const *twi_table,
                                      float_32 const *last_stage_twi_table, int16_t const *bitrev_tbl, float_32 *temp_buf,
                                      int32_t bitrev );                             
void CEVA_DSP_LIB_FLOAT_FFT_CX_INV( int32_t log2_buf_len, float_32 *in_buf, float_32 *out_buf, float_32 const *twi_table,
                                    int16_t const *bitrev_tbl, float_32 *temp_buf, int32_t br );

// Interpolation
void CEVA_DSP_LIB_INTPOL_Q15( int16_t *X, int16_t *Y, uint32_t N, int16_t a, int16_t b, int16_t *Z );
void CEVA_DSP_LIB_INTPOL_Q31( int32_t *X, int32_t *Y, uint32_t N, int32_t a, int32_t b, int32_t *Z );
void CEVA_DSP_LIB_INTPOL_SCX_Q15( cint16_t *X, cint16_t *Y, uint32_t N, int16_t a, int16_t b, cint16_t *Z );
void CEVA_DSP_LIB_INTPOL_SCX_Q31( cint32_t *X, cint32_t *Y, uint32_t N, int32_t a, int32_t b, cint32_t *Z );

// FIR Filter
void CEVA_DSP_LIB_FIR_Q15     ( int16_t *x, int16_t *b,  int16_t *state, int16_t *y, uint32_t N, uint32_t Nc );
void CEVA_DSP_LIB_FIR_Q31     ( int32_t *x, int32_t *b,  int32_t *state, int32_t *y, uint32_t N, uint32_t Nc );
void CEVA_DSP_LIB_FIR_SCX_Q15 ( cint16_t *x, int16_t *b,  cint16_t *state, cint16_t *y, uint32_t N, uint32_t Nc );
void CEVA_DSP_LIB_FIR_SCX_Q31 ( cint32_t *x, int32_t *b,  cint32_t *state, cint32_t *y, uint32_t N, uint32_t Nc );
void CEVA_DSP_LIB_FIR_CX_Q15  ( cint16_t *x, cint16_t *b,  cint16_t *state, cint16_t *y, uint32_t N, uint32_t Nc );
void CEVA_DSP_LIB_FIR_CX_Q31  ( cint32_t *X, cint32_t *B,  cint32_t *state, cint32_t *Y, uint32_t N, uint32_t Nc );
void CEVA_DSP_LIB_FIR_ACORR32 ( int32_t *input, int32_t *output, int32_t input_length, int32_t output_length, int16_t shift_m );
void CEVA_DSP_LIB_FIR_ACORR16 ( int16_t *input, int16_t *output, int16_t input_length, int16_t output_length );
void CEVA_DSP_LIB_FIR_XCORR32 ( int32_t *x, int32_t *h, int32_t *y, int32_t size_buf, int32_t size_buf_coef, int32_t shift_val );
void CEVA_DSP_LIB_FIR_XCORR16 ( int32_t size_buf_coef, int16_t *h, int16_t *y, int32_t size_buf, int16_t *x );
int16_t CEVA_DSP_LIB_FIR_SS16 ( int32_t size_table, int16_t sample, int16_t *state, int16_t const *coeff );
int32_t CEVA_DSP_LIB_FIR_SS32 ( int32_t size_table, int32_t sample, int32_t *state, int32_t const *coeff, int32_t shift_val );
void CEVA_DSP_LIB_FIR_SR16    ( int32_t size_table, int32_t buf_len, int16_t const *in_buf, int16_t *out_buf, int16_t const *coeff );
void CEVA_DSP_LIB_FIR_SR32    ( int32_t size_table, int32_t buf_len, int32_t const *in_buf, int32_t *out_buf, int32_t const *coeff, int32_t shift_val );
void CEVA_DSP_LIB_FIR_BLMS16  ( int16_t nInputs, int16_t adaptRate, int16_t T, int16_t *input, int16_t *desired, int16_t *StateAddr, int16_t *CoefAddr, int16_t *output, int16_t *error );
void CEVA_DSP_LIB_FIR_BLMS32  ( int16_t nInputs, int32_t adaptRate, int16_t T, int16_t shift_val, int32_t *input, int32_t *desired, int32_t *StateAddr, int32_t *CoefAddr, int32_t *output, int32_t *error );
void CEVA_DSP_LIB_FIR_DLMS32  ( int32_t adaptRate, int16_t T, int16_t shift_val, int32_t input, int32_t *StateAddr, int32_t *CoefAddr, int32_t *output, int32_t *error, int32_t desired );
void CEVA_DSP_LIB_FIR_DLMS16  ( int16_t adaptRate, int16_t T, int16_t input, int16_t desired, int16_t *StateAddr, int16_t *CoefAddr, int16_t *output, int16_t *error );
void CEVA_DSP_LIB_FIR_DEC32   (	int32_t *in_buffer, int32_t *out_buffer, int32_t *State_buf, int32_t *filter_coeffs_table, int32_t dec_val, int32_t Vec_size, int32_t N_Coeffs, int32_t shift_val );
void CEVA_DSP_LIB_FIR_DEC16   ( int16_t *in_buffer, int16_t *out_buffer, int16_t *State_buf, int16_t *filter_coeffs_table, int32_t dec_val, int32_t Vec_size, int32_t N_Coeffs );
void CEVA_DSP_LIB_FIR_CONVOL32(	int32_t *in_buffer, int32_t *out_buffer, int32_t *State_buf, int32_t *filter_coeffs_table, int32_t Vec_size, int32_t N_Coeffs, int32_t shift_val );
void CEVA_DSP_LIB_FIR_CONVOL16( int32_t Vec_size, int32_t N_Coeffs, int16_t *State_buf, int16_t *filter_coeffs_table, int16_t *out_buffer, int16_t *in_buffer );
void CEVA_DSP_LIB_FIR_INTERP16( int16_t D, int16_t N, int16_t T, int16_t T_D_ratio, int16_t *in_buffer, int16_t *out_buffer, int16_t *State_buf, int16_t *filter_coeffs_table );
void CEVA_DSP_LIB_FIR_INTERP32( int16_t D, int16_t N, int16_t T, int16_t T_D_ratio, int16_t shift_val, int32_t *in_buffer, int32_t *out_buffer, int32_t *State_buf, int32_t *filter_coeffs_table );                             

// IIR Fliter
void CEVA_DSP_LIB_IIR_BQC32( int32_t buf_len, int32_t shift_val, int32_t *x, int32_t *y, int32_t *a_b, int32_t *x_scr, int32_t *y_scr );
void CEVA_DSP_LIB_IIR_BQD32( int32_t buf_len, int32_t shift_val, int32_t *x, int32_t *y, int32_t *a_b, int32_t *x_scr, int32_t *y_scr );

#elif defined( _VECC )

// Math
//~~~~~~~~~~~~~~~~~~~
// div
int16_t CEVA_DSP_LIB_DIV_INTEGER_INT16( int16_t x, int16_t y );
int32_t CEVA_DSP_LIB_DIV_INTEGER_INT32( int32_t x, int32_t y );
int16_t CEVA_DSP_LIB_DIV16_SS( int16_t var1, int16_t var2 );
int32_t CEVA_DSP_LIB_DIV32_SS( int32_t var1, int32_t var2 );
int32_t CEVA_DSP_LIB_DIV32_SHIFTED_INT32( int32_t var1, int32_t var2, int32_t shift_val );

// pow
int32_t CEVA_DSP_LIB_POW2_INT32( int32_t arg_in, int16_t arg_exp_in, int16_t *arg_exp_out );
int32_t CEVA_DSP_LIB_POW10_INT32( int32_t arg_in, int16_t arg_exp_in, int16_t *arg_exp_out );
int32_t CEVA_DSP_LIB_POW_INT32( int32_t arg_in_X, int16_t arg_exp_in_X, int32_t arg_in_Y, int16_t arg_exp_in_Y, int16_t *arg_exp_out );

// sqrt
uint16_t CEVA_DSP_LIB_SQRT_INT16( uint16_t operand_be1, uint32_t rnd_flag );
uint16_t CEVA_DSP_LIB_SQRT_INT32( uint32_t operand_be1, uint32_t rnd_flag );

// Inverse sqrt
int16_t CEVA_DSP_LIB_ISQRT16( int16_t arg_in );
int32_t CEVA_DSP_LIB_ISQRT32( int32_t arg_in );

// log
int32_t CEVA_DSP_LIB_LOG2_INT32( int32_t arg_in, int16_t arg_exp_in, int16_t *arg_exp_out );
int32_t CEVA_DSP_LIB_LOG10_INT32( int32_t arg_in, int16_t arg_exp_in, int16_t *arg_exp_out );
int32_t CEVA_DSP_LIB_LOGN_INT32( int32_t arg_in, int16_t arg_exp_in, int16_t *arg_exp_out );

// Sigmoid
int32_t CEVA_DSP_LIB_SIGMOID( int32_t x );

// Trigonometry
//~~~~~~~~~~~~~~~~~~~
// cos
int16_t CEVA_DSP_LIB_COS_INT16( int16_t arg );
int32_t CEVA_DSP_LIB_COS_INT32( int32_t arg );

// Sin
int16_t CEVA_DSP_LIB_SIN_INT16( int16_t arg );
int32_t CEVA_DSP_LIB_SIN_INT32( int32_t arg );

// cossin
void  CEVA_DSP_LIB_COSSIN_Q15( int16_t* p_inp, int16_t* p_cossin, int N );

// tan
int16_t CEVA_DSP_LIB_TAN_INT16( int16_t arg );
int32_t CEVA_DSP_LIB_TAN_INT32( int32_t arg );
    
// atan    
int16_t CEVA_DSP_LIB_ATAN_INT16( int16_t arg );
int32_t CEVA_DSP_LIB_ATAN_INT32( int32_t arg );

// atan2
int16_t  CEVA_DSP_LIB_ATAN2_INT16( int16_t Y, int16_t X );
int32_t  CEVA_DSP_LIB_ATAN2_INT32( int32_t Y, int32_t X );

// Vectors
//~~~~~~~~~~~~~~~~~~~
void CEVA_DSP_LIB_VEC_ADD16( int16_t *a, int16_t *b, uint32_t N, int16_t *c );
void CEVA_DSP_LIB_VEC_ADD32( int32_t *a, int32_t *b, uint32_t N, int32_t *c );
void CEVA_DSP_LIB_VEC_SUB16( int16_t *a, int16_t *b, uint32_t N, int16_t *c );
void CEVA_DSP_LIB_VEC_SUB32( int32_t *a, int32_t *b, uint32_t N, int32_t *c );
void CEVA_DSP_LIB_VEC_NEG16( int16_t *a, uint32_t N, int16_t *c );
void CEVA_DSP_LIB_VEC_NEG32( int32_t *a, uint32_t N, int32_t *c );
int16_t CEVA_DSP_LIB_VEC_MAX_ABS16( int16_t *a, uint32_t N );
int32_t CEVA_DSP_LIB_VEC_MAX_ABS32( int32_t *a, uint32_t N );
int16_t CEVA_DSP_LIB_VEC_MAX_ABS16_WITH_INDEX( uint32_t *ind, int16_t *buf, uint32_t size_buf, uint32_t first_index );
int32_t CEVA_DSP_LIB_VEC_MAX_ABS32_WITH_INDEX( uint32_t *ind, int32_t *buf, uint32_t size_buf, uint32_t first_index );
int16_t CEVA_DSP_LIB_VEC_MAX16( int16_t *buf, uint32_t size_buf );
int16_t CEVA_DSP_LIB_VEC_MAX16_WITH_INDEX( uint32_t *ind, int16_t *buf, uint32_t size_buf, uint32_t first_index );
int32_t CEVA_DSP_LIB_VEC_MAX32( int32_t *buf, uint32_t size_buf );
int32_t CEVA_DSP_LIB_VEC_MAX32_WITH_INDEX( uint32_t *ind, int32_t *buf, uint32_t size_buf, uint32_t first_index );
int16_t CEVA_DSP_LIB_VEC_MIN16( int16_t *buf, uint32_t size_buf );
int16_t CEVA_DSP_LIB_VEC_MIN16_WITH_INDEX( uint32_t *ind, int16_t *buf, uint32_t size_buf, uint32_t first_index );
int32_t CEVA_DSP_LIB_VEC_MIN32( int32_t *buf, uint32_t size_buf );
int32_t CEVA_DSP_LIB_VEC_MIN32_WITH_INDEX( uint32_t *ind, int32_t *buf, uint32_t size_buf, uint32_t first_index );
void CEVA_DSP_LIB_VEC_MUL_Q15( int16_t *a, int16_t *b, uint32_t N, int16_t *c );
void CEVA_DSP_LIB_VEC_MUL_Q31( int32_t *a, int32_t *b, uint32_t N, int32_t *c );
int32_t CEVA_DSP_LIB_VEC_DOT_Q15( int16_t *a, int16_t *b, uint32_t N );
int32_t CEVA_DSP_LIB_VEC_DOT_Q31( int32_t *a, int32_t *b, uint32_t N );
int32_t CEVA_DSP_LIB_VEC_DOT_Q15X7( int16_t *a, int8_t *b, uint32_t N );
int32_t CEVA_DSP_LIB_VEC_DOT_Q31X15( int32_t *a, int16_t *b, uint32_t N );
cint32_t CEVA_DSP_LIB_VEC_CX_DOT_Q31( cint32_t *a, cint32_t *b, uint32_t N );
void CEVA_DSP_LIB_VEC_SHF16( int16_t *inp, int32_t shift_val, uint32_t size_buf, int16_t *out );
void CEVA_DSP_LIB_VEC_SHF16_NO_SAT( int16_t *inp, int32_t shift_val, uint32_t size_buf, int16_t *out );
void CEVA_DSP_LIB_VEC_SHF32( int32_t *inp, int32_t shift_val, uint32_t size_buf, int32_t *out );
void CEVA_DSP_LIB_VEC_SHF32_NO_SAT( int32_t *inp, int32_t shift_val, uint32_t size_buf, int32_t *out );

// Matrics
//~~~~~~~~~~~~~~~~~~~
void CEVA_DSP_LIB_MAT_CX_ADD16( cint16_t *A, cint16_t *B, uint32_t Nrow, uint32_t Ncol, cint16_t *C );
void CEVA_DSP_LIB_MAT_CX_ADD32( cint32_t *A, cint32_t *B, uint32_t Nrow, uint32_t Ncol, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_SUB16( cint16_t *A, cint16_t *B, uint32_t Nrow, uint32_t Ncol, cint16_t *C );
void CEVA_DSP_LIB_MAT_CX_SUB32( cint32_t *A, cint32_t *B, uint32_t Nrow, uint32_t Ncol, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_MUL_TRANS_Q31( cint32_t *A, uint32_t Nrow, uint32_t Ncol, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_TRANS_Q31( cint32_t *A, uint32_t M, uint32_t N, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_MUL_CONJ_Q15( cint16_t *A, cint16_t *B, uint32_t N, uint32_t M, uint32_t L, cint16_t *C );
void CEVA_DSP_LIB_MAT_CX_MUL_CONJ_Q31( cint32_t *A, cint32_t *B, uint32_t N, uint32_t M, uint32_t L, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_TRANS_MUL_Q15( cint16_t *A, uint32_t Nrow, uint32_t Ncol, cint16_t *C );
void CEVA_DSP_LIB_MAT_CX_TRANS_MUL_Q31( cint32_t *A, uint32_t Nrow, uint32_t Ncol, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_CONJ_MUL_Q31( cint32_t *A, cint32_t *B, uint32_t N, uint32_t M, uint32_t L, cint32_t *C );
void CEVA_DSP_LIB_MAT_CX_MUL_Q31( cint32_t *A, cint32_t *B, uint32_t N, uint32_t M, uint32_t L, cint32_t *C );

// Data
//~~~~~~~~~~~~~~~~~~~
void CEVA_DSP_LIB_BLOCKCOPY( int8_t *src, int8_t *dst, int32_t size );
void CEVA_DSP_LIB_BYTESWAP( int16_t *src, int16_t *dst, int32_t size );

// Signal Processing
//~~~~~~~~~~~~~~~~~~~
// Interpolation
void CEVA_DSP_LIB_INTPOL_Q31( int32_t *X, int32_t *Y, uint32_t N, int32_t a, int32_t b, int32_t *Z );
void CEVA_DSP_LIB_INTPOL_SCX_Q31( cint32_t *X, cint32_t *Y, uint32_t N, int32_t a, int32_t b, cint32_t *Z );

// FIR Filter
void CEVA_DSP_LIB_FIR_Q31     ( int32_t *x, int32_t *b,  int32_t *state, int32_t *y, uint32_t N, uint32_t Nc );
void CEVA_DSP_LIB_FIR_SCX_Q31 ( cint32_t *x, int32_t *b,  cint32_t *state, cint32_t *y, uint32_t N, uint32_t Nc );
void CEVA_DSP_LIB_FIR_CX_Q31  ( cint32_t *X, cint32_t *B,  cint32_t *state, cint32_t *Y, uint32_t N, uint32_t Nc );
void CEVA_DSP_LIB_FIR_ACORR32 ( int32_t *input, int32_t *output, int32_t input_length, int32_t output_length, int16_t shift_m );
void CEVA_DSP_LIB_FIR_ACORR16 ( int16_t *input, int16_t *output, int16_t input_length, int16_t output_length );
void CEVA_DSP_LIB_FIR_XCORR32 ( int32_t *x, int32_t *h, int32_t *y, int32_t size_buf, int32_t size_buf_coef, int32_t shift_val );
void CEVA_DSP_LIB_FIR_XCORR16 ( int32_t size_buf_coef, int16_t *h, int16_t *y, int32_t size_buf, int16_t *x );
int16_t CEVA_DSP_LIB_FIR_SS16 ( int32_t size_table, int16_t sample, int16_t *state, int16_t const *coeff );
int32_t CEVA_DSP_LIB_FIR_SS32 ( int32_t size_table, int32_t sample, int32_t *state, int32_t const *coeff, int32_t shift_val );
void CEVA_DSP_LIB_FIR_SR16    ( int32_t size_table, int32_t buf_len, int16_t const *in_buf, int16_t *out_buf, int16_t const *coeff );
void CEVA_DSP_LIB_FIR_SR32    ( int32_t size_table, int32_t buf_len, int32_t const *in_buf, int32_t *out_buf, int32_t const *coeff, int32_t shift_val );
void CEVA_DSP_LIB_FIR_BLMS16  ( int16_t nInputs, int16_t adaptRate, int16_t T, int16_t *input, int16_t *desired, int16_t *StateAddr, int16_t *CoefAddr, int16_t *output, int16_t *error );
void CEVA_DSP_LIB_FIR_BLMS32  ( int16_t nInputs, int32_t adaptRate, int16_t T, int16_t shift_val, int32_t *input, int32_t *desired, int32_t *StateAddr, int32_t *CoefAddr, int32_t *output, int32_t *error );
void CEVA_DSP_LIB_FIR_DLMS32  ( int32_t adaptRate, int16_t T, int16_t shift_val, int32_t input, int32_t *StateAddr, int32_t *CoefAddr, int32_t *output, int32_t *error, int32_t desired );
void CEVA_DSP_LIB_FIR_DLMS16  ( int16_t adaptRate, int16_t T, int16_t input, int16_t desired, int16_t *StateAddr, int16_t *CoefAddr, int16_t *output, int16_t *error );
void CEVA_DSP_LIB_FIR_DEC32   (	int32_t *in_buffer, int32_t *out_buffer, int32_t *State_buf, int32_t *filter_coeffs_table, int32_t dec_val, int32_t Vec_size, int32_t N_Coeffs, int32_t shift_val );
void CEVA_DSP_LIB_FIR_DEC16   ( int16_t *in_buffer, int16_t *out_buffer, int16_t *State_buf, int16_t *filter_coeffs_table, int32_t dec_val, int32_t Vec_size, int32_t N_Coeffs );
void CEVA_DSP_LIB_FIR_CONVOL32(	int32_t *in_buffer, int32_t *out_buffer, int32_t *State_buf, int32_t *filter_coeffs_table, int32_t Vec_size, int32_t N_Coeffs, int32_t shift_val );
void CEVA_DSP_LIB_FIR_CONVOL16( int32_t Vec_size, int32_t N_Coeffs, int16_t *State_buf, int16_t *filter_coeffs_table, int16_t *out_buffer, int16_t *in_buffer );
void CEVA_DSP_LIB_FIR_INTERP16( int16_t D, int16_t N, int16_t T, int16_t T_D_ratio, int16_t *in_buffer, int16_t *out_buffer, int16_t *State_buf, int16_t *filter_coeffs_table );
void CEVA_DSP_LIB_FIR_INTERP32( int16_t D, int16_t N, int16_t T, int16_t T_D_ratio, int16_t shift_val, int32_t *in_buffer, int32_t *out_buffer, int32_t *State_buf, int32_t *filter_coeffs_table );                             

// IIR Fliter
void CEVA_DSP_LIB_IIR_BQC32( int32_t buf_len, int32_t shift_val, int32_t *x, int32_t *y, int32_t *a_b, int32_t *x_scr, int32_t *y_scr );
void CEVA_DSP_LIB_IIR_BQD32( int32_t buf_len, int32_t shift_val, int32_t *x, int32_t *y, int32_t *a_b, int32_t *x_scr, int32_t *y_scr );

#elif defined( _VECC_EXPN )

#if defined( __senspro1000__ ) || defined( __senspro500__ ) || defined( __senspro250__ ) || defined( __senspro100__ ) || defined( __senspro50__ )

#endif /* ( defined( __senspro1000__ ) || defined( __senspro500__ ) || defined( __senspro250__ ) || defined( __senspro100__ ) || defined( __senspro50__ ) ) */

#if defined( SENSPRO1000 ) || defined( SENSPRO500 )
#define NUM_INT32_IN_VECTOR 16
#define NUM_INT16_IN_VECTOR 32
#define _satu               _sat
#elif defined( SENSPRO250 )
#define NUM_INT32_IN_VECTOR 8
#define NUM_INT16_IN_VECTOR 16
#define _satu               _sat
#elif SENSPRO100
#error un-supported SensPro
#elif SENSPRO50
#error un-supported SensPro
#else /* !( defined( SENSPRO1000 ) || defined( SENSPRO500 ) || defined( SENSPRO500 ) ) */
#define NUM_INT32_IN_VECTOR 16
#define NUM_INT16_IN_VECTOR 32
#define _vacccasti2n        _vacccasti16
#define _vcmpb2n            _vcmp
#define _vcmpb4n            _vcmp
#define _vcasts4n           _vcast
#define _as_int2xN_t        _as_int16
#define _as_uint2xN_t       _as_uint16
#define int2xN_t            int16
#define uint2xN_t           uint16
#define int4xN_t            int32
#define uint4xN_t           uint32
#define short2xN_t          short16
#define ushort2xN_t         ushort16
#define short4xN_t          short32
#if ( __VFP__ == 1 )
#define _vfpcmpb2n          _vfpcmp    
#define _as_float2xN_t      _as_float16
#define float2xN_t          float16  
#endif /* ( __VFP__ == 1 ) */
#endif /* ( defined( SENSPRO1000 ) || defined( SENSPRO500 ) || defined( SENSPRO500 ) ) */

#if ( __VFP__ == 1 )
    
#define NUM_FLOAT_IN_VECTOR 16

// Signal Processing
//~~~~~~~~~~~~~~~~~~~
// FFT
void CEVA_VDSP_LIB_FLOAT_FFT_CX( float_32 *in_buffer_rl, float_32 *in_buffer_cx, float_32 *out_buffer_rl, float_32 *out_buffer_cx, const float_32 *twi_table_rl, const float_32 *twi_table_cx, const int32_t *bit_reverse_indexes, int32_t final_stage_output_length );

// Math
//~~~~~~~~~~~~~~~~~~~
// div
void CEVA_VDSP_LIB_FLOAT_DIV(float_32* a_in, float_32* b_in, uint32_t N, float_32* out);

// log
void CEVA_VDSP_LIB_FLOAT_LOG2(float_32* a_in, uint32_t N, float_32* out);
void CEVA_VDSP_LIB_FLOAT_LOG10(float_32* a_in, uint32_t N, float_32* out);
void CEVA_VDSP_LIB_FLOAT_LOGN(float_32* a_in, uint32_t N, float_32* out);

// pow
void CEVA_VDSP_LIB_FLOAT_POW2(float_32* a_in, uint32_t N, float_32* out);
void CEVA_VDSP_LIB_FLOAT_POW10(float_32* a_in, uint32_t N, float_32* out);
void CEVA_VDSP_LIB_FLOAT_POW(float_32* a_in, float_32* b_in, uint32_t N, float_32* out);

// Trigonometry
//~~~~~~~~~~~~~~~~~~~
// atan 
void CEVA_VDSP_LIB_FLOAT_ATAN(float_32* a_in, uint32_t N, float_32* out);
void CEVA_VDSP_LIB_FLOAT_ATAN2(float_32* y, float_32* x, uint32_t N, float_32* out);

// cos
void CEVA_VDSP_LIB_FLOAT_COS(float_32* a_in, uint32_t N, float_32* out);

// sin
void CEVA_VDSP_LIB_FLOAT_SIN(float_32* a_in, uint32_t N, float_32* out);

// tan
void CEVA_VDSP_LIB_FLOAT_TAN(float_32* a_in, uint32_t N, float_32* out);

// Signals
//~~~~~~~~~~~~~~~~~~~
float_32 CEVA_DSP_LIB_FLOAT_SIGMOID(float_32* a_in, uint32_t N, float_32* out);

#endif /* ( __VFP__ == 1 ) */


#endif /* ( defined( _OOB ) || defined( WIN32 ) || defined( _ASM_OPT ) ) */

#endif /* _CEVA_DSP_LIB_H */
