#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define limpiar       "clear"
#define BLANCO      "\x1b[0m"
#define ROJO        "\x1b[31m"
#define AZUL        "\x1b[34m"
#define AMARILLO    "\x1b[33m"
#define VERDE       "\x1b[32m"

//lee el lemario y genera las palabra aleatorias
void traducir_archivo(char pal[][40]);
//remplaza la palabra elegida por espacios
void crear_palabra_desc(char palabraDes[], char palabraEsc[]);

//remplaza la letra ingresada en los espacios
int remplazar(char palabraEsc[], char palabraDes[], char ing);
//imrime el atril con el munieco
void interfaz(int vid, char palabrasDes[], char palabraEsc[], char palabraDes[]);
//imprime cuadro de letras equivocadas
void equivocadas(int cont, char equiv[]);

//imrime el atril con el munieco
void historial(int turn, float porcen[], char win[], char palabraEsc[]);
//imprime historial de partidas
void cuadro(int partida, char palabra[], char gano, float porcentaje);