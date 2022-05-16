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

//Entrada: cantidad de discos en el archivo leido
//Salida: lista con los pib de cada hijo
//Descripcion: funcion que crea los procesos hijos y retorna un arreglo con los pib de cada hijo.
int * hijosMios(int cantDiscos){

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

//Entrada: lista de todos los datos del disco correspondiente
//Salida: lista de los 4 datos finales solicitados
//Descripcion: lee la lista de datos y ejecuta el calculo correspondiente necesario
float * calculoResultados(float * listaDatos){
    float* listaRespuesta = (float*)malloc(sizeof(int)*4);
    float cantidadDatos = listaDatos[0];
    float sumaReal = 0.0;
    float sumaImaginaria = 0.0;
    float potencia = 0.0;
    float ruido = 0.0;
    for (int i=0; i<cantidadDatos;i++){
        sumaReal = sumaReal + listaDatos[3+(5*i)];
        sumaImaginaria = sumaImaginaria + listaDatos[4+(5*i)];
        ruido = ruido + listaDatos[5+(5*i)];
    }
    potencia = ((sumaReal*sumaReal)+(sumaImaginaria*sumaImaginaria))*((sumaReal*sumaReal)+(sumaImaginaria*sumaImaginaria));
    float mediaReal = sumaReal/cantidadDatos;
    float mediaImaginaria = sumaImaginaria/cantidadDatos;
    //printf("RESULTADOS:\nMedia real: %f\nMedia imaginaria: %f\nPotencia: %f\nRuido total: %f\n",listaRespuesta[0],listaRespuesta[1],listaRespuesta[2],listaRespuesta[3]);
    listaRespuesta[0]= mediaReal;
    listaRespuesta[1]= mediaImaginaria;
    listaRespuesta[2]= potencia;
    listaRespuesta[3]= ruido;
    return listaRespuesta;
}

//Entrada: lista de los datos de cada disco
//Salida: escritura de archivo correspondiente a datos de cada disco y escritura por pantalla de ser indicada
//Descripcion: funcion que crea el archivo final a entregar
void escribirArchivo(int b, float * listaDatos, int numeroDisco){
    char nombreArchivo[16] = "propiedades.txt";
    FILE* archivo;
    archivo=fopen(nombreArchivo,"a");
    fprintf(archivo, "Disco %d:\nMedia Real: %f\nMedia imaginaria: %f\nPotencia: %f\nRuido total: %f\n",numeroDisco,listaDatos[0],listaDatos[1],listaDatos[2],listaDatos[3]);
    if (b==1){
        printf("Disco %d:\nMedia Real: %f\nMedia imaginaria: %f\nPotencia: %f\nRuido total: %f\n",numeroDisco,listaDatos[0],listaDatos[1],listaDatos[2],listaDatos[3]);
    }
    fclose(archivo);
}