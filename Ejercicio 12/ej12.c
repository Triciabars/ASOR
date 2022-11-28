#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

int sigint = 0;
int sigtstop = 0;

void handler(int signal) {
    if(signal == SIGINT) {
        sigint++;
    }
    if(signal == SIGTSTP) {
        sigtstop++;
    }
}
int main(int argc, char *argv[]) {
        if(argc != 2) {
                printf("Vuelve a ejecutar un PID\n");
                exit(EXIT_FAILURE);
        }
        pid_t pid = atoi(argv[1]);
        struct sigaction signal;
        signal.sa_handler = &handler;
        signal.sa_flags = 0;
        if(sigaction(SIGINT, &signal, NULL) == -1) perror("Error: SIGINT\n");
        if(sigaction(SIGTSTP, &signal, NULL) == -1) perror("Error:SIGTSTP\n");
        while(sigint < 10 && sigtstop < 10);
        printf("Se ha recibido la señal SIGINT %i veces\n", sigint);
        printf("Se ha recibido la señal SIGTSTP %i veces\n", sigtstop);
 return 0;
}
        
