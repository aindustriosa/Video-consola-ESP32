// pinos.h - Onde está conectada cada cousa na placa da videoconsola.
// Os números son os GPIO reais do XIAO ESP32-C3 (entre parénteses, a etiqueta Dx).
#pragma once

// Pantalla TFT ILI9341 (bus SPI)
#define VC_PIN_SCK      8    // (D8)
#define VC_PIN_MOSI    10    // (D10)
#define VC_PIN_DC      21    // (D6)
#define VC_PIN_CS      20    // (D7)
#define VC_PIN_RST      5    // (D3)
#define VC_PIN_PANTALLA 9    // (D9) acende a pantalla a través dun transistor (ALTO = acesa)

// Botóns: chip PCF8574A conectado por I2C
#define VC_PIN_SDA      6    // (D4)
#define VC_PIN_SCL      7    // (D5)
#define VC_PIN_INT      3    // (D1) aviso do PCF8574A cando cambia un botón
#define VC_PCF8574_DIR  0x38 // enderezo I2C do PCF8574A (A0, A1 e A2 a GND)

// Zumbador (buzzer) pasivo
#define VC_PIN_ZUMBADOR 4    // (D2)

// Batería: divisor de tensión de dúas resistencias iguais (100k + 100k)
#define VC_PIN_BATERIA  2    // (D0)
