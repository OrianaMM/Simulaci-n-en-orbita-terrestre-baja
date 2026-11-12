#include <math.h>
#include <stddef.h>
#include "fisica.h"

/*constantes de calculo dadas por el problema*/
#define PI 3.14159265358979323846 

double calcularVelocidadOrbital(const Mision *mision) {
    return sqrt(mision->G * mision->MT / r);
}

double calcularPeriodoOrbital(const Mision *mision) {
    return 2 * PI * sqrt(pow(r, 3) / (mision->G * mision->MT));
}

double calcularAceleracionCentripeta(const Mision *mision) {
    return mision->G * mision->MT / pow(r, 2);
}
