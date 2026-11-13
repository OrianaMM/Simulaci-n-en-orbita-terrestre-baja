# Cálculos físicos de referencia

## 1. Radio orbital

`r = RT + h`

`r = 6.371.000 m + 192.000 m = 6.563.000 m`

## 2. Velocidad orbital circular

En una órbita circular ideal, la fuerza gravitatoria proporciona la fuerza centrípeta:

`Fg = Fc`

`G · MT · m / r² = m · v² / r`

Se simplifica la masa de Orion:

`v = sqrt(G · MT / r)`

Resultado de referencia: aproximadamente **7.792,8 m/s**.

## 3. Período orbital

`T = 2 · π · r / v`

También puede expresarse como:

`T = 2 · π · sqrt(r³ / (G · MT))`

Resultado de referencia: aproximadamente **5.290 s**, es decir, **88,2 minutos**.

## 4. Aceleración centrípeta

`ac = v² / r = G · MT / r²`

Resultado de referencia: aproximadamente **9,25 m/s²**.

## 5. Maniobra con propulsor lateral

Datos: aceleración lateral `a = 0,50 m/s²`; duración `t = 10 s`.

Velocidad lateral adquirida:

`vx = a · t = 5 m/s`

Desplazamiento lateral durante el impulso, bajo aceleración constante:

`d = 1/2 · a · t² = 25 m`

**Alcance del modelo:** los 25 m representan el desplazamiento lateral durante los 10 segundos en un modelo simplificado. El impulso cambia el vector velocidad y la nave deja de seguir la órbita circular original. Para predecir la trayectoria orbital posterior completa se necesita integrar el movimiento considerando la gravedad y la orientación del impulso.
