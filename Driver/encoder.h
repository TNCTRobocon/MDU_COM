/* 
 * File:   encoder.h
 * Author: TERU
 *
 * Created on 2016/03/23, 2:54
 */

#ifndef ENCODER_H
#define	ENCODER_H
#include <stdint.h>
#include <stdbool.h>

void encoder_setup();

inline int16_t encoder_raw();
inline int16_t encoder_speed_raw();//差分
inline int16_t encoder_spin_raw();//r/sec

void encoder_period(uint16_t);
uint32_t get_encoder_period();
int16_t timer_flag();
inline void encoder_direction(bool);







#endif	/* ENCODER_H */

