#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include "funciones.h"

#define LECTURA 0
#define ESCRITURA 1

//Entrada: LArgo de los parametros ingresados, cantidad de discos, ancho de discos, 
        // nombre del archivo que contiene visualizaciones,nombre del archivo de salida.
//Salida: 0 si esta correcto, 1 si existe un error, 2 si el archivo es nulo.
//Descripcion: Funcion que valida las bandera de posibles datos erroneos.
int validadorBanderas(int argc,int cantDis,int anchoDis, char nomVis[],char nomOut[]){ 

    if (cantDis <= 0)
    {
        return 1;
    }
    
    if (anchoDis <= 0)
    {
        return 1;
    }

    if (strcmp(nomOut," ") == 0)
    {
        return 1;
    }

    FILE * archivo = fopen(nomVis,"r");
    if (archivo==NULL)
    {
        return 2;
    }
    fclose(archivo);

    return 0;
}

//Entrada: Lista con todos los valores pertenecientes a una visibilidad.
//Salida: FLoat con la distancia del centro a la visibilidad
//Descripcion: Funcion que calcula la distancia del centro a la visibilidad
float dCentroVis(float u,float v){ 

    float distancia = -1;
    
    distancia = sqrt((u * u) + (v * v));

    return distancia;
}

//Entrada: cantidad de discos, ancho de los discos, distancia de una visibilidad al centro.
//Salida: Numero entero que simboliza a que disco pertenece.
//Descripcion: Funcion que calcula a que disco pertenece la visibilidad.
int identificadorDiscoVis(int cantDis,double anchoDis, double disDisco){ 

    for (int i = 1; i <= cantDis; i++)
    {
        if (disDisco < anchoDis * i)
        {
            return i;
        }
        
    }

    return -1;
    
} 

//Entrada: cantidad de discos en el archivo leido
//Salida: lista con los pib de cada hijo
//Descripcion: funcion que crea los procesos hijos y retorna un arreglo con los pib de cada hijo.
hijo * hijosMios(int cantDiscos){

    hijo * listaHijos = (hijo*)malloc(sizeof(hijo)*cantDiscos);
    
    int pib = 1;
    
    for (int i = 0; i < cantDiscos; i++) //en cada ciclo quiero crear un hijo
    {   

        pipe(listaHijos[i].pipeHijoPadre);
        pipe(listaHijos[i].pipePadreHijo);

        
        if (pib > 0) //soy el padre
        {
            pib = fork();

            if (pib == 0)//soy el clon
            {   
                close(listaHijos[i].pipePadreHijo[ESCRITURA]);
                close(listaHijos[i].pipeHijoPadre[LECTURA]); 

                printf("SOy el hijo %d a punto de dup2 ",i);

                dup2(listaHijos[i].pipePadreHijo[LECTURA],STDIN_FILENO);
                dup2(listaHijos[i].pipeHijoPadre[ESCRITURA],STDOUT_FILENO);

                free(listaHijos);
                
                execl("./vis","./vis",NULL);

                perror("exec ls failed");
                exit(EXIT_FAILURE);
                
                
            }
            else //sigo siendo el padre
            {
                listaHijos[i].pib = pib; // GUarda en la lista el pib del hijo
            }
        }
        
    }

    return listaHijos;

}


//Entrada: lista de los datos de cada disco
//Salida: escritura de archivo correspondiente a datos de cada disco y escritura por pantalla de ser indicada
//Descripcion: funcion que crea el archivo final a entregar
void escribirArchivo(float * listaDatos, int numeroDisco,char nomOut[]){
    
    FILE* archivo;
    archivo=fopen(nomOut,"a");

    fprintf(archivo, "Disco %d:\nMedia Real: %f\nMedia imaginaria: %f\nPotencia: %f\nRuido total: %f\n",
                numeroDisco,listaDatos[0],listaDatos[1],listaDatos[2],listaDatos[3]);

    fclose(archivo);
}