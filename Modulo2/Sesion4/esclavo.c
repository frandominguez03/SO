/**
 * Sistemas Operativos
 * Módulo 2, Sesión 4, Ejercicio 5 - Esclavo
 * Francisco Domínguez Lorente
 */

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<math.h>

int main(int argc, char* argv[]) {
    int fd[2];
    int divisores = 2;
    int primo = 0;
    int extInf, extSup;
    char numero[4];

    if(argc != 3) {
        printf("\nError en parámetro. Ejecución: ./esclavo <extremoInferior> <extremoSuperior>");
        exit(EXIT_FAILURE);
    }

    if(strtol(argv[1], NULL, 10) > strtol(argv[2], NULL, 10)) {
        printf("\nEl extremo inferior no puede ser mayor que el extremo superior (esclavo)");
        exit(EXIT_FAILURE);
    }

    extInf = strtol(argv[1], NULL, 10);
    extSup = strtol(argv[2], NULL, 10);

    for(int i = extInf; i <= extSup; i++) {
        for(int j=2; j <= sqrt(i); j++) {
            if(i%j == 0) {
                // No es primo
                primo = 1;
            }
        }

        if(primo == 0) {
            sprintf(numero, "%d\n", i);
            write(fd[1], numero, strlen(numero)+1);
            printf("\n");
        }

        primo = 0;
    }

    return EXIT_SUCCESS;
}