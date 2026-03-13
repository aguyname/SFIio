#ifndef SFI_H
#define SFI_H

#include <stddef.h>
typedef long ssize_t; 
int SFIwrite(const char *__restrict filename, long int line, const char *__restrict content);
#endif //SFI_H
