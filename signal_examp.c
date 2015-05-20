#include <signal.h>
#include <stdio.h>

extern void psignal (int __sig, const char *__s);
extern __sighandler_t sigset (int __sig, __sighandler_t __disp) __THROW;
extern int sigignore (int __sig) __THROW;


void sig_usr(int signo)
{
        if (signo == SIGINT) {
                puts("still running (at sig_usr)");
                signal(SIGINT, SIG_IGN);
        }
}

int main(int argc, char *argv[])
{

        // void (*signal(int, void (*)(int)))(int);
        /*
          SIG_IGN
          SIG_ERR
          SIG_DFL
        */

        int tmp;
        while (1){
                if (SIG_ERR == signal(SIGINT, sig_usr)) {
                        puts("SIGINT error");
                        break;
                }
                scanf("%d", &tmp);
                printf("tmp: %d\n", tmp);
                if (!tmp) break;
        }
        return 0;
}
