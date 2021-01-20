/**
 * Sistemas Operativos
 * Módulo 2, Sesión 6, Ejercicio 5
 * Francisco Domínguez Lorente
 */

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    int fdFuente, fdDestino;
    char* memoriaFuente;
    char* memoriaDestino;
    struct stat bufferFuente;
    struct stat bufferDestino;

    if(argc < 3) {
        printf("\nSintaxis de uso: ./ejercicio1 FUENTE DESTINO");
        perror("\nSintaxis incorrecta");
        exit(EXIT_FAILURE);
    }

    if((fdFuente = open(argv[1], O_RDONLY) == -1)) {
        printf("\nError al abrir el archivo fuente");
        perror("\nError al abrir el archivo fuente");
        exit(EXIT_FAILURE);
    }

    if((stat(argv[1], &bufferFuente) == -1)) {
        printf("\nError en stat");
        perror("\nError en stat");
        exit(EXIT_FAILURE);
    }

    if((fdDestino = open(argv[2], O_RDWR | O_CREAT | O_TRUNC)) == -1) {
        printf("\nError al abrir el archivo destino");
        perror("\nError al abrir el archivo destino");
        exit(EXIT_FAILURE);
    }

    if((stat(argv[2], &bufferDestino) == -1)) {
        printf("\nError en stat");
        perror("\nError en stat");
        exit(EXIT_FAILURE);
    }

    if((ftruncate(fdDestino, bufferFuente.st_size)) == -1) {
        printf("\nError en ftruncate");
        perror("\nError en ftruncate");
        exit(EXIT_FAILURE);
    }

    memoriaFuente = (char *) mmap(0, bufferFuente.st_size, PROT_READ, MAP_SHARED, fdFuente, 0);

    if(memoriaFuente == MAP_FAILED) {
        printf("\nError en mmap de la fuente");
        perror("\nError en mmap de la fuente");
        exit(EXIT_FAILURE);
    }

    memoriaDestino = (char *) mmap(0, bufferDestino.st_size, PROT_WRITE, MAP_SHARED, fdDestino, 0);

    if(memoriaDestino == MAP_FAILED) {
        printf("\nError en mmap del destino");
        perror("\nError en mmap del destino");
        exit(EXIT_FAILURE);
    }

    close(fdFuente);
    close(fdDestino);

    memcpy(memoriaFuente, memoriaDestino, bufferDestino.st_size);

    return EXIT_SUCCESS;
}