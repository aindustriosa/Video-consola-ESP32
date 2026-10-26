// 05 - Mover un cadrado
// Movemos un cadrado coa cruceta sen que saia da pantalla.
//
// Truco: a pantalla non se borra soa. Para mover algo:
//   1) pintamos o cadrado vello coa cor do fondo (borrámolo)
//   2) cambiamos a posición
//   3) pintamos o cadrado no sitio novo

#include <VideoConsola.h>

const int LADO = 24;          // tamaño do cadrado
const int VELOCIDADE = 4;     // puntos que avanza en cada volta

int x = 108;                  // posición (esquina de arriba á esquerda)
int y = 148;
uint16_t cor_cadrado = AMARELO;

void setup() {
  consola.iniciar();
  pantalla.encher(NEGRO);
  pantalla.rectangulo(x, y, LADO, LADO, cor_cadrado);
}

void loop() {
  botons.ler();

  int novo_x = x;
  int novo_y = y;
  if (botons.esta_premido(ESQUERDA)) novo_x = novo_x - VELOCIDADE;
  if (botons.esta_premido(DEREITA))  novo_x = novo_x + VELOCIDADE;
  if (botons.esta_premido(ARRIBA))   novo_y = novo_y - VELOCIDADE;
  if (botons.esta_premido(ABAIXO))   novo_y = novo_y + VELOCIDADE;

  // Que non saia da pantalla
  if (novo_x < 0) novo_x = 0;
  if (novo_y < 0) novo_y = 0;
  if (novo_x > ANCHO_PANTALLA - LADO) novo_x = ANCHO_PANTALLA - LADO;
  if (novo_y > ALTO_PANTALLA - LADO)  novo_y = ALTO_PANTALLA - LADO;

  // Co botón A cambiamos a cor ao chou
  if (botons.acaba_de_premer(BOTON_A)) {
    cor_cadrado = cor(consola.aleatorio(50, 255), consola.aleatorio(50, 255), consola.aleatorio(50, 255));
    pantalla.rectangulo(x, y, LADO, LADO, cor_cadrado);
  }

  // Só redebuxamos se se moveu
  if (novo_x != x || novo_y != y) {
    pantalla.rectangulo(x, y, LADO, LADO, NEGRO);              // borrar
    x = novo_x;
    y = novo_y;
    pantalla.rectangulo(x, y, LADO, LADO, cor_cadrado);        // debuxar
  }

  consola.agardar(16);
}
