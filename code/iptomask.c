#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

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
void transnum(int num, char *binamask)
{
	char *tmpmask = binamask;
	int tmpnum = 0;

	while (32 > tmpnum) {
		if (0 == tmpnum % 8 && strlen(binamask) != 0)
			strncpy(tmpmask++, ".", 1);

		if (num <= tmpnum)
			strncpy(tmpmask++, "0", 1);
		else
			strncpy(tmpmask++, "1", 1);

		tmpnum++;
	}
	memcpy(tmpmask++, "\0", 1);
}

char *numtomask(int num)
{
	char *binamask = malloc(sizeof(char) * 32 + 4);
	char *tmpmask = binamask;

	if (32 < num || 0 > num) {
		printf("This is not a short mask: %d", num);
	} else {
		transnum(num, tmpmask);
	}
	return binamask;
}

void bintodec(char *binary)
{
	char *tmp = binary;
	char *retdec =  malloc(sizeof(char) * 15);
	int count = 0;

	while (tmp) {

		if (*tmp == "1") {
			printf("equal to 1: %s\n", tmp);
			count++;
		} else if (0 >= strncmp(tmp, "0", 1)) {
			break;
		}
		if (0 >= strncmp(tmp + 1, ".", 1)) {

			count = (int)pow(2.0, (double)count);

			if (256 == count)
				count--;

			printf("count: %d\n", count);

			sprintf(retdec, "%d", count);

			printf("retdec: %s\n", retdec);

			memcpy(retdec, ".", 1);

			sleep(1);
		}

		tmp++;
	}
	printf("%s\n", retdec);
}

int main(int argc, char *argv[])
{
	puts(argv[1]);

	char *binarymask = numtomask(atoi(argv[1]));

	bintodec(binarymask);
	return 0;
}

