// son.cpp - ver son.h.
// O zumbador é pasivo: para que soe hai que mandarlle unha onda cadrada (PWM)
// coa frecuencia da nota. Facémolo co periférico LEDC do ESP32.
// IMPORTANTE: primeiro a frecuencia e despois o "duty" (se non, non soa).
#include "son.h"
#include "pinos.h"
#include <Arduino.h>

Son son;

static const int RES = 10;                            // bits de resolución do PWM
static const uint32_t FORZA[4] = {0, 94, 312, 656};   // duty de cada volume (0..3)

// O núcleo 3.x de Arduino-ESP32 cambiou as funcións LEDC: soportamos os dous.
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
  static void pwm_iniciar()        { ledcAttach(VC_PIN_ZUMBADOR, 1000, RES); }
  static void pwm_duty(uint32_t d) { ledcWrite(VC_PIN_ZUMBADOR, d); }
  static void pwm_freq(uint32_t f) { ledcChangeFrequency(VC_PIN_ZUMBADOR, f, RES); }
#else
  static const int CANLE = 0;
  static void pwm_iniciar()        { ledcSetup(CANLE, 1000, RES); ledcAttachPin(VC_PIN_ZUMBADOR, CANLE); }
  static void pwm_duty(uint32_t d) { ledcWrite(CANLE, d); }
  static void pwm_freq(uint32_t f) { ledcChangeFrequency(CANLE, f, RES); }
#endif

void Son::iniciar() {
  pwm_iniciar();
  pwm_duty(0);
}

void Son::volume(int nivel) { _volume = nivel < 0 ? 0 : (nivel > 3 ? 3 : nivel); }

int  Son::_forza_volume()      { return FORZA[_volume]; }
void Son::_frecuencia(int f)   { if (f > 0) pwm_freq((uint32_t)f); }
void Son::_forza(int duty)     { pwm_duty(duty); }
void Son::silencio()           { pwm_duty(0); }

void Son::ton(int frecuencia, int ms) {
  if (frecuencia <= 0 || _volume == 0) {
    silencio();
  } else {
    _frecuencia(frecuencia);
    _forza(_forza_volume());
  }
  if (ms > 0) { delay(ms); silencio(); }
}

void Son::bip() { ton(1500, 40); }

void Son::nota(int frecuencia, int ms) {
  if (frecuencia <= 0 || _volume == 0) {
    silencio();
    if (ms > 0) delay(ms);
    return;
  }
  int forza = _forza_volume();
  _frecuencia(frecuencia);
  int ataque = (ms > 24) ? 8 : 2;
  bool vibrato = ms > 180;
  const int paso = 10;
  for (int t = 0; t < ms; t += paso) {
    float amp = (t < ataque) ? (float)(t + paso) / ataque : 1.0f - 0.45f * ((float)t / ms);
    if (amp > 1) amp = 1;
    _forza((int)(forza * amp));
    if (vibrato) _frecuencia((int)(frecuencia * (((t / paso) & 1) ? 1.008f : 0.992f)));
    delay(ms - t > paso ? paso : ms - t);
  }
  silencio();
}

void Son::melodia(const Nota* notas, int cantas) {
  for (int i = 0; i < cantas; i++) {
    nota(notas[i].frecuencia, notas[i].duracion);
    delay(8);
  }
  silencio();
}

void Son::salto() {
  if (_volume == 0) return;
  _frecuencia(680); _forza(_forza_volume());
  for (float f = 680; f < 1300; f *= 1.13f) { _frecuencia((int)f); delay(7); }
  silencio();
}

void Son::moeda() { nota(988, 70); nota(1319, 130); }

void Son::laser() {
  if (_volume == 0) return;
  _frecuencia(2100); _forza(_forza_volume());
  for (float f = 2100; f > 850; f *= 0.85f) { _frecuencia((int)f); delay(4); }
  silencio();
}

void Son::explosion() {
  if (_volume == 0) return;
  static const int F[5] = {520, 380, 300, 240, 180};
  _frecuencia(F[0]); _forza(_forza_volume());
  for (int f : F) { _frecuencia(f); delay(16); }
  silencio();
}

void Son::rebote() {
  if (_volume == 0) return;
  static const int F[4] = {820, 1180, 1500, 1150};
  _frecuencia(F[0]); _forza(_forza_volume());
  for (int f : F) { _frecuencia(f); delay(12); }
  silencio();
}

void Son::perder() {
  static const Nota N[] = {{659, 160}, {523, 160}, {440, 230}, {0, 40},
                           {494, 150}, {440, 150}, {392, 280}, {0, 50},
                           {415, 140}, {392, 150}, {349, 160}, {330, 560}};
  melodia(N);
}

void Son::ganar() {
  static const Nota N[] = {{523, 110}, {659, 110}, {784, 110}, {1047, 260},
                           {0, 60}, {784, 110}, {1047, 400}};
  melodia(N);
}
