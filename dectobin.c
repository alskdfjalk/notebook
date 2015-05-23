#include <stdlib.h>
#include <stdio.h>


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
void bspop(struct bsinfo *binfo)
{
        printf("%d", binfo->tail->data);
        struct binarystack *tmp = binfo->tail->last;

        free(binfo->tail);
        binfo->tail = tmp;

        binfo->len--;
}
int main(int argc, char *argv[])
{
        if (argc != 2) {
                puts("error argument");
                return -1;
        }

        struct bsinfo *bsdata = malloc(sizeof(struct bsinfo *));
        bsinit(bsdata);

        int data = atoi(argv[1]);
        while (data) {
                bspush(bsdata, data & 1);
                data>>=1;
        }

        printf("Decimal ===>> Binary\n");
        printf("%7d ===>> ", atoi(argv[1]));

        while (bsdata->len)
                bspop(bsdata);

        free(bsdata);
        printf("\n");
        return 0;
}
