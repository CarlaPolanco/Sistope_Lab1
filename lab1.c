#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "funciones.h"

int main(int argc, char *argv[])
{
    /* BLOQUE DE RECOLECCION DE BANDERAS */

    int validador = 0, cantDis = -1, anchoDis = -1, b = 0, valBanderas = 0;
    char nomVis[100],nomOut[100];

    // Se guardan las banderas en variables
    while ((validador = getopt(argc,argv,"i:o:n:d:b")) != -1)
    {
        switch (validador)
        {
        case 'i':
            strcpy(nomVis,optarg);
            break;
        case 'o':
            strcpy(nomOut,optarg);
            break;
        case 'n':
            sscanf(optarg,"%d",&cantDis);
            break;
        case 'd':
            sscanf(optarg,"%d",&anchoDis);
            break;
        case 'b':
            b = 1;
            break;
        default: 
            printf("La bandera ingresada no es valida.Termino la ejecucion\n");
            return 1;
            break;
        }
    }
    
    /* BLOQUE DE VALIDACIONES */

    valBanderas = validadorBanderas(argc,cantDis,anchoDis,nomVis,nomOut);

    if (valBanderas == 1)
    {
        printf(" Cantidad de discos incorrecto. \n Ancho de disco incorrecto. \n Nombre de salida esta vacio. Fin del programa \n\n");

        return 1;
    }

    else if (valBanderas == 2)
    {
        printf(" EL archivo de visilidades es NULL. Fin del programa ");

        return 1;
    }

    else
    {
        printf("Las banderas estan correctas");
    }

    // Verifica bandera de impresion por consola

    if (b == 1)
    {
        printf("La bandera SI esta activada \n\n");
    }
    else{
        printf("La bandera NO esta activada \n\n");
    }

    /* BLOQUE DE LECTURA */

    char buffer[100];

    FILE * archivo = fopen(nomVis,"r");

    if (archivo == NULL)
    {
        printf("Archivo Invalido, se cierra el programa.");
        return 1;
    }
    else
    {   
        while (!feof(archivo))
        {
            fgets(buffer,100,archivo); // Lectura del archivo linea por linea, retorna 1 linea guardada en buffer

            char * token = strtok(buffer, ","); // Separa el buffer por comas

            int columna = 0,visDisco = -1; //Columna en donde estoy posicionada, Disco al cual pertenece la visibilidad
            double visibilidad[5]; // arreglo que almacena la visibilidad

            while( token != NULL ) {

                if (columna == 0) // posicion en eje u
                {
                    sscanf(token,"%lf",&visibilidad[0]);
                }

                if (columna == 1) // posicion en eje v
                {
                    sscanf(token,"%lf",&visibilidad[1]);
                }

                if (columna == 2) // valor real de la visibilidad
                {
                    sscanf(token,"%lf",&visibilidad[2]);
                }

                if (columna == 3) // valor imaginario de la visibilidad
                {
                    sscanf(token,"%lf",&visibilidad[3]);
                }

                if (columna == 4) // ruido de la visibilidad
                {
                    sscanf(token,"%lf",&visibilidad[4]);
                }
                
                token = strtok(NULL, ","); // DEsplaza el token a la siguiente columna
                columna++;

            }// ERROR ESTOY LEYENDO UN VALOR DE MAS SOLUCIONARLO QUE NO SE OLVIDE.

            visDisco = identificadorDiscoVis(cantDis,anchoDis,visibilidad);
            
        }
        
    }
    
    fclose(archivo);
    
    return 0;
}
