
#include "interfaz.h"
#include "fisica.h"
#include "raylib.h"

#include <math.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    PANTALLA_MENU,
    PANTALLA_MISION
} Pantalla;

/* FUNCIONES AUXILIARES DE DIBUJO*/


static Vector2 sumar(Vector2 a, Vector2 b) {
    return (Vector2){a.x + b.x, a.y + b.y};
}

static Vector2 escalar(Vector2 v, float escala) {
    return (Vector2){v.x * escala, v.y * escala};
}

// Dibuja triangulos sin depender del orden de los vertices.
static void triangulo(Vector2 a, Vector2 b, Vector2 c, Color color) {
    DrawTriangle(a, b, c, color);
    DrawTriangle(a, c, b, color);
}

static void dibujarEstrellas(void) {
    // Posiciones fijas para evitar parpadeos.
    for (int i = 0; i < 115; i++) {
        int x = (i * 173 + 47) % 900;
        int y = (i * 97 + 31) % 600;

        // Evitar estrellas demasiado visibles sobre el panel.
        if (x > 580 && y > 80 && y < 545) {
            continue;
        }

        float radio = (i % 9 == 0) ? 1.7f : 0.8f;
        unsigned char brillo = (unsigned char)(90 + (i * 37) % 150);

        DrawCircle(x, y, radio, (Color){210, 225, 255, brillo});
    }
}

static void dibujarContinente(const Vector2 *puntos, int cantidad,
                              Color color) {
    // Triangulacion en abanico para formas convexas.
    for (int i = 1; i < cantidad - 1; i++) {
        triangulo(puntos[0], puntos[i], puntos[i + 1], color);
    }
}

static void dibujarTierra(Vector2 centro) {
    const float radio = 125.0f;

    // Resplandor atmosferico.
    for (int i = 12; i >= 1; i--) {
        DrawCircleV(
            centro,
            radio + i * 1.7f,
            (Color){30, 120, 225, 5}
        );
    }

    DrawCircleV(centro, radio + 4, (Color){45, 130, 220, 130});

    // Oceano.
    DrawCircleV(centro, radio, (Color){15, 85, 170, 255});
    DrawCircleV(centro, radio - 5, (Color){17, 105, 195, 255});

    // Continente occidental.
    Vector2 americaNorte[] = {
        {centro.x - 104, centro.y - 67},
        {centro.x - 78, centro.y - 99},
        {centro.x - 43, centro.y - 111},
        {centro.x - 18, centro.y - 88},
        {centro.x - 33, centro.y - 65},
        {centro.x - 22, centro.y - 42},
        {centro.x - 52, centro.y - 23},
        {centro.x - 69, centro.y - 43},
        {centro.x - 91, centro.y - 38}
    };

    dibujarContinente(
        americaNorte, 9, (Color){65, 150, 88, 255}
    );

    // America del Sur.
    Vector2 americaSur[] = {
        {centro.x - 49, centro.y - 14},
        {centro.x - 17, centro.y - 23},
        {centro.x + 4, centro.y + 5},
        {centro.x - 8, centro.y + 34},
        {centro.x - 24, centro.y + 70},
        {centro.x - 37, centro.y + 96},
        {centro.x - 51, centro.y + 59},
        {centro.x - 61, centro.y + 18}
    };

    dibujarContinente(
        americaSur, 8, (Color){51, 151, 89, 255}
    );

    // Europa y Asia (forma estilizada).
    Vector2 eurasia[] = {
        {centro.x + 14, centro.y - 89},
        {centro.x + 44, centro.y - 109},
        {centro.x + 85, centro.y - 86},
        {centro.x + 110, centro.y - 49},
        {centro.x + 97, centro.y - 22},
        {centro.x + 69, centro.y - 35},
        {centro.x + 54, centro.y - 10},
        {centro.x + 27, centro.y - 32},
        {centro.x + 8, centro.y - 51}
    };

    dibujarContinente(
        eurasia, 9, (Color){91, 161, 83, 255}
    );

    // Africa.
    Vector2 africa[] = {
        {centro.x + 18, centro.y - 19},
        {centro.x + 57, centro.y - 16},
        {centro.x + 71, centro.y + 13},
        {centro.x + 48, centro.y + 61},
        {centro.x + 30, centro.y + 80},
        {centro.x + 13, centro.y + 37},
        {centro.x + 6, centro.y + 3}
    };

    dibujarContinente(
        africa, 7, (Color){181, 163, 91, 255}
    );

    // Regiones de vegetacion.
    DrawEllipse(
        (int)centro.x - 42, (int)centro.y + 19,
        12, 21, (Color){39, 127, 74, 180}
    );

    DrawEllipse(
        (int)centro.x + 49, (int)centro.y - 57,
        22, 9, (Color){69, 136, 71, 170}
    );

    // Nubes semitransparentes.
    DrawEllipse(
        (int)centro.x - 52, (int)centro.y - 75,
        35, 7, (Color){235, 245, 255, 85}
    );

    DrawEllipse(
        (int)centro.x + 49, (int)centro.y + 45,
        33, 6, (Color){235, 245, 255, 90}
    );

    DrawEllipse(
        (int)centro.x - 48, (int)centro.y + 70,
        24, 5, (Color){235, 245, 255, 65}
    );

    // Sombra suave en el borde derecho.
    for (int i = 0; i < 15; i++) {
        float r = radio - i * 2.5f;
        DrawCircleSector(
            centro, r, -78, 78, 48,
            (Color){3, 12, 40, 5}
        );
    }

    // Casquetes polares.
    DrawEllipse(
        (int)centro.x, (int)(centro.y - 116),
        32, 8, (Color){218, 240, 250, 220}
    );

    DrawEllipse(
        (int)centro.x, (int)(centro.y + 116),
        27, 7, (Color){218, 240, 250, 200}
    );

    DrawCircleLines(
        (int)centro.x, (int)centro.y,
        radio + 1, (Color){110, 195, 255, 160}
    );
}

