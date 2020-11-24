/**
 * Sistemas Operativos
 * Módulo 2, Sesión 5, Ejercicio 3
 * Francisco Domínguez Lorente
 */

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    sigset_t new_mask;

    printf("Mi PID es: %d\n", getpid());

    /* Rellenamos la máscara de señales con todas las señales */
    sigfillset(&new_mask);

    /* Eliminamos la señal SIGUSR1 */
    sigdelset(&new_mask, SIGUSR1);

    /* Esperamos a la señal SIGUSR1 */
    sigsuspend(&new_mask);
}