#include <signal.h>
#include <stdlib.h>
#include <stdio.h>


void sig_segv(int signo)
{
        puts("Core dump now");
        exit(signo);
}
int main(int argc, char *argv[])
{
        signal(SIGSEGV, sig_segv);
        char *p = "a";
        *p = "b";
        return 0;
}
