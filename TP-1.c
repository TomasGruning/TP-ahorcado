#include "TP-1.h"

int main()
{
    srand(time(NULL));
    
    char continuar = 's';
    int inicio = 1; 
    
    //valores para el regitro
    int turnos = 0, cant_ganadas = 0;
    char palabra_registro[30][40], gano[30];
    float porcentaje[30];


    while(inicio != 3 && continuar != 'n')
    {
        char confirmacion = 'n', in;
        int eleccion = 1, contador_equivocadas = 0, contador_ingresadas = 0, comprobante_equivocada = 0, vidas = 7;

        char* palabras[CANT_PALABRAS], *palabra_escondida;
        char* letras_equivocadas, *letras_ingresadas;
        letras_equivocadas = malloc(sizeof(int)*27);
        letras_ingresadas = malloc(sizeof(int)*27);

        //elige una opcion
        while(confirmacion != 's')
        {
            confirmacion = 's';

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
                system(limpiar);
                printf("  Elija una palabra\n");
                printf(AMARILLO"------------------------------\n");
                for(int x=0; x < CANT_PALABRAS; x++)
                {
                    printf(" "AMARILLO"("BLANCO"%d"AMARILLO") "BLANCO"%s\n", x+1, palabras[x]);
                }
                printf(AMARILLO"\n\n==>"BLANCO" ");
                scanf("%d", &eleccion);

                if(eleccion >= 1 && eleccion <= CANT_PALABRAS){
                    getchar();
                    printf(BLANCO"\n\n Estas seguro? "AMARILLO"["BLANCO"S"AMARILLO"/"BLANCO"N"AMARILLO"]:"BLANCO" ");
                    scanf("%c", &confirmacion);
                }
            }
        }

        if(inicio == 1){
            palabra_escondida = malloc(sizeof(char)*strlen(palabras[eleccion-1]+1));
            strcpy(palabra_escondida, palabras[eleccion-1]);
            for(int x=0; x < CANT_PALABRAS; free(palabras[x++]));
            FREE;

            //prepara la palabra para el juego
            char* palabra_descubierta;
            palabra_descubierta = malloc(sizeof(char)*strlen(palabra_escondida+1));
            strcpy(palabra_registro[turnos], palabra_escondida);
            crear_palabra_desc(palabra_descubierta, palabra_escondida);            

            //juego
            while(strcmp(palabra_descubierta, palabra_escondida) != 0 && vidas != 0)
            {
                interfaz(contador_equivocadas, letras_equivocadas, vidas, palabra_descubierta);

                if(comprobante_equivocada == 1){
                    printf(ROJO"\n\n\n ** La letra ya fue ingresada **"BLANCO);
                }

                else if(comprobante_equivocada == 2){
                    printf(ROJO"\n\n\n ** Ingrese una letra **"BLANCO);
                }

                getchar();
                printf("\n\n\n escriba una letra: ");
                scanf("%c", &in);
                comprobante_equivocada = 0;

                //comprueba si se ingreso una letra valida
                if((in >= 'A' &&  in <= 'Z') || (in >= 'a' && in <= 'z')){

                    if(repetida(letras_ingresadas, in, contador_ingresadas) == 0){
                        letras_ingresadas[contador_ingresadas] = in;
                        contador_ingresadas++;

                        if(remplazar(palabra_escondida, palabra_descubierta, in) == 0){
                            vidas--;
                            letras_equivocadas[contador_equivocadas] = in;
                            contador_equivocadas++;
                        }
                    }

                    else{
                        comprobante_equivocada = 1;
                    }
                }

                else{
                    comprobante_equivocada = 2;
                }

            }

            if(vidas == 0){
                strcpy(palabra_descubierta, palabra_escondida);  
            }
            free(palabra_escondida);
            interfaz(contador_equivocadas, letras_equivocadas, vidas, palabra_descubierta);
            free(palabra_descubierta);
            free(letras_equivocadas);
            free(letras_ingresadas);
            
            //resultado
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
            printf(BLANCO"\n\nVolver al menu? "AMARILLO"["BLANCO"S"AMARILLO"/"BLANCO"N"AMARILLO"]:"BLANCO" ");
            scanf("%c", &continuar);

            //calcula porcentaje de ganadas
            porcentaje[turnos] = (cant_ganadas * 100) / (turnos+1);
            turnos++;
        }

        else if(inicio == 2){
            if(turnos != 0){
                system(limpiar);
                for(int x=0; x < turnos; x++)
                {
                    if(x == 0){
                        printf("\n");
                    }
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

    historial(turnos, porcentaje, gano, palabra_registro);
    system(limpiar);
    return 0;
}

void traducir_archivo(char* pal[])
{
    long int lineas_restantes = 84746;
    
    FILE* archivo;
    archivo = fopen("lemario.txt", "r");
    for(int x=0; x < CANT_PALABRAS; x++)
    {
        char buffer[40];
        long int saltos_de_linea;
        if(x == 0){
            saltos_de_linea = rand()%lineas_restantes;
        }
        else{
            int reducido = lineas_restantes / (CANT_PALABRAS * 0.30);
            saltos_de_linea = rand()%reducido+1;
        }

        for(int y=0; y < saltos_de_linea; y++)
        {
            fgets(buffer, 40, archivo);
        }
        buffer[strlen(buffer)-LIMTE] = '\0';
        pal[x] = malloc(sizeof(char)*(strlen(buffer)+1));
        strcpy(pal[x], buffer); 
        lineas_restantes -= saltos_de_linea;
    }
    fclose(archivo);
}

void crear_palabra_desc(char* palabraDes, char* palabraEsc)
{
    int largo = strlen(palabraEsc);
    for(int x=0; x < largo; x++)
    {
        if(palabraEsc[x] == '_' || palabraEsc[x] == ' '){
            palabraDes[x] = ' ';
        }

        else{
            palabraDes[x] = '_';
        }
    }
    palabraDes[largo] = '\0';
}


int remplazar(char* palabraEsc, char* palabraDes, char ing)
{
    int hay=0, largo = strlen(palabraEsc);

    for(int x=0; x < largo; x++)
    {
        if(ing == palabraEsc[x] || ing == palabraEsc[x] - 32 || ing == palabraEsc[x] + 32){
            hay = 1;
            palabraDes[x] = palabraEsc[x];
        }
    }

    return hay;
}

void interfaz_equivocadas(int cont, char* equiv)
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

void interfaz(int cont, char* equiv, int vid, char* palabraDes)
{
    int largo = strlen(palabraDes);
    interfaz_equivocadas(cont, equiv);
    
    //imprime el monigote
    printf(" ------\n");
    printf(" |    |\n");
    
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
                printf(AMARILLO" |  "BLANCO" /|\\\n");
            }

            else{
                printf(AMARILLO" |  "BLANCO"  |\\\n");
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

    for(int x=0; x < largo; x++)
    {
        printf(" %c", palabraDes[x]);
    }
    
    printf(AMARILLO"\n |");
    printf("\n___________"BLANCO);
    
}

int repetida(char* letrasIng, char ingresada, int cont_in)
{
    int compr = 0;
    
    for(int x=0; x < cont_in; x++)
    {
        if(letrasIng[x] == ingresada){
            compr = 1;
        }
    }

    return compr;
}


void historial(int turn, float porcen[], char win[], char palabraReg[][40])
{
    FILE* archivo;
    archivo = fopen("historial.txt", "w+");
    fprintf(archivo, "Numero de partida: 1\n");
    fprintf(archivo, "Palabra Secreta: %s\n", palabraReg[0]);
    fprintf(archivo, "Partida Ganada?: %c\n",win[0]);
    fprintf(archivo, "Estadistica hasta el momento: %%%.2f\n", porcen[0]);
    
    if(turn > 1){
        printf("\n %d\n", turn);
        for(int x=1; x < turn; x++)
        {
            fprintf(archivo, "\nNumero de partida: %d\n", x+1);
            fprintf(archivo, "Palabra Secreta: %s\n", palabraReg[x]);
            fprintf(archivo, "Partida Ganada?: %c\n",win[x]);
            fprintf(archivo, "Estadistica hasta el momento: %%%.2f\n", porcen[x]);   
        }
        fclose(archivo);
    }

    else{
        fclose(archivo);
    }
}

void cuadro(int partida, char palabra[], char win, float porcen)
{
    printf(AMARILLO"  Numero de partida:  "BLANCO"%d"AMARILLO"", partida);
    printf("\n  Palabra Secreta:  "BLANCO"%s"AMARILLO"\n", palabra);
    printf("  Partida Ganada?:  "BLANCO"%c"AMARILLO"\n", win);
    printf("  Estadistica hasta el momento: "BLANCO"%%%.2f"AMARILLO"", porcen);
}