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
    
void timer_setup();
void timer_period(uint16_t period);
void timer_enable(bool);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

