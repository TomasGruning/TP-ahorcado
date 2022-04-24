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
//genera cuadro de letras equivocadas
void interfaz_equivocadas(int cont, char equiv[]);
//imrime la interfaz del juego
void interfaz(int cont, char equiv[], int vid, char palabrasDes[], char palabraEsc[], char palabraDes[]);
//ejecuta las acciones correspondientes si la letra ingresada no esta en la palabra
void equivocada(char palabraEsc[], char palabraDesc[], char letrasIng[], char letrasEquiv[], int cont_rep, int cont_equiv, int compr_rep, char ingresada, int vid);

//imrime el atril con el munieco
void historial(int turn, float porcen[], char win[], char palabraEsc[]);
//imprime historial de partidas
void cuadro(int partida, char palabra[], char gano, float porcentaje);