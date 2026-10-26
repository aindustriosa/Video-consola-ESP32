// O meu xogo
// Escribe aquí o teu programa. Mira os exemplos en lib/VideoConsola/examples/
// para ver como debuxar, ler os botóns e facer sons.

#include <VideoConsola.h>

void setup() {
  consola.iniciar();
  pantalla.encher(NEGRO);
  pantalla.texto_centrado("O meu xogo", 150, AMARELO);
}

void loop() {
  botons.ler();

  if (botons.acaba_de_premer(BOTON_A)) {
    son.bip();
  }

  consola.agardar(16);
}
