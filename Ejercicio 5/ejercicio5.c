#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
        char buf[256];
 	    fd_set tub_read, tub_write;
        int tuberia_1, tuberia_2;
        int rc;
        struct timeval timeout;

        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
 	    tuberia_1 = open("tuberia", O_RDWR | O_NONBLOCK);
        tuberia_2 = open("tuberia2", O_RDWR | O_NONBLOCK);
        if(tuberia_1 == -1) perror("Error en el open");
        if(tuberia_2 == -1) perror("Error en el open");
	    FD_ZERO(&tub_read);
        FD_ZERO(&tub_write);
        FD_SET(tuberia_1, &tub_read);
        FD_SET(tuberia_2, &tub_read);
        FD_SET(tuberia_1, &tub_write);
        FD_SET(tuberia_2, &tub_write);
        rc = select(tuberia_2+1, &tub_read, &tub_write, NULL, &timeout);
                if(rc == 0) { } else if(rc == -1) {
                        perror("Fallo en el select()");
                } else {
	                    	if(FD_ISSET(tuberia_1, &tub_read)) {
                                ssize_t size = read(tuberia_1, buf, sizeof(buf));
                                if(size == -1) perror("Error en read()");
                                else if (size == 0) { 
                                        close(tuberia_1);
                                        tuberia_1 = open("tuberia", O_RDWR | O_NONBLOCK);
                                }else {
                                        buf[size] = '\0';
                                        printf("Se ha recibido algo por la tuberia 0: %s\n", buf);
                                        ssize_t size2 = write(tuberia_1, buf, sizeof(buf));
                                        buf[size2] = '\0';
                                        printf("Se ha escrito %s\n", buf);
                                }
                            }
                            if(FD_ISSET(tuberia_2, &tub_read)) {
                                ssize_t size = read(tuberia_2, buf, sizeof(buf));
                                if(size == -1) perror("Error en read()");
                                else if (size == 0) { 
                                        close(tuberia_2);
                                        tuberia_2 = open("tuberia2", O_RDWR | O_NONBLOCK);
                                } else {
                                        buf[size] = '\0';
                                        printf("Se ha recibido algo por la tuberia 1: %s\n", buf);
                                        ssize_t size2 = write(tuberia_2, buf, sizeof(buf));
                                        buf[size2] = '\0';
                                        printf("Se ha escrito %s\n", buf);
                            }
		                    }
			            }
	close(tuberia_1);
    close(tuberia_2);
    return 0;
}
