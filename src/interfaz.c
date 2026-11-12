#include "interfaz.h"

#include <stdbool.h>

#if defined(__has_include)
    #if __has_include("raylib.h")
        #include "raylib.h"
    #else
        #define RAYLIB_STUB
    #endif
#else
    #include "raylib.h"
#endif

#ifdef RAYLIB_STUB
typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

typedef struct Rectangle {
    float x;
    float y;
    float width;
    float height;
} Rectangle;

#define WHITE ((Color){255, 255, 255, 255})
#define LIGHTGRAY ((Color){200, 200, 200, 255})
#define SKYBLUE ((Color){135, 206, 235, 255})
#define BLUE ((Color){0, 0, 255, 255})
#define KEY_NULL 0
#define KEY_ESCAPE 256
#define MOUSE_BUTTON_LEFT 0

static inline bool CheckCollisionPointRec(Vector2 point, Rectangle rec) {
    return point.x >= rec.x && point.x <= rec.x + rec.width &&
           point.y >= rec.y && point.y <= rec.y + rec.height;
}

static inline void InitWindow(int width, int height, const char *title) {
    (void)width;
    (void)height;
    (void)title;
}

static inline void SetExitKey(int key) {
    (void)key;
}

static inline void SetTargetFPS(int fps) {
    (void)fps;
}

static inline bool WindowShouldClose(void) {
    return false;
}

static inline void CloseWindow(void) {
}

static inline void BeginDrawing(void) {
}

static inline void ClearBackground(Color color) {
    (void)color;
}

static inline void DrawText(const char *text, int posX, int posY, int fontSize, Color color) {
    (void)text;
    (void)posX;
    (void)posY;
    (void)fontSize;
    (void)color;
}

static inline int MeasureText(const char *text, int fontSize) {
    (void)text;
    (void)fontSize;
    return 0;
}

static inline void DrawRectangleRec(Rectangle rec, Color color) {
    (void)rec;
    (void)color;
}

static inline bool IsMouseButtonPressed(int button) {
    (void)button;
    return false;
}

static inline bool IsKeyPressed(int key) {
    (void)key;
    return false;
}

static inline Vector2 GetMousePosition(void) {
    return (Vector2){0.0f, 0.0f};
}
#endif

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