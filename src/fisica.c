#include <math.h>
#include <stddef.h>
#include "fisica.h"

double calcularRadioOrbital(const Mision *mision) {
    if (mision == NULL) return 0.0;
    return mision->radioTierra + mision->alturaOrbital;
}

double calcularVelocidadOrbital(const Mision *mision) {
    /* TODO: implementar sqrt(G * MT / r), validando los datos. */
    (void)mision;
    return 0.0;
}

double calcularPeriodoOrbital(const Mision *mision) {
    /* TODO: implementar 2 * PI * sqrt(r^3 / (G * MT)). */
    (void)mision;
    return 0.0;
}

double calcularAceleracionCentripeta(const Mision *mision) {
    /* TODO: implementar G * MT / r^2. */
    (void)mision;
    return 0.0;
}
