#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        pid_t pid = fork();
        if(pid == -1) {
                perror("Error en el fork");
        } else if(pid == 0) { 
                //sleep(10);
                int res = chdir("/tmp");
                if(res == -1) perror("error");
                pid_t pid2 = setsid();
                printf("Id. de proceso: %i\n", pid);
                printf("Id. de proceso padre: %i\n", getppid());
                printf("Id. de grupo de procesos: %i\n", getpgrp());
                printf("Id. de sesión: %i\n", getsid(pid));
                printf("Directorio de trabajo: %s\n", get_current_dir_name());
        } else if(pid > 0) { 
                sleep(10);
                printf("Id. de proceso: %i\n", pid);
                printf("Id. de proceso padre: %i\n", getppid());
                printf("Id. de grupo de procesos: %i\n", getpgrp());
                printf("Id. de sesión: %i\n", getsid(pid));
                printf("Directorio de trabajo: %s\n", get_current_dir_name());
        }
        return 0;
}
