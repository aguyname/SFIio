#include <stdio.h>
#include <sys/stat.h>
long long FileSizeLarge(const char *filename) {
    if (!filename)
        return -1;

    struct stat st;
    
    if (stat(filename, &st) == 0)
        return (long long)st.st_size;
    
    return -1;
}



long int FileLines(const char *filename) {
    if (!filename)
        return -1;

    FILE *fp = fopen(filename, "r");
    if (!fp)
        return -1;

    long int lines = 0;
    int ch;
    
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            lines++;
    }
    
    /* If file doesn't end with newline, count last line */
    if (lines == 0) {
        /* Check if file is empty */
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) > 0)
            lines = 1;
    } else {
        /* Check if last character was newline */
        fseek(fp, -1, SEEK_END);
        if (fgetc(fp) != '\n')
            lines++;
    }
    
    fclose(fp);
    return lines;
}

