/*
 *  trans_lb.c
 *
 *  2015-05-24 张雅峰(Crazy Jerry)
 */

/*
 *  'dectobin.c'
         转换十进制到二进制
         二进制转十进制

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
        int ret = binfo->tail->data;
        struct binarystack *tmp = binfo->tail->last;

        free(binfo->tail);
        binfo->tail = tmp;

        binfo->len--;
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
                        puts("This is not binary number");
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
void help(char *name)
{
        printf("Binary and decimal transfor tools\n"
               "\t%s [option] <number>\n"
               "\t\t-b\t"
               "binary to decimal(二进制转十进制)\n"
               "\t\t-d\t"
               "decimal to binary(十进制转二进制)\n"
               "\tFor example: \n"
               "\t\t%s -d 255\n\n", name, name);
}

int main(int argc, char *argv[])
{
        if (argc != 3) {
                help(argv[0]);
                return -1;
        }

        int data = atoi(argv[2]);

        char *opt = argv[1];
        if ('-' == opt[0] && 'd' == opt[1])
                dectobin(data);
        else if ('-' == opt[0] && 'b' == opt[1]) {
                bintodec(data);
        } else
                help(argv[0]);
        return 0;
}
