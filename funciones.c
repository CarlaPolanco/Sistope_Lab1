#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

double dCentroVis(double visibilidad[]){ // Funcion que calcula la distancia del centro a la visibilidad

    double distancia = -1 ;

    distancia = ( (visibilidad[0] * visibilidad[0]) + (visibilidad[1] * visibilidad[1]) ) * 0.5;

    return distancia;
}


int identificadorDiscoVis(int cantDis,double anchoDis, double disDisco){ // Funcion que calcula a que disco pertenece la visibilidad

    double radiosDiscos[cantDis*2];
    int j = 1; // j es el multiplicador para ver el ancho de cada uno de los discos

    for (int i = 0; i < cantDis*2; i++) // sirve para saber el rango de cada disco QUIZAS ESTO SE PUEDA OPTIMIZAR PARA AHORRAR RECURSOS DEL COMPUTADOR, YA QUE ESTA OPERACION ES IGUAL PARA TODAS LAS VISIBILIDADES
    {   
        if (i == 0) 
        {
            radiosDiscos[0] = 0;
            radiosDiscos[1] = anchoDis * j;
            j++;
            i = 2;
        }
        else
        {
            radiosDiscos[i-1] = 0;
            radiosDiscos[i] = anchoDis * j;
            j++;
        }
         
    }
    
    
    for (int i = 0; i < (cantDis*2)-1; i=i+2) // COmpara la distancia en los rangos de los radios
    {
        if (disDisco >= radiosDiscos[i] && disDisco <= radiosDiscos[i+1])
        {
            return i;
        }

    }
    
    return -3; // significa que no entro en ninguna rango puede ser un error o esta en el ultimo disco inficito
} 
