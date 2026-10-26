// cores.h - Cores listas para usar (formato RGB565 de 16 bits).
// Se queres outra cor, usa cor(vermello, verde, azul) con valores de 0 a 255.
#pragma once
#include <stdint.h>

constexpr uint16_t cor(uint8_t r, uint8_t g, uint8_t b) {
  return (uint16_t)(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

constexpr uint16_t NEGRO        = cor(0, 0, 0);
constexpr uint16_t BRANCO       = cor(255, 255, 255);
constexpr uint16_t GRIS         = cor(128, 128, 128);
constexpr uint16_t GRIS_ESCURO  = cor(64, 64, 64);
constexpr uint16_t VERMELLO     = cor(255, 0, 0);
constexpr uint16_t LARANXA      = cor(255, 140, 0);
constexpr uint16_t AMARELO      = cor(255, 230, 0);
constexpr uint16_t VERDE        = cor(0, 200, 0);
constexpr uint16_t VERDE_ESCURO = cor(0, 100, 0);
constexpr uint16_t CIAN         = cor(0, 230, 230);
constexpr uint16_t AZUL         = cor(0, 70, 255);
constexpr uint16_t AZUL_CEO     = cor(90, 170, 255);
constexpr uint16_t AZUL_ESCURO  = cor(0, 0, 110);
constexpr uint16_t MORADO       = cor(140, 0, 200);
constexpr uint16_t ROSA         = cor(255, 120, 180);
constexpr uint16_t MARRON       = cor(140, 80, 30);
