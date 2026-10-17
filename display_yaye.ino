#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

constexpr int8_t TFT_SCK_PIN = 15;
constexpr int8_t TFT_MOSI_PIN = 2;
constexpr int8_t TFT_DC_PIN = 27;
constexpr int8_t TFT_CS_PIN = -1;
constexpr int8_t TFT_RST_PIN = -1;
constexpr uint8_t TFT_ROTATION = 1;

constexpr uint16_t COLOR_BG = 0x0000;
constexpr uint16_t COLOR_TEXT = 0xFFFF;

SPIClass tftSpi(HSPI);
Adafruit_ILI9341 tft(&tftSpi, TFT_DC_PIN, TFT_CS_PIN, TFT_RST_PIN);

void setup() {
  tftSpi.begin(TFT_SCK_PIN, -1, TFT_MOSI_PIN, -1);
  tft.begin(20000000);
  tft.setRotation(TFT_ROTATION);
  tft.fillScreen(COLOR_BG);

  const char* message = "Display yaye";

  tft.setTextSize(4);
  tft.setTextColor(COLOR_TEXT, COLOR_BG);

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;
  tft.getTextBounds(message, 0, 0, &x1, &y1, &w, &h);

  tft.setCursor((tft.width() - w) / 2 - x1, (tft.height() - h) / 2 - y1);
  tft.print(message);
}

void loop() {
}
