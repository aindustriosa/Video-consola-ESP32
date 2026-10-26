// VideoConsola.h - SDK para programar a videoconsola ESP32 de A Industriosa.
//
// Inclúe este ficheiro e xa tes:
//   pantalla  -> debuxar formas, textos e debuxos
//   botons    -> ler a cruceta e os botóns A, B e MENU
//   son       -> notas, melodías e efectos
//   consola   -> iniciar, esperar, tempo, números ao chou, gardar datos e batería
//
// Exemplo mínimo:
//   #include <VideoConsola.h>
//   void setup() {
//     consola.iniciar();
//     pantalla.texto("Ola!", 80, 150);
//   }
//   void loop() {}
#pragma once

#include "cores.h"
#include "pantalla.h"
#include "botons.h"
#include "son.h"
#include "consola.h"
