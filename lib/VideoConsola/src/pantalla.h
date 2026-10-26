// pantalla.h - Debuxar na pantalla de 240x320 puntos.
//
// As coordenadas empezan na esquina de arriba á esquerda:
//   x vai de 0 (esquerda) a 239 (dereita)
//   y vai de 0 (arriba)   a 319 (abaixo)
//
// Debúxase directamente na pantalla: para mover algo hai que borralo
// (pintando enriba a cor do fondo) e debuxalo de novo no sitio novo.
#pragma once
#include <Arduino.h>
#include "lgfx_config.h"
#include "cores.h"

constexpr int ANCHO_PANTALLA = 240;
constexpr int ALTO_PANTALLA  = 320;

class Pantalla {
public:
  VC_LGFX lcd;   // acceso directo a LovyanGFX (para quen queira ir máis aló)

  void iniciar();

  // --- Formas ---
  void encher(uint16_t cor);                                    // pinta toda a pantalla
  void punto(int x, int y, uint16_t cor);
  void recta(int x1, int y1, int x2, int y2, uint16_t cor);     // liña dun punto a outro
  void rectangulo(int x, int y, int ancho, int alto, uint16_t cor);  // recheo
  void marco(int x, int y, int ancho, int alto, uint16_t cor);       // só o bordo
  void circulo(int x, int y, int raio, uint16_t cor);                // recheo
  void circunferencia(int x, int y, int raio, uint16_t cor);         // só o bordo
  void triangulo(int x1, int y1, int x2, int y2, int x3, int y3, uint16_t cor);

  // --- Texto ---
  // tamano 1 = letras de 8 puntos, 2 = 16 puntos, 3 = 24 puntos...
  // Devolve a x onde remata o texto (para seguir escribindo ao lado).
  int texto(const char* txt, int x, int y, uint16_t cor = BRANCO,
            uint16_t fondo = NEGRO, int tamano = 2);
  int texto(const String& txt, int x, int y, uint16_t cor = BRANCO,
            uint16_t fondo = NEGRO, int tamano = 2);
  int texto(long numero, int x, int y, uint16_t cor = BRANCO,
            uint16_t fondo = NEGRO, int tamano = 2);
  int texto(int numero, int x, int y, uint16_t cor = BRANCO,
            uint16_t fondo = NEGRO, int tamano = 2) {
    return texto((long)numero, x, y, cor, fondo, tamano);
  }
  int texto(unsigned long numero, int x, int y, uint16_t cor = BRANCO,
            uint16_t fondo = NEGRO, int tamano = 2) {
    return texto((long)numero, x, y, cor, fondo, tamano);
  }
  // Escribe o texto centrado na horizontal.
  int texto_centrado(const char* txt, int y, uint16_t cor = BRANCO,
                     uint16_t fondo = NEGRO, int tamano = 2);
  int texto_centrado(const String& txt, int y, uint16_t cor = BRANCO,
                     uint16_t fondo = NEGRO, int tamano = 2);
  // Ancho en puntos que ocupa un texto.
  int ancho_texto(const char* txt, int tamano = 2);

  // --- Debuxos feitos con texto ---
  // Cada fila é un texto e cada carácter un cadradiño dunha cor:
  //   '.' ou ' ' = transparente (non se pinta)
  //   '0' negro   '1' branco  '2' vermello '3' laranxa '4' amarelo
  //   '5' verde   '6' azul    '7' morado   '8' rosa     '9' gris
  // Exemplo:
  //   const char* corazon[] = {
  //     ".22.22.",
  //     "2222222",
  //     ".22222.",
  //     "..222..",
  //     "...2...",
  //   };
  //   pantalla.debuxo(corazon, 100, 50, 4);   // cada cadradiño mide 4x4 puntos
  void debuxo(const char* const* mapa, int filas, int x, int y, int tamano = 1);
  template <size_t N>
  void debuxo(const char* (&mapa)[N], int x, int y, int tamano = 1) {
    debuxo(mapa, (int)N, x, y, tamano);
  }
  template <size_t N>
  void debuxo(const char* const (&mapa)[N], int x, int y, int tamano = 1) {
    debuxo(mapa, (int)N, x, y, tamano);
  }

  // Borra (pinta coa cor de fondo) o rectángulo que ocupa un debuxo.
  void borrar_debuxo(const char* const* mapa, int filas, int x, int y, int tamano,
                     uint16_t fondo);
  template <size_t N>
  void borrar_debuxo(const char* (&mapa)[N], int x, int y, int tamano, uint16_t fondo) {
    borrar_debuxo(mapa, (int)N, x, y, tamano, fondo);
  }
  template <size_t N>
  void borrar_debuxo(const char* const (&mapa)[N], int x, int y, int tamano, uint16_t fondo) {
    borrar_debuxo(mapa, (int)N, x, y, tamano, fondo);
  }

  // Cambia a cor dun número ('0'..'9') nos debuxos.
  void cor_do_debuxo(char caracter, uint16_t cor);

private:
  uint16_t _paleta[10] = {NEGRO, BRANCO, VERMELLO, LARANXA, AMARELO,
                          VERDE, AZUL, MORADO, ROSA, GRIS};
};

extern Pantalla pantalla;
