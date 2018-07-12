#include "file.h"
#include <stddef.h>
#include <stdint.h>
#include "../Setting/configuration.h"
static GC_Body_t lst_gc[FILE_MAX], *gc_free; //GCの管理領域

void file_init() {
    uint16_t i;
    file_t p;
    //make single link sturcture
    gc_free = &lst_gc[0];
    for (i = 0; i < FILE_MAX - 1; i++) {
        lst_gc[i].next = &lst_gc[i + 1];
    }
    lst_gc[FILE_MAX - 1].next = NULL;
    //stop bag
    for (i = 0; i < FILE_MAX - 1; i++) {
        p = (file_t) & lst_gc[i];
        p->next = NULL;
        p->parent = NULL;
        p->child = NULL;
    }

}

uint16_t file_free() {
    GC_Body_t *it;
    unsigned int cnt = 1;
    if (gc_free == NULL)return 0;
    for (it = gc_free; it->next != NULL; it = it->next) {
        cnt++;
    }
    return cnt;
}

uint16_t file_used() {
    return FILE_MAX - file_free();
}

uint16_t file_memory(){
    return sizeof (lst_gc);
}


file_t file_create(const char *name) {
    GC_Body_t *mem;
    file_t path;
    //メモリー配置(pop)
    if (gc_free == NULL)return NULL; //メモリーが配置できない。
    mem = (GC_Body_t*) gc_free;
    gc_free = gc_free->next;
    mem->next = NULL;
    path = (file_t) mem;
    //木構造を初期化
    path->parent = NULL;
    path->child = NULL; //一応NULLにしておく
    path->next = NULL;
    path->name = name;
    return path;
}

void file_delete(file_t path) {
    //push動作
    GC_Body_t* mem = (GC_Body_t*) path;
    mem->next = gc_free;
    gc_free = mem;
}