//Proyecto: Torreta que destruye pac-mans

#include "raylib.h"

int main(void)
{
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Torreta");

    Texture2D torreta =LoadTexture("assets/torreta.png");

    int frameWidth = torreta.width;
    int frameHeight = torreta.height;

    //Definimos el rectángulo que se usará para dibujar
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };

    //Rectángulo de coordenadas para el rectángulo source
    Rectangle destRec = { screenWidth/2.0f, screenHeight/2.0f, frameWidth/2.0f, frameHeight/2.0f};

    Vector2 vectorTorreta = { (float)destRec.width/2, (float)destRec.height/2 };

    int rotation = 0;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if(IsKeyDown(KEY_D)) rotation++;
        if(IsKeyDown(KEY_A)) rotation--;
        //INICIO DIBUJO
        BeginDrawing();

        ClearBackground(RAYWHITE);

        //DrawCircle(posicionTorreta.x,posicionTorreta.y, 30, RED);
        DrawTexturePro(torreta, sourceRec, destRec, vectorTorreta, rotation, WHITE);

        //FIN DIBUJO
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
