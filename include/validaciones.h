#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Lee un número real y verifica que esté dentro del intervalo indicado. */
double leerDoubleValidado(const char *mensaje, double minimo, double maximo);

/* Lee una opción entera del menú. */
int leerOpcionMenu(int minimo, int maximo);

#endif
