#include <stddef.h>
#include "simulacion.h"
#include "fisica.h"

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

ResultadoManiobra simularManiobraLateral(double aceleracion, double duracion) {
    ResultadoManiobra resultado = {0};

    resultado.aceleracionLateral = aceleracion;
    resultado.duracion = duracion;
    resultado.velocidadLateral = aceleracion * duracion;                   /* v = a * t */
    resultado.desplazamiento = 0.5 * aceleracion * duracion * duracion;    /* s = 1/2 * a * t^2 */

    return resultado;
}
