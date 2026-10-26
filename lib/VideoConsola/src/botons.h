// botons.h - Ler os 7 botóns da consola.
//
// Chama a botons.ler() unha vez en cada volta do loop() e despois pregunta:
//   botons.esta_premido(BOTON_A)     -> true mentres o botón estea premido
//   botons.acaba_de_premer(BOTON_A)  -> true só no momento de premelo
//   botons.acaba_de_soltar(BOTON_A)  -> true só no momento de soltalo
#pragma once
#include <stdint.h>

// Número de cada botón (é a pata do chip PCF8574A onde está conectado).
enum Boton {
  ARRIBA     = 0,
  ABAIXO     = 1,
  ESQUERDA   = 2,
  DEREITA    = 3,
  BOTON_B    = 4,
  BOTON_A    = 5,
  BOTON_MENU = 6,
};

class Botons {
public:
  void iniciar();
  void ler();                          // le o estado de todos os botóns
  bool esta_premido(Boton b);
  bool acaba_de_premer(Boton b);
  bool acaba_de_soltar(Boton b);
  bool algun_premido();                // hai algún botón premido?
  void agardar_boton();                // espera ata que se prema e solte un botón
  bool conectados();                   // o chip dos botóns responde?

private:
  uint8_t _agora = 0;
  uint8_t _antes = 0;
};

extern Botons botons;
