#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "funciones.h"

int main(int argc, char const *argv[])
{
    //Lectura con Getopt
    int validador = 0, cantDis = -1, anchoDis = -1, b = 0;
    char nomVis[100],nomOut[100];


    while (validador= getopt(argc,argv,"i:o:n:d:b"))
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
    
    printf("nomVis: %s \n",nomVis);
    printf("nomOut: %s \n",nomOut);
    printf("cantDis: %d \n",cantDis);
    printf("anchoDis: %d \n",anchoDis);

    if (b = 0)
    {
        printf("SI");
    }
    else{
        printf("No");
    }
    
    
    return 0;
}
