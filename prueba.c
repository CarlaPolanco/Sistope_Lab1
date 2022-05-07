#include <stdio.h>
#include <stdlib.h>

double dCentroVis(double visibilidad[]){ // Funcion que calcula la distancia del centro a la visibilidad

    double distancia = -1 ;

    printf("FUNCION   u: %lf v: %lf \n\n",visibilidad[0],visibilidad[1]);

    distancia = ( (visibilidad[0] * visibilidad[0]) + (visibilidad[1] * visibilidad[1]) ) * 0.5;

    printf("FUNCION   Distancia: %lf \n\n", distancia);

    return distancia;
}

int main()
{
    double visibilidad[5] = {2,3,4,5,6};
    double distancia;

    distancia = dCentroVis(visibilidad);

    printf("%lf \n ",distancia);
    return 0;
}


/*
                     IMPRESION DE BANDERAS 

    printf("\n\n------ Verificacion de las banderas ingresadas ----------\n");
    printf("nomVis: %s \n",nomVis);
    printf("nomOut: %s \n",nomOut);
    printf("cantDis: %d \n",cantDis);
    printf("anchoDis: %d \n",anchoDis);
    printf("--------------------------------------------------------\n");

                     MUESTRA DE VISIBILIDADES

    for (int i = 0; i < 5; i++)
            {
                printf(" %lf ",visibilidad[i]);
            }

            printf("\n");


     INTENTO DE CALCULO DE RADIOS
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

    */
