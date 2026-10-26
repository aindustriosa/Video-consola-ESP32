// consola.h - Funcións xerais: arrincar, esperar, tempo, números ao chou,
// gardar datos (que non se borran ao apagar) e batería.
#pragma once
#include <Arduino.h>

class Consola {
public:
  // Prepara pantalla, botóns e son. Chámaa ao principio de setup().
  void iniciar();

  void agardar(int ms);                 // espera uns milisegundos
  unsigned long tempo();                // ms desde que se acendeu a consola
  int  aleatorio(int minimo, int maximo);   // número ao chou entre minimo e maximo (incluídos)

  // Gardar números na memoria permanente (p. ex. o récord dun xogo).
  // O nome pode ter ata 15 letras, sen espazos nin acentos.
  void gardar(const char* nome, long valor);
  long ler(const char* nome, long se_non_existe = 0);

  float bateria_voltios();              // tensión da batería (3,3 V baleira ... 4,2 V chea)
  int   bateria();                      // porcentaxe aproximada (0..100)
};

extern Consola consola;
