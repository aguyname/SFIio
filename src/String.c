#include "String.h"
#include "Stringmspace.c"  
#include <stdlib.h>
#include <string.h>

void CreateString(String *s, Stringmspace *a) {
    if(!s) return;
    
    s->str = NULL;
    s->cap = 1;
    s->len = 0;
    s->memory = a;
    s->arena_allocated = (a != NULL && a->ptr != NULL);
}

int Stringfrom(String *s, const char *src) {
    if(!s || !src || !s->arena_allocated || !s->memory || s->memory->err == true) 
        return -1;
    
    size_t src_len = strlen(src);
    if(s->memory->offset + src_len >= s->memory->cap) {
       s->memory->outofmemory = true;
       s->memory->err = true;
       return -1;
    }
    
    if(s->memory->ptr == NULL) {
        s->memory->err = true;
        return -1;
    }
    
    char *tmp = (char*) s->memory->ptr + s->memory->offset;
    s->memory->offset += src_len + 1; 
    
    memcpy(tmp, src, src_len + 1);
    s->str = tmp;
    s->len = src_len;
    s->cap = src_len + 1;
    return 0;
}


size_t Stringlen(const String *s) {
    return s ? s->len : 0;
}

bool check_err(const String *s) {
     if(!s)
        return true;
      return s->memory->err;
}


void DelString(String *s) {
    if(s && s->str && !s->arena_allocated) {
        free(s->str);
    }
}
