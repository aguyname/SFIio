#include <unistd.h>
#include <string.h>
#include <stdlib.h> 
#include "SFIio.h"
#include "utils.c" // this file contains all the utilities
#include "String.c" //Because am a moron am just gonna keep placing files like this haha

// File: SFI::io.c
// This file contains Specific File Index (SFI) operators for manipulating file data
// These operators include functions to inserr new data at a specific line (SFIwrite) and remove a range of lines (SFIremove).
// Note: SFIremove is still in work
// Both functions utilize dynamic memory allocation to read and modify file contents.
// Memory management and file handling practices are carefully implemented to ensure the proper handling of resources.
// These functions invlove complex debugging please use them carefully
/* SFIwrite: inserts data into a file at a specified line index */
/*
 * SFIwrite - inserts data into a file at a given line number.
 * @filename: The name of the file to be modified.
 * @line: The line number at which new data should be written (1-based index).
 * @data: The data to be written into the file.
 * 
 * Returns:
 *   0 on success, -1 on failure.
 */
 
int SFIwrite(const char *restrict filename, long int line, char *restrict content) {
    if(!filename || line <= 0 || !content)
        return -1;

    char str[1024] = {0};
    long int line_count = 0;
    FILE *ptr = NULL;
    if((ptr = fopen(filename, "r+")) == NULL) {
        perror("fopen");
        return -1;
    }
    
    Stringmspace mem;
    long int filesno = FileLines(filename);
    long int filesize = FileSizeLarge(filename);
    filesize = filesize + (filesize/2);
    
    String *a = (String *) malloc(sizeof(String) * filesno);
    initCreateobj(&mem);
    CreateStringMspace(&mem, filesize);
    
    for(long int i = 0; i < filesno; i++) 
             CreateString(&a[i], &mem);
    
    while (fgets(str, sizeof(str), ptr) != NULL) {
        Stringfrom(&a[line_count], str);
        if (a[line_count].str == NULL) {
            Delobj(&mem);
            free(a);
            fclose(ptr);
            return -1;
        }
        line_count++;
    }

    if(fseek(ptr, 0, SEEK_SET) != 0) {
        perror("fseek");
        Delobj(&mem);
        free(a);
        fclose(ptr);
        return -1;
    }

    for(int j = 0; j < line - 1 && j < line_count; j++)
        fwrite(a[j].str, sizeof(char), Stringlen(&a[j]), ptr);

    fwrite(content, sizeof(char), strlen(content), ptr);
    fputc('\n', ptr);

    for(int j = line - 1; j < line_count; j++)
        fwrite(a[j].str, sizeof(char), Stringlen(&a[j]), ptr);
        
    Delobj(&mem);
    free(a);
    fclose(ptr);
    return 0;
}
