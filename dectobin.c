/*
 *  dectobin.c
 *
 *  2015-05-24 张雅峰(Crazy Jerry)

 Copyright (C) 2014 Free Software Foundation, Inc.
 License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
 This is free software: you are free to change and redistribute it.

 */

/*
 *  'dectobin.c'
         转换
         十进制到二进制
         二进制转十进制
         十六进制转十进制

     编译选项:
         gcc -Wall -lm dectobin.c
         因为使用了math.h库
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

struct binarystack {
        short int data;
        struct binarystack *last;
        struct binarystack *next;
};

struct bsinfo {
        int len;
        struct binarystack *root;
        struct binarystack *tail;
};

void bsinit(struct bsinfo *binfo)
{
        binfo->len = 0;
        binfo->root = NULL;
        binfo->tail = NULL;
}
int bspush(struct bsinfo *binfo, const short int nu)
{
        if (nu < 0) {
                puts("Error num");
                return -1;
        }
        struct binarystack *tmp = malloc(sizeof(struct binarystack *));
        if (binfo->root == NULL) {
                binfo->root = malloc(sizeof(struct binarystack *));
                binfo->root = tmp;
                binfo->root->data = nu;
                binfo->root->next = NULL;
                binfo->root->last = NULL;
        } else {
                struct binarystack *tmplast = malloc(sizeof(struct binarystack *));
                if (binfo->tail == NULL) {
                        binfo->tail = tmp;
                        binfo->root->next = tmp;
                        binfo->tail->last = binfo->root;
                } else {
                        tmplast = binfo->tail;
                        binfo->tail = tmp;
                        binfo->tail->last = tmplast;
                }
                binfo->tail->data = nu;
                binfo->tail->next = NULL;
        }
        (binfo->len)++;
        return 0;
}
short int bspop(struct bsinfo *binfo)
{
        int ret;
        struct binarystack *tmp;
        if (NULL == binfo->tail && NULL != binfo->root) {
                ret = binfo->root->data;
                free(binfo->root);
                binfo->len--;
        }
        else {
                ret = binfo->tail->data;
                tmp = malloc(sizeof(struct binarystack));
                tmp = binfo->tail->last;

                free(binfo->tail);
                binfo->tail = tmp;
                binfo->len--;
        }
        return ret;
}

void dectobin(const int data)
{
        int tmp = data;
        struct bsinfo *bsdata = malloc(sizeof(struct bsinfo *));
        bsinit(bsdata);

        while (tmp) {
                bspush(bsdata, tmp & 1);
                tmp>>=1;
        }

        int len = bsdata->len;

        printf("%10s ===>> Binary\n", "Decimal");
        printf("%10d ===>> ", data);
        while (bsdata->len)
                printf("%d", bspop(bsdata));

        free(bsdata);
        printf("   (长度: %d)\n", len);
}
void bintodec(const int data)
{
        int tmp = data;
        struct bsinfo *bsdata = malloc(sizeof(struct bsinfo *));
        bsinit(bsdata);

        while (tmp){
                int i = tmp % 10;
                if (2 <= i) {
                        puts("This is not binary");
                        exit(-1);
                }
                bspush(bsdata, i);
                tmp /= 10;
        }

        int len = bsdata->len;
        int ret = 0;
        printf("%10s  ===>>  Decimal\n", "Binary");
        printf("%10d  ===>>  ", data);
        while (bsdata->len) {
                ret += (bspop(bsdata) * (int)pow(2.0, (double)bsdata->len));
        }
        printf("%d", ret);
        free(bsdata);
        printf("   (长度: %d)\n", len);
}
int gethex(const char *data)
{
        char tmp = (char)*data;
        if ('A' <= tmp && 'Z' >= tmp)
                tmp += 32;
        switch((char)tmp) {
        case 'a':
                return 10;
        case 'b':
                return 11;
        case 'c':
                return 12;
        case 'd':
                return 13;
        case 'e':
                return 14;
        case 'f':
                return 15;
        default:
                return atoi(data);
        }
}
void hextodec(const char *data)
{
        const char *tmp = data;
        int datalen = strlen(tmp);

        int ret = 0;
        int len;
        printf("%10s  ===>>  Decimal\n", "Hex");
        printf("%10s  ===>>  ", tmp);
        int i = 0;
        while ((len = (--datalen)) >= 0)
                ret += ((int)gethex((char *)(tmp + len)) * (int)pow(16.0, i++));
        printf("%d\t   (长度: %ld)\n", ret, strlen(tmp));
}
void help(char *name)
{
        printf("Binary/Decimal/Hex transfor tools\n"
               "\t%s [option] <number>\n"
               "\t\t-b\t"
               "binary to decimal(二进制转十进制)\n"
               "\t\t-d\t"
               "decimal to binary(十进制转二进制)\n"
               "\t\t-h\t"
               "hex to decimal(十六进制转十进制)\n"
               "\tFor example: \n"
               "\t\t%s -d 255\n\n", name, name);
}

int main(int argc, char *argv[])
{
        if (argc != 3) {
                help(argv[0]);
                return -1;
        }
        char *opt = argv[1];

        if ('-' == opt[0] && 'h' == opt[1])
                hextodec(argv[2]);
        else {
                int data = atoi(argv[2]);
                if ('-' == opt[0] && 'd' == opt[1])
                        dectobin(data);
                else if ('-' == opt[0] && 'b' == opt[1]) {
                        bintodec(data);
                } else
                        help(argv[0]);
        }
        return 0;
}
