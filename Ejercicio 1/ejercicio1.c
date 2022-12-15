#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUF_SIZE 500

int main(int argc, char *argv[])
{
	struct addrinfo pruebas;
	struct addrinfo *solucion, *r;
	int sfd, s, j;
	size_t l;
	size_t size_read;
	char buf[BUF_SIZE];
	if (argc < 3) {
		fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
		exit(EXIT_FAILURE);
	    }
	memset(&pruebas, 0, sizeof(struct addrinfo));
	pruebas.ai_family = AF_UNSPEC;    
	pruebas.ai_socktype = SOCK_DGRAM; 
	pruebas.ai_flags = 0;
	pruebas.ai_protocol = 0;      
	s = getaddrinfo(argv[1], argv[2], &pruebas, &solucion);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	} 
	for (r = solucion; r != NULL; r = r->ai_next) {
		sfd = socket(r->ai_family, r->ai_socktype, r->ai_protocol); 
	 	if (sfd == -1)
		    continue;
		if (connect(sfd, r->ai_addr, r->ai_addrlen) != -1)
		    break;
		close(sfd);
   	}
	if (r == NULL) {              
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    	}
	freeaddrinfo(solucion);
  	for (j = 3; j < argc; j++) {
        	l = strlen(argv[j]) + 1;
		 if (l + 1 > BUF_SIZE) {
           	 fprintf(stderr,"Ignoring long message in argument %d\n", j);
		    continue;
		}
		 if (write(sfd, argv[j], l) != l) {
		    fprintf(stderr, "partial/failed write\n");
		    exit(EXIT_FAILURE);
		}
		size_read=(sfd,buf, BUF_SIZE);
		if (size_read == -1) {
		    perror("read");
		    exit(EXIT_FAILURE);
		}
		printf("Received %ld bytes: %s\n", (long) size_read, buf);
	    }

	   exit(EXIT_SUCCESS);
	}
