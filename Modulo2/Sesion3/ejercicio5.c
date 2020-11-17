/**
 * Sistemas Operativos
 * Módulo 2, Sesión 3, Ejercicio 5
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
    int listaPids[5];
    int numhijos = 5;

    for(int i = 0; i < numhijos; i++) {
        if((nuevoProceso = fork()) < 0) {
            printf("\nError en el fork");
            perror("\nError en la llamada fork");
            exit(EXIT_FAILURE);
        } else if(nuevoProceso == 0) {
            printf("Soy el proceso con PID: %d\n", getpid());
            listaPids[i] = getpid();
            exit(EXIT_SUCCESS);
        }
    }

    // Esperamos primero a los impares
    for(int i = 1; i <= numhijos; i+=2) {
        if((hijoTerminado = waitpid(listaPids[i], NULL, 0)) != -1) {
            printf("Acaba de finalizar mi hijo con PID: %d\n", hijoTerminado);
            printf("Solo me quedan %d hijos\n", --numhijos);
        }
    }

    // Esperamos ahora a los pares
    for(int i = 0; i < numhijos; i+2) {
        if((hijoTerminado = waitpid(listaPids[i], NULL, 0)) != -1) {
            printf("Acaba de finalizar mi hijo con PID: %d\n", hijoTerminado);
            printf("Solo me quedan %d hijos\n", --numhijos);
        }
    }

    return EXIT_SUCCESS;
}