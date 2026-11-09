
#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Torreta");

    Vector2 posicionPelota = {(float) screenWidth/2, (float) screenWidth/2};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if(IsKeyDown(KEY_D)) posicionPelota.x += 0.2f;
        if(IsKeyDown(KEY_S)) posicionPelota.y += 0.2f;
        if(IsKeyDown(KEY_W)) posicionPelota.y -= 0.2f;
        if(IsKeyDown(KEY_A)) posicionPelota.x -= 0.2f;
        //INICIO DIBUJO
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircle(posicionPelota.x,posicionPelota.y, 30, RED);

        //FIN DIBUJO
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
