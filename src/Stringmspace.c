#include <string.h>
#include <stdlib.h>
#include "Stringmspace.h"

void initCreateobj(Stringmspace *a) {
    if(!a) return;

    a->ptr = NULL;
    a->offset = 0;
    a->cap = 0;
    a->err = false;
    a->outofmemory = false;
}

void CreateStringMspace(Stringmspace *a, size_t size) {
    if(!a || !size) return;
    
    void *tmp = malloc(size);
    if(!tmp) {
        a->err = true;
        a->cap = 0;
        a->offset = 0;
        return;
    }
    
    a->ptr = tmp;
    a->cap = size;
    a->offset = 0;
    a->err = false;
}

void *Fromaobj(Stringmspace *a, size_t size) { 
    if(!a || !a->ptr || size == 0) 
        return NULL;
    
    if(a->offset + size >= a->cap) {
        a->outofmemory = true;
        a->err = true;
        return NULL;
    }
    if(a->err != true) {
    void *allocated = (char*)a->ptr + a->offset;
    a->offset += size;
    return allocated;
   }
   return NULL;
}

void Delobj(Stringmspace *a) {
    if(!a) return;
    free(a->ptr);
    a->ptr = NULL;
    a->offset = 0;
    a->cap = 0;
    a->err = false;
    a->outofmemory = false;
}
