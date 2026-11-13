#include <stdio.h>
#include "analisis.h"
#include "fisica.h"
#include "simulacion.h"
#include "validaciones.h"

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

void analizarPulsoLateralDinamico(const Mision *mision) { /*responde a la pregunta d*/
    double pulso = 0.50; /*aceleracion del problema en m/s^2*/

    printf("Trayectoria resultante con un pulso auxiliar lateral\n");
    printf("Velocidad orbital antes del pulso: %.2f m/s\n",
           calcularVelocidadOrbital(mision));
    printf("Aceleracion del propulsor auxiliar: %.2f m/s^2\n", pulso);

    /*Validacion de entrada: numero valido y dentro de un rango*/
    double dt = leerDoubleValidado("Ingrese la duracion del pulso en segundos (0.1 a 600): ",
                                   0.1, 600.0);

    /*El calculo se hace en simulacion.c*/
    ResultadoManiobra res = simularManiobraLateral(pulso, dt);

    printf("\n--- Calculo de pulso en %.2f segundos ---\n", res.duracion);
    printf("Desviacion lateral instantanea (delta s): %.2f metros\n", res.desplazamiento);
    printf("Velocidad lateral adquirida: %.2f m/s\n", res.velocidadLateral);
    printf("Comportamiento de la trayectoria:\n");
    printf("Al aplicar este pulso perpendicular durante %.2f s,\n", res.duracion);
    printf("se altera la componente radial de la velocidad, transformando\n");
    printf("la trayectoria circular original en una orbita eliptica.\n");
}
