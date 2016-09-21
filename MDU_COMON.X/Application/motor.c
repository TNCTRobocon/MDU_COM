/*
 * File:   Application.c
 * Author: satos
 *
 * Created on 2016/09/05, 16:21
 */
#include "motor.h"


static /*Q16_16*/float p=0.005;
static /*Q16_16*/float i=0.0002;
static /*Q16_16*/float d=0.0005;

static int8_t dt=0;//dtモードで送られるdt比(ここではp制御モードとdtモードの区別用)
static int32_t speed,dir=0;
static /*Q16_16*/float  now_error,sigma_error,delta_error,before_error=0;
static Q15_t ps=0;
static int8_t mc_flag=0;
void motor(){
    
      if(mc_flag == 1  && timer_flag() == 1){
          now_error=speed-encoder_speed_raw();
          if(speed!=0 && abs(now_error)!=1){
          sigma_error+=now_error;
          }
          delta_error=now_error-before_error;
          float u=now_error*p+sigma_error*i+delta_error*d;//(error*p+se*i)>>16
          Q15_t mv=0;//p制御の操作量
           
           if(u>-0.95 && u<0.95){
           mv=ConvertQ15(u);
           }else if(u<-0.95){
           mv=ConvertQ15(-0.95);
           }else if(u>0.95){
           mv=ConvertQ15(0.95);
           }
           
           if(speed==0){
               ps=pid_limit(ps,mv,-0.95,0.95);
             }else if(speed>0){
               ps=pid_limit(ps,mv,0.15,0.95);
             }else if(speed<0){
               ps=pid_limit(ps,mv,-0.95,-0.15);
           }
            pwm_dts(ps);
            before_error=now_error;
        }
           
}

void set_motor_dt(float dt_get){
        dt=(int)dt_get;
        mc_flag=0;
        speed=0;
        sigma_error=0;
        //delta_error=0;
        ps=0;
}
void set_motor_speed(int32_t speed_true){
        dt=0;
        mc_flag=1;
        int32_t sign = (speed_true>0)-(speed_true<0);
        if(speed != speed_true){
        sigma_error=0;
        if((dir*sign)<0){
        ps=0;
        }
        }
        speed=speed_true;
        dir=sign;
}

Q15_t pid_limit(Q15_t n,Q15_t mv,float min,float max){
     if(n+mv>ConvertQ15(min) && n+mv<ConvertQ15(max)){
               return (n+mv);
               }else if(n+mv<=ConvertQ15(min)){
               return ConvertQ15(min);    
               }else {//(n+mv>=ConvertQ15(max)){
               return ConvertQ15(max);    
               }
}

Q16_16 ConvertQ16_16(float xc){
    Q16_16 c=1;
    Q16_16 yc=(int)xc;
    float sc=xc-(int)xc;
     sc=1/sc;
     c=c<<16;
     c=c/sc;
     yc=yc<<16;
     c=(0x0000FFFF&c) + (0xFFFF0000&yc);
    return  c;
}

void set_p(float pc){
    p=pc;
    //p=ConvertQ16_16(pc);
}
void set_i(float ic){
    i=ic;
    //i=ConvertQ16_16(ic);
}
void set_d(float dc){
    d=dc;
    //d=ConvertQ16_16(dc);
}

float get_pid(char pid){
    switch(pid){
      case 'p':
         return p;
         break;
      case 'i':
         return i;
         break;
      case 'd':
         return d;
         break;
      default:
         return 0;      
    }
}

void change_pid(int mode){
    switch(mode){
        case 1://'p':
          i=0;
          d=0;
         break;
        case 2://'pi':
          d=0;
         break;
        case 3://'pd':
          i=0;
         break;
      default://とりあえずオフ
          p=0;
          i=0;
          d=0;
    }
}