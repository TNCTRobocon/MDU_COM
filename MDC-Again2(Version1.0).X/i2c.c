#include <pic12f1822.h>
#include "i2c.h"
#include "pwm.h"

static int8_t i2c_data;


//揚互換

void i2c_init(uint8_t address) {

    INTCON = 0b11000000;

    SSPADD = (address << 1);
    SSPSTAT = 0b10000100;
    SSPCON = 0b00110110;
    SSPCON2 = 0b10010000;
    SSPCON3 = 0;

    SSP1IE = true;
    SSP1IF = false;
}



inline void i2c_isr(){
    unsigned char dammy;
    if(SSP1IF){
        if(!R_nW){
            if(!D_nA){
                dammy=SSPBUF;
            }else{
                i2c_data=(int8_t)SSPBUF;
            }
        }
    }
    SSP1IF=0;
    CKP=1;
}

int8_t i2c_get(){
    return i2c_data;
}

//void i2c_task() {
//    int8_t dammy;
//    if (SSP1IF) {
//        if (!R_nW) {
//            if (!D_nA) {
//                dammy = SSPBUF;
//            } else {
//                pwm_dt((int16_t) SSPBUF << 8);
//            }
//            SSP1IF = false;
//            CKP = true;
//        }
//    }
//}