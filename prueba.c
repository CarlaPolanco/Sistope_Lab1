#include <stdio.h>
#include <stdlib.h>

void imprimoString(char string[]){
    printf("string: %s \n",string);
}

int main()
{
    char string[100] = "Soy un string" ;
    imprimoString(string);
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
