#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
        if(argc != 2) {
                printf("Especifica el directorio\n");
                exit(EXIT_FAILURE);
        }
        DIR *dir;
        struct dirent *dirp;
        char * dirname = argv[1];
        char * path;
        struct stat buf;
        char buffer[1024];
        int res;
        int size = 0;

         res = lstat(dirname, &buf);
        if(res == -1) {
                perror("Error");
                exit(EXIT_FAILURE);
        } else if(!S_ISDIR(buf.st_mode)) { 
                printf("Debe apuntar a un directorio\n");
                exit(EXIT_FAILURE);
        }
         dir = opendir(argv[1]);

        while((dirp = readdir(dir)) != NULL) {
                if(dirp->d_type == DT_REG) {
                        printf("%s\n", dirp->d_name);
                        
			= size + buf.st_size;
                }
                 if(dirp->d_type == DT_DIR) {
                        printf("%s/\n", dirp->d_name);
                        size = size + buf.st_size;
                }
                if(dirp->d_type == DT_LNK) {
                        path = strcat(dirname, "/");
                        path = strcat(path, dirp->d_name);
                        ssize_t tambuf = readlink(path, buffer, sizeof(buffer) - 1);
                        if(tambuf != -1) {
                                buffer[tambuf] = '\0';
                                printf("%s -> %s\n", dirp->d_name, buffer);
                                size = size + buf.st_size;
                        } else perror("Fallo");
                }
                if(dirp->d_type == DT_BLK) {
                        printf("%s*\n", dirp->d_name);
                        size = size + buf.st_size;
                }
                }
        closedir(dir);

        size = size / 1024; 
        printf("Tamaño total (KB): %i\n", size);

        return 0;
}