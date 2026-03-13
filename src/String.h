#ifndef STRING_H
#define STRING_H
#include <stddef.h>
#include <stdbool.h>
#include "Stringmspace.h"
typedef struct String {
        Stringmspace *memory;
        char *str;
        size_t cap;
        size_t len;
        bool arena_allocated;
} String;

void CreateString(String *s, Stringmspace *a);

int Stringfrom(String *s, const char *src);

int StringAppend(String *s, const char *str);

void DelString(String *s);

#endif
