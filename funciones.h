#ifndef funciones_h_
#define funciones_h_

typedef struct hijo
{
    int pipeHijoPadre[2];
    int pipePadreHijo[2];
    int cantVis;
    int pib;   

}hijo;

int validadorBanderas(int argc,int cantDis,int anchoDis, char nomVis[],char nomOut[]);

float dCentroVis(float u,float v);

int identificadorDiscoVis(int cantDis,float anchoDis, float disDisco);

hijo * hijosMios(int cantDiscos);

void escribirArchivo(float * listaDatos, int numeroDisco,char nomOut[]);

#endif