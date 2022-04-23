#include "TP.h"

int main()
{
    srand(time(NULL));
    system(limpiar);

    char continuar = 's';
    int inicio = 1; 
    
    //valores para el regitro
    int turnos = 0, cant_ganadas = 0;
    char palabra_registro[30][40], gano[30];
    float porcentaje[30];


    while(inicio != 3 && continuar != 'n')
    {
        char palabra_escondida[30], confirmacion = 's', in;
        char letras_equivocadas[27], letras_ingresadas[27], palabras[4][40];
        int eleccion = 1, contador_equivocadas = 0, contador_repetidos = 0, compr_repetido = 0, vidas = 7;

        system(limpiar);
        printf(AMARILLO"       Ingrese una opcion\n");

        printf("----------------------------------");
        printf("\n| "BLANCO"1"AMARILLO")"BLANCO" Elegir una palabra nueva    "AMARILLO"|");
        printf("\n| "BLANCO"2"AMARILLO")"BLANCO" Ver historial de partidas   "AMARILLO"|");
        printf("\n| "BLANCO"3"AMARILLO")"BLANCO" Salir                       "AMARILLO"|");
        printf("\n----------------------------------");

        printf("\n\n==>"BLANCO" ");
        scanf("%d", &inicio);

        if(inicio == 1){
            traducir_archivo(palabras);

            //selecciona la palabra
            do
            {
                system(limpiar);
                printf(AMARILLO"            Eliga una palabra\n");
                printf(BLANCO"\n  "AMARILLO"("BLANCO"1"AMARILLO") "BLANCO"%s "AMARILLO"- ("BLANCO"2"AMARILLO") "BLANCO"%s "AMARILLO"- ("BLANCO"3"AMARILLO") "BLANCO"%s\n\n      "AMARILLO"("BLANCO"4"AMARILLO") "BLANCO"%s "AMARILLO"- ("BLANCO"5"AMARILLO") "BLANCO"%s\n"AMARILLO, palabras[0], palabras[1], palabras[2], palabras[3], palabras[4]);
                if(eleccion < 1 && eleccion > 5){
                    printf(ROJO"\n\n     ** Escribi un numero del 1 al 5 **\n"AMARILLO);
                }
                printf("\n\n==>"BLANCO" ");
                scanf("%d", &eleccion);

                getchar();
                printf(BLANCO"\n\n Estas seguro? "AMARILLO"["BLANCO"S"AMARILLO"/"BLANCO"N"AMARILLO"]:"BLANCO" ");
                scanf("%c", &confirmacion);
                
            }while(eleccion < 1 && eleccion > 5 || confirmacion != 's');
            strcpy(palabra_escondida, palabras[eleccion-1]);

            char palabra_descubierta[strlen(palabra_escondida)];
            strcpy(palabra_registro[turnos], palabra_escondida);
            crear_palabra_desc(palabra_descubierta, palabra_escondida);            

            //juego
            while(strcmp(palabra_descubierta, palabra_escondida) != 0 && vidas != 0)
            {
                equivocadas(contador_equivocadas, letras_equivocadas);
                interfaz(vidas, palabra_descubierta, palabra_escondida, palabra_descubierta);

                if(compr_repetido == 1){
                    printf(ROJO"\n\n\n ** La letra ya fue ingresada **"BLANCO);
                }

                else if(compr_repetido == 2){
                    printf(ROJO"\n\n\n ** Ingrese una letra **"BLANCO);
                }

                getchar();
                printf("\n\n\n escriba una letra: ");
                scanf("%c", &in);
                compr_repetido = 0;

                //comprueba si se ingreso una letra valida
                if(in >= 'A' && in && in <= 'Z' || in >= 'a' && in <= 'z'){
                    //comprueba si la letra ya fue ingresada
                    for(int x=0; x < contador_repetidos; x++)
                    {
                        if(letras_ingresadas[x] == in){
                            compr_repetido = 1;
                        }
                    }

                    if(compr_repetido == 0){
                        letras_ingresadas[contador_repetidos] = in;
                        contador_repetidos++;

                        if(remplazar(palabra_escondida, palabra_descubierta, in) == 0){
                            vidas--;
                            letras_equivocadas[contador_equivocadas] = in;
                            contador_equivocadas++;
                        }
                    }
                }

                else{
                    compr_repetido = 2;
                }

            }

            if(vidas == 0){
                strcpy(palabra_descubierta, palabra_escondida);
                
            }
            equivocadas(contador_equivocadas, letras_equivocadas);
            interfaz(vidas, palabra_descubierta, palabra_escondida, palabra_descubierta);

            if(vidas != 0){
                gano[turnos] = 's';
                cant_ganadas++;
                printf(AMARILLO"\n\n\n ------------------\n");
                printf(AMARILLO" |     "BLANCO"GANASTE"AMARILLO"     |");
                printf("\n ------------------\n");
            }

            else{
                gano[turnos] = 'n';
                printf(ROJO"\n\n\n ------------------\n");
                printf(ROJO" |    "BLANCO"Perdiste"ROJO"    |");
                printf("\n ------------------\n");
            }

            getchar();
            printf(BLANCO"\n\nQueres jugar de nuevo? "AMARILLO"["BLANCO"S"AMARILLO"/"BLANCO"N"AMARILLO"]:"BLANCO" ");
            scanf("%c", &continuar);

            //calcula porcentaje de ganadas
            porcentaje[turnos] = (cant_ganadas * 100) / (turnos+1);
            turnos++;

            //genera el historial
            FILE* archivo;
            if(turnos == 1){
                archivo = fopen("historial.txt", "w+");
                fprintf(archivo, "Numero de partida: %d\n", turnos);
            }
            else{
                archivo = fopen("historial.txt", "a");
                fprintf(archivo, "\nNumero de partida: %d\n", turnos);
            }    
            fprintf(archivo, "Palabra Secreta: %s\n", palabra_escondida);
            fprintf(archivo, "Partida Ganada?: %c\n",gano[turnos-1]);
            fprintf(archivo, "Estadistica hasta el momento: %%%.2f\n", porcentaje[turnos-1]);
            fclose(archivo);

        }

        else if(inicio == 2){
            if(turnos != 0){
                system(limpiar);
                for(int x=0; x < turnos; x++)
                {
                    cuadro(x+1, palabra_registro[x], gano[x], porcentaje[x]);
                    printf("\n\n");
                }

                getchar();
                printf(BLANCO"\n Volver al menu? "AMARILLO"["BLANCO"S"AMARILLO"/"BLANCO"N"AMARILLO"]:"BLANCO" ");
                scanf("%c", &continuar);
            }

            else{
                system(limpiar);
                printf("\n No se jugo ninguna partida\n\n");

                getchar();
                printf(BLANCO"\nVolver al menu? "AMARILLO"["BLANCO"S"AMARILLO"/"BLANCO"N"AMARILLO"]:"BLANCO" ");
                scanf("%c", &continuar);
            }
        }
    }

    system(limpiar);
    return 0;
}

