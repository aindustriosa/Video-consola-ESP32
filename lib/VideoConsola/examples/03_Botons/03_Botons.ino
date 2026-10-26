// 03 - Botóns
// Vemos na pantalla que botóns estamos a premer.
//
// En cada volta do loop():
//   1) botons.ler()  -> le como están os botóns agora
//   2) preguntamos por cada un con botons.esta_premido(...)

#include <VideoConsola.h>

// Debuxa un botón: acendido (premido) ou apagado
void debuxa_boton(int x, int y, const char* nome, bool premido) {
  uint16_t cor_fondo = premido ? AMARELO : GRIS_ESCURO;
  uint16_t cor_letra = premido ? NEGRO : BRANCO;
  pantalla.circulo(x, y, 22, cor_fondo);
  int ancho = pantalla.ancho_texto(nome, 1);
  pantalla.texto(nome, x - ancho / 2, y - 4, cor_letra, cor_fondo, 1);
}

void setup() {
  consola.iniciar();
  pantalla.encher(NEGRO);
  pantalla.texto_centrado("Preme os botóns", 20, BRANCO);
}

void loop() {
  botons.ler();

  // Cruceta
  debuxa_boton(60, 130, "Arriba", botons.esta_premido(ARRIBA));
  debuxa_boton(60, 210, "Abaixo", botons.esta_premido(ABAIXO));
  debuxa_boton(22, 170, "Esq",    botons.esta_premido(ESQUERDA));
  debuxa_boton(98, 170, "Der",    botons.esta_premido(DEREITA));

  // A, B e MENU
  debuxa_boton(205, 160, "A",    botons.esta_premido(BOTON_A));
  debuxa_boton(160, 190, "B",    botons.esta_premido(BOTON_B));
  debuxa_boton(180, 270, "MENU", botons.esta_premido(BOTON_MENU));

  // acaba_de_premer() só é verdade no instante de premer: ideal para un "bip"
  if (botons.acaba_de_premer(BOTON_A)) son.bip();

  consola.agardar(20);   // pequena pausa (50 voltas por segundo)
}
