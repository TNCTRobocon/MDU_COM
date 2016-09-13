/* 
 * File:   dsp_helper.h
 * Author: TERU
 *
 * Created on 2016/03/29, 2:05
 */

#ifndef DSP_HELPER_H
#define	DSP_HELPER_H

#include <stdint.h>

typedef int16_t Q15_t;
typedef uint16_t Q16_t;
//変換
#define ConvertQ15(X)  ((X < 0.0) ? (int16_t)(32768*(X) - 0.5) : (int16_t)(32767*(X) + 0.5)) 
#define ConvertQ16(x) ((x)*UINT16_MAX)
#define ReconvertQ15(x) ((x)/INT16_MAX)
#define ReconvertQ16(x) ((x)/UINT16_MAX)


#endif	/* DSP_HELPER_H */

