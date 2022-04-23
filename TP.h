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

void traducir_archivo(char random[][40], char pal[][40]);
void crear_palabra_desc(char palabraDes[], char palabraEsc[]);
int remplazar(char palabraEsc[], char palabraDes[], char ing);
void interfaz(int vid, char palabrasDes[], char palabraEsc[], char palabraDes[]);
void equivocadas(int cont, char equiv[]);
void cuadro(int partida, char palabra[], char gano, float porcentaje);