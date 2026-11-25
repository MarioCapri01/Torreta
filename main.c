//Proyecto: Torreta que destruye pac-mans
// PUNTEROS:
/*
    Concepto: Variables que apuntan a direcciones de memoria.
    * -> accede al valor de la variable que estamos apuntando
    & -> obtiene la dirección de memoria de la variable a la que se está apuntando.
        ejemplo:
            int valor = 10;
            int *puntero = &valor;
    malloc -> memory allocator. Reserva espacio en memoria.  -> #include <stdlib.h>
        ejemplo:
            char l = malloc(1);             // -> reserva espacio en memoria para un byte
        o...
            char l = malloc(sizeof(char));  // -> reserva espacio en memoria para un byte
        Importante: controlar errores si usamos malloc
            if(l == NULL) {                 // -> si 'l' se ha salido del espacio asignado
                fprintf(stderr, "Mensaje de error");
                return 1;
            }
            nuestraFuncion(l);
            ...
            nuestraFuncion(char *letter){
                *letter = 'b';              // -> Con esto estamos trabajando con la propia variable que pasamos como argumento, no una copia de la misma
            }
    free -> libera espacio de malloc
        ejemplo:
            free(l);                        // -> no hace falta el asterisco en la variable


*/
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BALAS 500000

typedef struct Bala {
    bool habilitada;
    Vector2 position;       // Bullet position on screen
    Vector2 acceleration;   // Amount of pixels to be incremented to position every frame
} Bala;

int main(void)
{
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Torreta");

    // INICIO TORRETA
    Texture2D torreta =LoadTexture("assets/torreta.png");

    int frameWidth = torreta.width;
    int frameHeight = torreta.height;

    //Rectángulo de coordenadas para el rectángulo source
    Rectangle destRecTorreta = { screenWidth/2.0f, screenHeight/2.0f, frameWidth/2.0f, frameHeight/2.0f};

    Vector2 vectorCentro = { (float)destRecTorreta.width/2, (float)destRecTorreta.height/2 };

    //Definimos el rectángulo que se usará para dibujar
    Rectangle sourceRecTorreta = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };


    int rotacion = 0;

    //FIN TORRETA

    //INICIO BALA
    Texture2D texturaBala = LoadTexture("assets/bala.png");

    Bala *balas = (Bala *)RL_CALLOC(MAX_BALAS, sizeof(Bala));

    int frameBalaWidth = texturaBala.width;
    int frameBalaHeight = texturaBala.height;
    float escalaBala = 0.3f;
    //Vector posicion Bala
    /*
    Rectangle destRecBala = { screenWidth/2.0f, screenHeight/2.0f, frameBalaWidth/2.0f, frameBalaHeight/2.0f};
    Vector2 posicionBala = { (float)destRecBala.width/2, (float)destRecBala.height/2 };
    */
    int contadorBalas = 0;
    float velocidadBala = 9.0f;
    int rotacionTorreta = rotacion - 90;
    printf("rotacion Torreta: %d\n", rotacionTorreta);
    //FIN BALA

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if(IsKeyDown(KEY_D)) {
                rotacion++;
                rotacionTorreta++;
        }
        if(IsKeyDown(KEY_A)) {
                rotacion--;
                rotacionTorreta--;
        }

        // Añadimos una nueva bala si se pulsa la tecla
        if(IsKeyPressed(KEY_SPACE))
        {
                balas[contadorBalas].habilitada = true;
                balas[contadorBalas].position = (Vector2){(float) ((screenWidth - (frameBalaWidth * escalaBala))/2), (float) ((screenHeight - (frameBalaHeight * escalaBala))/2)};
                balas[contadorBalas].acceleration = (Vector2){
                        velocidadBala*cosf(rotacionTorreta*DEG2RAD),
                        velocidadBala*sinf(rotacionTorreta*DEG2RAD)
                    };
                contadorBalas++;
                printf("screenWidth: %d\n", screenWidth);
                printf("rotación: %d\n", rotacion);
                printf("vector: %d\n", rotacion);
        }

        // Actualizamos posición de cada bala
        for (int i = 0; i < contadorBalas; i++){
            if(balas[i].habilitada){
                balas[i].position.x += balas[i].acceleration.x;
                balas[i].position.y += balas[i].acceleration.y;

                // Comprobamos si debemo eliminar la bala
                if(balas[i].position.x > screenWidth || balas[i].position.y > screenHeight) balas[i].habilitada = false;
            }
        }

        //INICIO DIBUJO
        BeginDrawing();

            ClearBackground(RAYWHITE);

            //Dibuja una textura a partir de un rectángulo de rectángulo de destino, rectángulo fuente, con rotación y escalado
            DrawTexturePro(torreta, sourceRecTorreta, destRecTorreta, vectorCentro, rotacion, WHITE);

            // Dibuja las balas
            for (int i = 0; i < contadorBalas; i++){
                DrawTextureEx(texturaBala, balas[i].position, 0.0f, escalaBala, WHITE);

            }

        //FIN DIBUJO
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
