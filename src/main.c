#include <stdio.h>
#include "fisica.h"
#include "simulacion.h"
#include "validaciones.h"

void ejecutarAnalisis(const Mision *mision) {
    printf("Demostración analítica de que la atracción gravitatoria actúa como la fuerza centrípeta del sistema\n");
    /*se muestran los datos fijo*/
    printf(" Datos de la mision:\n");
    printf("-Radio de la Tierra: %.2f m\n", mision->RT);
    printf("-Altura orbital: %.2f m\n", mision->h);
    printf("-Radio orbital total: %.2f m\n", mision->r);
    printf("-Masa de la nave: %.2f kg\n\n", mision->masaNave);

    /*resolución de fuerzas (F_g = F_c)*/
    printf("Analisis de fuerzas:\n");
    printf("F_g (Gravedad Newtoniana)= G * (MT * m) / r^2\n");
    printf("F_c (Fuerza Centripeta)= m * (v^2 / r)\n");
    printf("Como F_g actua como la unica fuerza neta hacia el centro,\n");
    printf("se confirma que F_g = F_c, permitiendo despejar v.\n\n");

    /*calculo de los resultados numéricos*/
    double v = calcularVelocidadOrbital(mision);
    double T = calcularPeriodoOrbital(mision);
    double ac = calcularAceleracionCentripeta(mision);

    printf("Resultados calculados:\n");
    printf("Velocidad orbital(v): %.2f m/s (%.2f km/s)\n", v, v / 1000.0);
    printf("Periodo orbital(T): %.2f segundos (%.2f minutos)\n", T, T / 60.0);
    printf("Aceleracion centripeta(ac): %.2f m/s^2\n", ac);
}

int main(void) {
    Mision mision = {
        .MT = 5.972e24,
        .RT = 6371000.0,
        .h = 192000.0,  
        .masaNave = 33000.0,       
        .G = 6.674e-11,  
        .r = 6563000.0,
    };
    /* TODO: inicializar la misión, mostrar el menú y coordinar las opciones. */
    printf("Simulador de órbita terrestre baja (LEO) - Orion\n");
    printf("Estructura inicial del proyecto.\n");

    return 0;
}
