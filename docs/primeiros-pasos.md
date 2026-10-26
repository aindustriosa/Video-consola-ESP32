# Primeiros pasos

Podes programar a consola de dúas maneiras. Escolle unha.

## Opción A: VS Code + PlatformIO (recomendada)

1. Instala [VS Code](https://code.visualstudio.com/) e, dentro del, a extensión **PlatformIO IDE**.
2. Descarga este repositorio (botón verde **Code → Download ZIP**) e descomprímeo.
3. En VS Code: **File → Open Folder** e abre a carpeta do repositorio.
4. Conecta a consola co cable USB-C.
5. Preme a frecha **→ (Upload)** da barra de abaixo.

A primeira vez tarda un anaco porque descarga todo o necesario.

O teu programa está en `xogo/xogo.ino`. Para probar un exemplo, copia o seu
`.ino` de `lib/VideoConsola/examples/` dentro de `xogo/` (borrando o que había).

## Opción B: Arduino IDE

1. Instala o [Arduino IDE](https://www.arduino.cc/en/software).
2. En **Preferencias → URLs adicionais de xestor de placas**, engade:
   `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
3. En **Ferramentas → Placa → Xestor de placas**, instala **esp32** (de Espressif).
4. En **Ferramentas → Xestionar bibliotecas**, instala **LovyanGFX**.
5. Copia a carpeta `lib/VideoConsola` dentro da túa carpeta de bibliotecas de
   Arduino (normalmente `Documentos/Arduino/libraries/`).
6. Reinicia o Arduino IDE.
7. Escolle a placa **XIAO_ESP32C3** e o porto da consola.
8. Abre un exemplo en **Ficheiro → Exemplos → VideoConsola** e preme **Subir**.

## Se non grava

- **Non aparece o porto**: proba outro cable (algúns só cargan e non levan datos).
- **Falla ao gravar**: desconecta o USB, mantén premido o botón **BOOT** do XIAO,
  conecta o USB e solta o botón. Despois grava de novo.
- No Arduino IDE, baixa **Ferramentas → Upload Speed** a **115200**.

## Como é un programa

```cpp
#include <VideoConsola.h>   // trae pantalla, botons, son e consola

void setup() {
  // Execútase unha vez ao acender
  consola.iniciar();
}

void loop() {
  // Repítese sen parar
  botons.ler();
  // ... mover cousas, debuxar, facer sons ...
  consola.agardar(16);
}
```

Mira a [referencia do SDK](referencia.md) para ver todo o que podes facer.
