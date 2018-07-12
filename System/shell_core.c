#include "shell_core.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../Driver/uart.h"
#include "../Setting/configuration.h"
#include "error.h"

static const char multi_split[] = ":";
static const char word_split[] = " \r\n";
file_t current; //現在のパス
file_t root; //最上位パス
file_t lst_quick[QUICK_MAX]; //クイックリスト

file_t path_root() {
    return root;
}

file_t path_current() {
    return current;
}

void path_move(file_t path) {
    current = path;
}

void path_init() {
    //メモリ空間を初期化しroot,currentの場所を決める。
    file_init();
    current = root = directory_create("root");

}

int path_insert(file_t brother, file_t it) {
    if (brother == NULL)return -1;
    if (it == NULL)return -2;
    //brother
    it->next = brother->next;
    brother->next = it;
    return 0;
}

Access_t path_access_get(file_t path) {
    if (path != NULL) {
        return path->fags&AccessMask;
    } else {
        return AccessNone;
    }
}

void path_access_set(file_t path, Access_t acc) {
    if (path != NULL) {
        path->fags = (path->fags&~AccessMask) | (acc & AccessMask);
    }
}

FileType_t path_filetype_get(file_t path) {
    if (path != NULL) {
        return path->fags&FileTypeMask;
    } else {
        return FileTypeNone;
    }
}

void path_filetype_set(file_t path, FileType_t type) {
    if (path != NULL) {
        path->fags = (path->fags&~FileTypeMask) | (type & FileTypeMask);
    }
}

file_t path_get(const char* name) {
    const char split[] = "/"; //Directory用区切り文字
    file_t it;
    bool fag = true;
    char buf[WORD_MAX], *p, *word;
    if (name == NULL)return NULL;
    strcpy(buf, name); //const外しを行う
    p = buf;
    if (*p == '/') {
        it = root;
        p++;
        if (*p == 0)return root;
    } else {
        it = current;
    }

    it = it->child;
    word = strtok(p, split);
    while (word != NULL) {
        while (!strcmp(".", word)) {
            word = strtok(NULL, split);
            if (word == NULL)return it;
        }

        while (!strcmp("..", word)) {
            //初回は下がりすぎているので2つ戻す。
            if (fag) {
                it = it->parent;
                fag = false;
            }

            it = it->parent;
            word = strtok(NULL, split);
            if (word == NULL)return it;
        }

        if (it->name == NULL) {
        } else if (!strcmp(word, it->name)) {
            word = strtok(NULL, split);
            if (word == NULL) {
                return it;
            } else {
                it = it->child;
                if (it == NULL)return NULL;
            }
        } else {
            it = it->next;
            if (it == NULL)return NULL;
        }

    }
    return it;
}

file_t path_get_registor(const char* name) {
    int idx;
    file_t it;
    if (name == NULL)return NULL;
    for (idx = 0; idx < QUICK_MAX; idx++) {
        if (lst_quick[idx] != NULL) {
            for (it = lst_quick[idx]->child; it != NULL; it = it->next) {
                if (!strcmp(name, it->name)) {
                    return it;
                }
            }
        }
    }
    return NULL;
}

file_t path_get_all(const char* name) {
    file_t it;
    it = path_get(name);
    if (it != NULL)return it;
    it = path_get_registor(name);
    if (it != NULL)return it;
    return NULL;
}

file_t directory_create(const char *name) {
    file_t path = file_create(name);

    if (name == NULL)return NULL;
    path->fags = AccessNone | FileTypeDirectory;
    path->child = NULL; //まだ子要素は存在しない。
    return path;
}

int directory_insert(file_t directory, file_t file) {
    if (directory == NULL)return -1; //error
    if (file == NULL)return -2;
    if ((directory->fags & FileTypeMask) != FileTypeDirectory)return -3;


    //メモリー配置を行う。
    file->parent = directory;
    file->next = directory->child;
    directory->child = file;

    return 0;
}

int directory_registor(file_t dir) {
    if (dir == NULL)return -1;
    int idx;
    for (idx = 0; idx < QUICK_MAX; idx++) {
        if (lst_quick[idx] == NULL) {
            lst_quick[idx] = dir;
            return 0;
        }
    }
    return -1;
}

void directory_registor_init() {
    int idx;
    for (idx = 0; idx < QUICK_MAX; idx++) {
        lst_quick[idx] = NULL;
    }
}

int shell_system(char *command) {
    int mcnt = 0, midx = 0, argc = 0, ans = 0;
    char *argv[WORD_MAX], *mul[MULTI_MAX];
    char *temp;

    mul[mcnt] = temp = strtok(command, multi_split);
    while (temp != NULL && argc < MULTI_MAX) {
        mul[++mcnt] = temp = strtok(NULL, multi_split);
    }
    for (; midx < mcnt; midx++) {
        argv[argc = 0] = temp = strtok(mul[midx], word_split);
        while (temp != NULL && argc < WORD_MAX) {
            argv[++argc] = temp = strtok(NULL, word_split);
        }
        ans = shell_system_s(argc, argv);
    }
    return ans;
}

int shell_system_s(int argc, char* argv[]) {
    file_t it;
    it = path_get_all(argv[0]);
    if (it == NULL) {
        return  error_print(ERROR_NOT_EXIST);
    }

    switch (it->fags & FileTypeExcute) {
        case FileTypeExcute:
            if (it->fags & AccessExcute) {
                return it->func(argc, argv);
            } else {
                return error_print(ERROR_NOT_SURPPORT);
            }
        default:
            return error_print(ERROR_NOT_EXCUTE);
    }
}

file_t execute_create(const char* name, int(*func)(int, char**)) {
    file_t path = file_create(name);
    if (path == NULL)return NULL;
    path->fags = AccessExcute | FileTypeExcute;
    path->func = func;
    return path;
}

file_t integer_create(const char* name, int* ptr, Access_t acc) {
    file_t path = file_create(name);
    if (path == NULL)return NULL;
    if (ptr == NULL)return NULL;
    path->fags = acc | FileTypeInteger;
    path->ptr_int = ptr;
    return path;
}

file_t float_create(const char* name, float* ptr, Access_t acc) {
    file_t path = file_create(name);
    if (path == NULL)return NULL;
    if (ptr == NULL)return NULL;
    path->fags = acc | FileTypeFloat;
    path->ptr_float = ptr;
    return path;

}

//ここでは最低限し無くてはならないuartの処理についてのみ記述する。
static void (*listen)(void) = NULL;
static void (*general)(void) = NULL;
static void (*selected)(void) = NULL;

void select_listen_set(void (*func)(void)) {
    listen = func;
}

void select_general_set(void (*func)(void)) {
    general = func;
}

void select_selected_set(void (*func)(void)) {
    selected = func;
}

void select_listen() {
    uart_stop();
    //uart_putl("change listen");
    //uart_begin();
    if (listen != NULL) {
        listen();
    }
}

void select_general() {
    uart_stop();
    //uart_putl("change general");
    //uart_begin();
    if (general != NULL) {
        general();
    }
}

void select_selected() {
    uart_clr();
    uart_putl("open bus");
    uart_begin();
    if (selected != NULL) {
        selected();
    }
}

file_t directory_insert_excute(file_t dir, const excute_pair* lst_pair, uint16_t size) {
    int i;
    for (i = 0; i < size; i++) {
        directory_insert(dir, execute_create(lst_pair[i].name, lst_pair[i].command));
    }
    return dir;
}