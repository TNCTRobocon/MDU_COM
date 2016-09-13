

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef APPLICATION_H//XC_HEADER_TEMPLATE_H
#define	APPLICATION_H//XC_HEADER_TEMPLATE_H
#include "../Setting/types.h"
#include <stdint.h>
#include <stdbool.h>
//#include <xc.h> // include processor files - each processor file is guarded.  

void motor();
void set_motor_dt(Q15_t);
void set_motor_speed(int32_t);
void set_p(Q8_8_t);
void set_i(Q8_8_t);
void set_d(Q8_8_t);

#endif	/* APPLICATION_H */

