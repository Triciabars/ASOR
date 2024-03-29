#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

void main(int argc, char *argv[]) {
    struct addrinfo hints;
    struct addrinfo *res;
    struct sockaddr_storage cli;
    char buf[81];
    hints.ai_family = AF_UNSPEC;   
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;    
    hints.ai_protocol = 0;      
    getaddrinfo(argv[1], argv[2], &hints, &res);
    int sd = socket(res->ai_family, res->ai_socktype, 0);
    bind(sd, (struct sockaddr *)res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);
    listen(sd, 5);

    while(1) {
        socklen_t clen = sizeof(cli);
        int cli_sd = accept(sd, (struct sockaddr*) &cli, &clen);
        int c = recv(cli_sd, buf, 80, 0);
        send(cli_sd, buf, c, 0);
        close(cli_sd);
    }
}
