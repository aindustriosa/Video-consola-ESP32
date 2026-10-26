// 06 - Debuxos (sprites)
// Facemos un personaxe "pintando" con números. Cada número é unha cor:
//   '.' transparente  '0' negro  '1' branco  '2' vermello '3' laranxa '4' amarelo
//   '5' verde         '6' azul   '7' morado  '8' rosa     '9' gris
//
// Temos dous debuxos case iguais (as pernas cambian) e alternámolos
// mentres camiña: así parece que se move. Iso chámase animación.

#include <VideoConsola.h>

const char* paso1[] = {
  "...4444...",
  "..444444..",
  "..388338..",
  "..388888..",
  "...8888...",
  "..666666..",
  ".86666668.",
  ".86666668.",
  "...6666...",
  "...0..0...",
  "...0..0...",
  "..00..00..",
};

const char* paso2[] = {
  "...4444...",
  "..444444..",
  "..388338..",
  "..388888..",
  "...8888...",
  "..666666..",
  ".86666668.",
  ".86666668.",
  "...6666...",
  "...0..0...",
  "..0....0..",
  ".00....00.",
};

const int TAMANO = 6;     // cada cadradiño mide 6x6 puntos
const int Y = 180;
int x = 90;
int fotograma = 0;        // que debuxo toca: 0 ou 1

void setup() {
  consola.iniciar();
  pantalla.encher(AZUL_CEO);
  pantalla.rectangulo(0, Y + 12 * TAMANO, 240, 320, VERDE);
  pantalla.texto_centrado("Move co </>", 20, BRANCO, AZUL_CEO);
  pantalla.texto_centrado("B: cambiar de cor", 45, BRANCO, AZUL_CEO, 1);
  pantalla.debuxo(paso1, x, Y, TAMANO);
}

void loop() {
  botons.ler();

  int novo_x = x;
  if (botons.esta_premido(ESQUERDA)) novo_x -= 3;
  if (botons.esta_premido(DEREITA))  novo_x += 3;
  novo_x = constrain(novo_x, 0, ANCHO_PANTALLA - 10 * TAMANO);

  // B cambia a cor '6' (a camiseta) por outra ao chou
  bool redebuxar = false;
  if (botons.acaba_de_premer(BOTON_B)) {
    pantalla.cor_do_debuxo('6', cor(consola.aleatorio(0, 255), consola.aleatorio(0, 255), consola.aleatorio(0, 255)));
    redebuxar = true;
  }

  if (novo_x != x) {
    pantalla.borrar_debuxo(paso1, x, Y, TAMANO, AZUL_CEO);
    x = novo_x;
    fotograma = 1 - fotograma;      // 0 -> 1 -> 0 -> 1 ...
    redebuxar = true;
  }

  if (redebuxar) {
    if (fotograma == 0) pantalla.debuxo(paso1, x, Y, TAMANO);
    else                pantalla.debuxo(paso2, x, Y, TAMANO);
  }

  consola.agardar(60);
}
