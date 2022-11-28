#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
            printf("Vuelve a ejecutar PID\n");
            exit(EXIT_FAILURE);
    }
    pid_t pid = atoi(argv[1]);
    sigset_t set, pendiente;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTSTP);
    sigprocmask(SIG_BLOCK, &set, NULL);
    printf("Señales SIGINT y SIGTSTOP bloqueadas\n");
    sleep(10);
    sigpending(&pendiente);
        if(sigismember(&pendiente, SIGINT)) {
                printf("Se recibió la llamada SIGINT\n");
        }
        if(sigismember(&pendiente, SIGTSTP)) {
                printf("Se recibió la llamada SIGTSTOP, desbloqueando la llamada...\n");
                sigdelset(&pendiente, SIGINT);
                sigprocmask(SIG_UNBLOCK, &pendiente, NULL); 
                printf("Proceso reanudado");
        }
        return 0;
}
