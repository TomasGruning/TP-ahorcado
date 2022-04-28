#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #define limpiar   "cls"
    #define LIMTE      1
#else
    #define limpiar   "clear"
    #define LIMTE      2
#endif

#define CANT_PALABRAS      5
#define BLANCO        "\x1b[0m"
#define ROJO          "\x1b[31m"
#define AZUL          "\x1b[34m"
#define AMARILLO      "\x1b[33m"
#define VERDE         "\x1b[32m"

//lee el lemario y genera las palabra aleatorias
void traducir_archivo(char pal[][40]);

//remplaza la palabra elegida por espacios
void crear_palabra_desc(char palabraDes[], char palabraEsc[]);


//remplaza la letra ingresada en los espacios
int remplazar(char palabraEsc[], char palabraDes[], char ing);

//genera el cuadro de letras equivocadas
void interfaz_equivocadas(int cont, char equiv[]);

//imprime la interfaz del juego
void interfaz(int cont, char equiv[], int vid, char palabrasDes[], char palabraEsc[], char palabraDes[]);

//comrueba si la letra ya fue ingresada
int repetida(char letrasIng[], char ingresada, int cont_in);


//modifica el archivo con el historial de partidas
void historial(int turn, float porcen[], char win[], char palabraEsc[]);

//imprime el historial de partidas
void cuadro(int partida, char palabra[], char gano, float porcentaje);