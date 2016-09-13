#include "system.h"
#include <string.h>
#include <stdlib.h>

#include "../Driver/uart.h"
#include "../Driver/ports.h"

#include "../Setting/configuration.h"


int system_address_ofset = +16; //アドレスを変化させる

typedef struct {
    func_t func;
    const char* name;
    option_t option;
} system_item_t;

static system_item_t table[SYSTEM_SIZE]; //実体
//static system_item_t*   quick[SYSTEM_SIZE];//管理用の領域
//TODO あとで二分探索

static SystemMode_t system_mode;
static char system_log[CMD_LENGTH]; //RE用の過去の命令の記録
static bool debag_mode = false;

void system_setup() {
    int i;
    for (i = 0; i < SYSTEM_SIZE; i++) {
        table[i].option = OptionDisenable;
        //quick[i]=NULL;
    }
    //system_mode=OnlySystemMode;

    system_add(basic_select, "sel", OptionSystem);
    system_add(basic_reset, "reboot", OptionSystem);
    system_add(basic_recall, "recall", OptionSystem);
    system_insert(basic_echo, "echo");
    system_insert(option_mode, "option");

    system_insert(basic_repeat, "repeat");
    //lip code
    system_change(SystemModeListen);
    //uart_puts("wake up on debag mode [Don't Multi conection.]\r");
    //system_mode=SystemModeListen;
}

int system_decode(const char *str) {
    int argc;
    char text[CMD_LENGTH];
    char* argv[CMD_MAX];
    static const char split[] = " :";
    int err;
    if (str != NULL) {
        //being decode
        argc = 0;
        strcpy(text, str);
        argv[argc] = strtok(text, split);
        while (argv[argc] != NULL && argc < CMD_MAX) {
            argv[++argc] = strtok(NULL, split);
        }
        //call action
        err = system_call(argc, argv);

        switch (err) {
            case SYSTEM_FOUND_OUT:
                uart_putl("Error:Found out.");
                break;
            case SYSTEM_NO_LOG:
                break;
            case SYSTEM_INPUT_ERROR:
                uart_putl("Error:Input is bad");
            default:
                //save last commnad for "RE" command
                strcpy(system_log, str);
                break;
        }
        return err;
    } else {
        return -1; //入力が不正である。
    }
}

int system_call(int argc, char** argv) {
    if (argc > 0) {
        int i;
        for (i = 0; i < SYSTEM_SIZE; i++) {
            option_t op = table[i].option;
            bool fag = op != OptionDisenable&&
                    !strcmp(table[i].name, argv[0]);


            if (fag) {
                switch (system_mode) {
                    case SystemModeListen:
                        if (op == OptionSystem) {
                            return table[i].func(argc, argv);
                        }
                        break;
                    case SystemModeGeneral:
                    case SystemModeSeleceted:
                        return table[i].func(argc, argv);
                }
            }
        }
        return SYSTEM_FOUND_OUT; //存在しない
    } else {
        return SYSTEM_INPUT_ERROR; //不正
    }
}

int system_add(func_t func, const char* name, option_t option) {
    //find an unused area.
    int i;
    system_item_t* p;

    for (i = 0; i < SYSTEM_SIZE; i++) {
        if (table[i].option == OptionDisenable) {
            break;
        }
    }

    if (i == SYSTEM_SIZE)return -1; //空き領域がない
    //代入
    p = &table[i];
    p->func = func;
    p->name = name;
    p->option = option;

    return 0;
}

inline int system_address() {
    return port_address() + system_address_ofset;
}

inline bool system_error_cheak(int err){
    return err<0;//適時へんこうすること
}

inline void system_change(SystemMode_t mode) {
    system_mode = mode;
    switch (mode) {
        case SystemModeListen:
        case SystemModeGeneral:
            uart_stop();
            led_rx(false);
            return;
        case SystemModeSeleceted:
            uart_begin();
            led_rx(true);
            return;
    }
}

int basic_echo(int argc, char** argv) {
    if (argc > 0)uart_putl(argv[1]);
    return 0;
}

int basic_select(int argc, char** argv) {
    if (argc > 0) {
        int tadd = atoi(argv[1]);

        if (tadd == 0) {
            //Genaral Mode
            system_change(SystemModeGeneral);
        } else if (tadd == system_address()) {
            //Selected
            system_change(SystemModeSeleceted);
        } else {
            system_change(SystemModeListen);
        }
    } else {
        system_change(SystemModeListen);
    }
    return 0;
}

int basic_reset(int argc, char** argv) {
    asm("reset");
    return 0; //ただしもどらない
}

int basic_recall(int argc, char** argv) {
    if (debag_mode) {
        uart_bufs("RE:");
        uart_putl(system_log);
    }
    system_decode(system_log);
    return SYSTEM_NO_LOG;
}

int basic_repeat(int argc, char** argv) {
    if (argc > 1) {
        uint16_t cnt;
        int test;
        
        do {
            test=system_call(argc - 1, argv + 1);
            if (system_error_cheak(test))return test;
            for (cnt = 0; cnt < 0xffff; cnt++); //遅延
        } while (uart_depth() == 0);

        return 0;
    } else {
        return SYSTEM_INPUT_ERROR;
    }

}

int option_mode(int argc, char** argv) {
    if (argc > 1) {

        if (*argv[1] == 'd') {
            debag_mode = true;
            uart_putl("changed debag mode");
        } else {
            debag_mode = false;
            uart_putl("reset mode");
        }
    }
    return 0;
}