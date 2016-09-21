

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef APPLICATION_H//XC_HEADER_TEMPLATE_H
#define	APPLICATION_H//XC_HEADER_TEMPLATE_H
#include "../Setting/types.h"
#include "../Setting/configuration.h"
#include "../Task/task.h"
#include "../Driver/uart.h"
#include "../Driver/encoder.h"
#include "../Driver/pwm.h"
#include "../Driver/timer.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <xc.h> // include processor files - each processor file is guarded.  

void motor();
void set_motor_dt(float);
void set_motor_speed(int32_t);

Q15_t pid_limit(Q15_t,Q15_t,float,float);
Q16_16 ConvertQ16_16(float);
void set_p(float);
void set_i(float);
void set_d(float);
float get_pid(char);
void change_pid(int);
#endif	/* APPLICATION_H */

/*
 1.90   1  0.5
 1.80   1  0.25
 1.60   1  0.125
 1.20   1  0.0625
 0.40   0  0.03125
 0.80   0  0.015625
 1.60   1  0.0078125
 1.20   1  0.00390625
  //Q8_8_tの少数部の最大値  0.99609375
  //               
 */