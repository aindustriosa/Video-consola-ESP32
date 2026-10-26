// pantalla.cpp - ver pantalla.h.
#include "pantalla.h"
#include "fonte.h"

Pantalla pantalla;

// Le o seguinte carácter dun texto UTF-8 (os acentos ocupan 2 bytes).
static uint32_t seguinte_caracter(const char*& p) {
  uint8_t b = (uint8_t)*p++;
  if (b < 0x80) return b;
  if ((b & 0xE0) == 0xC0) {
    uint8_t b2 = (uint8_t)*p;
    if ((b2 & 0xC0) == 0x80) { p++; return ((b & 0x1F) << 6) | (b2 & 0x3F); }
    return b;
  }
  if ((b & 0xF0) == 0xE0) {
    uint8_t b2 = (uint8_t)p[0], b3 = (uint8_t)p[1];
    if ((b2 & 0xC0) == 0x80 && (b3 & 0xC0) == 0x80) {
      p += 2; return ((b & 0x0F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
    }
  }
  return b;
}

static int conta_caracteres(const char* s) {
  int n = 0;
  for (; *s; ++s) if (((uint8_t)*s & 0xC0) != 0x80) n++;
  return n;
}

void Pantalla::iniciar() {
  lcd.init();
  lcd.setRotation(VC_ROTACION);

  // Axustes de cor (gamma) afinados a ollo para este modelo de pantalla.
  struct Orde { uint8_t cmd; uint8_t n; uint8_t datos[15]; };
  static const Orde ORDES[] = {
    {0xCF, 3, {0x00, 0xC1, 0x30}},
    {0xED, 4, {0x64, 0x03, 0x12, 0x81}},
    {0xE8, 3, {0x85, 0x00, 0x78}},
    {0xCB, 5, {0x39, 0x2C, 0x00, 0x34, 0x02}},
    {0xF7, 1, {0x20}},
    {0xEA, 2, {0x00, 0x00}},
    {0xC0, 1, {0x23}},
    {0xC1, 1, {0x10}},
    {0xC5, 2, {0x3E, 0x28}},
    {0xC7, 1, {0x86}},
    {0xB1, 2, {0x00, 0x18}},
    {0xF2, 1, {0x00}},
    {0x26, 1, {0x01}},
    {0xE0, 15, {0x0F,0x26,0x24,0x0B,0x0E,0x09,0x54,0xA8,0x46,0x0C,0x17,0x09,0x0F,0x07,0x00}},
    {0xE1, 15, {0x00,0x19,0x1B,0x04,0x10,0x07,0x2A,0x47,0x39,0x03,0x06,0x06,0x30,0x38,0x0F}},
  };
  lcd.startWrite();
  for (auto& o : ORDES) {
    lcd.writeCommand(o.cmd);
    for (int i = 0; i < o.n; i++) lcd.writeData(o.datos[i]);
  }
  lcd.endWrite();
  delay(20);
  encher(NEGRO);
}

void Pantalla::encher(uint16_t cor) { lcd.fillScreen(cor); }
void Pantalla::punto(int x, int y, uint16_t cor) { lcd.drawPixel(x, y, cor); }
void Pantalla::recta(int x1, int y1, int x2, int y2, uint16_t cor) { lcd.drawLine(x1, y1, x2, y2, cor); }

void Pantalla::rectangulo(int x, int y, int ancho, int alto, uint16_t cor) {
  if (ancho > 0 && alto > 0) lcd.fillRect(x, y, ancho, alto, cor);
}

void Pantalla::marco(int x, int y, int ancho, int alto, uint16_t cor) {
  if (ancho > 0 && alto > 0) lcd.drawRect(x, y, ancho, alto, cor);
}

void Pantalla::circulo(int x, int y, int raio, uint16_t cor) { lcd.fillCircle(x, y, raio, cor); }
void Pantalla::circunferencia(int x, int y, int raio, uint16_t cor) { lcd.drawCircle(x, y, raio, cor); }

void Pantalla::triangulo(int x1, int y1, int x2, int y2, int x3, int y3, uint16_t cor) {
  lcd.fillTriangle(x1, y1, x2, y2, x3, y3, cor);
}

int Pantalla::texto(const char* txt, int x, int y, uint16_t cor, uint16_t fondo, int tamano) {
  if (tamano < 1) tamano = 1;
  // Os 4 tons que van do fondo á cor (para que os bordos das letras queden suaves).
  int rc = (cor >> 11) & 0x1F, gc = (cor >> 5) & 0x3F, bc = cor & 0x1F;
  int rf = (fondo >> 11) & 0x1F, gf = (fondo >> 5) & 0x3F, bf = fondo & 0x1F;
  uint16_t ton[4];
  for (int k = 0; k < 4; k++) {
    int r = (rf * (3 - k) + rc * k) / 3;
    int g = (gf * (3 - k) + gc * k) / 3;
    int b = (bf * (3 - k) + bc * k) / 3;
    ton[k] = (uint16_t)((r << 11) | (g << 5) | b);
  }
  int lado = 8 * tamano;
  uint16_t* buf = (uint16_t*)malloc((size_t)lado * lado * 2);
  if (!buf) return x;
  lcd.setSwapBytes(true);
  const char* p = txt;
  while (*p) {
    const uint16_t* g = vc::glifo(seguinte_caracter(p));
    int i = 0;
    for (int fy = 0; fy < 8; fy++) {
      for (int ry = 0; ry < tamano; ry++) {
        for (int fx = 0; fx < 8; fx++) {
          uint16_t c = ton[(g[fy] >> (14 - 2 * fx)) & 3];
          for (int rx = 0; rx < tamano; rx++) buf[i++] = c;
        }
      }
    }
    lcd.pushImage(x, y, lado, lado, buf);
    lcd.waitDMA();   // agardar a que se envíe antes de reutilizar o buffer
    x += lado;
  }
  free(buf);
  return x;
}

int Pantalla::texto(const String& txt, int x, int y, uint16_t cor, uint16_t fondo, int tamano) {
  return texto(txt.c_str(), x, y, cor, fondo, tamano);
}

int Pantalla::texto(long numero, int x, int y, uint16_t cor, uint16_t fondo, int tamano) {
  char b[16];
  snprintf(b, sizeof(b), "%ld", numero);
  return texto(b, x, y, cor, fondo, tamano);
}

int Pantalla::ancho_texto(const char* txt, int tamano) {
  return conta_caracteres(txt) * 8 * tamano;
}

int Pantalla::texto_centrado(const char* txt, int y, uint16_t cor, uint16_t fondo, int tamano) {
  int x = (ANCHO_PANTALLA - ancho_texto(txt, tamano)) / 2;
  if (x < 0) x = 0;
  return texto(txt, x, y, cor, fondo, tamano);
}

int Pantalla::texto_centrado(const String& txt, int y, uint16_t cor, uint16_t fondo, int tamano) {
  return texto_centrado(txt.c_str(), y, cor, fondo, tamano);
}

void Pantalla::debuxo(const char* const* mapa, int filas, int x, int y, int tamano) {
  if (tamano < 1) tamano = 1;
  lcd.startWrite();
  for (int f = 0; f < filas; f++) {
    const char* fila = mapa[f];
    int c = 0;
    while (fila[c]) {
      char ch = fila[c];
      int ini = c;
      while (fila[c] == ch) c++;   // xunta os cadradiños seguidos da mesma cor
      if (ch >= '0' && ch <= '9') {
        lcd.fillRect(x + ini * tamano, y + f * tamano, (c - ini) * tamano, tamano,
                     _paleta[ch - '0']);
      }
    }
  }
  lcd.endWrite();
}

void Pantalla::borrar_debuxo(const char* const* mapa, int filas, int x, int y, int tamano,
                             uint16_t fondo) {
  int ancho = 0;
  for (int f = 0; f < filas; f++) {
    int n = strlen(mapa[f]);
    if (n > ancho) ancho = n;
  }
  rectangulo(x, y, ancho * tamano, filas * tamano, fondo);
}

void Pantalla::cor_do_debuxo(char caracter, uint16_t cor) {
  if (caracter >= '0' && caracter <= '9') _paleta[caracter - '0'] = cor;
}
