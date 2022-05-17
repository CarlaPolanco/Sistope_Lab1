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

	float numero = -1;
	float * listaVisibilidad = (float*)malloc(sizeof(float)*5); 
	// listaVisibilidad = [u,v,real,imaginario,ruido]

	int bandera = -1;
	int cantVis = 0;

	float sumatoriaReal = 0.0;
	float sumatoriaImaginaria = 0.0;
	float sumatoriaRuido = 0.0;
	float potencia = 0.0;

	read(STDIN_FILENO,&bandera,sizeof(float)); // lee la bandera

	while (bandera == 1)
	{
		for (int i = 0; i < 5; i++) // guarda los valores
		{
			read(STDIN_FILENO,&numero,sizeof(float)); // lee al padre
			listaVisibilidad[i] = numero ;
		}

		sumatoriaRuido = sumatoriaRuido + listaVisibilidad[4];
		sumatoriaImaginaria = sumatoriaImaginaria + listaVisibilidad[3];
		sumatoriaReal = sumatoriaReal + listaVisibilidad[2];
		potencia = potencia + dCentroVis(listaVisibilidad[0],listaVisibilidad[1]);
		cantVis = cantVis + 1;

		read(STDIN_FILENO,&bandera,sizeof(float)); // lee la bandera
	}

	sumatoriaReal = sumatoriaReal / cantVis;
	sumatoriaImaginaria = sumatoriaImaginaria / cantVis;
	
	write(STDOUT_FILENO,&sumatoriaReal,sizeof(float)); // Escribe al padre
	write(STDOUT_FILENO,&sumatoriaImaginaria,sizeof(float)); // Escribe al padre
	write(STDOUT_FILENO,&potencia,sizeof(float)); // Escribe al padre
	write(STDOUT_FILENO,&sumatoriaRuido,sizeof(float)); // Escribe al padre
	
	free(listaVisibilidad);

	exit(EXIT_SUCCESS);
}