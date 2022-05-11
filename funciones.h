#ifndef funciones_h_
#define funciones_h_

int validadorBanderas(int argc,int cantDis,int anchoDis, char nomVis[],char nomOut[]);

float dCentroVis(float visibilidad[]);

int identificadorDiscoVis(int cantDis,double anchoDis, double disDisco);

int * hijosMios(int cantDiscos);

#endif