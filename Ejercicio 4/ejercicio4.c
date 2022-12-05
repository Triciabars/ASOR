#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
int main(int argc, char *argv[]) {
        if(argc != 2) {
           printf("Vuelve a ejecutar el programa\n");
           exit(EXIT_FAILURE);
	    }
        char *casa = getenv("HOME");
        char *path = "/tuberia";
        char *buf = malloc(sizeof(argv[1]));
        strcat(casa, path); // home: root/tuberia
        buf = strcat(argv[1], "\n");
	    if(mkfifo(casa, 0222) == -1) perror("Error al crear la tuberia");
        int fd = open(casa, O_WRONLY);
        if(fd == -1) perror("Error al abrir la tuberia");
	    ssize_t escrito = write(fd, argv[1], strlen(buf));
        if(escrito == 0) printf("No se ha escrito nada\n");
        else if (escrito == -1) perror("Error al escribir en la tuberia");
        close(fd);
return 0;
}

