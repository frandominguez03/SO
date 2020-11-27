/**
 * Sistemas Operativos
 * Módulo 2, Sesión 5, Ejercicio 2
 * Francisco Domínguez Lorente
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static int numSig1 = 0, numSig2 = 0, numSig3 = 0;

static void manejador(int numsig) {
    if(numsig == SIGINT) {
        numSig1++;
        printf("\nIntroducida señal %d, número de veces: %d\n", SIGINT, numSig1);
    } else if(numsig == SIGUSR1) {
        numSig2++;
        printf("Introducida señal %d, número de veces: %d\n", SIGUSR1, numSig2);
    } else if(numsig == SIGUSR2) {
        numSig3++;
        printf("Introducida señal %d, número de veces: %d\n", SIGUSR2, numSig3);
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = manejador;

    /* Rellenamos la máscara de señales con todas las señales */
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    printf("Mi PID es: %d\n", getpid());

    if(sigaction(SIGINT, &sa, NULL) == -1 ||
       sigaction(SIGUSR1, &sa, NULL) == -1 ||
       sigaction(SIGUSR2, &sa, NULL) == -1) {
        printf("Error en el manejador\n");
        exit(EXIT_FAILURE);
    }

    while(1) {

    }
}