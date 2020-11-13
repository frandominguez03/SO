/**
 * Sistemas Operativos
 * Módulo 2, Sesión 3, Ejercicio 4
 * Francisco Domínguez Lorente
 */

#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char* argv[]) {
    pid_t nuevoProceso;
    pid_t hijoTerminado;
    pid_t idHijo;

    for(int i = 1; i <= 5; i++) {
        if((nuevoProceso = fork()) < 0) {
            printf("\nError en el fork");
            perror("\nError en la llamada fork");
            exit(EXIT_FAILURE);
        } else if(nuevoProceso == 0) {
            idHijo = getpid();
            printf("Soy el proceso con PID: %d\n", getpid());
            exit(EXIT_SUCCESS);
        } else {
            if((hijoTerminado = waitpid(idHijo, NULL, 0)) != -1) {
                printf("Acaba de finalizar mi hijo con PID: %d\n", hijoTerminado);
                printf("Solo me quedan %d hijos\n", 5-i);
            }
        }
    }

    return EXIT_SUCCESS;
}