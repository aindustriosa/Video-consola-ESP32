// fonte.h - Letra propia de 8x8 puntos (2 bits por punto).
#pragma once
#include <stdint.h>

namespace vc {

struct Glifo {
  uint16_t cp;         // código Unicode do carácter
  uint16_t filas[8];   // 8 filas, 2 bits por punto
};

extern const Glifo FONTE_GLIFOS[];
extern const int   FONTE_N;

// Devolve as 8 filas do carácter (ou un espazo se non o temos).
const uint16_t* glifo(uint32_t cp);

}  // namespace vc
