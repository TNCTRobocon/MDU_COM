/* 
 * File:   pwm.h
 * Author: TERU
 *
 * Created on 2015/08/19, 20:43
 */

#ifndef PWM_H
#define	PWM_H
#include <stdint.h>
#include <stdbool.h>
typedef uint16_t Q16;//for Q16 format.
typedef int16_t Q15;//for Q15 format.
typedef uint8_t Q8;//for Q8 format


//cast to QXX format, but won't cast invert. 
#define Q16(x) (uint16_t)((float)(x)*UINT16_MAX)
#define Q15(x) (int16_t)((float)(x)*INT16_MAX)
#define Q8(x) (uint8_t)((float)(x)*UINT8_MAX)

#define Abs(x) ((x)>0?(x):-(x))
//初期化関数
void motor_init();

void tmr_init();
void pwm_init();
void clk_init();

//これらは割り込みを有効にした後に実行すること。
void pwm_dt(Q15 dt);
inline void tmr_cycle(uint8_t on,uint8_t cycle);
inline void tmr_dt(Q8 dt,uint8_t cycle);
//割り込み以外呼び出し禁止
inline void isr_tmr();

#endif	/* PWM_H */

