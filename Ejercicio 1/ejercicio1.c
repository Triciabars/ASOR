#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
 if(argc < 3) {
 	printf("Uso: comando1 argumento1 comando2 argumento2\n");
 	exit(EXIT_FAILURE);
 }
 int descf[2]; 
 int res1, res2;
 char *cmd1[] = {argv[1], argv[2], NULL};
 char *cmd2[] = {argv[3], argv[4], NULL};
 pipe(descf);
 pid_t pid = fork();
 if(pid == -1) {
	 perror("Error en el fork()");
 } else if(pid > 0) { // Ejecución del padre:
	 close(descf[1]); // Cerramos el extremo de escritura del pipe
	 dup2(descf[1], 1); 
 	close(descf[0]);
 	res1 = execvp(cmd1[0], cmd1); //Ejecuta comando1 argumento 1
if(res1 == -1) perror("Fallo en execvp1()");
} else if(pid == 0) { // Ejecución del hijo
	 close(descf[0]); // Cerramos el extremo de lectura del pipe
	 dup2(descf[0], 0); 
	 close(descf[1]);
	 res2 = execvp(cmd2[0], cmd2); // Ejecuta comando2 argumento 2
if(res2 == -1) perror("Fallo en execvp2()");
 }
 close(descf[1]);
 close(descf[0]);
 return 0;
}
