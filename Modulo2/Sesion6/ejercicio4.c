/**
 * Sistemas Operativos
 * Módulo 2, Sesión 6, Ejercicio 4
 * Francisco Domínguez Lorente
 */

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    struct flock cerrojo;
    int fd;

    cerrojo.l_type = F_WRLCK;
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0;

    if((fd = open("prueba.txt", O_RDWR | O_TRUNC)) == -1) {
        printf("\nError en el open");
        perror("\nError en el open");
        exit(EXIT_FAILURE);
    }

    int filecontrol = fcntl(fd, F_SETLK, &cerrojo);

    if(filecontrol == EDEADLK || filecontrol == -1) {
        printf("El programa ya se está ejecutando en otra instancia\n");
        exit(EXIT_FAILURE);
    } else {
        if(write(fd, "He escrito", 5) != 5) {
            printf("\nError en write");
            perror("\nError en write");
            exit(EXIT_FAILURE);
        }
        
        while(1){};
    }

    return EXIT_SUCCESS;
}