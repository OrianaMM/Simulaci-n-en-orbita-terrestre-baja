#include "interfaz.h"
#include "raylib.h"

void iniciarInterfaz(void) {
    InitWindow(900, 600, "ARTEMIS - Simulador orbital");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("PROYECTO ARTEMIS", 270, 220, 35, WHITE);
        DrawText("Simulador orbital - Orion", 290, 280, 20, SKYBLUE);

        EndDrawing();
    }

    CloseWindow();
}