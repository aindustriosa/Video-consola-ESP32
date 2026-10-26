// son.h - Facer sons co zumbador.
//
// As frecuencias van en hercios (Hz): canto máis alto o número, máis aguda a nota.
// Os tempos van en milisegundos (1000 ms = 1 segundo).
// Mentres soa unha nota o programa espera (non fai outra cousa).
#pragma once
#include <stdint.h>
#include <stddef.h>

// Notas musicais (escala central) e a mesma escala unha oitava por riba.
constexpr int DO  = 523, RE  = 587, MI  = 659, FA  = 698, SOL  = 784, LA  = 880, SI  = 988;
constexpr int DO2 = 1047, RE2 = 1175, MI2 = 1319, FA2 = 1397, SOL2 = 1568, LA2 = 1760, SI2 = 1976;
constexpr int SILENCIO = 0;

struct Nota {
  int frecuencia;   // Hz (0 = silencio)
  int duracion;     // ms
};

class Son {
public:
  void iniciar();
  void volume(int nivel);                 // 0 = mudo ... 3 = máximo
  int  volume() const { return _volume; }

  void ton(int frecuencia, int ms);       // ton plano
  void nota(int frecuencia, int ms);      // nota con ataque suave (soa máis musical)
  void bip();                             // pitido curto
  void silencio();

  // Toca unha lista de notas.
  void melodia(const Nota* notas, int cantas);
  template <size_t N>
  void melodia(const Nota (&notas)[N]) { melodia(notas, (int)N); }

  // Efectos para xogos
  void salto();
  void moeda();
  void laser();
  void explosion();
  void rebote();
  void perder();
  void ganar();

private:
  void _frecuencia(int f);
  void _forza(int duty);
  int  _forza_volume();
  int  _volume = 2;
};

extern Son son;
