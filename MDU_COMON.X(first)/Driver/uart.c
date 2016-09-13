#include "../Setting/configuration.h"
#include "uart.h"

#include <string.h>



//キュー実装
static volatile uint16_t rused, rin, rout;
static char rbuf[RX_BUFFER_SIZE];

static volatile uint16_t tused, tin, tout;
static char tbuf[TX_BUFFER_SIZE];

void uart_setup() {

//    const unsigned int config1 =
//            UART_EN & UART_IDLE_CON & UART_ALTRX_ALTTX & UART_DIS_LOOPBACK &
//            UART_DIS_ABAUD & UART_NO_PAR_8BIT&UART_1STOPBIT;
//    const unsigned int config2 =
//            UART_INT_TX_BUF_EMPTY & UART_TX_PIN_NORMAL & UART_TX_ENABLE &
//            UART_INT_RX_CHAR & UART_ADR_DETECT_DIS&UART_RX_OVERRUN_CLEAR;
//
//    ConfigIntUART1(UART_RX_INT_EN & UART_RX_INT_PR5 & UART_TX_INT_EN & UART_TX_INT_PR4);
//    OpenUART1(config1, config2, 10);
    U1MODEBITS mode;
    U1STABITS sta;
    //各種設定
    mode.UARTEN=true;
    mode.USIDL=false;
    mode.ALTIO=true;
    mode.WAKE=true;
    mode.LPBACK=false;
    mode.ABAUD=false;
    mode.PDSEL=0b00;//8bit parity off
    mode.STSEL=false;//1 stop
    sta.UTXISEL=true;
    sta.UTXBRK=false;
    sta.UTXEN=true;
    sta.URXISEL=0b00;//each char
    
    U1STAbits=sta;
    U1MODEbits=mode;
    U1BRG=10;
    //割り込み設定
    IFS0bits.U1RXIF=false;
    IFS0bits.U1TXIF=false;
    IPC2bits.U1RXIP=5;
    IPC2bits.U1TXIP=4;
    IEC0bits.U1RXIE=true;
    IEC0bits.U1TXIE=true;
    
    
    //管理領域初期化
    rused = 0;
    rin = rout = 0;
    tused = 0;
    tin = tout = 0;
}

//ヘルパー関数

inline uint16_t uart_depth() {
    return rused;
}

int16_t uart_find(char key) {
    register uint16_t idx, size;
    for (size = rused, idx = rout; size > 0; --size, idx = (idx + 1) % RX_BUFFER_SIZE) {
        if (rbuf[idx] == key)return idx;
    }
    return -1;
}

inline char uart_seek(int16_t idx) {
    uint16_t pos = (idx + rout) % RX_BUFFER_SIZE;
    return rbuf[pos];
}

inline void uart_remove(uint16_t cnt) {
    rout = (rout + cnt) % RX_BUFFER_SIZE;
    rused -= cnt;
}

inline void uart_remove_all(){
    rused=0;
}

inline char uart_getc() {
    register char c;
    if (uart_exist()) {
        //データが存在する。
        c = rbuf[rout];
        rout = (rout + 1) == RX_BUFFER_SIZE ? 0 : rout + 1;
        rused--;
    } else {
        c = '\0';
    }
    return c;
}

char* uart_gets(char* buf, size_t sz) {
    if (buf != NULL && sz != 0) {
        //引数は正常
        char* keep = buf;
        register char c;
        do {
            c = uart_getc();
            if (c != '\r') {
                *(buf++) = c;
            } else {
                *(buf++) = '\0';
                return keep;
            }
        } while (--sz > 0);
        *(buf - 1) = '\0'; //強制終端
        return keep;
    } else {
        return NULL;
    }
}

inline uint16_t uart_used() {
    return tused;
}

inline bool uart_full() {
    return !(TX_BUFFER_SIZE - tused > 0);
}

inline char uart_bufc(char c) {
    tbuf[tin] = c;
    tin = (tin + 1) == TX_BUFFER_SIZE ? 0 : tin + 1;
    tused++;
    return c;
}

inline const char* uart_bufs(const char* buf) {
    const char* keep = buf;
    while (*buf != '\0') {
        uart_bufc(*(buf++));
    }
    return keep;
}

inline void uart_flush() {
    if (!IEC0bits.U1TXIE) {
        while (tused > 0 && U1STAbits.UTXBF == false) {
            U1TXREG = tbuf[tout];
            tout = (tout + 1) == TX_BUFFER_SIZE ? 0 : tout + 1;
            tused--;
        }
        IEC0bits.U1TXIE = true;
    }
}

inline void  uart_stop(){
    TRISCbits.TRISC13=true;//T
    
    U1STAbits.UTXEN=false;
}

inline void uart_begin(){
    LATCbits.LATC13=true;
    TRISCbits.TRISC13=false;//TX
    
    U1STAbits.UTXEN=true;
}

inline char uart_putc(char c) {
    if (tused + 1 < TX_BUFFER_SIZE) {
        //とりあえず詰む
        uart_bufc(c);
        //送信
        uart_flush();
        return c;
    } else {
        return '\0';
    }
}

const char* uart_print(const char* str, bool nl) {
    //TODO 
    size_t len = strlen(str);
    if (tused + len < TX_BUFFER_SIZE) {
        const char* keep = str;
        //すべてキューに詰む
        uart_bufs(str);
        if (nl) {
            uart_bufc('\r');
        }
        //送信
        uart_flush();
        return keep;
    } else {
        return NULL;
    }
}

void _ISR _U1RXInterrupt() {
    char c;
    do {
        c = U1RXREG;

        if (rused < RX_BUFFER_SIZE) {
            //データ保持量が適正
            rbuf[rin] = c;
            rused++;
            rin = (rin + 1) == RX_BUFFER_SIZE ? 0 : rin + 1;
        } else {
            //無視　
        }

    } while (U1STAbits.URXDA);
    IFS0bits.U1RXIF = false;
}

void _ISR _U1TXInterrupt() {
    while (tused > 0 && U1STAbits.UTXBF == false) {
        U1TXREG = tbuf[tout];
        tout = (tout + 1) == TX_BUFFER_SIZE ? 0 : tout + 1;
        tused--;
    }

    IEC0bits.U1TXIE = tused > 0;
    IFS0bits.U1TXIF = false;
}
