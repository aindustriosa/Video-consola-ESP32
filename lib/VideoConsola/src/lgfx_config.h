// lgfx_config.h - Configuración da librería LovyanGFX para a nosa pantalla.
// Non fai falla tocar nada aquí para programar xogos.
//
// O cristal da pantalla vai xirado 90 graos no módulo: por iso declaramos o panel
// como 320x240 e usamos a rotación 7, que dá unha pantalla vertical de 240x320.
#pragma once

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "pinos.h"

#define VC_ROTACION 7

class VC_LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9341 _panel;
  lgfx::Bus_SPI       _bus;

public:
  VC_LGFX() {
    {
      auto cfg = _bus.config();
      cfg.spi_host    = SPI2_HOST;
      cfg.spi_mode    = 0;
      cfg.freq_write  = 20000000;   // 20 MHz: con máis velocidade algúns módulos fallan
      cfg.freq_read   = 16000000;
      cfg.spi_3wire   = false;
      cfg.use_lock    = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      cfg.pin_sclk    = VC_PIN_SCK;
      cfg.pin_mosi    = VC_PIN_MOSI;
      cfg.pin_miso    = -1;
      cfg.pin_dc      = VC_PIN_DC;
      _bus.config(cfg);
      _panel.setBus(&_bus);
    }
    {
      auto cfg = _panel.config();
      cfg.pin_cs          = VC_PIN_CS;
      cfg.pin_rst         = VC_PIN_RST;
      cfg.pin_busy        = -1;
      cfg.panel_width     = 320;
      cfg.panel_height    = 240;
      cfg.memory_width    = 320;
      cfg.memory_height   = 240;
      cfg.offset_x        = 0;
      cfg.offset_y        = 0;
      cfg.offset_rotation = 0;
      cfg.readable        = false;
      cfg.invert          = false;
      cfg.rgb_order       = true;
      cfg.dlen_16bit      = false;
      cfg.bus_shared      = false;
      _panel.config(cfg);
    }
    setPanel(&_panel);
  }
};
