/* 
 * File:   timer.h
 * Author: TERU
 *
 * Created on 2016/07/11, 18:14
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include<stdint.h>
#include<stdbool.h> 

//タイマ2とタイマ3による32bitタイマ
void timer_setup();
void timer_period(uint32_t period);
void timer_enable(bool check);

int16_t timer_check();

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

