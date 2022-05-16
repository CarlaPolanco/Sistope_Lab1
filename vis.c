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
	/* LISTA DE PRUEBA*/

	float listaPrueba[16]= {3.0,82.984130,-266.901452,-0.093600,-0.079059,11.070505,82.984130,-266.901452,0.433206,-0.164955,9.616252,-119.089415,-196.833666,0.197163,0.107890,18.713923};
            
	/* FIN LISTA PRUEBA*/

	int pipefd[2];
	char mensaje[100];
	pipe(pipefd);

	// PUENTE PIPE
	//printf("%d\n", STDOUT_FILENO);
    //dup2(pipefd[READ],STDOUT_FILENO);
    //close(pipefd[WRITE]);


	printf("TESTEO mi pib es: %d y el de mi padre es: %d \n",getpid(),getppid());
	//read(pipefd[READ], mensaje, 100); //lectura de pipe e impresion
	printf("hijo dice: %s\n", mensaje);

	/* CALCULOS */

	float * resultados = calculoResultados(listaPrueba);
	printf("RESULTADOS:\nMedia real: %f\n,Media imaginaria: %f\nPotencia: %f\nRuido total: %f\n",resultados[0],resultados[1],resultados[2],resultados[3]);

	return 0;
}