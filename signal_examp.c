#include <signal.h>
#include <stdio.h>


void sig_usr(int signo)
{
        if (signo == SIGINT)
                puts("\nGet ctrl-c, quting");

}

int main(int argc, char *argv[])
{
        if (signal(SIGINT, sig_usr) == SIG_ERR)
                puts("signal get error");
        // void (*signal(int, void (*)(int)))(int);
        /*
          SIG_IGN
          SIG_ERR
          SIG_DFL
        */

        int tmp;
        scanf("%d", &tmp);
        printf("tmp: %d\n", tmp);
        return 0;
}
