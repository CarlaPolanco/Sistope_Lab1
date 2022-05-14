#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include "funciones.h"

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
	int pipefd[2];
	char mensaje[100];
	pipe(pipefd);

	// PUENTE PIPE
	printf("%d\n", STDOUT_FILENO);
    //dup2(pipefd[READ],STDOUT_FILENO);
    close(pipefd[WRITE]);


	printf("TESTEO mi pib es: %d y el de mi padre es: %d \n",getpid(),getppid());
	printf("lectura 1\n");
	//read(pipefd[READ], mensaje, 100); //lectura de pipe e impresion
	printf("lectura 2\n");
	printf("hijo dice: %s\n", mensaje);
	printf("lectura 3\n");


	return 0;
}