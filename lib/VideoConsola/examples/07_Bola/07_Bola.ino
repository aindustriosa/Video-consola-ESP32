// 07 - Xogo da bóla
// Un xogo completo: move a pa coa cruceta e non deixes caer a bóla.
// Cada rebote na pa suma un punto e a bóla vai cada vez máis rápido.
// O récord gárdase na memoria e non se perde ao apagar.

#include <VideoConsola.h>

const int ALTO_MARCADOR = 30;
const int RAIO = 5;
const int PA_ANCHO = 50;
const int PA_ALTO = 8;
const int PA_Y = 295;

float bola_x, bola_y;       // posición da bóla
float vel_x, vel_y;         // velocidade da bóla
int pa_x;                   // posición da pa
int puntos;
long record;

void debuxa_marcador() {
  pantalla.rectangulo(0, 0, ANCHO_PANTALLA, ALTO_MARCADOR, AZUL_ESCURO);
  pantalla.texto("Puntos:", 8, 8, BRANCO, AZUL_ESCURO);
  pantalla.texto(puntos, 120, 8, AMARELO, AZUL_ESCURO);
}

void novo_xogo() {
  pantalla.encher(NEGRO);
  bola_x = 120;
  bola_y = 100;
  vel_x = consola.aleatorio(0, 1) ? 2 : -2;
  vel_y = 2;
  pa_x = (ANCHO_PANTALLA - PA_ANCHO) / 2;
  puntos = 0;
  debuxa_marcador();
  pantalla.rectangulo(pa_x, PA_Y, PA_ANCHO, PA_ALTO, BRANCO);
}

void pantalla_de_inicio() {
  pantalla.encher(NEGRO);
  pantalla.texto_centrado("BÓLA", 90, AMARELO, NEGRO, 4);
  pantalla.texto_centrado("Récord:", 170, BRANCO);
  pantalla.texto_centrado(String(record), 195, VERDE);
  pantalla.texto_centrado("Preme un botón", 260, GRIS, NEGRO, 1);
  botons.agardar_boton();
}

void setup() {
  consola.iniciar();
  record = consola.ler("record_bola", 0);
  pantalla_de_inicio();
  novo_xogo();
}

void loop() {
  botons.ler();

  // --- Mover a pa ---
  int novo_pa_x = pa_x;
  if (botons.esta_premido(ESQUERDA)) novo_pa_x -= 5;
  if (botons.esta_premido(DEREITA))  novo_pa_x += 5;
  novo_pa_x = constrain(novo_pa_x, 0, ANCHO_PANTALLA - PA_ANCHO);
  if (novo_pa_x != pa_x) {
    pantalla.rectangulo(pa_x, PA_Y, PA_ANCHO, PA_ALTO, NEGRO);
    pa_x = novo_pa_x;
    pantalla.rectangulo(pa_x, PA_Y, PA_ANCHO, PA_ALTO, BRANCO);
  }

  // --- Mover a bóla ---
  pantalla.circulo(bola_x, bola_y, RAIO, NEGRO);   // borrar
  bola_x += vel_x;
  bola_y += vel_y;

  // Rebote nas paredes
  if (bola_x < RAIO || bola_x > ANCHO_PANTALLA - RAIO) {
    vel_x = -vel_x;
    bola_x = constrain(bola_x, RAIO, ANCHO_PANTALLA - RAIO);
    son.ton(600, 10);
  }
  if (bola_y < ALTO_MARCADOR + RAIO) {
    vel_y = -vel_y;
    bola_y = ALTO_MARCADOR + RAIO;
    son.ton(600, 10);
  }

  // Rebote na pa
  if (vel_y > 0 && bola_y + RAIO >= PA_Y && bola_y < PA_Y + PA_ALTO &&
      bola_x >= pa_x - RAIO && bola_x <= pa_x + PA_ANCHO + RAIO) {
    vel_y = -(vel_y + 0.3);                          // cada vez máis rápido
    vel_x += (bola_x - (pa_x + PA_ANCHO / 2)) / 10;  // o bordo da pa desvía a bóla
    bola_y = PA_Y - RAIO;
    puntos++;
    son.rebote();
    debuxa_marcador();
  }

  // Caeu?
  if (bola_y > ALTO_PANTALLA) {
    son.perder();
    if (puntos > record) {
      record = puntos;
      consola.gardar("record_bola", record);
      pantalla.texto_centrado("¡Novo récord!", 150, AMARELO);
      son.ganar();
      consola.agardar(1500);
    }
    pantalla_de_inicio();
    novo_xogo();
    return;
  }

  pantalla.circulo(bola_x, bola_y, RAIO, AMARELO);  // debuxar
  pantalla.rectangulo(pa_x, PA_Y, PA_ANCHO, PA_ALTO, BRANCO);
  consola.agardar(16);
}
