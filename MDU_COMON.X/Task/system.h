/* 
 * File:   system.h
 * Author: TERU
 *
 * Created on 2016/04/04, 16:37
 */


#ifndef SYSTEM_H
#define	SYSTEM_H
#include "../Setting/types.h"

#define SYSTEM_OK (0)
#define SYSTEM_FOUND_OUT (-1)//コマンドが存在しない
#define SYSTEM_NO_LOG (100)//記録を取らない
#define SYSTEM_INPUT_ERROR (-2)//入力が不正
#define SYSTEM_FORMAT_ERROR (-3)//入力形式が不正


#define Pwm_min (-0.95)
#define Pwm_max (0.95)
#define Dt_min (-95)
#define Dt_max (95)

extern int system_address_ofset;

void system_setup();
int system_decode(const char *str);
int system_call(int argc,char **argv);
int system_add(func_t,const char*,option_t);
#define system_insert(FUNC,NAME) system_add(FUNC,NAME,OptionNone)
typedef enum {
    SystemModeListen,
    SystemModeGeneral,
    SystemModeSeleceted
} SystemMode_t;
inline int system_address();
inline bool system_error_cheak(int);//単純なエラーチェック
inline void  system_change(SystemMode_t);

//標準コマンド
int basic_echo(int,char**);
int basic_select(int,char**);
int basic_reset(int,char**);
int basic_recall(int,char**);
int basic_repeat(int,char**);
int option_mode(int,char**);

int motor_dt(int,char**);

int pid_mode(int,char**);
int motor_control(int,char**);
int interval_timer_mc(int,char**);

int motor_control_period(int,char**);
int interval_timer_mcp(int,char**);

int period_encoder(int,char**);

float dt_map(float);
void ftoa(char *string,double f,int figure);
#endif	/* SYSTEM_H */