#include <stdio.h>
#include <setjmp.h>
#include <signal.h>

jmp_buf buf;

void sig_re(int sig)
{
        puts("SIGINT now");
        longjmp(buf, 1);
}
int main(int argc, char *argv[])
{
        signal(SIGINT, sig_re);
        if (setjmp(buf)){
                puts("back in main");
                return 0;
        } else
                puts("first time");
loop:
        goto loop;
}