void traducir_archivo(char pal[][40])
{
    long int lineas_restantes = 84747;
    
    FILE* archivo;
    archivo = fopen("lemario.txt", "r");
    for(int x=0; x < 5; x++)
    {
        char buffer[40];
        long int saltos_de_linea;
        if(x == 0){
            saltos_de_linea = rand()%lineas_restantes;
        }
        else{
            saltos_de_linea = rand()%(lineas_restantes-1)+1;
        }

        for(int x=0; x < saltos_de_linea; x++)
        {
            fgets(buffer, 40, archivo);
        }
        buffer[strlen(buffer)-3] = '\0';
        strcpy(pal[x], buffer);
        lineas_restantes -= saltos_de_linea;
    }
    fclose(archivo);
}

void crear_palabra_desc(char palabraDes[], char palabraEsc[])
{
    for(int x=0; x < strlen(palabraEsc); x++)
    {
        if(palabraEsc[x] == '_' || palabraEsc[x] == ' '){
            palabraDes[x] = ' ';
        }

        else{
            palabraDes[x] = '_';
        }
    }
    palabraDes[strlen(palabraEsc)] = '\0';
}

int remplazar(char palabraEsc[], char palabraDes[], char ing)
{
    int hay=0;

    for(int x=0; x < strlen(palabraEsc); x++)
    {
        if(ing == palabraEsc[x] || ing == palabraEsc[x] - 32 || ing == palabraEsc[x] + 32){
            hay = 1;
            palabraDes[x] = palabraEsc[x];
        }
    }

    return hay;
}

void interfaz(int vid, char palabrasDes[], char palabraEsc[], char palabraDes[])
{
    //imprime el monigote
    if(strcmp(palabraDes, palabraEsc) != 0){
        printf(" ------\n");
        printf(" |    |\n");
    }
    
    if(strcmp(palabraDes, palabraEsc) == 0){
        printf(BLANCO"   \\O/");
        printf("\n    |");
        printf("\n   / \\       ");
    }
    
    else{
        if(vid < 7){
            if(vid == 0){
                printf(" |    "BLANCO"X\n");
            }

            else{
                printf(" |    "BLANCO"O\n");
            }
        }
        else{
            printf(" |    "BLANCO" \n");
        }
        if(vid < 6){
            if(vid < 5){
                if(vid < 4){
                    printf(AMARILLO" |  "BLANCO"/ | \\\n");
                }

                else{
                    printf(AMARILLO" |  "BLANCO"  | \\\n");
                }
            }

            else{
                printf(AMARILLO" |  "BLANCO"  |  \n");
            }
        }
        else{
            printf(AMARILLO" |  "BLANCO"     \n");
        }

        if(vid < 3){
            if(vid < 2){
                printf(AMARILLO" |   "BLANCO"/ \\         ");
            }

            else{
                printf(AMARILLO" |   "BLANCO"  \\         ");
            }
        }

        else{
            printf(AMARILLO" |   "BLANCO"            ");
        }
    }

    for(int x=0; x < strlen(palabrasDes); x++)
    {
        printf(" %c", palabrasDes[x]);
    }
    if(strcmp(palabraDes, palabraEsc) != 0){
        printf(AMARILLO"\n |");
        printf("\n___________"BLANCO);
    }
    
}

void equivocadas(int cont, char equiv[])
{
    //imprime letras equivocadas
    system(limpiar);
    printf(AMARILLO" ---------------------------------\n    "BLANCO);
    for(int x=0; x < cont; x++)
    {
        if(x == cont - 1){
            if(equiv[x] >= 'A' && equiv[x] <= 'Z'){
                printf("%c", equiv[x]);
            }

            else{
                printf("%c", equiv[x] - 32);
            }
        }

        else{
            if(equiv[x] >= 'A' && equiv[x] <= 'Z'){
                printf("%c - ", equiv[x]);
            }

            else{
                printf("%c - ", equiv[x] - 32);
            }
        }
    }
    printf(AMARILLO"\n ---------------------------------\n\n");
}

void cuadro(int partida, char palabra[], char gano, float porcentaje)
{
    printf(AMARILLO"  Numero de partida:  "BLANCO"%d                            "AMARILLO"", partida);
    printf("\n  Palabra Secreta:  "BLANCO"%s                          "AMARILLO"\n", palabra);
    printf("  Partida Ganada?:  "BLANCO"%c                              "AMARILLO"\n", gano);
    printf("  Estadistica hasta el momento: "BLANCO"%%%.2f           "AMARILLO"", porcentaje);
}