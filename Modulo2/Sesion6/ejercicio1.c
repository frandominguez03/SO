/**
 * Sistemas Operativos
 * Módulo 2, Sesión 6, Ejercicio 1
 * Francisco Domínguez Lorente
 */

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char* orden;
    char* operador;
    char* archivo;
    int fichero;

    if(argc < 3) {
        printf("\nSintaxis de ejecución: ./ejercicio1 orden </> archivo");
        exit(EXIT_FAILURE);
    } else {
        orden = argv[1];
        operador = argv[2];
        archivo = argv[3];
    }

    if(strcmp(operador, "<") == 0) {
        if((fichero = open(archivo, O_RDONLY)) < 0) {
            printf("\nError al intentar abrir el archivo de lectura");
            perror("\nError al intentar abrir el archivo de lectura");
            exit(EXIT_FAILURE);
        }

        // Al ser de lectura, cerramos el descriptor de entrada estándar
        close(0);

        if(fcntl(fichero, F_DUPFD, 0) == -1) {
            printf("\nError en fcntl");
            perror("\nError en fcntl");
            exit(EXIT_FAILURE);
        }
    } else if(strcmp(operador, ">") == 0) {
        if((fichero = open(archivo, O_WRONLY|O_CREAT)) < 0) {
            printf("\nError al intentar abrir el archivo de escritura");
            perror("\nError al intentar abrir el archivo de escritura");
            exit(EXIT_FAILURE);
        }

        // Al ser de escritura, cerramos el descriptor de salida estándar
        close(1);

        if(fcntl(fichero, F_DUPFD, 1) == -1) {
            printf("\nError en fcntl");
            perror("\nError en fcntl");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("\nEl operador introducido no es válido. Solo se permiten < o >");
        exit(EXIT_FAILURE);
    }

    if(execlp(orden, orden, NULL) < 0) {
        printf("\nError en execlp");
        perror("\nError en execlp");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}