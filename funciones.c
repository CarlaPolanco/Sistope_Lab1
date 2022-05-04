#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int identificadorDiscoVis(int cantDis,int anchoDis, int visibilidad[]){
    return 0;
}