#ifndef FISICA_H
#define FISICA_H

typedef struct {
    double masaTierra;       /* kg */
    double radioTierra;      /* m */
    double alturaOrbital;    /* m */
    double masaOrion;        /* kg */
    double constanteG;       /* N·m²/kg² */
} Mision;

/* Devuelve el radio orbital: radio terrestre + altura. */
double calcularRadioOrbital(const Mision *mision);

/* Devuelve la velocidad orbital circular en m/s. */
double calcularVelocidadOrbital(const Mision *mision);

/* Devuelve el período orbital en segundos. */
double calcularPeriodoOrbital(const Mision *mision);

/* Devuelve la aceleración centrípeta en m/s². */
double calcularAceleracionCentripeta(const Mision *mision);

#endif
