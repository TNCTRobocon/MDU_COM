/* 
 * File:   motor.h
 * Author: TERU
 *
 * Created on 2016/04/04, 21:26
 */

#ifndef MOTOR_H
#define	MOTOR_H

void motor_book();

//拡張コマンド
int motor_dt(int,char**);
int motor_st(int,char**);
int motor_fr(int,char**);
int motor_gdt(int,char**);
int motor_gst(int,char**);
int motor_gfr(int,char**);
#endif	/* MOTOR_H */

