#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Especifica el fichero\n");
        exit(EXIT_FAILURE);
    }
    struct flock lock;
    time_t rawtime;
    struct tm* hora;
    char buffer [9];
    int fd;
    printf("Comprueba el estado del cerrojo...\n");
    fd = open(argv[1], O_WRONLY);
    memset(&lock, 0, sizeof(lock));
    fcntl(fd, F_GETLK, &lock); 
    if(lock.l_type != F_UNLCK) {
        printf("El cerrojo está bloqueado\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Cerrojo desbloqueado\n");
        lock.l_type = F_WRLCK; 
        memset(&lock, 0, sizeof(lock));
        fcntl(fd, F_SETLKW, &lock); 
        time(&rawtime);
        hora = localtime(&rawtime);
        strftime(buffer, sizeof(buffer), "%T", hora);
        write(fd, buffer, 8);
        printf("Cerrojo adquirido\n");
        sleep(5);
        printf("Liberando cerrojo\n");
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLKW, &lock);
    }
 close(fd);
 return 0;
}