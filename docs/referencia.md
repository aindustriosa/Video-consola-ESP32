# Referencia do SDK

```cpp
#include <VideoConsola.h>
```

Isto dáche catro obxectos: `consola`, `pantalla`, `botons` e `son`.

## consola

| Función | Que fai |
|---|---|
| `consola.iniciar()` | Prepara todo. Sempre ao principio de `setup()` |
| `consola.agardar(ms)` | Espera uns milisegundos (1000 ms = 1 segundo) |
| `consola.tempo()` | Milisegundos desde que se acendeu |
| `consola.aleatorio(min, max)` | Número ao chou entre `min` e `max` |
| `consola.gardar("nome", valor)` | Garda un número que non se borra ao apagar |
| `consola.ler("nome", se_non_hai)` | Le un número gardado |
| `consola.bateria()` | Batería en porcentaxe (0 a 100) |
| `consola.bateria_voltios()` | Tensión da batería |

## pantalla

A pantalla mide **240 x 320** puntos (`ANCHO_PANTALLA` e `ALTO_PANTALLA`).
O punto (0, 0) é a esquina de arriba á esquerda.

```
(0,0) ──────── x ────────▶ (239,0)
  │
  y
  │
  ▼
(0,319)
```

| Función | Que fai |
|---|---|
| `pantalla.encher(cor)` | Pinta toda a pantalla |
| `pantalla.punto(x, y, cor)` | Un punto |
| `pantalla.recta(x1, y1, x2, y2, cor)` | Unha liña |
| `pantalla.rectangulo(x, y, ancho, alto, cor)` | Rectángulo recheo |
| `pantalla.marco(x, y, ancho, alto, cor)` | Só o bordo do rectángulo |
| `pantalla.circulo(x, y, raio, cor)` | Círculo recheo |
| `pantalla.circunferencia(x, y, raio, cor)` | Só o bordo do círculo |
| `pantalla.triangulo(x1, y1, x2, y2, x3, y3, cor)` | Triángulo recheo |
| `pantalla.texto(texto, x, y, cor, fondo, tamaño)` | Escribe texto ou un número |
| `pantalla.texto_centrado(texto, y, cor, fondo, tamaño)` | Texto centrado |
| `pantalla.ancho_texto(texto, tamaño)` | Canto ocupa un texto |
| `pantalla.debuxo(mapa, x, y, tamaño)` | Debuxa un personaxe feito con números |
| `pantalla.borrar_debuxo(mapa, x, y, tamaño, fondo)` | Borra ese personaxe |
| `pantalla.cor_do_debuxo('6', cor)` | Cambia unha cor dos debuxos |

`cor`, `fondo` e `tamaño` son opcionais (por defecto: branco, negro e 2).
O texto admite acentos, ñ, ¿ e ¡.

### Cores

`NEGRO`, `BRANCO`, `GRIS`, `GRIS_ESCURO`, `VERMELLO`, `LARANXA`, `AMARELO`,
`VERDE`, `VERDE_ESCURO`, `CIAN`, `AZUL`, `AZUL_CEO`, `AZUL_ESCURO`, `MORADO`,
`ROSA`, `MARRON`.

Para facer outra: `cor(vermello, verde, azul)`, cada un de 0 a 255.

### Debuxos con números

Cada fila é un texto e cada carácter, un cadradiño:

| `.` | `0` | `1` | `2` | `3` | `4` | `5` | `6` | `7` | `8` | `9` |
|---|---|---|---|---|---|---|---|---|---|---|
| transparente | negro | branco | vermello | laranxa | amarelo | verde | azul | morado | rosa | gris |

```cpp
const char* corazon[] = {
  ".22.22.",
  "2222222",
  ".22222.",
  "..222..",
  "...2...",
};
pantalla.debuxo(corazon, 100, 50, 4);   // cada cadradiño mide 4 x 4 puntos
```

## botons

Chama a `botons.ler()` unha vez en cada volta de `loop()`.

| Función | Que fai |
|---|---|
| `botons.ler()` | Le como están os botóns agora |
| `botons.esta_premido(b)` | `true` mentres está premido |
| `botons.acaba_de_premer(b)` | `true` só no momento de premelo |
| `botons.acaba_de_soltar(b)` | `true` só no momento de soltalo |
| `botons.algun_premido()` | Hai algún premido? |
| `botons.agardar_boton()` | Espera ata que se prema e solte un botón |

Botóns: `ARRIBA`, `ABAIXO`, `ESQUERDA`, `DEREITA`, `BOTON_A`, `BOTON_B`, `BOTON_MENU`.

## son

Mentres soa algo o programa espera, así que usa sons curtos dentro dos xogos.

| Función | Que fai |
|---|---|
| `son.nota(frecuencia, ms)` | Toca unha nota |
| `son.ton(frecuencia, ms)` | Ton plano (máis "robótico") |
| `son.bip()` | Pitido curto |
| `son.melodia(lista)` | Toca unha lista de notas |
| `son.volume(n)` | Volume de 0 (mudo) a 3 |
| `son.silencio()` | Cala |
| `son.salto()`, `son.moeda()`, `son.laser()`, `son.explosion()`, `son.rebote()` | Efectos |
| `son.ganar()`, `son.perder()` | Melodías de fin de partida |

Notas: `DO`, `RE`, `MI`, `FA`, `SOL`, `LA`, `SI` e unha oitava máis aguda:
`DO2`, `RE2`... `SI2`. Silencio: `SILENCIO`.

```cpp
const Nota CANCION[] = { {DO, 200}, {MI, 200}, {SOL, 400} };
son.melodia(CANCION);
```

## Para ir máis aló

`pantalla.lcd` dá acceso directo á librería
[LovyanGFX](https://github.com/lovyan03/LovyanGFX), con moitas máis funcións.
