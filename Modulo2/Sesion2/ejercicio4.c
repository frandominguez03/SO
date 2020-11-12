/**
 * Sistemas Operativos
 * Módulo 2, Sesión 2, Ejercicio 4
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
#include<ftw.h>

int numArchivos = 0, size = 0;

int buscar(const char* path, const struct stat* stat, int flags, struct FTW* ftw) {
    if(S_ISREG(stat->st_mode) && (stat->st_mode & S_IXGRP) && (stat->st_mode & S_IXOTH)) {
        printf("%s %ld\n", path, stat->st_ino);
        numArchivos++;
        size += stat->st_blksize;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    if(nftw(argc >= 2 ? argv[1] : ".", buscar, 10, 0) != 0) {
        printf("\nError en NFTW\n");
        perror("\nError en NFTW");
        exit(EXIT_FAILURE);
    }

    printf("\nExisten %d archivos con permisos de ejecución para grupo y otros\n", numArchivos);
    printf("\nEl tamaño total ocupado por dichos archivos es %d bytes\n", size);

    return EXIT_SUCCESS;
}