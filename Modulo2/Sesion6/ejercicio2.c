/**
 * Sistemas Operativos
 * Módulo 2, Sesión 6, Ejercicio 2
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

int main(int argc, char *argv[]) {
    char* orden1;
    char* orden2;
    int fd[2];
    pid_t pid;
    int status;

    if(argc < 3) {
        printf("\nSintaxis de ejecución: ./ejercicio1 orden1 | orden2");
        exit(EXIT_FAILURE);
    } else {
        orden1 = argv[1];
        orden2 = argv[3];
    }

    if(strcmp(argv[2], "|") == 0) {
        pipe(fd);

        if((pid = fork()) < 0) {
            printf("\nError en el fork");
            perror("\nError en el fork");
            exit(EXIT_FAILURE);
        } else if(pid == 0) {
            // Estamos en el proceso hijo. Escribimos en el cauce con la primera orden
            close(fd[0]);
            close(1);

            if(fcntl(fd[1], F_DUPFD, 1) == -1) {
                printf("\nError en fcntl");
                perror("\nError en fcntl");
                exit(EXIT_FAILURE);
            }

            if(execlp(orden1, orden1, NULL) < 0) {
                printf("\nError en execlp");
                perror("\nError en execlp");
                exit(EXIT_FAILURE);
            }
        }

        if((pid = fork()) < 0) {
            printf("\nError en el fork");
            perror("\nError en el fork");
            exit(EXIT_FAILURE);
        } else if(pid == 0) {
            // Estamos en el proceso hijo. Leemos del cauce con la segunda orden
            close(fd[1]);
            close(0);

            if(fcntl(fd[0], F_DUPFD, 0) == -1) {
                printf("\nError en fcntl");
                perror("\nError en fcntl");
                exit(EXIT_FAILURE);
            }

            if(execlp(orden2, orden2, NULL) < 0) {
                printf("\nError en execlp");
                perror("\nError en execlp");
                exit(EXIT_FAILURE);
            }
        }

    } else {
        printf("\nEl operador introducido no es válido. Solo se permite |");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}