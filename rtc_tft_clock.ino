#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <RTClib.h>

constexpr int8_t TFT_SCK_PIN = 15;
constexpr int8_t TFT_MOSI_PIN = 2;
constexpr int8_t TFT_DC_PIN = 27;
constexpr int8_t TFT_CS_PIN = -1;
constexpr int8_t TFT_RST_PIN = -1;
constexpr uint8_t TFT_ROTATION = 1;

constexpr uint8_t I2C_SDA_PIN = 21;
constexpr uint8_t I2C_SCL_PIN = 22;

constexpr bool FORCE_SET_RTC_TO_COMPILE_TIME = false;

constexpr uint16_t COLOR_BG = 0x0000;
constexpr uint16_t COLOR_TEXT = 0xFFFF;
constexpr uint16_t COLOR_TEAL = 0x0BF0;
constexpr uint16_t COLOR_MUTED = 0x9CD3;
constexpr uint16_t COLOR_GREEN = 0x07E0;
constexpr uint16_t COLOR_RED = 0xF800;

const char* DAYS[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char* MONTHS[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

SPIClass tftSpi(HSPI);
Adafruit_ILI9341 tft(&tftSpi, TFT_DC_PIN, TFT_CS_PIN, TFT_RST_PIN);
RTC_DS3231 rtc;

bool rtcOk = false;
int lastSecond = -1;
uint32_t lastRead = 0;
uint32_t lastRtcAttempt = 0;
String fieldCache[8];

String two(int value) {
  return value < 10 ? "0" + String(value) : String(value);
}

void drawField(uint8_t slot, int x, int y, int w, int h, const String& text, uint8_t size, uint16_t fg, uint16_t bg) {
  String key = text + "|" + String(fg) + "|" + String(bg);
  if (fieldCache[slot] == key) {
    return;
  }
  fieldCache[slot] = key;
  tft.fillRect(x, y, w, h, bg);
  tft.setTextSize(size);
  tft.setTextColor(fg, bg);
  tft.setCursor(x, y);
  tft.print(text);
}

void drawLayout() {
  tft.fillScreen(COLOR_BG);
  tft.fillRect(0, 0, 320, 26, COLOR_TEAL);
  tft.setTextSize(2);
  tft.setTextColor(COLOR_TEXT, COLOR_TEAL);
  tft.setCursor(8, 5);
  tft.print("RTC Clock");
  tft.setTextSize(1);
  tft.setTextColor(COLOR_MUTED, COLOR_BG);
  tft.setCursor(8, 228);
  tft.print("DS3231 RTC | no WiFi");
  for (uint8_t i = 0; i < 8; i++) {
    fieldCache[i] = "";
  }
}

bool initRtc() {
  if (!rtc.begin()) {
    return false;
  }
  Wire.setClock(400000);
  if (FORCE_SET_RTC_TO_COMPILE_TIME || rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  return true;
}

void showError() {
  drawField(0, 212, 5, 104, 16, "No RTC", 2, COLOR_RED, COLOR_TEAL);
  drawField(1, 8, 50, 304, 24, "RTC NOT FOUND", 3, COLOR_RED, COLOR_BG);
  drawField(2, 8, 110, 304, 16, "Check the wiring:", 2, COLOR_TEXT, COLOR_BG);
  drawField(3, 8, 136, 304, 16, "SDA = GPIO 21", 2, COLOR_MUTED, COLOR_BG);
  drawField(4, 8, 158, 304, 16, "SCL = GPIO 22", 2, COLOR_MUTED, COLOR_BG);
  drawField(5, 8, 180, 304, 16, "VCC = 3.3V, GND = GND", 2, COLOR_MUTED, COLOR_BG);
}

void showTime(const DateTime& now) {
  int hour = now.hour() % 12;
  if (hour == 0) {
    hour = 12;
  }

  String timeText = two(hour) + ":" + two(now.minute()) + ":" + two(now.second());
  String dateText = String(now.day()) + " " + MONTHS[now.month() - 1] + " " + String(now.year());

  drawField(0, 212, 5, 104, 16, "RTC OK", 2, COLOR_GREEN, COLOR_TEAL);
  drawField(1, 8, 44, 240, 40, timeText, 5, COLOR_TEXT, COLOR_BG);
  drawField(2, 256, 58, 48, 24, now.hour() >= 12 ? "PM" : "AM", 3, COLOR_TEAL, COLOR_BG);
  drawField(3, 8, 108, 304, 24, DAYS[now.dayOfTheWeek()], 3, COLOR_TEXT, COLOR_BG);
  drawField(4, 8, 142, 304, 24, dateText, 3, COLOR_MUTED, COLOR_BG);
  drawField(5, 8, 190, 304, 16, "Temp: " + String(rtc.getTemperature(), 1) + " C", 2, COLOR_MUTED, COLOR_BG);

  Serial.print("Time: ");
  Serial.print(timeText);
  Serial.print(now.hour() >= 12 ? " PM  " : " AM  ");
  Serial.println(dateText);
}

void setup() {
  Serial.begin(115200);
  delay(300);

  tftSpi.begin(TFT_SCK_PIN, -1, TFT_MOSI_PIN, -1);
  tft.begin(20000000);
  tft.setRotation(TFT_ROTATION);

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  rtcOk = initRtc();

  drawLayout();

  if (!rtcOk) {
    Serial.println("RTC not found. Check wiring.");
  }
}

void loop() {
  if (!rtcOk) {
    showError();

    if (millis() - lastRtcAttempt >= 2000) {
      lastRtcAttempt = millis();
      if (initRtc()) {
        rtcOk = true;
        lastSecond = -1;
        drawLayout();
      }
    }
    return;
  }

  if (millis() - lastRead < 50) {
    return;
  }
  lastRead = millis();

  DateTime now = rtc.now();

  if (now.year() < 2020 || now.year() > 2099) {
    rtcOk = false;
    drawLayout();
    return;
  }

  if (now.second() == lastSecond) {
    return;
  }
  lastSecond = now.second();

  showTime(now);
}
