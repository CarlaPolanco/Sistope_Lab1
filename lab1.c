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
    double anchoDis = -1;
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
            sscanf(optarg,"%lf",&anchoDis);
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
        printf("Las banderas estan correctas\n");
    }

    // Verifica bandera de impresion por consola

    if (b == 1)
    {
        printf("La bandera SI escritura por pantalla esta activada \n\n");
    }
    else{
        printf("La bandera de escritura por pantalla NO esta activada \n\n");
    }

    /* BLOQUE DE PIPES */

    int pipefd[2];
    pipe(pipefd);
    close(pipefd[LECTURA]);
    write(STDOUT_FILENO, "MENSAJE DE CONFIRMACION", 24);

    /* BLOQUE DE LECTURA */

    char buffer[100];
    int columna; //Columna en donde estoy posicionada,
    float visibilidad[5]; // arreglo que almacena la visibilidad
    float disVis = -1; // distancia del centro a la visibilidad
    int radVis = -1; // Disco al cual pertenece la visibilidad

    FILE * archivo = fopen(nomVis,"r");

    if (archivo == NULL)
    {
        printf("Archivo Invalido, se cierra el programa.");
        return 1;
    }
    else
    {   
        int * pipHijos = hijosMios(cantDis); // Creacion de procesos hijos

        if( pipHijos == NULL){

        //execl(nasdsdadn) // ./hijos -> recibir y procesar los datos del padre
        //execl(path_proceso,path_proceso,NULL); -> comando para cambiar el programa principal del hijo

        /* PUENTE PIPE */

        /*printf("lectura testeo 1\n");
        close(pipefd[ESCRITURA]);
        printf("lectura testeo 2\n");
        dup2(pipefd[LECTURA],STDOUT_FILENO);
        printf("lectura testeo 3\n");*/


        /* EXECL */
        execl("./vis","./vis",NULL);


        exit(0);

        }else{

            for (int i = 0; i < cantDis; i++) 
            {
                waitpid(pipHijos[i], NULL,0); // EL PADRE ESPERA POR CADA UNO DE SUS HIJOS, PARA NO CREAR PROCESOS ZOMBIES
            }

            
            while (!feof(archivo)) // LECTURA DEL ARCHIVO QUIZAS ESTO SE PUEDA PASAR A UNA FUNCION POR BUENAS PRACTICAS
            {

                fgets(buffer,100,archivo); // Lectura del archivo linea por linea, retorna 1 linea guardada en buffer

                char * token = strtok(buffer, ","); // Separa el buffer por comas

                columna = 0; 
                disVis = -1;
                radVis = -1;
                
                while( token != NULL ) {

                    if (columna == 0) // posicion en eje u
                    {
                        sscanf(token,"%f",&visibilidad[0]);
                    }

                    if (columna == 1) // posicion en eje v
                    {
                        sscanf(token,"%f",&visibilidad[1]);
                    }

                    if (columna == 2) // valor real de la visibilidad
                    {
                        sscanf(token,"%f",&visibilidad[2]);
                    }

                    if (columna == 3) // valor imaginario de la visibilidad
                    {
                        sscanf(token,"%f",&visibilidad[3]);
                    }

                    if (columna == 4) // ruido de la visibilidad
                    {
                        sscanf(token,"%f",&visibilidad[4]);
                    }
                    
                    token = strtok(NULL, ","); // Desplaza el token a la siguiente columna
                    columna++;

                }// ERROR ESTOY LEYENDO UN VALOR DE MAS SOLUCIONARLO QUE NO SE OLVIDE. cambiar double a float

                disVis = dCentroVis(visibilidad); // retorna la distancia del centro a la visibilidad

                printf("disVIs; %f ",disVis);

                radVis = identificadorDiscoVis(cantDis,anchoDis,disVis); // retorna al radio al cual pertenece la visibilidad
                
                printf("radio: %d \n", radVis); // IMPRIME EL RADIO DE LAS VISIBILIDADES

                // ACA HAY QUE OMPLEMENTAR LAS PIPE
            }

            fclose(archivo);
        }

        free(pipHijos);     
    }
    return 0;

}
