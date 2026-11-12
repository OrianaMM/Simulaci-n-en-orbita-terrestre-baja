#include "simulacion.h"
#include "simulacion.h"
#include "fisica.h"
#include <stddef.h>

ResultadoManiobra simularManiobraLateral(double aceleracion, double duracion) {
    ResultadoManiobra resultado = {0};

    /* TODO: validar entradas y calcular:
       velocidad lateral = aceleracion * duracion
       desplazamiento = 0.5 * aceleracion * duracion^2
    */
    (void)aceleracion;
    (void)duracion;
    return resultado;
}


void inicializarMision(Mision *mision) {
    if (mision == NULL) {
        return;
    }

    mision->MT = 5.972e24;
    mision->RT = 6371000.0;
    mision->h = 192000.0;
    mision->masaNave = 33000.0;
    mision->G = 6.674e-11;
    mision->r = mision->RT + mision->h;
}