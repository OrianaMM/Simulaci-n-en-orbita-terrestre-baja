#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#endif

#define CONSOLE_WIDTH 90
#define CONSOLE_HEIGHT 26

typedef struct {
    float x, y;
    float vx, vy;
    float angulo; // Ángulo de trayectoria para la orientación del cohete
    int etapa;    // 1: Ignición y Ascenso Vertical, 2: Giro de Pitch/Gravedad, 3: Inserción Orbital
    char simbolo;
} NaveArtemis;

void inicializar_sistema(NaveArtemis *nave) {
    nave->x = 10.0f;
    nave->y = 22.0f; // Comienza en la plataforma de lanzamiento
    nave->vx = 0.0f;
    nave->vy = 0.0f;
    nave->angulo = 90.0f; // Apuntando hacia arriba
    nave->etapa = 1;
    nave->simbolo = 'A';
}

void actualizar_fisica_animada(NaveArtemis *nave, float dt) {
    // Fases didácticas del vuelo de Artemis
    if (nave->etapa == 1) {
        // Fase 1: Ascenso vertical puro (Despegue)
        nave->vy = -0.8f;
        nave->vx = 0.1f;
        if (nave->y < 15.0f) {
            nave->etapa = 2; // Iniciar maniobra de giro (Gravity Turn)
        }
    } 
    else if (nave->etapa == 2) {
        // Fase 2: Inclinación hacia la horizontal para buscar órbita
        nave->vx = 1.2f;
        nave->vy = -0.4f;
        if (nave->x > 45.0f) {
            nave->etapa = 3; // Captura orbital lunar
        }
    } 
    else if (nave->etapa == 3) {
        // Fase 3: Movimiento circular/orbital alrededor del centro de la pantalla (la Luna)
        static float angulo_orbital = 0.0f;
        float centro_x = 55.0f;
        float centro_y = 10.0f;
        float radio = 18.0f;

        angulo_orbital += 0.08f; // Velocidad angular de la órbita
        nave->x = centro_x + cosf(angulo_orbital) * radio;
        nave->y = centro_y + sinf(angulo_orbital) * (radio * 0.5f); // Perspectiva elíptica
    }

    // Actualización de posición si no está en órbita circular estricta controlada
    if (nave->etapa != 3) {
        nave->x += nave->vx * dt;
        nave->y += nave->vy * dt;
    }

    // Restricciones de límites de pantalla
    if (nave->x < 2) nave->x = 2;
    if (nave->x >= CONSOLE_WIDTH - 2) nave->x = CONSOLE_WIDTH - 2;
    if (nave->y < 2) nave->y = 2;
    if (nave->y >= CONSOLE_HEIGHT - 2) nave->y = CONSOLE_HEIGHT - 2;
}

void renderizar_animacion(const NaveArtemis *nave) {
    // Limpiar pantalla sin parpadeo usando ANSI
    printf("\033[H");

    char pantalla[CONSOLE_HEIGHT][CONSOLE_WIDTH + 1];

    // 1. Dibujar el fondo del espacio / atmósfera
    for (int i = 0; i < CONSOLE_HEIGHT; i++) {
        for (int j = 0; j < CONSOLE_WIDTH; j++) {
            if (i == CONSOLE_HEIGHT - 1) {
                pantalla[i][j] = '='; // Superficie terrestre / plataforma
            } else if (j == 0 || j == CONSOLE_WIDTH - 1) {
                pantalla[i][j] = '|';
            } else {
                pantalla[i][j] = ' ';
            }
        }
        pantalla[i][CONSOLE_WIDTH] = '\0';
    }

    // 2. Dibujar la Luna a la derecha como objetivo didáctico
    int luna_cx = 55;
    int luna_cy = 10;
    int radio_luna = 6;
    for (int i = 0; i < CONSOLE_HEIGHT - 1; i++) {
        for (int j = 0; j < CONSOLE_WIDTH; j++) {
            float dist = sqrtf(powf(j - luna_cx, 2) + powf((i - luna_cy) * 2, 2)); // Ajuste de proporción de caracteres
            if (dist < radio_luna) {
                pantalla[i][j] = 'O'; // Cuerpo de la Luna
            }
        }
    }

    // 3. Dibujar la estela de fuego y propulsión detrás del cohete (si está activo)
    int nx = (int)nave->x;
    int ny = (int)nave->y;
    
    if (nave->etapa == 1 && ny + 1 < CONSOLE_HEIGHT - 1) {
        pantalla[ny + 1][nx] = 'v'; // Fuego de los propulsores principales
    } else if (nave->etapa == 2 && nx - 1 > 0) {
        pantalla[ny][nx - 1] = '~'; // Estela de gas horizontal
    }

    // 4. Dibujar la nave en su posición actual
    if (nx > 0 && nx < CONSOLE_WIDTH - 1 && ny >= 0 && ny < CONSOLE_HEIGHT - 1) {
        pantalla[ny][nx] = nave->simbolo;
    }

    // Imprimir el canvas completo por consola
    for (int i = 0; i < CONSOLE_HEIGHT; i++) {
        printf("%s\n", pantalla[i]);
    }

    // 5. Panel didáctico explicativo en tiempo real
    printf("=========================================================================================\n");
    if (nave->etapa == 1) {
        printf("[FASE 1] DESPEGUE VERTICAL: El SLS empuja con maximo impulso superando la gravedad.  |\n");
    } else if (nave->etapa == 2) {
        printf("[FASE 2] GIRO GRAVITACIONAL (PITCH): Inclinacion de trayectoria para ganar velocidad. |\n");
    } else if (nave->etapa == 3) {
        printf("[FASE 3] INSERCION ORBITAL: La nave equilibra velocidad y gravedad alrededor de la Luna.|\n");
    }
    printf("=========================================================================================\n");
}

int main(void) {
    
    printf("🚀 ¡Bienvenido al Simulador de Misión Artemis! 🚀\n");
    printf("En este simulador podrás probar el funcionamiento de la insercción de una nave en la órbita baja terrestre\n");
    printf("A continuación, en el menú, seleccioná que querés simular\n");
    NaveArtemis msn;
    inicializar_sistema(&msn);

    // Ocultar cursor de consola (ANSI) y limpiar pantalla inicial
    printf("\033[?25l");
    printf("\033[2J");

    int ciclos = 0;
    while (ciclos < 180) { // Duración total de la animación didáctica
        actualizar_fisica_animada(&msn, 0.5f);
        renderizar_animacion(&msn);
        SLEEP(90); // Control de velocidad de los fotogramas (FPS de consola)
        ciclos++;
    }

    // Restaurar cursor al salir
    printf("\033[?25h\n");
    printf("¡Simulacion orbital completada con exito!\n");
    return 0;
}
