#include <stdio.h>

int main(int argc, char *argv[])
{
        union {
                short s;
                char c[sizeof(short)];
        } un;
        un.s = 0x0102;
        if (2 == sizeof(short)) {
                if (1 == un.c[0] && 2 == un.c[1])
                        puts("big-endian");
                else if (2 == un.c[0] && 1 == un.c[1])
                        puts("little-endian");
                else
                        puts("unknow");
        } else
                printf("sizeof(short) = %ld\n", sizeof(short));
        return 0;
}
