#include "shell_bin.h"
#include "shell_core.h"
#include "shell.h"
#include "../Setting/types.h"
#include <stdlib.h>
#include <string.h>
#include "../Driver/uart.h"
#include "../Setting/configuration.h"
#include "../Driver/timer.h"
#include "error.h"

static PSV excute_pair lst_bin[] = {
    {"exit", bin_exit},
    {"echo", bin_echo},
    {"ls", bin_ls},
    {"pwd", bin_pwd},
    {"tree", bin_tree},
    {"cd", bin_cd},
    {"system", bin_system},
    {"set", bin_set},
    {"get", bin_get},
    {"loop", bin_loop},
    {"delay", bin_delay}
};

file_t bin_create() {
    file_t bin;
    bin = directory_create("bin");
    directory_insert_excute(bin,lst_bin,sizeof(lst_bin)/sizeof(lst_bin[0]));
    return bin;
}

int bin_exit(int argc, char **argv) {
    uart_putl("exit");
    exit(8);
}

int bin_echo(int argc, char** argv) {
    if (argc > 1) {
        uart_putl(argv[1]);
    }
    return 0;
}

int bin_ls(int argc, char** argv) {
    file_t it;
    file_t current = path_current();
    char buf[CMD_LENGTH];
    if (argc == 1) {
        for (it = current->child; it != NULL; it = it->next) {
            uart_bufs(it->name);
            uart_bufc(',');
        }
        uart_bufc('\r');
    } else if (argc == 2) {
        if (!strcmp(argv[1], "all")) {
            for (it = current->child; it != NULL; it = it->next) {
                uart_bufs(it->name);
                uart_bufc('[');
                uart_bufs(itoa(buf, it->fags&AccessMask, 16));
                uart_bufs("]\r");
            }
        }
    }
    uart_flush();
    return 0;
}

static void bin_pwd_sub(file_t path) {
    if (path == path_root())return;
    bin_pwd_sub(path->parent);
    uart_bufc('/');
    uart_bufs(path->name);
}

int bin_pwd(int argc, char** argv) {
    file_t current = path_current();
    if (current != path_root()) {
        bin_pwd_sub(current); //面倒くさいのでスタックを使う。
    } else {
        uart_bufc('/');
    }
    uart_putc('\r');
    return 0;
}

void bin_tree_sub(int depth, file_t path) {
    int i;
    file_t it;
    if (path == NULL)return;
    for (i = 0; i < depth; i++) {
        uart_bufc('|');
    }

    if ((path->fags & FileTypeMask) == FileTypeDirectory) {
        uart_bufs(path->name);
        uart_bufs("*\r");
        for (it = path->child; it != NULL; it = it->next) {
            bin_tree_sub(depth + 1, it);
        }
    } else {
        uart_bufl(path->name);
    }

}

int bin_tree(int argc, char** argv) {
    bin_tree_sub(0, path_current());
    uart_flush();
    return 0;
}

int bin_cd(int argc, char** argv) {
    file_t it;
    if (argc > 1) {
        it = path_get_all(argv[1]);
        if (it != NULL) {
            if ((it->fags & FileTypeMask) == FileTypeDirectory) {
                path_move(it);
            } else {
                return error_print(ERROR_NOT_DIRECTORY);
            }
        } else {
            return error_print(ERROR_FOUND_OUT);
        }
    }
    return 0;
}

int bin_system(int argc, char** argv) {
    char buf[CMD_LENGTH];
    uart_bufl("memory");
    uart_bufs("used:");
    uart_bufl(itoa(buf, file_used(), 10));
    uart_bufs("free:");
    uart_bufl(itoa(buf, file_free(), 10));
    uart_bufs("memory[KB]");
    uart_bufl(itoa(buf,file_memory(),10));
    uart_flush();
    return 0;
}

