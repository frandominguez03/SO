/**
 * Sistemas Operativos
 * Módulo 2, Sesión 2, Ejercicio 2
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

int main(int argc, char* argv[]) {
    DIR *directorio;
    struct dirent *lectura;
    struct stat atributos;
    int octal;
    char* pathname;

    if (argc < 3) {
        printf("\nSintaxis de ejecución: ./ejercicio2 <pathname> <numero>");
        perror("\nError en la sintaxis de ejecución");
        exit(EXIT_FAILURE);
    }

    else {
        pathname = argv[1];
        octal = strtol(argv[2], NULL, 8);
    }

    // Abrimos el directorio
    directorio = opendir(pathname);

    if(directorio == NULL) {
        printf("\nError al abrir el directorio");
        perror("\nError en opendir");
        exit(EXIT_FAILURE);
    }

    // Leemos todas las entradas del directorio
    while((lectura=readdir(directorio)) != NULL) {
        // Construimos la ruta
        char ruta[512];
        sprintf(ruta, "%s/%s", pathname, lectura->d_name);

        if(stat(ruta, &atributos) < 0) {
            printf("\nError al intentar acceder a los atributos del archivo");
            perror("\nError en stat");
            exit(EXIT_FAILURE);
        }

        mode_t permisosAntiguos = atributos.st_mode;

        if(S_ISREG(permisosAntiguos)) {
           if(chmod(ruta, (atributos.st_mode & ~octal)) < 0) {
                printf("\n%s : %d %o", ruta, errno, atributos.st_mode);
            }

            else {
                printf("\n%s : %o %o", ruta, permisosAntiguos, atributos.st_mode);
            }
        }
        
    }

    if(closedir(directorio) < 0) {
        printf("\nError al cerrar el directorio");
        perror("\nError en closedir");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}