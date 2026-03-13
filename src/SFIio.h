#ifndef SFI_H
#define SFI_H

#include <stddef.h>
typedef long ssize_t; 
int SFIinserts(const char *__restrict filename, ssize_t *lineno, const char **data);
int SFIremove(const char *__restrict filename, long int start_line, long int end_line);
#endif //SFI_H
