/*
 *  trans_lb.c
 *
 *  2015-05-11 张雅峰(Crazy Jerry)
 */

/*
 *  'trans_lb.c' Transfor "\n" to "\r\n"
 */
#if !defined _STDLIB_H
#include <stdlib.h>
#endif
#if !defined _ERRNO_H
#include <errno.h>
#endif
#if !defined __need_FILE
#include <stdio.h>
#endif
#if !defined _SYS_STAT_H
#include <sys/stat.h>
#endif
#if !defined _STRING_H
#include <string.h>
#endif
#if !defined BUFFSIZE
#define BUFFSIZE 4096
#endif


int getsize(char *fname)
{
        struct stat *fstat = malloc(sizeof(struct stat));
        if (!fstat)
                return 1;

        if (stat(fname, fstat) != 0) {
                perror(fname);
        } else {
                long int f_st_size = fstat->st_size;
                if ((1024 * 1000 * 1000) <= f_st_size)
                        printf("GB: %ld.%ld\n", f_st_size / 1000 / 1000 / 1000, f_st_size % 1000 % 1000 % 1000);
                else if ((1024 * 1000) <= f_st_size)
                        printf("MB: %ld.%ld\n", f_st_size / 1000 / 1000, f_st_size % 1000 % 1000);
                else if (1024 <= f_st_size)
                        printf("KB: %ld\n", f_st_size);
                else if (1024 >= f_st_size)
                        printf("Bits: %ld\n", f_st_size);
                if ((1024 * 1000 * 100) <= f_st_size) {
                        printf("文件略大,时间可能稍长,");
                        printf("是否继续?(y/n): ");
                        char yesno;
                        yesno = getchar();
                        if (yesno != 'y')
                                return 1;
                }
        }
        return 0;
}

void newfileisnull(char *fname)
{
        struct stat *fstat = malloc(sizeof(struct stat));
        if (stat(fname, fstat) != 0)
                perror(fname);
        else {
                if (!fstat->st_size)
                        printf("Empty file: %s\n", fname);
        }
}
int readfile(char *buf, FILE *fp)
{
        if (NULL == fgets(buf, BUFFSIZE, fp)) {
                perror("Ret");
                return EOF;
        }
        char *symbol = buf + (strlen(buf) - 1);
        if ('\n' == *symbol) {
                memset(symbol, '\0', 1);
                return 0;
        }
        return 1;
}

int savenew(char *buf, FILE *fp)
{
        int ret;
        if (EOF == (ret = fputs(buf, fp)))
                perror("Write error:");
        return ret;
}
