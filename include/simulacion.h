#ifndef SIMULACION_H
#define SIMULACION_H

#include "fisica.h"

#define MAX_SIMULACIONES 100

typedef struct {
    double aceleracionLateral; /* m/s² */
    double duracion;           /* s */
    double velocidadLateral;   /* m/s */
    double desplazamiento;     /* m */
} ResultadoManiobra;

/* Calcula una maniobra lateral con aceleración constante. */
ResultadoManiobra simularManiobraLateral(double aceleracion, double duracion);

#endif
