/**
 * Sistemas Operativos
 * Módulo 2, Sesión 1, Ejercicio 4
 * Francisco Domínguez Lorente
 */

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

#define S_ISREG2(modo) ((modo & S_IFMT) == S_IFREG)

int main(int argc, char* argv[]) {
    struct stat atributos;
    char tipoArchivo[30];

    if (argc < 2) {
        printf("\nSintaxis de ejecución: ./ejercicio4 <nombre_archivo>\n");
        perror("\nError en open");
		exit(EXIT_FAILURE);
    }

    if(lstat(argv[1], &atributos) < 0) {
        printf("\nError al intentar acceder a los atributos de %s", argv[1]);
        perror("\nError en lstat");
        printf("\nError %d en open", errno);
    }

    if(S_ISREG2(atributos.st_mode) == 1) {
        printf("El archivo es un fichero regular\n");
    } else {
        printf("El archivo NO es un fichero regular\n");
    }

    return EXIT_SUCCESS;
}