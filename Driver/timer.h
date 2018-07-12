/* 
 * File:   timer.h
 * Author: TERU
 *
 * Created on 2016/07/11, 18:14
 */

#ifndef TIMER_HEADER_H
#define	TIMER_HEADER_H

#include<stdint.h>
#include<stdbool.h> 

//タイマ2とタイマ3による32bitタイマ
void timer23_setup();
void timer23_period(uint32_t period);
void timer23_enable(bool check);

int16_t timer23_check();

//タイマー1によるSystem用delay
// 指定された時間以上の時間を待つ。

void delay_ns(uint16_t);
void delay_us(uint16_t);
void delay_ms(uint16_t);


#endif	/* TIMER_H */