static void dibujarOrion(Vector2 posicion, float direccion,
                         float tiempoReal) {
    Vector2 adelante = {
        cosf(direccion),
        sinf(direccion)
    };

    Vector2 lateral = {
        -adelante.y,
        adelante.x
    };

    // Estructura de la nave.
    Vector2 punta = sumar(posicion, escalar(adelante, 18));
    Vector2 base = sumar(posicion, escalar(adelante, -12));

    Vector2 alaIzq = sumar(
        sumar(posicion, escalar(adelante, -9)),
        escalar(lateral, 12)
    );

    Vector2 alaDer = sumar(
        sumar(posicion, escalar(adelante, -9)),
        escalar(lateral, -12)
    );

    // Propulsion animada, solamente visual.
    float oscilacion = 4.0f + 3.0f * sinf(tiempoReal * 18.0f);

    Vector2 extremoLlama = sumar(
        base, escalar(adelante, -(15 + oscilacion))
    );

    Vector2 llamaIzq = sumar(base, escalar(lateral, 5));
    Vector2 llamaDer = sumar(base, escalar(lateral, -5));

    triangulo(
        llamaIzq, llamaDer, extremoLlama,
        (Color){255, 104, 36, 220}
    );

    Vector2 llamaInterna = sumar(
        base, escalar(adelante, -(8 + oscilacion * 0.5f))
    );

    triangulo(
        sumar(base, escalar(lateral, 2.5f)),
        sumar(base, escalar(lateral, -2.5f)),
        llamaInterna,
        (Color){255, 225, 115, 255}
    );

    // Alas.
    triangulo(
        posicion, alaIzq, base,
        (Color){95, 145, 185, 255}
    );

    triangulo(
        posicion, base, alaDer,
        (Color){65, 115, 160, 255}
    );

    // Fuselaje principal.
    Vector2 hombroIzq = sumar(
        posicion, escalar(lateral, 5)
    );

    Vector2 hombroDer = sumar(
        posicion, escalar(lateral, -5)
    );

    triangulo(
        punta, hombroIzq, hombroDer,
        (Color){226, 235, 244, 255}
    );

    triangulo(
        hombroIzq, hombroDer, base,
        (Color){160, 187, 215, 255}
    );

    // Cabina.
    DrawCircleV(
        sumar(posicion, escalar(adelante, 5)),
        3.2f, (Color){50, 205, 255, 255}
    );

    // Etiqueta.
    DrawText(
        "ORION",
        (int)posicion.x + 18,
        (int)posicion.y - 23,
        15,
        RAYWHITE
    );
}

