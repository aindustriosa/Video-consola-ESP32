// consola.cpp - ver consola.h.
#include "consola.h"
#include "pantalla.h"
#include "botons.h"
#include "son.h"
#include "pinos.h"
#include <Preferences.h>
#include <esp_system.h>

Consola consola;

void Consola::iniciar() {
  Serial.begin(115200);

  // Primeiro acendemos a pantalla (vai alimentada a través dun transistor).
  pinMode(VC_PIN_PANTALLA, OUTPUT);
  digitalWrite(VC_PIN_PANTALLA, HIGH);
  delay(50);

  pantalla.iniciar();
  botons.iniciar();
  son.iniciar();
  randomSeed(esp_random());

  if (!botons.conectados()) {
    pantalla.texto_centrado("Non atopo", 130, VERMELLO);
    pantalla.texto_centrado("os botóns", 150, VERMELLO);
    pantalla.texto_centrado("Revisa o I2C", 180, GRIS, NEGRO, 1);
    delay(3000);
    pantalla.encher(NEGRO);
  }
}

void Consola::agardar(int ms)       { delay(ms); }
unsigned long Consola::tempo()      { return millis(); }
int  Consola::aleatorio(int minimo, int maximo) { return random(minimo, maximo + 1); }

void Consola::gardar(const char* nome, long valor) {
  Preferences p;
  p.begin("videoconsola", false);
  p.putLong(nome, valor);
  p.end();
}

long Consola::ler(const char* nome, long se_non_existe) {
  Preferences p;
  p.begin("videoconsola", true);
  long v = p.getLong(nome, se_non_existe);
  p.end();
  return v;
}

float Consola::bateria_voltios() {
  // O divisor parte a tensión á metade: multiplicamos por 2.
  return analogReadMilliVolts(VC_PIN_BATERIA) * 2 / 1000.0f;
}

int Consola::bateria() {
  int p = (int)((bateria_voltios() - 3.3f) * 100 / (4.2f - 3.3f));
  return p < 0 ? 0 : (p > 100 ? 100 : p);
}
