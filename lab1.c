#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include "funciones.h"

#define LECTURA 0
#define ESCRITURA 1

int main(int argc, char *argv[])
{
    /* BLOQUE DE RECOLECCION DE BANDERAS */
    int validador = 0, cantDis = -1, b = 0, valBanderas = 0;
    float anchoDis = -1;
    char nomVis[100], nomOut[100];

    // Se guardan las banderas en variables
    while ((validador = getopt(argc, argv, "i:o:n:d:b")) != -1)
    {
        switch (validador)
        {
        case 'i':
            strcpy(nomVis, optarg);
            break;
        case 'o':
            strcpy(nomOut, optarg);
            break;
        case 'n':
            sscanf(optarg, "%d", &cantDis);
            break;
        case 'd':
            sscanf(optarg, "%f", &anchoDis);
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

    valBanderas = validadorBanderas(argc, cantDis, anchoDis, nomVis, nomOut);

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


    /* BLOQUE DE LECTURA */

    char buffer[100];
    int columna;          // Columna en donde estoy posicionada,
    float visibilidad[5]; // arreglo que almacena la visibilidad
    float disVis = -1;    // distancia del centro a la visibilidad
    int radVis = -1;      // Disco al cual pertenece la visibilidad
    int bandera = 1;      // cuanto termino de hacer la lectura
    float *listaDatosFinales;  // lista que almacena las salidad de los hijos
    float valor = 0.0;    // variable que pasara los valores por la pipe
    int valorEntero = -1; // variable que pasara la cantidad de visualizaciones por la pipe

    FILE *archivo;

    hijo *hijos = hijosMios(cantDis); // Creacion de procesos hijos

    if (hijos != NULL) // SOy el padre
    {

        for (int i = 0; i < cantDis; i++)
        {
            close(hijos[i].pipePadreHijo[LECTURA]);
            close(hijos[i].pipeHijoPadre[ESCRITURA]);
        }

        archivo = fopen(nomVis, "r");

        if (archivo == NULL)
        {
            printf("Archivo Invalido, se cierra el programa.");
            return 1;
        }
        else
        {
            while (archivo != NULL && !feof(archivo)) // LECTURA DEL ARCHIVO QUIZAS ESTO SE PUEDA PASAR A UNA FUNCION POR BUENAS PRACTICAS
            {
                fgets(buffer, 100, archivo); // Lectura del archivo linea por linea, retorna 1 linea guardada en buffer

                char *token = strtok(buffer, ","); // Separa el buffer por comas

                columna = 0;
                disVis = -1;
                radVis = -1;


                while (token != NULL)
                {

                    if (columna == 0) // posicion en eje u
                    {
                        sscanf(token, "%f", &visibilidad[0]);
                    }

                    if (columna == 1) // posicion en eje v
                    {
                        sscanf(token, "%f", &visibilidad[1]);
                    }

                    if (columna == 2) // valor real de la visibilidad
                    {
                        sscanf(token, "%f", &visibilidad[2]);
                    }

                    if (columna == 3) // valor imaginario de la visibilidad
                    {
                        sscanf(token, "%f", &visibilidad[3]);
                    }

                    if (columna == 4) // ruido de la visibilidad
                    {
                        sscanf(token, "%f", &visibilidad[4]);
                    }

                    token = strtok(NULL, ","); // Desplaza el token a la siguiente columna
                    columna++;
                }

                disVis = dCentroVis(visibilidad[0], visibilidad[1]); // retorna la distancia del centro a la visibilidad

                radVis = identificadorDiscoVis(cantDis, anchoDis, disVis); // retorna al radio al cual pertenece la visibilidad

                
                if (radVis != -1)
                {
                    bandera = 1; // Voy a mandar algo, are you ready?

                    write(hijos[radVis - 1].pipePadreHijo[ESCRITURA], &bandera, sizeof(int));

                    for (int j = 0; j < 5; j++)
                    {   
                        write(hijos[radVis - 1].pipePadreHijo[ESCRITURA], &visibilidad[j], sizeof(float));
                    }
                }
                
                
            }
            fclose(archivo);

            bandera = 0; // Termino de leer el archivo

            for (int i = 0; i < cantDis; i++) // Le aviso a mis hijos
            {
                write(hijos[i].pipePadreHijo[ESCRITURA], &bandera, sizeof(int));
            }
            
            listaDatosFinales = (float *)malloc(sizeof(float) * 4);

            for (int i = 0; i < cantDis; i++) // LEEE AL HIJO
            {
                for (int j = 0; j < 4; j++)
                {
                    read(hijos[i].pipeHijoPadre[LECTURA], &valor, sizeof(float)); //Media real, media imaginaria, potencia, ruidototal
                    listaDatosFinales[j] = valor;
                }
                read(hijos[i].pipeHijoPadre[LECTURA], &valorEntero, sizeof(int)); //cantVisibildaes
                hijos[i].cantVis = valorEntero;

                // ESCRITURA ARCHIVO/ ESCRITURA POR PANTALLA
                escribirArchivo(listaDatosFinales, i + 1, nomOut);
            }
            free(listaDatosFinales);

            for (int i = 0; i < cantDis; i++)
            {
                waitpid(hijos[i].pib, NULL, 0); // EL PADRE ESPERA POR CADA UNO DE SUS HIJOS, PARA NO CREAR PROCESOS ZOMBIES
            }


        }
        if(b==1){ //si la bandera es detectada
            for(int i=0; i<cantDis; i++){
                printf("Soy el hijo con pid %d y procese %d visibilidades\n",hijos[i].pib,hijos[i].cantVis);
            }
        }

        free(hijos);

    }else{
        return 1;
    }
    //printf("Termine con exito \n");
    return 0;
}
