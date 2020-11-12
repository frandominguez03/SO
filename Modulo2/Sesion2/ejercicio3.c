/**
 * Sistemas Operativos
 * Módulo 2, Sesión 2, Ejercicio 3
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

void busqueda(char* path, int *numArchivos, int *size) {
    DIR *directorio;
    struct dirent *lectura;
    struct stat atributos;
    char ruta[PATH_MAX];

    // Abrimos el directorio
    directorio = opendir(path);

    if(directorio == NULL) {
        printf("\nError al abrir el directorio\n");
        perror("\nError en opendir");
        exit(EXIT_FAILURE);
    }

    // Leemos todas las entradas del directorio
    while((lectura=readdir(directorio)) != NULL) {
        // Construimos la ruta
        sprintf(ruta, "%s/%s", path, lectura->d_name);

        // Si es un directorio, llamamos de nuevo a la función de forma recursiva
        if(lectura->d_type == DT_DIR && strcmp(".", lectura->d_name) != 0 && strcmp("..", lectura->d_name) != 0) {
            busqueda(ruta, numArchivos, size);
        }

        else {
            if(stat(ruta, &atributos) < 0) {
                printf("\nError al intentar acceder a los atributos del archivo\n");
                perror("\nError en stat");
                exit(EXIT_FAILURE);
            }

            if(lectura->d_type == DT_REG && (atributos.st_mode & S_IXGRP) && (atributos.st_mode & S_IXOTH)) {
                printf("%s %ld\n", ruta, atributos.st_ino);
                (*numArchivos)++;
                (*size) += atributos.st_blksize;
            }
        }
    }

    if(closedir(directorio) < 0) {
        printf("\nError al cerrar el directorio");
        perror("\nError en closedir");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {
    char* pathname;
    int numArchivos = 0, size = 0;

    if (argc == 2) {
        pathname = argv[1];
    }

    else {
        pathname = ".";
    }

    busqueda(pathname, &numArchivos, &size);

    printf("\nExisten %d archivos con permisos de ejecución para grupo y otros\n", numArchivos);
    printf("\nEl tamaño total ocupado por dichos archivos es %d bytes\n", size);

    return EXIT_SUCCESS;
}