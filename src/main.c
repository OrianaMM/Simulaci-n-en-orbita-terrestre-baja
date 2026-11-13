#include <stdio.h>
#include "fisica.h"
#include "simulacion.h"
#include "analisis.h"
#include "interfaz.h"
#include "validaciones.h"

void mostrarMenu(const Mision *mision) {
    limpiarPantalla();
    printf("=== ARTEMIS: Orion en orbita terrestre baja ===\n");
    printf("Altura: %.0f m | Masa: %.0f kg | Radio orbital: %.0f m\n\n",
           mision->h, mision->masaNave, mision->r);
    printf("1. Analisis (gravedad = fuerza centripeta)\n");
    printf("2. Resultados orbitales\n");
    printf("3. Pulso con propulsor lateral\n");
    printf("4. Modificar parametros\n");
    printf("5. Simulacion grafica\n");
    printf("0. Salir\n\n");
}

void mostrarResultados(const Mision *mision) {
    double v = calcularVelocidadOrbital(mision);
    double T = calcularPeriodoOrbital(mision);
    double ac = calcularAceleracionCentripeta(mision);

    printf("\nVelocidad orbital: %.2f m/s (%.3f km/s)\n", v, v / 1000.0);
    printf("Periodo orbital: %.2f s (%.2f min)\n", T, T / 60.0);
    printf("Aceleracion centripeta: %.4f m/s^2\n", ac);
    printf("\nModelo simplificado: orbita circular, Tierra esferica,\n");
    printf("sin atmosfera ni otras perturbaciones.\n");
}

void modificarParametros(Mision *mision) {
    int opcion;

    do {
        limpiarPantalla();
        printf("=== Modificar parametros ===\n");
        printf("Altura: %.0f m | Masa: %.0f kg\n\n", mision->h, mision->masaNave);
        printf("1. Cambiar altura\n");
        printf("2. Cambiar masa\n");
        printf("3. Restaurar valores originales\n");
        printf("0. Volver\n\n");

        opcion = leerOpcionMenu(0, 3);

        if (opcion == 1) {
            mision->h = leerDoubleValidado("Nueva altura [m] (160000 a 2000000): ", 160000.0, 2000000.0);
            mision->r = mision->RT + mision->h;  /* r depende de h */
            mensajeOk("Altura actualizada.");
            pausar();
        } else if (opcion == 2) {
            mision->masaNave = leerDoubleValidado("Nueva masa [kg] (1000 a 200000): ", 1000.0, 200000.0);
            mensajeOk("Masa actualizada.");
            pausar();
        } else if (opcion == 3) {
            if (confirmar("Restaurar valores originales?")) {
                inicializarMision(mision);
                mensajeOk("Valores restaurados.");
            }
            pausar();
        }
    } while (opcion != 0);
}

int main(void) {
    Mision mision;
    int opcion;

    inicializarMision(&mision);

    do {
        mostrarMenu(&mision);
        opcion = leerOpcionMenu(0, 5);

        switch (opcion) {
            case 1:
                ejecutarAnalisis(&mision);
                pausar();
                break;
            case 2:
                mostrarResultados(&mision);
                pausar();
                break;
            case 3:
                analizarPulsoLateralDinamico(&mision);
                pausar();
                break;
            case 4:
                modificarParametros(&mision);
                break;
            case 5:
                iniciarInterfaz(&mision);
                break;
            case 0:
                if (!confirmar("Seguro que desea salir?")) {
                    opcion = -1;
                }
                break;
        }
    } while (opcion != 0);

    printf("\nFin del programa.\n");
    return 0;
}
