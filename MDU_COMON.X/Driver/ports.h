/* 
 * File:   ports.h
 * Author: TERU
 *
 * Created on 2016/03/23, 1:15
 */

#ifndef PORTS_H
#define	PORTS_H
#include <stdint.h>
#include <stdbool.h>


void ports_setup();

inline uint16_t port_address();

inline void led_rx(bool);
inline void led_pwm(bool);

inline int16_t port_get(int idx);

inline bool pin_encode_idx();
inline bool pin_encode_x();
inline bool pin_encode_y();

#endif	/* PORTS_H */

