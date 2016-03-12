#if !defined _SYS_STAT_H
#include <sys/stat.h>
#endif
#if !defined __need_FILE
#include <stdio.h>
#endif
#if !defined _STDLIB_H
#include <stdlib.h>
#endif
#if !defined _STRING_H
#include <string.h>
#endif
#if !defined _ERRNO_H
#include <errno.h>
#endif
#if !defined _UNISTD_H
#include <unistd.h>
#endif
#if !defined BUFFSIZE
#define BUFFSIZE 4096
#endif

extern int getsize(char *);
extern void savenew(char *, FILE *);
extern int readfile(char *, FILE *);
extern void newfileisnull(char *);


int main(int argc, char *argv[])
{
        if (argc != 2){
                puts("Error, wrong filename");
                return 1;
        }
        const char *newsymbol = {"\r\n"};
        char *fname = argv[1];
        char *newname = malloc(strlen(fname));
        strcpy(newname, fname);
        strcat(newname, ".new.txt");

        if (1 == getsize(fname))
                return 0;

        FILE *rf = fopen(fname, "r");
        FILE *wf = fopen(newname, "w");
        char *buff = malloc(sizeof(char *) * BUFFSIZE);

        int ret;
        while (EOF != (ret = readfile(buff, rf))) {
                if (0 != ret)
                        continue;
                strncat(buff, newsymbol, strlen(newsymbol));
                savenew(buff, wf);
        }
        fclose(rf);
        fclose(wf);

        newfileisnull(newname);
        return 0;
}
