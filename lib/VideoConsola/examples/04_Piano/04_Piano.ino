// 04 - Piano
// Cada botón toca unha nota musical.
// Notas dispoñibles: DO RE MI FA SOL LA SI (e DO2, RE2... unha oitava máis aguda).

#include <VideoConsola.h>

// Unha melodía é unha lista de {nota, duración en ms}
const Nota CUMPREANOS[] = {
  {DO, 200}, {DO, 200}, {RE, 400}, {DO, 400}, {FA, 400}, {MI, 700},
};

void setup() {
  consola.iniciar();
  pantalla.encher(NEGRO);
  pantalla.texto_centrado("Piano", 20, AMARELO, NEGRO, 3);
  pantalla.texto("Arriba  DO", 40, 90);
  pantalla.texto("Dereita RE", 40, 120);
  pantalla.texto("Abaixo  MI", 40, 150);
  pantalla.texto("Esquer. FA", 40, 180);
  pantalla.texto("B       SOL", 40, 210);
  pantalla.texto("A       LA", 40, 240);
  pantalla.texto("MENU: canción", 20, 290, GRIS, NEGRO, 2);
}

void loop() {
  botons.ler();

  if (botons.esta_premido(ARRIBA))   son.nota(DO, 150);
  if (botons.esta_premido(DEREITA))  son.nota(RE, 150);
  if (botons.esta_premido(ABAIXO))   son.nota(MI, 150);
  if (botons.esta_premido(ESQUERDA)) son.nota(FA, 150);
  if (botons.esta_premido(BOTON_B))  son.nota(SOL, 150);
  if (botons.esta_premido(BOTON_A))  son.nota(LA, 150);

  if (botons.acaba_de_premer(BOTON_MENU)) son.melodia(CUMPREANOS);
}
