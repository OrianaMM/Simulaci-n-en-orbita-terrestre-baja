#include <stdio.h>
#include <stdlib.h>
#include "validaciones.h"

/* Descarta lo que haya quedado escrito en la linea de entrada */
static void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* Si se cierra la entrada (EOF) se termina el programa,
   para no quedar en un bucle infinito */
static void controlarFin(int resultado) {
    if (resultado == EOF) {
        printf("\nEntrada finalizada. Cerrando el programa.\n");
        exit(0);
    }
}

double leerDoubleValidado(const char *mensaje, double minimo, double maximo) {
    double valor;
    int leidos;
    int c;

    while (1) {
        printf("%s", mensaje);
        leidos = scanf("%lf", &valor);
        controlarFin(leidos);

        c = getchar();               /* tiene que venir el ENTER y nada mas */
        if (c != '\n') {
            limpiarBuffer();
        }

        if (leidos != 1 || c != '\n') {
            mensajeError("Ingrese un numero valido (use punto decimal, ej: 0.5).");
        } else if (valor < minimo || valor > maximo) {
            printf("Valor fuera de rango. Debe estar entre %.2f y %.2f.\n", minimo, maximo);
        } else {
            return valor;
        }
    }
}

int leerOpcionMenu(int minimo, int maximo) {
    int opcion;
    int leidos;
    int c;

    while (1) {
        printf("Seleccione una opcion: ");
        leidos = scanf("%d", &opcion);
        controlarFin(leidos);

        c = getchar();
        if (c != '\n') {
            limpiarBuffer();
        }

        if (leidos != 1 || c != '\n') {
            mensajeError("Ingrese solo un numero entero.");
        } else if (opcion < minimo || opcion > maximo) {
            printf("Opcion invalida. Elija entre %d y %d.\n", minimo, maximo);
        } else {
            return opcion;
        }
    }
}

int confirmar(const char *mensaje) {
    char respuesta;
    int leidos;
    int c;

    while (1) {
        printf("%s (s/n): ", mensaje);
        leidos = scanf(" %c", &respuesta);
        controlarFin(leidos);

        c = getchar();
        if (c != '\n') {
            limpiarBuffer();
        }

        if (c == '\n' && (respuesta == 's' || respuesta == 'S')) {
            return 1;
        }
        if (c == '\n' && (respuesta == 'n' || respuesta == 'N')) {
            return 0;
        }
        mensajeError("Responda con 's' o 'n'.");
    }
}

void pausar(void) {
    printf("\nPresione ENTER para continuar...");
    if (getchar() == EOF) {
        exit(0);
    }
}

void limpiarPantalla(void) {
    int i;
    for (i = 0; i < 30; i++) {
        printf("\n");
    }
}

void mensajeError(const char *texto) {
    printf("ERROR: %s\n", texto);
}

void mensajeOk(const char *texto) {
    printf("OK: %s\n", texto);
}
