// botons.cpp - ver botons.h.
// Os botóns van a masa (GND) ao premelos: o PCF8574A le un 0 cando están premidos.
#include "botons.h"
#include "pinos.h"
#include <Arduino.h>
#include <Wire.h>

Botons botons;

void Botons::iniciar() {
  Wire.begin(VC_PIN_SDA, VC_PIN_SCL, 100000);
  Wire.beginTransmission((uint8_t)VC_PCF8574_DIR);
  Wire.write(0xFF);   // todas as patas como entradas
  Wire.endTransmission();
}

void Botons::ler() {
  _antes = _agora;
  if (Wire.requestFrom((uint8_t)VC_PCF8574_DIR, (uint8_t)1) == 1) {
    _agora = (uint8_t)(~Wire.read()) & 0x7F;   // invertemos: 1 = premido
  } else {
    _agora = 0;
  }
}

bool Botons::esta_premido(Boton b)    { return (_agora >> b) & 1; }
bool Botons::acaba_de_premer(Boton b) { return ((_agora >> b) & 1) && !((_antes >> b) & 1); }
bool Botons::acaba_de_soltar(Boton b) { return !((_agora >> b) & 1) && ((_antes >> b) & 1); }
bool Botons::algun_premido()          { return _agora != 0; }

void Botons::agardar_boton() {
  do { ler(); delay(10); } while (algun_premido());    // primeiro, que estean todos soltos
  do { ler(); delay(10); } while (!algun_premido());   // agora, que se prema un
  do { ler(); delay(10); } while (algun_premido());    // e que se solte
}

bool Botons::conectados() {
  Wire.beginTransmission((uint8_t)VC_PCF8574_DIR);
  return Wire.endTransmission() == 0;
}
