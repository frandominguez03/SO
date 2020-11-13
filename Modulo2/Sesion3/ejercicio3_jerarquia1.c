/**
 * Sistemas Operativos
 * Módulo 2, Sesión 3, Ejercicio 3 - Jerarquía tipo 1
 * Francisco Domínguez Lorente
 */

#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

int main(int argc, char* argv[]) {
    pid_t childpid;

    /*
    Jerarquía de procesos tipo 1
    */
    for (int i=0; i < 20; i++) {
        if ((childpid = fork()) == -1) {
            fprintf(stderr, "Could not create child %d: %s\n", i, strerror(errno));
            exit(-1);
        } else if (childpid == 0) {
            printf("PID proceso hijo: %d\n", getpid());
            printf("PID proceso padre: %d\n", getppid());
            exit(EXIT_SUCCESS);
        }

        if (childpid)
            break;
    }
    
    return EXIT_SUCCESS;
}