static void dibujarPanel(const Mision *mision,
                         double velocidad,
                         double periodo,
                         double aceleracion,
                         double tiempoSimulacion) {
    Rectangle panel = {588, 90, 292, 455};

    DrawRectangleRounded(
        panel, 0.05f, 8,
        (Color){24, 35, 56, 255}
    );

    DrawRectangleLinesEx(
        panel, 1,
        (Color){62, 91, 130, 255}
    );

    DrawText(
        "TELEMETRIA ORBITAL",
        605, 112, 21,
        (Color){105, 199, 255, 255}
    );

    DrawLine(
        606, 146, 860, 146,
        (Color){65, 92, 125, 255}
    );

    DrawText("ALTITUD", 608, 169, 15, LIGHTGRAY);
    DrawText(
        TextFormat("%.2f km", mision->h / 1000.0),
        608, 192, 25, WHITE
    );

    DrawText("VELOCIDAD ORBITAL", 608, 246, 15, LIGHTGRAY);
    DrawText(
        TextFormat("%.2f km/s", velocidad / 1000.0),
        608, 269, 25, WHITE
    );

    DrawText("PERIODO ORBITAL", 608, 323, 15, LIGHTGRAY);
    DrawText(
        TextFormat("%.2f min", periodo / 60.0),
        608, 346, 25, WHITE
    );

    DrawText("ACELERACION CENTRIPETA", 608, 400, 14, LIGHTGRAY);
    DrawText(
        TextFormat("%.2f m/s2", aceleracion),
        608, 423, 24, WHITE
    );

    DrawLine(
        606, 468, 860, 468,
        (Color){65, 92, 125, 255}
    );

    DrawCircle(
        615, 497, 5,
        (Color){75, 220, 145, 255}
    );

    DrawText(
        "ORBITA CIRCULAR",
        628, 487, 16,
        (Color){145, 230, 185, 255}
    );

    DrawText(
        TextFormat("Tiempo: %.0f s", tiempoSimulacion),
        608, 518, 13, LIGHTGRAY
    );
}

// ----------------------------------------------------
// INTERFAZ PRINCIPAL
// ----------------------------------------------------

void iniciarInterfaz(const Mision *mision) {
    if (mision == NULL) {
        return;
    }

    double velocidad = calcularVelocidadOrbital(mision);
    double periodo = calcularPeriodoOrbital(mision);
    double aceleracion = calcularAceleracionCentripeta(mision);

    if (periodo <= 0.0 || !isfinite(periodo)) {
        return;
    }

    const int ancho = 900;
    const int alto = 600;

    const char *subtitulo =
        "Simulador de Insercion y Estabilidad en Orbita Terrestre Baja";

    Pantalla pantallaActual = PANTALLA_MENU;

    InitWindow(ancho, alto, "ARTEMIS - Simulador orbital");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    Rectangle botonIniciar = {330, 320, 240, 60};

    double tiempoSimulacion = 0.0;
    const double escalaTiempo = 60.0;

    Vector2 centroTierra = {298.0f, 320.0f};
    const float radioOrbita = 185.0f;

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        if (pantallaActual == PANTALLA_MENU) {
            if (
                CheckCollisionPointRec(mouse, botonIniciar) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
            ) {
                tiempoSimulacion = 0.0;
                pantallaActual = PANTALLA_MISION;
            }
        } else {
            tiempoSimulacion += GetFrameTime() * escalaTiempo;

            if (IsKeyPressed(KEY_ESCAPE)) {
                pantallaActual = PANTALLA_MENU;
            }
        }

        BeginDrawing();
        ClearBackground((Color){8, 14, 29, 255});

        dibujarEstrellas();

        if (pantallaActual == PANTALLA_MENU) {
            DrawText("ARTEMIS", 320, 150, 55, WHITE);

            int tamanoFuente = 18;
            int anchoTexto = MeasureText(subtitulo, tamanoFuente);

            DrawText(
                subtitulo,
                (ancho - anchoTexto) / 2,
                230,
                tamanoFuente,
                LIGHTGRAY
            );

            bool mouseEncima = CheckCollisionPointRec(
                mouse, botonIniciar
            );

            DrawRectangleRounded(
                botonIniciar, 0.18f, 8,
                mouseEncima
                    ? (Color){46, 160, 225, 255}
                    : (Color){25, 95, 180, 255}
            );

            DrawText("INICIAR MISION", 352, 340, 22, WHITE);
        }

        if (pantallaActual == PANTALLA_MISION) {
            DrawText(
                "MISION ORION",
                30, 25, 30, WHITE
            );

            DrawText(
                "SIMULACION DE ORBITA CIRCULAR",
                30, 64, 15,
                (Color){120, 175, 215, 255}
            );

            // Orbita de referencia.
            DrawCircleLines(
                (int)centroTierra.x,
                (int)centroTierra.y,
                radioOrbita,
                (Color){100, 185, 245, 220}
            );

            dibujarTierra(centroTierra);

            // Posicion orbital a partir del periodo fisico.
            double angulo =
                2.0 * PI * tiempoSimulacion / periodo;

            Vector2 posicionNave = {
                centroTierra.x +
                    radioOrbita * (float)cos(angulo),

                centroTierra.y -
                    radioOrbita * (float)sin(angulo)
            };

            // Direccion tangencial.
            float direccion = (float)(-angulo - PI / 2.0);

            dibujarOrion(
                posicionNave,
                direccion,
                (float)GetTime()
            );

            dibujarPanel(
                mision,
                velocidad,
                periodo,
                aceleracion,
                tiempoSimulacion
            );

            DrawText(
                "ESC - Volver al menu",
                30, 568, 17, LIGHTGRAY
            );
        }

        EndDrawing();
    }

    CloseWindow();
}
