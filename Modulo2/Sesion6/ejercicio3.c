/**
 * Sistemas Operativos
 * Módulo 2, Sesión 6, Ejercicio 3
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
    pid_t pid;

    cerrojo.l_type = F_WRLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;

    if((pid = fork()) < 0) {
        printf("\nError en el fork");
        perror("\nError en el fork");
        exit(EXIT_FAILURE);
    } else if(pid == 0) {
        if((fd = open("prueba.txt", O_RDWR)) == -1) {
            printf("\nError en el open");
            perror("\nError en el open");
            exit(EXIT_FAILURE);
        }

        int filecontrol = fcntl(fd, F_SETLK, &cerrojo);

        if(filecontrol == EDEADLK || filecontrol == -1) {
            printf("Kernel comprueba que estamos en una situación de interbloqueo\n");
        }
    }

    if((pid = fork()) < 0) {
        printf("\nError en el fork");
        perror("\nError en el fork");
        exit(EXIT_FAILURE);
    } else if(pid == 0) {
        if((fd = open("prueba.txt", O_RDWR)) == -1) {
            printf("\nError en el open");
            perror("\nError en el open");
            exit(EXIT_FAILURE);
        }

        int filecontrol = fcntl(fd, F_SETLK, &cerrojo);

        if(filecontrol == EDEADLK || filecontrol == -1) {
            printf("Kernel comprueba que estamos en una situación de interbloqueo\n");
        }
    }

    return EXIT_SUCCESS;
}