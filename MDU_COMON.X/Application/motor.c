/*
 * File:   Application.c
 * Author: satos
 *
 * Created on 2016/09/05, 16:21
 */
#include "../Setting/configuration.h"
#include "../Task/task.h"
#include "../Driver/uart.h"
#include "motor.h"

//static Q8_8_t p,i,d;
static float p=0.0001;
static float i=0.0001;
static float d=0.001;

static int8_t dt=0;//dtモードで送られるdt比(ここではp制御モードとdtモードの区別用)
static int32_t speed,se=0;
static float ps=0;
unsigned mc_flag=0;
void motor(){
      if(mc_flag == 1 && timer_flag() == 1){
          float e=speed-encoder_speed_raw();
          se+=e;
           //speed(理想の回転数)と
           //p(p制御のためのちょうどいい値)は本体から送る
           float x=e*p+se*i;
           float mv=0;//p制御の操作量
           
           if(x>-95 && x<95){
           mv=x;
           }else if(x<-95){
           mv=-95;
           }else if(x>95){
           mv=95;
           }
           
           
           
            if(speed==0){
               ps=ps+mv;
             }else if(speed>0){
               if(ps+mv>15 && ps+mv<95){
               ps=ps+mv;
               }else if(ps+mv<=15){
               ps=15;    
               }else if(ps+mv>=95){
               ps=95;    
               }
           }else if(speed<0){
               
               if(ps+mv<-15 && ps+mv>-95){
               ps=ps+mv;
               }else if(ps+mv>=-15){
               ps=-15;    
               }else if(ps+mv<=-95){
               ps=-95;    
               }
           }
           
             pwm_dts(ConvertQ15(dt_map(ps)));
             
        }
           
}

void set_motor_dt(int8_t dt_get){
        dt=dt_get;
        mc_flag=0;
        speed=0;
        se=0;
        ps=0;
}
void set_motor_speed(int32_t speed_true){
        dt=0;
        speed=speed_true;
        mc_flag=1;
        if(speed != speed_true){
        se=0;
        ps=0;
        }
}

void set_p(float pc){
    p=pc;
    /*float x=1/(pc-(int)pc);
    p=(1<<8)/x;
    if(pc>=1){
    p=p+(int)pc<<8;
    }*/   
}
void set_i(float ic){
    i=ic;
    /*float x=1/(ic-(int)ic);
    i=(1<<8)/x;
    if(ic>=1){
    i=i+(int)ic<<8;
    }*/
}
void set_d(float dc){
    d=dc;
   /* float x=1/(dc-(int)dc);
    d=(1<<8)/x;
    if(dc>=1){
    d=d+(int)dc<<8;
    }*/   
}
//Q15_t mv=0;//p制御の操作量
           
           /*if(x>-0.95 && x<0.95){
           mv=ConvertQ15(x);
           }else if(x<-0.95){
           mv=ConvertQ15(-0.95);
           }else if(x>0.95){
           mv=ConvertQ15(0.95);
           }
           
           
           
            if(speed==0){
               ps=ps+mv;
               pwm_dts(ps);
             }else if(speed>0){
               if(ps+mv>ConvertQ15(0.15) && ps+mv<ConvertQ15(0.95)){
               ps=ps+mv;
               }else if(ps+mv<=ConvertQ15(0.15)){
               ps=ConvertQ15(0.15);    
               }else if(ps+mv>=ConvertQ15(0.95)){
               ps=ConvertQ15(0.95);    
               }
               pwm_dts(ps);
           }else if(speed<0){
               
               if(ps+mv<ConvertQ15(-0.15) && ps+mv>ConvertQ15(-0.95)){
               ps=ps+mv;
               }else if(ps+mv>=ConvertQ15(-0.15)){
               ps=ConvertQ15(-0.15);    
               }else if(ps+mv<=ConvertQ15(-0.95)){
               ps=ConvertQ15(-0.95);    
               }
             pwm_dts(ps);
           }*/