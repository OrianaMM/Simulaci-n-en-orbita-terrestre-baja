#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Lee un número real y verifica que esté dentro del intervalo indicado. */
double leerDoubleValidado(const char *mensaje, double minimo, double maximo);

/* Lee una opción entera del menú. */
int leerOpcionMenu(int minimo, int maximo);

/* --- Agregados para la interfaz de consola --- */

/* Pregunta si/no. Devuelve 1 para si, 0 para no. */
int confirmar(const char *mensaje);

/* Espera un ENTER del usuario. */
void pausar(void);

/* Borra la pantalla de la consola. */
void limpiarPantalla(void);

/* Mensajes con formato uniforme. */
void mensajeError(const char *texto);
void mensajeOk(const char *texto);

#endif
