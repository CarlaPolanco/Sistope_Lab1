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

    */
