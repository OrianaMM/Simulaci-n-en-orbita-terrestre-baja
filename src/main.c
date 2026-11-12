#include "fisica.h"
#include "simulacion.h"
#include "analisis.h"
#include "interfaz.h"

int main(void) {
    Mision mision;

    inicializarMision(&mision);

    ejecutarAnalisis(&mision);

   iniciarInterfaz(&mision);

    return 0;
}