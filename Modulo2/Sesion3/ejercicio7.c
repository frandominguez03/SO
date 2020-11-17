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

    char* background;
    char bg[] = "bg";
    bool segundoPlano = false;
    char ruta[] = "/usr/bin/";
    char ejecucion[] = "";
    pid_t pid;
    int estado;
    
    if(argc < 2) {
        printf("\nError de sintaxis. Ejecución: ./ejercicio1 <programa> [param1, param2...] bg");
        perror("\nError en número de parámetros");
        exit(EXIT_FAILURE);
    } else {
        if(strcmp(argv[argc-1], bg) == 0) {
            background = argv[argc-1];
            segundoPlano = true;
        }
    }

    // Concatenamos el nombre del programa
    sprintf(ruta, "%s%s", ruta, argv[1]);

    if(segundoPlano) {
        for(int i = 2; i < argc-1; i++) {
            sprintf(ejecucion, "%s%s", ejecucion, argv[i]);
        }

        if((pid = fork()) < 0) {
            perror("\nError en el fork");
            exit(EXIT_FAILURE);
        } else if(pid == 0) {
            if(execl(ruta, ejecucion, NULL) < 0) {
                perror("Error en execl\n");
                exit(EXIT_FAILURE);
            }
        }

        wait(&estado);
        
    } else {
        for(int i = 2; i < argc; i++) {
            sprintf(ejecucion, "%s%s", ejecucion, argv[i]);
        }

        if(execl(ruta, ejecucion, NULL) < 0) {
            perror("Error en execl\n");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}