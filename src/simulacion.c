#include "simulacion.h"
#include "simulacion.h"
#include "fisica.h"
#include <stddef.h>

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