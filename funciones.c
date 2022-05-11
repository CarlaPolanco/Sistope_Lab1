#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>

int validadorBanderas(int argc,int cantDis,int anchoDis, char nomVis[],char nomOut[]){ // Funcion que valida las bandera de posibles datos erroneos

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

float dCentroVis(float visibilidad[]){ // Funcion que calcula la distancia del centro a la visibilidad

    float distancia = -1;
    
    distancia = sqrt((visibilidad[0] * visibilidad[0]) + (visibilidad[1] * visibilidad[1]));

    return distancia;
}

int identificadorDiscoVis(int cantDis,double anchoDis, double disDisco){ // Funcion que calcula a que disco pertenece la visibilidad

    for (int i = 1; i < cantDis; i++)
    {
        if (disDisco < anchoDis * i)
        {
            return i;
        }
        
    }

    return -1;
    
} 

int * hijosMios(int cantDiscos){ // Funcion que retorna un arreglo con los pib de cada hijo.

    int* pibHijos = (int*)malloc(sizeof(int)*cantDiscos); 

    for (int i = 0; i < cantDiscos; i++) // llenado del arreglo con ceros para eliminar datos basuras
    {
        pibHijos[i] = 0;
    }
    

    int pib = 1;

    printf("OJO, EL PID DEL PADRE ES= %d\n",getpid());
    
    for (int i = 0; i < cantDiscos; i++) //en cada ciclo quiero crear un hijo
    {   
        
        if (pib > 0) //soy el padre
        {
            pib = fork();

            if (pib == 0)//soy el clon
            {    
                return NULL; // si soy el hijo salgo del ciclo y retorno NULL
            }
            else //sigo siendo el padre
            {
                pibHijos[i] = pib; // GUarda en la lista el pib del hijo
            }
        }
        
    }

    return pibHijos;

}