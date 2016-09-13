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

///static Q8_8_t p,i,d;
static float p=0.001;
static float i=0.0001;
static float d=0.001;

static Q15_t dt=ConvertQ15(0);//dtモードで送られるdt比(ここではp制御モードとdtモードの区別用)
static int32_t speed,se=0;
static Q15_t ps=0;

void motor(){
   //p=1<<8;//0.001;//要調整(のちに通信で受け取るようになる)
    //i=1<<8;
      if(dt == 0 && timer_flag() == 1){
          float e=speed-encoder_speed_raw();
          se+=e;
           //speed(理想の回転数)と
           //p(p制御のためのちょうどいい値)は本体から送る
          
          float x=e*p+se*i;
           Q15_t mv=ConvertQ15(0);//p制御の操作量
           
           if(x>-0.95 && x<0.95){
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
           }
           
        }
           
}

void set_motor_dt(Q15_t dt_get){
        dt=dt_get;
        speed=0;
        se=0;
        ps=0;
}
void set_motor_speed(int32_t speed_true){
        dt=0;
        speed=speed_true;
        if(speed != speed_true){
        se=0;
        ps=0;
        }
}

void set_p(Q8_8_t pc){
    p=pc;
}
void set_i(Q8_8_t ic){
    i=ic;
}
void set_d(Q8_8_t dc){
    d=dc;
}