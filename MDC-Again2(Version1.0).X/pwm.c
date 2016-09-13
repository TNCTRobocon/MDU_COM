#include "pwm.h"
#include <pic12f1822.h>

const static  Q16 dt_min = Q16(0.2f);

static uint8_t ton = 100;
static uint8_t toff = 100;

static struct {
        unsigned dir : 1;
        unsigned ldir : 1;
        unsigned fag:1;
} w;

void motor_init() {

    pwm_init();
    //tmr_init();
    clk_init();
}

void tmr_init() {
    //configurate on pots
    TRISAbits.TRISA4=false;
    ANSELAbits.ANSA4=false;
    LATAbits.LATA4=false;
    //init tmr0
    OPTION_REGbits.T0CS = false; //inside clock
    OPTION_REGbits.PSA = true; //prescaler enable;
    OPTION_REGbits.PS = 0; //prescale by (1-1)^2
    //interrput enable
    INTCONbits.TMR0IF = false;
    INTCONbits.TMR0IE = true;
}

void pwm_init() {
    //Pin Assignment for PWM

    /* Pin Infomation
     * PWMA  RA5 Pull-dowm
     * PWMB  RA0 AN0 Pull-down
     */

    TRISA5 = true;
    TRISA0 = true;

    ANSELAbits.ANSA0 = false; //anolog input disenable


    APFCONbits.CCP1SEL = true; //conect to RA5
    APFCONbits.P1BSEL = false; //conect to RA0

    LATAbits.LATA0 = false;
    LATAbits.LATA5 = false;

    //finished asignment.
    //tmr2 begin to count.(10bit Quality on 32MHz, 7.81kHz by divsion 4)

    T2CONbits.TMR2ON = false;
    T2CONbits.T2OUTPS = 0; //div 1
    T2CONbits.T2CKPS = 2; //div 4
    PR2 = 0xFF;
    T2CONbits.TMR2ON = true;

    //finished timer configuration

    //PWM configuration start.

    CCP1CONbits.P1M = 0b10; //half pwm
    CCP1CONbits.DC1B = 0; //Lowest 2 bit of Dt Cycle
    CCP1CONbits.CCP1M = 0b1111; //all active 'H'
    PSTR1CONbits.STR1SYNC = true; //hardware cotrol  
    //PSTR1CONbits.STR1A=true;//controled by LAT
    PSTR1CONbits.STR1A = false;
    PSTR1CONbits.STR1B = false;

    pwm_dt(0);
}

void clk_init(){
    //configurate on pots
    TRISAbits.TRISA4=false;
    ANSELAbits.ANSA4=false;
    LATAbits.LATA4=false;
    //
    CLKRCON=0b11001110;
}


inline static void insert_dt(Q16 var) {
    CCPR1L = var >> 8;
    CCP1CONbits.DC1B = var >> 6;
}

void pwm_dt(Q15 dt) {
    Q16 abs = Abs(dt) << 1; //reformat
    //    static bool ldir = false;
    //    bool dir = dt < 0;

    
    w.dir = dt < 0;

    if (dt_min > abs) {
        abs = 0;
    }

    if (w.dir != w.ldir) {
        PIR1bits.TMR2IF = false;
        while (!PIR1bits.TMR2IF);
        TRISA5 = true;
        TRISA0 = true;
        w.dir ? insert_dt(0xFFFF) : insert_dt(0); //stop

        PIR1bits.TMR2IF = false;
        while (!PIR1bits.TMR2IF);
    }

    if (abs == 0) {
        TRISA5 = true;
        TRISA0 = true;
    } else if (w.dir) {
        TRISA5 = true;
        TRISA0 = false;
        insert_dt(abs);
    } else {
        TRISA5 = false;
        TRISA0 = true;
        insert_dt(-abs);
    }

    w.ldir = w.dir;
}

inline void tmr_cycle(uint8_t on, uint8_t cycle){
    ton=on;
    toff=cycle-on;
}

inline void tmr_dt(Q8 dt, uint8_t cycle){
    tmr_cycle((uint16_t)dt*cycle>>8,cycle);
}


inline void isr_tmr() {

    if (w.fag) {
        TMR0 = ~ton;
    } else {
        TMR0 = ~toff;
    }
    LATAbits.LATA4=w.fag;
    w.fag=!w.fag;

}