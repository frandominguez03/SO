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
    char ruta[] = "/usr/bin/";
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

    // Concatenamos el nombre del programa
    sprintf(ruta, "%s%s", ruta, argv[1]);

    if(segundoPlano == 1) {
        printf("Llega");
        // Creo un array de longitud argc-1 porque el último parámetro es 'bg' y no nos interesa
        char* ejecucion[argc-1];

        // Lo inicializo y asigno el primer valor a ruta y el último valor a NULL
        // La ruta debe de ser el primer valor del array porque así lo requiere execv
        // A su vez, el array debe de terminar en NULL porque así lo requiere execv
        for(int i=1; i < argc-2; i++)
            ejecucion[i] = "";

        ejecucion[0] = ruta;
        ejecucion[argc-2] = NULL;

        // Le asigno todos los parámetros
        for(int i = 1; i < argc-2; i++) {
            ejecucion[i] = argv[i+1];
        }

        if((pid = fork()) < 0) {
            perror("\nError en el fork");
            exit(EXIT_FAILURE);
        } else if(pid == 0) {
            if(execv(ruta, ejecucion) < 0) {
                perror("Error en execv\n");
                exit(EXIT_FAILURE);
            }
        }

        wait(&estado);        
        
    } else {
        if(argc == 2) {
            char* ejecucion[2] = {"", NULL};

            if(execv(ruta, ejecucion) < 0) {
                perror("Error en execl\n");
                exit(EXIT_FAILURE);
            }
        }

        else {
            // Creo un array de longitud argc
            char* ejecucion[argc];

            // Lo inicializo y asigno el primer valor a ruta y el último valor a NULL
            // La ruta debe de ser el primer valor del array porque así lo requiere execv
            // A su vez, el array debe de terminar en NULL porque así lo requiere execv
            for(int i=1; i < argc-1; i++)
                ejecucion[i] = "";
            
            ejecucion[0] = ruta;
            ejecucion[argc-1] = NULL;
            
            // Le asigno todos los parámetros
            for(int i = 1; i < argc-1; i++) {
                ejecucion[i] = argv[i+1];
            }

            if(execv(ruta, ejecucion) < 0) {
                perror("Error en execv %d\n");
                exit(EXIT_FAILURE);
            }
        }

        wait(&estado);
    }

    return EXIT_SUCCESS;
}