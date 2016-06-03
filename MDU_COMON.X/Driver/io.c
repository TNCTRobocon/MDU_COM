#include "io.h"
#include "../Task/system.h"
#include "uart.h"
#include "encoder.h"
#include "pwm.h"
#include "ports.h"
#include "../Setting/p30F4012.h"
#include <string.h>
#include <stdlib.h>

//変数名等
const char cmp_port_encode[] = "port.encoder"; //read only
const char cmp_port_idx[] = "port.idx"; //read only
const char cmp_addr_value[] = "addr"; //read only
const char cmp_addr_ofset[] = "addr.ofset"; //border
const char cmp_pwm_max[] = "pwm.max"; //border
const char cmp_pwm_min[] = "pwm.min"; //border
const char cmp_pwm_period[] = "pwm.period"; //border
const char cmp_pwm_dt[]="pwm.dt";//read only


//オプション
const char cmp_help[] = "help";
//Help時用　グループ分け ここにあるとヘルプに表示される。
const char *group_get[] = {cmp_port_encode, cmp_port_idx, cmp_addr_value, cmp_addr_ofset,
                           cmp_pwm_max,cmp_pwm_min,cmp_pwm_period,cmp_pwm_dt};
const char *group_set[] = {cmp_addr_ofset,cmp_pwm_max,cmp_pwm_min,cmp_pwm_period};


void io_setup() {
    //登録
    system_insert(io_get, "get");
    system_insert(io_set, "set");
    system_insert(option_test, "test");
    system_insert(motor_dt, "dt");
}

int io_get(int argc, char** argv) {
    //最初の要素を削除
    char* cmp = argv[1];
    char buf[32];
    bool split_fag = false;
    argc--;
    argv++;

    //help
    if (!strcmp(cmp, cmp_help) || argc < 0) {
        int idx;
        uart_puts("Format: get [Name]..\r"
                "[Name] ={");
        for (idx = 0; idx < (sizeof (group_get) / sizeof (*group_get)); idx++) {
            if (idx != 0)uart_bufc(',');
            uart_puts(group_get[idx]);
        }
        uart_putc('}');
    } else {

        while (argc > 0) {

            cmp = argv[0];
            if (split_fag) {
                uart_bufc(',');
            }

            if (!strcmp(cmp, cmp_port_encode)) {
                //エンコーダ情報
                uart_bufs("Idx:");
                uart_bufc(pin_encode_idx() ? '1' : '0');
                uart_bufc(',');
                uart_bufs("X:");
                uart_bufc(pin_encode_x() ? '1' : '0');
                uart_bufc(',');
                uart_bufs("Y:");
                uart_bufc(pin_encode_y() ? '1' : '0');

            } else if (!strcmp(cmp, cmp_port_idx)) {
                int idx;
                int port;
                idx = atoi(argv[1]);
                port = port_get(idx);
                itoa(buf, port, 16);
                uart_bufs("port.idx(");
                uart_bufc('0' + idx);
                uart_bufs("):");
                uart_bufs(buf);

                argc--;
                argv++; //go more one!!
            } else if (!strcmp(cmp, cmp_addr_value)) {
                uart_bufs("addr:");
                itoa(buf, system_address(), 10);
                uart_bufs(buf);
            } else if (!strcmp(cmp, cmp_addr_ofset)) {
                uart_bufs("addr.ofset:");
                itoa(buf, system_address_ofset, 10);
                uart_bufs(buf);
            } else if (!strcmp(cmp, cmp_pwm_period)) {
                uart_bufs("pwm.period:");
                itoa(buf, (get_pwm_period()/10), 10);
                uart_bufs(buf);
                uart_bufc('0'+get_pwm_period()%10);
            } else if (!strcmp(cmp, cmp_pwm_max)) {
                Q16_t max =get_pwm_max();//UINT16_MAX倍されている
                int var = max/(UINT16_MAX/1000);//1000分率になる。
                uart_bufs("pwm.max:0.");
                itoa(buf,var,10);
                uart_bufs(buf);
            } else if (!strcmp(cmp, cmp_pwm_min)) {
                Q16_t min =get_pwm_min();//UINT16_MAX倍されている
                int var = min/(UINT16_MAX/1000);//1000分率になる。
                uart_bufs("pwm.min:0.");
                itoa(buf,var,10);
                uart_bufs(buf);
            }else if (!strcmp(cmp,cmp_pwm_dt)){
                Q16_t dt=get_pwm_dt();
                int var =dt/(UINT16_MAX/1000);
                uart_bufs("pwm.dt:");
                itoa(buf,var,10);
                uart_bufs(buf);
            }else{
                uart_bufs("?");
            }

            uart_flush();
            argc--;
            argv++; //go pre
            split_fag = true;
        }
    }
    uart_bufc('\r');
    uart_flush(); //ここで出力
    return 0;
}

int io_set(int argc, char** argv) {
    //一つ目を破棄
    argc -= 1;
    argv++;
    char *name = *argv; //変数名
    char *var; //値(文字列)
    int idx;
    if (argc < 0 || !strcmp(name, cmp_help)) {
        uart_bufs("Format:set ([Name] [value])..\r");
        uart_bufs("[Name]={");
        for (idx = 0; idx < (sizeof (group_set) / sizeof (*group_set)); idx++) {
            if (idx != 0)uart_bufc(',');
            uart_bufs(group_set[idx]);
        }
        uart_bufc('}');
    } else {
        while (argc > 1) {//二つ移動するため
            name = *argv;
            var = *(argv + 1);

            if (!strcmp(name, cmp_addr_ofset)) {
                system_address_ofset = atoi(var);
            }else if(!strcmp(name,cmp_pwm_max)){
                set_pwm_max(atof(var)*UINT16_MAX);
            }else if (!strcmp(name,cmp_pwm_min)){
                set_pwm_min(atof(var)*UINT16_MAX);
            }else if (!strcmp(name,cmp_pwm_period)){
                set_pwm_period(atoi(var));
            }else {
                uart_bufs("?");
            }
            //移動
            argc -= 2;
            argv += 2;
        }
    }
    uart_flush();
    return 0;
}

int option_test(int argc, char** argv) {
    char buf[8];
    itoa(buf, encoder_value(), 10);
    uart_putl(buf);
    return 0;
}

int motor_dt(int argc, char** argv) {
    if (argc == 0) {
        pwm_shutdown(true);
    } else {
        pwm_shutdown(false);
        float dt = atof(argv[1]);
        pwm_dts(ConvertQ15(dt));
    }
    return 0;
}