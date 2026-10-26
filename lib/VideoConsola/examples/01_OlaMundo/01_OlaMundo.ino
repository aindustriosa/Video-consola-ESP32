// 01 - Ola, mundo!
// O primeiro programa: escribir texto na pantalla.
//
// Todo programa de Arduino ten dúas partes:
//   setup() -> execútase UNHA vez ao acender a consola
//   loop()  -> repítese unha e outra vez para sempre

#include <VideoConsola.h>

void setup() {
  consola.iniciar();                 // prepara pantalla, botóns e son

  pantalla.encher(AZUL_ESCURO);      // pinta todo o fondo

  // texto(que, x, y, cor, fondo, tamaño)
  pantalla.texto("Ola, mundo!", 32, 60, AMARELO, AZUL_ESCURO, 2);
  pantalla.texto("Son a túa consola", 52, 100, BRANCO, AZUL_ESCURO, 1);

  // O texto centrado só necesita a altura (y)
  pantalla.texto_centrado("¡A programar!", 160, VERDE, AZUL_ESCURO, 2);

  // Tamén se poden escribir números
  pantalla.texto("2 + 3 =", 60, 220, BRANCO, AZUL_ESCURO, 2);
  pantalla.texto(2 + 3, 180, 220, VERMELLO, AZUL_ESCURO, 2);
}

void loop() {
  // Aínda non facemos nada aquí.
}
