// 08 - A serpe
// O clásico: come mazás para medrar e non choques contigo nin coas paredes.
//
// O campo é unha grella de cadros. A serpe gárdase como unha lista de
// cadros (x, y): o primeiro é a cabeza. En cada paso engadimos unha cabeza
// nova e, se non comeu, quitamos a cola.

#include <VideoConsola.h>

const int CADRO = 12;                              // tamaño de cada cadro en puntos
const int ARRIBA_CAMPO = 32;                       // deixamos sitio para o marcador
const int COLUMNAS = ANCHO_PANTALLA / CADRO;       // 20
const int FILAS = (ALTO_PANTALLA - ARRIBA_CAMPO) / CADRO;   // 24
const int MAXIMO = COLUMNAS * FILAS;

int serpe_x[MAXIMO];
int serpe_y[MAXIMO];
int lonxitude;
int dir_x, dir_y;            // dirección: (1,0) dereita, (-1,0) esquerda, (0,-1) arriba, (0,1) abaixo
int seguinte_dir_x, seguinte_dir_y;
int maza_x, maza_y;
int puntos;
int espera;                  // ms entre pasos (menos = máis rápido)
unsigned long ultimo_paso;

void pinta_cadro(int cx, int cy, uint16_t c) {
  pantalla.rectangulo(cx * CADRO + 1, ARRIBA_CAMPO + cy * CADRO + 1, CADRO - 2, CADRO - 2, c);
}

bool esta_na_serpe(int cx, int cy) {
  for (int i = 0; i < lonxitude; i++) {
    if (serpe_x[i] == cx && serpe_y[i] == cy) return true;
  }
  return false;
}

void nova_maza() {
  do {
    maza_x = consola.aleatorio(0, COLUMNAS - 1);
    maza_y = consola.aleatorio(0, FILAS - 1);
  } while (esta_na_serpe(maza_x, maza_y));
  pinta_cadro(maza_x, maza_y, VERMELLO);
}

void debuxa_marcador() {
  pantalla.rectangulo(0, 0, ANCHO_PANTALLA, ARRIBA_CAMPO - 2, VERDE_ESCURO);
  pantalla.texto("Mazás:", 8, 8, BRANCO, VERDE_ESCURO);
  pantalla.texto(puntos, 112, 8, AMARELO, VERDE_ESCURO);
}

void novo_xogo() {
  pantalla.encher(NEGRO);
  pantalla.rectangulo(0, ARRIBA_CAMPO - 2, ANCHO_PANTALLA, 2, VERDE);
  lonxitude = 3;
  for (int i = 0; i < lonxitude; i++) {
    serpe_x[i] = 10 - i;
    serpe_y[i] = 12;
    pinta_cadro(serpe_x[i], serpe_y[i], VERDE);
  }
  dir_x = 1; dir_y = 0;
  seguinte_dir_x = 1; seguinte_dir_y = 0;
  puntos = 0;
  espera = 180;
  debuxa_marcador();
  nova_maza();
  ultimo_paso = consola.tempo();
}

void fin_do_xogo() {
  son.perder();
  long record = consola.ler("record_serpe", 0);
  if (puntos > record) {
    record = puntos;
    consola.gardar("record_serpe", record);
  }
  pantalla.rectangulo(30, 110, 180, 100, AZUL_ESCURO);
  pantalla.marco(30, 110, 180, 100, BRANCO);
  pantalla.texto_centrado("Fin do xogo", 125, AMARELO, AZUL_ESCURO);
  pantalla.texto_centrado("Récord: " + String(record), 160, BRANCO, AZUL_ESCURO);
  pantalla.texto_centrado("Preme un botón", 188, GRIS, AZUL_ESCURO, 1);
  botons.agardar_boton();
  novo_xogo();
}

void setup() {
  consola.iniciar();
  novo_xogo();
}

void loop() {
  botons.ler();

  // Lemos a dirección sempre, pero non deixamos dar a volta sobre si mesma
  if (botons.esta_premido(ARRIBA)   && dir_y != 1)  { seguinte_dir_x = 0;  seguinte_dir_y = -1; }
  if (botons.esta_premido(ABAIXO)   && dir_y != -1) { seguinte_dir_x = 0;  seguinte_dir_y = 1; }
  if (botons.esta_premido(ESQUERDA) && dir_x != 1)  { seguinte_dir_x = -1; seguinte_dir_y = 0; }
  if (botons.esta_premido(DEREITA)  && dir_x != -1) { seguinte_dir_x = 1;  seguinte_dir_y = 0; }

  // Só avanzamos cando pasou o tempo de espera
  if (consola.tempo() - ultimo_paso < (unsigned long)espera) return;
  ultimo_paso = consola.tempo();
  dir_x = seguinte_dir_x;
  dir_y = seguinte_dir_y;

  int nova_x = serpe_x[0] + dir_x;
  int nova_y = serpe_y[0] + dir_y;

  // Chocou coa parede ou consigo mesma?
  if (nova_x < 0 || nova_x >= COLUMNAS || nova_y < 0 || nova_y >= FILAS ||
      esta_na_serpe(nova_x, nova_y)) {
    fin_do_xogo();
    return;
  }

  bool comeu = (nova_x == maza_x && nova_y == maza_y);

  if (!comeu) {
    pinta_cadro(serpe_x[lonxitude - 1], serpe_y[lonxitude - 1], NEGRO);   // borrar a cola
  } else {
    lonxitude++;
  }

  // Movemos todo o corpo unha posición cara atrás e poñemos a cabeza nova
  for (int i = lonxitude - 1; i > 0; i--) {
    serpe_x[i] = serpe_x[i - 1];
    serpe_y[i] = serpe_y[i - 1];
  }
  serpe_x[0] = nova_x;
  serpe_y[0] = nova_y;
  pinta_cadro(serpe_x[1], serpe_y[1], VERDE);       // o pescozo pasa a ser corpo
  pinta_cadro(nova_x, nova_y, VERDE_ESCURO);        // cabeza

  if (comeu) {
    puntos++;
    son.moeda();
    if (espera > 70) espera -= 6;
    debuxa_marcador();
    nova_maza();
  }
}
