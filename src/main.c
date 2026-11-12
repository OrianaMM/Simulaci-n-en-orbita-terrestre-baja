#include "simulacion.h"
#include "analisis.h"
#include "interfaz.h"
#include "fisica.h"

int main(void) {
    Mision mision;

    inicializarMision(&mision);

    ejecutarAnalisis(&mision);

    analizarPulsoLateralDinamico(&mision);

    iniciarInterfaz(&mision);

    return 0;
}