#ifndef FISICA_H
#define FISICA_H

typedef struct {
    double MT;       /* kg */
    double RT;      /* m */
    double h;    /* m */
    double masaNave;        /* kg */
    double G;       /* N·m²/kg² */
    double r;       /* m */
} Mision;

/* Devuelve la velocidad orbital circular en m/s. */
double calcularVelocidadOrbital(const Mision *mision);

/* Devuelve el período orbital en segundos. */
double calcularPeriodoOrbital(const Mision *mision);

/* Devuelve la aceleración centrípeta en m/s². */
double calcularAceleracionCentripeta(const Mision *mision);

#endif
