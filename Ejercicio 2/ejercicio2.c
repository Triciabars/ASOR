#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>

void main(int argc, char *argv[]) {
    struct addrinfo hints;
    struct addrinfo *res;
    struct sockaddr_storage cli;
    time_t rawtime;
    struct tm* timeinfo;
    char tbuffer[9];
    char buf[81], host[NI_MAXHOST], serv[NI_MAXSERV];

    hints.ai_family = AF_UNSPEC;   
    hints.ai_socktype = SOCK_DGRAM; 
    hints.ai_flags = AI_PASSIVE;    
    hints.ai_protocol = 0;         

    getaddrinfo(argv[1], argv[2], &hints, &res);
    int sd = socket(res->ai_family, res->ai_socktype, 0);
    bind(sd, (struct sockaddr *)res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);

    // Bucle de escucha del servidor:
    while(1) {
        socklen_t clen = sizeof(cli);
        int c = recvfrom(sd, buf, 80, 0, (struct sockaddr*) &cli, &clen);
        buf[c] = '\0';
        getnameinfo((struct sockaddr*) &cli, clen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        if(buf[0] == 't') {
                printf("%ld bytes de %s:%s\n", c, host, serv);
                ssize_t chars = strftime(tbuffer, sizeof(tbuffer), "%T", timeinfo);
                sendto(sd, tbuffer, chars, 0, (struct sockaddr *)&cli, clen);
        } else if(buf[0] == 'd') { 
                printf("%ld bytes de %s:%s\n", c, host, serv);
                ssize_t chars = strftime(tbuffer, sizeof(tbuffer), "%D", timeinfo);
                sendto(sd, tbuffer, chars, 0, (struct sockaddr *)&cli, clen);
        } else if(buf[0] == 'q') { 
                printf("Saliendo...\n");
                exit(EXIT_SUCCESS);
        } else {
                printf("Comando no soportado %s", buf);
        }
    }
}
