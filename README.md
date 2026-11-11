# Simulación en Órbita Terrestre Baja (LEO)

Proyecto integrador de **Algoritmos y Estructuras de Datos**, desarrollado en lenguaje C.

## Descripción

Simulador interactivo por consola de la nave Orion en una órbita terrestre baja (LEO). El programa permitirá consultar magnitudes orbitales, modificar parámetros de la misión, ejecutar una simulación de una maniobra lateral e informar los resultados.

> Los cálculos iniciales utilizan un modelo físico simplificado. Las hipótesis y limitaciones del modelo deben quedar explicitadas en los informes.

## Datos iniciales de la misión

| Parámetro | Símbolo | Valor |
|---|---:|---:|
| Altura orbital | h | 192.000 m |
| Masa de la Tierra | MT | 5,972 × 10²⁴ kg |
| Radio medio terrestre | RT | 6.371.000 m |
| Masa de Orion | m | 33.000 kg |
| Constante de gravitación universal | G | 6,674 × 10⁻¹¹ N·m²/kg² |

Radio orbital: `r = RT + h`.

## Funcionalidades previstas

1. Calcular la velocidad orbital circular.
2. Calcular el período orbital.
3. Calcular la aceleración centrípeta.
4. Simular una maniobra con propulsor lateral.
5. Permitir modificar los parámetros de la misión con validaciones.
6. Mostrar un informe con los resultados e historial de simulaciones.
0. Salir.

## Organización del proyecto

```text
.
├── README.md
├── .gitignore
├── include/
│   ├── fisica.h
│   ├── simulacion.h
│   └── validaciones.h
├── src/
│   ├── main.c
│   ├── fisica.c
│   ├── simulacion.c
│   └── validaciones.c
└── docs/
    └── calculos_fisicos.md
```

- `main.c`: menú principal y coordinación del programa.
- `fisica.c/.h`: funciones de cálculo orbital.
- `simulacion.c/.h`: maniobras, registro e informes de simulación.
- `validaciones.c/.h`: lectura y validación de datos ingresados.
- `docs/calculos_fisicos.md`: desarrollo de las ecuaciones y resultados de referencia.

## Compilación

Con GCC, desde la carpeta raíz:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/*.c -o simulador
```

En Windows, el ejecutable resultante puede llamarse `simulador.exe`.

## Estado

**Etapa inicial:** estructura y documentación base. Las funciones del simulador se implementarán y probarán progresivamente.

## Trabajo colaborativo

Antes de integrar cambios, cada integrante debería trabajar en una tarea o rama identificable, describir sus modificaciones en los commits y probar la compilación. Los nombres de los integrantes y sus responsabilidades pueden agregarse aquí cuando el grupo los defina.
