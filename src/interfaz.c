#include "interfaz.h"
#include "raylib.h"

typedef enum {
    PANTALLA_MENU,
    PANTALLA_MISION
} Pantalla;

void iniciarInterfaz(void) {
    const int ancho = 900;
    const int alto = 600;
    const char *subtitulo =
    "Simulador de Insercion y Estabilidad en Orbita Terrestre Baja";


    Pantalla pantallaActual = PANTALLA_MENU;

    InitWindow(ancho, alto, "ARTEMIS - Simulador orbital");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    Rectangle botonIniciar = {330, 320, 240, 60};

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        if (pantallaActual == PANTALLA_MENU) {
            if (CheckCollisionPointRec(mouse, botonIniciar) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                pantallaActual = PANTALLA_MISION;
            }
        }

        if (pantallaActual == PANTALLA_MISION) {
            if (IsKeyPressed(KEY_ESCAPE)) {
                pantallaActual = PANTALLA_MENU;
            }
        }

        BeginDrawing();
        ClearBackground((Color){10, 16, 32, 255});

        if (pantallaActual == PANTALLA_MENU) {
            DrawText("ARTEMIS", 320, 150, 55, WHITE);

            int tamanoFuente = 18;
            int anchoTexto = MeasureText(subtitulo, tamanoFuente);

            int posicionX = (ancho - anchoTexto) / 2;

            DrawText(subtitulo, posicionX, 230, tamanoFuente, LIGHTGRAY);

            bool mouseEncima = CheckCollisionPointRec(
                mouse, botonIniciar
            );

            DrawRectangleRec(
                botonIniciar,
                mouseEncima ? SKYBLUE : BLUE
            );

            DrawText("INICIAR MISION", 352, 340, 22, WHITE);
        }

        if (pantallaActual == PANTALLA_MISION) {
            DrawText("MISION ORION", 300, 80, 40, WHITE);

            DrawText("La simulacion comenzara aqui.",
                     240, 270, 24, SKYBLUE);

            DrawText("Presiona ESC para volver al menu",
                     260, 540, 18, LIGHTGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
}