/**
 * Sistemas Operativos
 * Módulo 2, Sesión 4, Ejercicio 5 - Maestro
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
#include<sys/wait.h>

int main(int argc, char* argv[]) {
    int fd[2];
    int extInfIntervalo1, extSupIntervalo1;
    int extInfIntervalo2, extSupIntervalo2;
    pid_t esclavo1;
    pid_t esclavo2;

    if(argc != 3) {
        printf("\nError en parámetro. Ejecución: ./maestro <extremoInferior> <extremoSuperior>");
        exit(EXIT_FAILURE);
    }

    if(strtol(argv[1], NULL, 10) > strtol(argv[2], NULL, 10)) {
        printf("\nEl extremo inferior no puede ser mayor que el extremo superior");
        exit(EXIT_FAILURE);
    }

    extInfIntervalo1 = strtol(argv[1], NULL, 10);
    extSupIntervalo1 = extInfIntervalo1 + strtol(argv[1], NULL, 10)/2;
    extInfIntervalo2 = extSupIntervalo1+1;
    extSupIntervalo2 = strtol(argv[2], NULL, 10);

    // Los declaramos como char
    char extInf1[5] = "";
    char extSup1[5] = "";
    char extInf2[5] = "";
    char extSup2[5] = "";

    sprintf(extInf1, "%d", extInfIntervalo1);
    sprintf(extSup1, "%d", extSupIntervalo1);
    sprintf(extInf2, "%d", extInfIntervalo2);
    sprintf(extSup2, "%d", extSupIntervalo2);

    pipe(fd);

    if((esclavo1 = fork()) < 0) {
        printf("\nError en el fork");
        perror("\nError en la llamada fork");
        exit(EXIT_FAILURE);
    } else if(esclavo1 == 0) {
        // Proceso hijo
        // Cerramos el descriptor de lectura
        close(fd[0]);

        // Duplicamos el descriptor de escritura para la salida
        // y llamamos al otro esclavo
        dup2(fd[1], STDOUT_FILENO);
        execlp("RUTA_AL_PROGRAMA/esclavo", "esclavo", extInf1, extSup1, NULL);
    } else {
        // Esperamos a que termine el hijo anterior para que los números salgan en orden
        wait(NULL);

        // Creamos otro hijo
        if((esclavo2 = fork()) < 0) {
            printf("\nError en el fork");
            perror("\nError en la llamada fork");
            exit(EXIT_FAILURE);
        } else if(esclavo2 == 0) {
            // Proceso hijo
            // Cerramos el descriptor de lectura
            close(fd[0]);

            // Duplicamos el descriptor de escritura para la salida
            // y llamamos al otro esclavo
            dup2(fd[1], STDOUT_FILENO);
            execlp("RUTA_AL_PROGRAMA/esclavo", "esclavo", extInf2, extSup2, NULL);
        } else {
            // Esperamos al otro hijo para finalizar el programa de forma correcta
            wait(NULL);

            // Proceso padre
            // Cerramos el descriptor de escritura
            close(fd[1]);

            // Duplicamos el descriptor de lectura para la entrada
            dup2(fd[0], STDIN_FILENO);
        }
    }

    return EXIT_SUCCESS;
}