int bin_set(int argc, char** argv) {
    int cnt = 1;
    file_t file;
    if (argc <= 2) {
        return error_print(ERROR_INPUT_FEW);
    }

    while (cnt + 1 < argc) {
        file = path_get(argv[cnt]);
        if (file != NULL) {
            if (file->fags & AccessWrite) {
                switch (file->fags & FileTypeMask) {
                    case FileTypeDirectory:
                        return error_print(ERROR_FILE_TYPE_DIRECTORY);
                    case FileTypeNone:
                        return error_print(ERROR_FILE_TYPE_NONE);
                    case FileTypeInteger:
                        *file->ptr_int = atoi(argv[cnt + 1]);
                        break;
                    case FileTypeFloat:
                        *file->ptr_float = atof(argv[cnt + 1]);
                        break;
                    default:
                        return error_print(ERROR_NOT_SURPPORT);
                }
            } else {
                return error_print(ERROR_NOT_ACCESS);
            }
        } else {
            return error_print(ERROR_NOT_EXIST);
        }
        cnt += 2;
    }
    uart_flush();
    return 0;
}

int bin_get(int argc, char** argv) {
    int cnt = 1;
    file_t file;
    bool fag = false; //コンマの制御
    char buf[CMD_LENGTH];
    while (cnt < argc) {
        if (fag) {
            uart_putc(',');
        }
        file = path_get(argv[cnt]);
        if (file != NULL) {
            if (file->fags & AccessWrite) {
                switch (file->fags & FileTypeMask) {
                    case FileTypeDirectory:
                        return error_print(ERROR_FILE_TYPE_DIRECTORY);
                    case FileTypeNone:
                        return error_print(ERROR_FILE_TYPE_NONE);
                    case FileTypeInteger:
                        uart_bufs(itoa(buf, *file->ptr_int, 10));
                        break;
                    case FileTypeFloat:
                        uart_bufs(itoa(buf, (int) *file->ptr_float, 10));
                        break;
                    default:
                        return error_print(ERROR_NOT_SURPPORT);
                }
            } else {
                return error_print(ERROR_NOT_ACCESS);
            }
            cnt += 1;
            fag = true;
        }
    }
    uart_flush();
    uart_putc('\r');
    return 0;
}

int bin_loop(int argc, char** argv) {
    int cnt;
    if (argc < 2)return -1;
    int error;
    cnt = atoi(argv[1]); //ループ数を取得
    if (cnt > 0) {
        argc -= 2;
        argv += 2;

        while (!uart_exist() && cnt-- > 0) {
            if ((error=shell_system_s(argc, argv)) < 0) {
                return error;
            }
            uart_flush();

        }
    } else {
        argc -= 1;
        argv += 1;

        while (!uart_exist()) {
            if (shell_system_s(argc, argv) < 0)return -1;
            uart_flush();
        }
    }
    return 0;
}

int bin_delay(int argc, char** argv) {
    uint16_t time; //待ち時間
    const uint16_t def=10;//デフォルト値
    if (argc > 1) {
        time = atoi(argv[1]);
        if (time != 0) {//時間指定あり
            if (argc > 2) {
                if (argv[2][0] == '-') {//オプション指定あり
                    if (!strcmp(argv[2], "-ns")) {
                        delay_ns(time);
                    } else if (!strcmp(argv[2], "-us")) {
                        delay_us(time);
                    } else if (!strcmp(argv[2], "-ms")) {
                        delay_ms(time);
                    } else {
                        return error_print(ERROR_INTPUT_FRAUD);
                    }
                    if (argc > 3) {
                        return shell_system_s(argc - 3, argv + 3);
                    } else {
                        return 0;
                    }
                }else{
                    delay_us(time);//オプション指定なし
                    return shell_system_s(argc - 2, argv + 2);
                }
            }else{
                delay_us(time);
                return 0;
            }
        } else {//  時間指定なし
            delay_us(def);
            return shell_system_s(argc - 1, argv + 1);
        }
    }
    delay_us(def);
    return 0;
}
