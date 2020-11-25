/**
 * Sistemas Operativos
 * Módulo 2, Sesión 3, Ejercicio 7
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
#include<string.h>
#include<stdbool.h>

int main(int argc, char* argv[]) {

    char bg[] = "bg";
    bool segundoPlano = 0;
    pid_t pid;
    int estado;
    
    if(argc < 2) {
        printf("\nError de sintaxis. Ejecución: ./ejercicio1 <programa> [param1, param2...] bg");
        perror("\nError en número de parámetros");
        exit(EXIT_FAILURE);
    } else {
        if(strcmp(argv[argc-1], bg) == 0) {
            segundoPlano = 1;
        }
    }

    if(segundoPlano == 1) {
        
        argv[argc-1]=NULL;

        if((pid = fork()) < 0) {
            perror("\nError en el fork");
            exit(EXIT_FAILURE);
        } else if(pid == 0) {
            if(execvp(argv[1], &argv[1]) < 0) {
                perror("Error en execv\n");
                exit(EXIT_FAILURE);
            }
        }

        wait(&estado);        
        
    } else {
        if(execvp(argv[1], &argv[1]) < 0) {
            perror("Error en execv %d\n");
            exit(EXIT_FAILURE);
        }

        wait(&estado);
    }

    return EXIT_SUCCESS;
}
