// 02 - Formas e cores
// Debuxamos rectángulos, círculos, liñas e triángulos.
//
// Lembra: a pantalla mide 240 de ancho (x) e 320 de alto (y),
// e o punto (0, 0) é a esquina de arriba á esquerda.

#include <VideoConsola.h>

void setup() {
  consola.iniciar();
  pantalla.encher(BRANCO);

  // Ceo e chan: rectangulo(x, y, ancho, alto, cor)
  pantalla.rectangulo(0, 0, 240, 220, AZUL_CEO);
  pantalla.rectangulo(0, 220, 240, 100, VERDE);

  // Sol: circulo(x_centro, y_centro, raio, cor)
  pantalla.circulo(190, 50, 25, AMARELO);

  // Casa: unha parede e un tellado
  pantalla.rectangulo(40, 150, 90, 70, LARANXA);
  pantalla.triangulo(30, 150, 140, 150, 85, 100, VERMELLO);
  pantalla.rectangulo(75, 180, 22, 40, MARRON);      // porta
  pantalla.marco(50, 165, 18, 18, BRANCO);           // fiestra (só o bordo)

  // Árbore
  pantalla.rectangulo(180, 170, 12, 50, MARRON);
  pantalla.circulo(186, 160, 22, VERDE_ESCURO);

  // Raios do sol: recta(x1, y1, x2, y2, cor)
  for (int i = 0; i < 8; i++) {
    float angulo = i * PI / 4;
    pantalla.recta(190 + cos(angulo) * 30, 50 + sin(angulo) * 30,
                   190 + cos(angulo) * 40, 50 + sin(angulo) * 40, AMARELO);
  }

  // Unha cor feita por nós: cor(vermello, verde, azul), de 0 a 255
  uint16_t violeta = cor(180, 120, 255);
  pantalla.texto_centrado("A miña casa", 270, violeta, VERDE, 2);
}

void loop() {
}
