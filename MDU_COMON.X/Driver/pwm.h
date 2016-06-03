/* 
 * File:   pwm.h
 * Author: TERU
 *
 * Created on 2016/03/23, 2:52
 */

#ifndef PWM_H
#define	PWM_H
#include "../Setting/types.h"

//基本的にシングルタスクの関数として記述している。
void pwm_setup();

inline void pwm_dt_direct(uint16_t dt,triple_t dir);

inline void pwm_dt(Q16_t dt,triple_t dir);
inline void pwm_dts(Q15_t dt);
//プロパティ及びユーティリティ
inline void set_pwm_period(uint16_t);
inline uint16_t get_pwm_period();
inline void set_pwm_max(uint16_t);
inline uint16_t get_pwm_max();
inline void set_pwm_min(uint16_t);
inline uint16_t get_pwm_min();
inline Q16_t  get_pwm_dt();

inline void pwm_shutdown(bool fag);
#endif	/* PWM_H */

