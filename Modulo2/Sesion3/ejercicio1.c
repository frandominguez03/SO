/**
 * Sistemas Operativos
 * Módulo 2, Sesión 3, Ejercicio 1
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
    pid_t nuevoProceso;
    int numero;

    if(argc < 2) {
        printf("\nError de sintaxis. Ejecución: ./ejercicio1 <numero>");
        perror("\nError en número de parámetros");
        exit(EXIT_FAILURE);
    } else {
        numero = strtol(argv[1], NULL, 10);
    }

    if((nuevoProceso = fork()) < 0) {
        printf("\nError en el fork");
        perror("\nError en la llamada fork");
        exit(EXIT_FAILURE);
    } else if(nuevoProceso == 0) {
        if(numero % 2 == 0) {
            printf("El número %d es par\n", numero);
        }

        else {
            printf("El número %d es impar\n", numero);
        }
    }

    return EXIT_SUCCESS;
}