#ifndef STRINGMSPACE_H
#define STRINGMSPACE_H
#include <stdbool.h>
#include <stddef.h>

typedef struct {
        void *ptr;
        size_t offset;
        size_t cap;
        
        bool err;
        bool memory;
        bool outofmemory;
} Stringmspace;

void initCreateobj(Stringmspace *a);
void CreateStringMspace(Stringmspace *a, size_t size);
void *Fromaobj(Stringmspace *a, size_t size);
void Delobj(Stringmspace *a);

#endif
