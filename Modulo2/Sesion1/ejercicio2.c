/**
 * Sistemas Operativos
 * Módulo 2, Sesión 1, Ejercicio 2
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

int main(int argc, char *argv[])
{
	int fd_archivo, fd_salida, numBloques;
	char buffer[80] = "";
	char cabecera[32];
	char bloque[12];

	if(argc < 2) {
		fd_archivo= STDIN_FILENO;
	} else {
		//Abrimos el archivo argumento
		if( (fd_archivo=open(argv[1],O_RDONLY))<0) {
			printf("\nError %d en open de %s", errno, argv[1]);
			perror("\nError en open");
			exit(EXIT_FAILURE);
		}
	}
	
	//Abrimos el archivo salida.txt
	if ( (fd_salida=open("salida.txt", O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR))<0) {
		printf("\nError %d en open de salida.txt", errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	// Reservamos espacio al principio del fichero para escribir posteriormente
	if (lseek(fd_salida, 32, SEEK_SET) < 0) {
		perror("\nError en write de al inicio del archivo");
		exit(EXIT_FAILURE);
	}

	numBloques = 0;
	while (read(fd_archivo, buffer, 80*sizeof(char)) > 0) {
		numBloques++;

		sprintf(bloque, "\n\nBloque %d\n", numBloques); //Añade '\0' al final de la cadena

		if (write(fd_salida, bloque, strlen(bloque)) != strlen(bloque)) {
			perror("\nError en write de cadenaBloque");
			exit(EXIT_FAILURE);
		}

		if (write(fd_salida, buffer, strlen(buffer)) < 0) {
			perror("\nError en write de bloque");
			exit(EXIT_FAILURE);
		}
	}

	if (lseek(fd_salida, 0, SEEK_SET) == -1) {
		printf("\nError en reposicionamiento del offset");
		exit(EXIT_FAILURE);
	}

	sprintf(cabecera, "Número de bloques total es %d", numBloques);

	if (write(fd_salida, cabecera, strlen(cabecera)) < 0) {
		perror("\nError en escritura al inicio del archivo");
		exit(EXIT_FAILURE);
	}

	close(fd_archivo);
	close(fd_salida);
	return EXIT_SUCCESS;
}
