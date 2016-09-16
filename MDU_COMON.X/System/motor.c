#include <stdlib.h>
#include <math.h>
#include "motor.h"
#include "shell.h"
#include "../Driver/pwm.h"
#include "../Setting/types.h"

file_t motor_create(){
    file_t mtr;
    mtr=directory_create("mtr");
    directory_insert(mtr,execute_create("dt",motor_dt));
    
    return mtr;
}

static inline float absf(float var){
    return var>0?var:-var;
}


int motor_dt(int argc,char** argv){
    float dt;
    if (argc<2){
        pwm_dts(0);
    }else{
        dt =atof(argv[1]);
        pwm_dts((int16_t)(dt*INT16_MAX));
    }
    return 0;
}