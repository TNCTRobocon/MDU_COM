#include "Setting/configuration.h"
#include "Driver/driver.h"
#include "Task/task.h"
#include "Driver/uart.h"
#include <stdbool.h>
#include <stdlib.h>
 

void get_main(Q15_t,int32_t);//通信で送られてくるdtとspeedをmainに持ってくる
void set_main(float);
static Q15_t dt=ConvertQ15(0);//dtモードで送られるdt比(ここではp制御モードとdtモードの区別用)
static int32_t speed=0;//p制御モードでの回転数の理想値
float p=0.001;//要調整(のちに通信で受け取るようになる)

int main(){
    
    Q15_t px=0;
     Q15_t py=0;
    
    driver_setup();
    task_setup();
    
    timer_enable(true);
    for (;;){
        
        process_old();
      if(dt == 0 && timer_flag() == 1){
        
           //speed(理想の回転数)と
           //p(p制御のためのちょうどいい値)は本体から送る
           float x=(speed-encoder_speed_raw())*p;
           Q15_t mv=ConvertQ15(0);//p制御の操作量
           
           if(x>-0.95 && x<0.95){
           mv=ConvertQ15(x);
           }else if(x<-0.95){
           mv=ConvertQ15(-0.95);
           }else if(x>0.95){
           mv=ConvertQ15(0.95);
           }
           
             if(speed>0){
               
               if(px+mv>ConvertQ15(0.15) && px+mv<ConvertQ15(0.95)){
               px=px+mv;
               }else if(px+mv<=ConvertQ15(0.15)){
               px=ConvertQ15(0.15);    
               }else if(px+mv>=ConvertQ15(0.95)){
               px=ConvertQ15(0.95);    
               }
               
             pwm_dts(px);
           }else if(speed<0){
               
               if(py+mv<ConvertQ15(-0.15) && py+mv>ConvertQ15(-0.95)){
               py=py+mv;
               }else if(px+mv>=ConvertQ15(-0.15)){
               px=ConvertQ15(-0.15);    
               }else if(px+mv<=ConvertQ15(-0.95)){
               px=ConvertQ15(-0.95);    
               }
               
             pwm_dts(py);
           }
        }
           
    }
    __asm("reset");//初期化
    return 0;//決してここまで来ない
}

void get_main(Q15_t dt_get,int32_t speed_true){
        dt=dt_get;
        speed=speed_true;
}

void set_main(float pc){
    p=pc;
}