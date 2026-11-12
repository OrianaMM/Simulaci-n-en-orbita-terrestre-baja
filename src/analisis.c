#include <stdio.h>
#include "analisis.h"
#include "fisica.h"

void ejecutarAnalisis(const Mision *mision) {
    if (mision == NULL) {
        printf("Error: los datos de la mision no son validos.\n");
        return;
    }

    printf("Demostracion analitica de que la atraccion gravitatoria ");
    printf("actua como fuerza centripeta del sistema.\n\n");

    printf("Datos de la mision:\n");
    printf("- Radio de la Tierra: %.2f m\n", mision->RT);
    printf("- Altura orbital: %.2f m\n", mision->h);
    printf("- Radio orbital total: %.2f m\n", mision->r);
    printf("- Masa de la nave: %.2f kg\n\n", mision->masaNave);

    printf("Analisis de fuerzas:\n");
    printf("F_g = G * (MT * m) / r^2\n");
    printf("F_c = m * (v^2 / r)\n");
    printf("Para una orbita circular ideal, F_g = F_c.\n\n");

    double v = calcularVelocidadOrbital(mision);
    double T = calcularPeriodoOrbital(mision);
    double ac = calcularAceleracionCentripeta(mision);

    printf("Resultados calculados:\n");
    printf("Velocidad orbital: %.2f m/s (%.2f km/s)\n",
           v, v / 1000.0);
    printf("Periodo orbital: %.2f segundos (%.2f minutos)\n",
           T, T / 60.0);
    printf("Aceleracion centripeta: %.2f m/s^2\n", ac);
}