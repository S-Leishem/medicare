#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <Wire.h>
#include <time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

const char* WIFI_SSID = "Soubam";
const char* WIFI_PASSWORD = "Linlin@1";

const char* NTP_SERVER_1 = "pool.ntp.org";
const char* NTP_SERVER_2 = "time.nist.gov";

const long GMT_OFFSET_SECONDS = 19800;
const int DAYLIGHT_OFFSET_SECONDS = 0;

constexpr uint16_t WEB_SERVER_PORT = 5500;

constexpr uint8_t SERVO_PINS[3] = {18, 19, 23};
constexpr uint8_t LED_PINS[3] = {13, 14, 33};

constexpr uint8_t MEDICINE_BUZZER_PIN = 25;
constexpr uint8_t SOS_BUZZER_PIN = 26;

constexpr uint8_t RGB_RED_PIN = 32;
constexpr uint8_t RGB_GREEN_PIN = 15;
constexpr uint8_t RGB_BLUE_PIN = 2;

constexpr uint8_t SOS_BUTTON_PIN = 27;
constexpr uint8_t STOP_BUTTON_PINS[3] = {4, 5, 12};

constexpr uint8_t OLED_SDA_PIN = 21;
constexpr uint8_t OLED_SCL_PIN = 22;
constexpr uint8_t OLED_ADDRESS = 0x3C;

constexpr bool STOP_BUTTON_ACTIVE_LOW = true;
constexpr bool SOS_BUTTON_ACTIVE_LOW = true;
constexpr bool RGB_COMMON_CATHODE = true;

constexpr int CLOSED_ANGLE = 0;
constexpr int OPEN_ANGLE = 180;
constexpr uint16_t SERVO_STEP_INTERVAL_MS = 15;
constexpr uint8_t SERVO_STEP_DEGREES = 3;

constexpr uint16_t BUTTON_DEBOUNCE_MS = 40;
constexpr uint32_t SOS_LONG_PRESS_MS = 3000;

const char* NAMES[3] = {"Morning", "Afternoon", "Night"};

struct Schedule {
  bool enabled;
  uint8_t hour;
  uint8_t minute;
  int32_t lastFiredDay;
};

struct Compartment {
  Servo servo;
  bool ringing;
  int angle;
  int target;
  uint32_t lastStep;
  uint32_t ringStart;
};

Schedule schedules[3] = {
  {true, 8, 0, -1},
  {true, 13, 0, -1},
  {true, 20, 0, -1}
};

Compartment compartments[3];

WebServer server(WEB_SERVER_PORT);
Preferences prefs;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

bool displayOk = false;
bool networkStarted = false;
uint32_t lastWiFiAttempt = 0;
uint32_t lastDisplay = 0;
uint32_t lastDisplayCheck = 0;
int lastDrawnSecond = -1;
uint32_t lastScheduleCheck = 0;
uint32_t lastSerial = 0;

bool sosActive = false;
bool sosButtonPressed = false;
bool sosLongPressHandled = false;
uint32_t sosButtonDownAt = 0;
uint32_t lastSosButtonChange = 0;
uint32_t lastSosBlink = 0;
bool sosBlinkState = false;

bool stopButtonStable[3] = {false, false, false};
bool stopButtonLastRaw[3] = {false, false, false};
uint32_t stopButtonLastChange[3] = {0, 0, 0};

const char PAGE[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8"><meta name="viewport" content="width=device-width, initial-scale=1">
<title>DailyMed | Settings</title>
<style>
:root{font-family:system-ui,-apple-system,Segoe UI,sans-serif;color:#183346;background:#eef5f7}*{box-sizing:border-box}body{margin:0}.wrap{max-width:940px;margin:auto;padding:28px 18px}header{display:flex;align-items:center;justify-content:space-between;gap:16px;flex-wrap:wrap;margin-bottom:22px}.brand{font-size:1.5rem;font-weight:800}.muted{color:#647786;font-size:.9rem}.badge{background:#e2f7ef;color:#126d52;padding:9px 13px;border-radius:40px;font-size:.85rem}.badge.off{background:#fde8ea;color:#b52732}.grid{display:grid;grid-template-columns:repeat(3,minmax(0,1fr));gap:16px}.card{background:white;border:1px solid #dce9ed;border-radius:18px;padding:22px;box-shadow:0 7px 24px #15374c0a}.card h2{font-size:1.1rem;margin:0 0 6px}.pill{font-size:.78rem;background:#e7f5f6;color:#16767a;border-radius:20px;padding:4px 9px;display:inline-block;margin-bottom:16px}label{display:block;font-weight:600;font-size:.88rem;margin:14px 0 6px}input[type=time]{width:100%;padding:11px;border:1px solid #c9d8de;border-radius:10px;font:inherit;background:#fff}.toggle{display:flex;align-items:center;gap:8px;margin-top:14px}.toggle label{margin:0}.toggle input{accent-color:#087e85;width:18px;height:18px}.btn{border:0;background:#087e85;color:white;border-radius:10px;padding:12px 15px;font-weight:700;cursor:pointer;width:100%;margin-top:18px}.btn:hover{background:#06676d}.btn.secondary{background:#e7f3f5;color:#11666b}.btn.secondary:hover{background:#d5eaee}.btn.danger{background:#c9303b}.btn.danger:hover{background:#a82630}.status{margin-top:14px;min-height:22px;font-size:.9rem}.error{color:#b52732}.success{color:#12704c}.row{display:flex;gap:12px;flex-wrap:wrap}.row>*{flex:1}.info{margin:0 0 20px;line-height:1.55}.foot{margin-top:22px}.small{font-size:.82rem;line-height:1.5}.sos{margin-bottom:18px}.state-on{color:#b52732;font-weight:700}@media(max-width:750px){.grid{grid-template-columns:1fr}.wrap{padding:18px 14px}}
</style>
</head>
<body><main class="wrap">
<header><div><div class="brand">DailyMed</div><div class="muted">Medicine schedule &amp; compartment settings</div></div><span class="badge" id="connection">Checking connection…</span></header>
<section class="card" style="margin-bottom:18px"><h2>Device status</h2><p class="info muted">Device time: <strong id="deviceTime">Loading…</strong><br>Web server: <strong id="deviceHost"></strong><br>SOS alarm: <strong id="sosState">OFF</strong></p><div class="row"><button class="btn secondary" style="margin-top:0" id="refresh">Refresh status</button><button class="btn danger" style="margin-top:0" id="sosOn">Trigger SOS</button><button class="btn secondary" style="margin-top:0" id="sosOff">Stop SOS</button></div></section>
<div class="grid" id="compartments"></div>
<section class="card foot"><h2>How it works</h2><p class="small muted">set the timer and check yourself</p></section>
</main>
<script>
const names=['Morning','Afternoon','Night'];
const grid=document.getElementById('compartments');
const pad=n=>String(n).padStart(2,'0');
let built=false,baseMs=null,basePerf=0;
function fmt(ms){const d=new Date(ms);let h=d.getUTCHours();const ap=h>=12?'PM':'AM';h=h%12||12;return d.getUTCFullYear()+'-'+pad(d.getUTCMonth()+1)+'-'+pad(d.getUTCDate())+' '+pad(h)+':'+pad(d.getUTCMinutes())+':'+pad(d.getUTCSeconds())+' '+ap;}
function tick(){if(baseMs===null)return;document.getElementById('deviceTime').textContent=fmt(baseMs+performance.now()-basePerf);}
setInterval(tick,200);
function build(items){grid.innerHTML=items.map((c,i)=>`<section class="card"><h2>Compartment ${i+1}</h2><span class="pill">${names[i]}</span><div class="muted small">Status: <strong id="state-${i}">idle</strong></div><form class="alarm" data-index="${i}"><div class="toggle"><input id="enabled-${i}" name="enabled" type="checkbox" ${c.enabled?'checked':''}><label for="enabled-${i}">Enable daily reminder</label></div><label for="time-${i}">Reminder time</label><input id="time-${i}" name="time" type="time" value="${pad(c.hour)}:${pad(c.minute)}" required><p class="small muted">for every timer compartment</p><p class="small muted">Timer set twbiyo guli chaba kwdanaba</p><button class="btn" type="submit">Save timer</button><div class="row"><button class="btn secondary test" type="button" data-index="${i}">Test</button><button class="btn secondary stop" type="button" data-index="${i}">Stop</button></div><div class="status" id="status-${i}"></div></form></section>`).join('');built=true;}
function status(i,message,ok){const el=document.getElementById('status-'+i);if(!el)return;el.textContent=message;el.className='status '+(ok?'success':'error');}
async function getConfig(){const res=await fetch('/api/config',{cache:'no-store'});if(!res.ok)throw new Error('HTTP '+res.status);return res.json();}
async function load(){document.getElementById('deviceHost').textContent=location.host;const badge=document.getElementById('connection');try{const data=await getConfig();badge.textContent='● DailyMed connected';badge.className='badge';if(data.epoch>0){const nb=data.epoch*1000+500;if(baseMs===null||Math.abs(baseMs+performance.now()-basePerf-nb)>1500){baseMs=nb;basePerf=performance.now();}tick();}else{baseMs=null;document.getElementById('deviceTime').textContent='Not synchronized';}const sos=document.getElementById('sosState');sos.textContent=data.sosActive?'ACTIVE':'OFF';sos.className=data.sosActive?'state-on':'';if(!built)build(data.compartments);data.compartments.forEach((c,i)=>{const s=document.getElementById('state-'+i);if(s)s.textContent=c.state;});}catch(e){badge.textContent='● DailyMed not connected';badge.className='badge off';baseMs=null;document.getElementById('deviceTime').textContent='Unavailable';}}
grid.addEventListener('submit',async e=>{if(!e.target.matches('form.alarm'))return;e.preventDefault();const f=e.target,i=Number(f.dataset.index),[hour,minute]=f.elements.time.value.split(':').map(Number);const p=new URLSearchParams({index:String(i),hour:String(hour),minute:String(minute),enabled:f.elements.enabled.checked?'1':'0'});status(i,'Saving…',true);try{const r=await fetch('/set?'+p.toString());if(!r.ok)throw new Error('HTTP '+r.status);status(i,'Saved on DailyMed ✓',true);}catch(err){status(i,'Could not save. Check the connection.',false);}});
grid.addEventListener('click',async e=>{const t=e.target.closest('.test'),s=e.target.closest('.stop');if(t){const i=Number(t.dataset.index);if(!confirm('Activate compartment '+(i+1)+' now? Make sure it is safe to move.'))return;try{const r=await fetch('/activate?index='+i);if(!r.ok)throw new Error();status(i,'Test started ✓',true);load();}catch(err){status(i,'Unable to start test.',false);}}if(s){const i=Number(s.dataset.index);try{const r=await fetch('/stop?index='+i);if(!r.ok)throw new Error();status(i,'Stopped ✓',true);load();}catch(err){status(i,'Unable to stop.',false);}}});
document.getElementById('sosOn').addEventListener('click',async()=>{await fetch('/sos?active=1');load();});
document.getElementById('sosOff').addEventListener('click',async()=>{await fetch('/sos?active=0');load();});
document.getElementById('refresh').addEventListener('click',load);
load();setInterval(load,2000);
</script></body></html>)rawliteral";

String two(int value) {
  return value < 10 ? "0" + String(value) : String(value);
}

bool getNow(struct tm& timeInfo) {
  if (time(nullptr) < 1609459200) {
    return false;
  }
  return getLocalTime(&timeInfo, 10);
}

String timeText(const struct tm& t) {
  int hour = t.tm_hour % 12;
  if (hour == 0) {
    hour = 12;
  }
  return two(hour) + ":" + two(t.tm_min) + ":" + two(t.tm_sec);
}

const char* meridiem(const struct tm& t) {
  return t.tm_hour >= 12 ? "PM" : "AM";
}

String dateText(const struct tm& t) {
  return String(t.tm_year + 1900) + "-" + two(t.tm_mon + 1) + "-" + two(t.tm_mday);
}

String getIpAddress() {
  if (WiFi.status() != WL_CONNECTED) {
    return "Not connected";
  }
  return WiFi.localIP().toString();
}

String getLinkText() {
  return getIpAddress() + ":" + String(WEB_SERVER_PORT);
}

bool readStopButtonRaw(uint8_t index) {
  int value = digitalRead(STOP_BUTTON_PINS[index]);
  return STOP_BUTTON_ACTIVE_LOW ? value == LOW : value == HIGH;
}

bool readButtonRaw() {
  int value = digitalRead(SOS_BUTTON_PIN);
  return SOS_BUTTON_ACTIVE_LOW ? value == LOW : value == HIGH;
}

void setRgb(bool red, bool green, bool blue) {
  bool on = RGB_COMMON_CATHODE ? HIGH : LOW;
  bool off = RGB_COMMON_CATHODE ? LOW : HIGH;
  digitalWrite(RGB_RED_PIN, red ? on : off);
  digitalWrite(RGB_GREEN_PIN, green ? on : off);
  digitalWrite(RGB_BLUE_PIN, blue ? on : off);
}

bool anyRinging() {
  for (uint8_t i = 0; i < 3; i++) {
    if (compartments[i].ringing) {
      return true;
    }
  }
  return false;
}

String stateName(uint8_t index) {
  Compartment& c = compartments[index];
  if (c.ringing) {
    return c.angle == OPEN_ANGLE ? "waiting for you" : "opening";
  }
  if (c.angle != CLOSED_ANGLE) {
    return "closing";
  }
  return "idle";
}

void loadSchedules() {
  prefs.begin("medibox", false);
  for (uint8_t i = 0; i < 3; i++) {
    String suffix = String(i);
    schedules[i].enabled = prefs.getBool(("en" + suffix).c_str(), schedules[i].enabled);
    schedules[i].hour = prefs.getUChar(("h" + suffix).c_str(), schedules[i].hour);
    schedules[i].minute = prefs.getUChar(("m" + suffix).c_str(), schedules[i].minute);
  }
}

void saveSchedule(uint8_t index) {
  String suffix = String(index);
  prefs.putBool(("en" + suffix).c_str(), schedules[index].enabled);
  prefs.putUChar(("h" + suffix).c_str(), schedules[index].hour);
  prefs.putUChar(("m" + suffix).c_str(), schedules[index].minute);
}

void startAlarm(uint8_t index) {
  Compartment& c = compartments[index];
  if (c.ringing) {
    return;
  }
  c.ringing = true;
  c.ringStart = millis();
  c.target = OPEN_ANGLE;
  digitalWrite(LED_PINS[index], HIGH);
}

void stopAlarm(uint8_t index) {
  Compartment& c = compartments[index];
  if (!c.ringing) {
    return;
  }
  c.ringing = false;
  c.target = CLOSED_ANGLE;
  digitalWrite(LED_PINS[index], LOW);
}

void updateServo(uint8_t index) {
  Compartment& c = compartments[index];
  if (c.angle == c.target) {
    return;
  }
  if (millis() - c.lastStep < SERVO_STEP_INTERVAL_MS) {
    return;
  }
  c.lastStep = millis();
  if (c.angle < c.target) {
    c.angle = min(c.angle + (int)SERVO_STEP_DEGREES, c.target);
  } else {
    c.angle = max(c.angle - (int)SERVO_STEP_DEGREES, c.target);
  }
  c.servo.write(c.angle);
}

void updateMedicineBuzzer() {
  bool on = anyRinging() && ((millis() / 400) % 2 == 0);
  digitalWrite(MEDICINE_BUZZER_PIN, on ? HIGH : LOW);
}

void updateSosOutputs() {
  if (!sosActive) {
    digitalWrite(SOS_BUZZER_PIN, LOW);
    setRgb(false, false, false);
    return;
  }
  digitalWrite(SOS_BUZZER_PIN, HIGH);
  if (millis() - lastSosBlink >= 400) {
    lastSosBlink = millis();
    sosBlinkState = !sosBlinkState;
  }
  setRgb(sosBlinkState, false, false);
}

void startSos() {
  sosActive = true;
  sosLongPressHandled = false;
}

void stopSos() {
  sosActive = false;
  sosLongPressHandled = false;
  digitalWrite(SOS_BUZZER_PIN, LOW);
  setRgb(false, false, false);
}

void processStopButtons() {
  for (uint8_t i = 0; i < 3; i++) {
    bool raw = readStopButtonRaw(i);

    if (raw != stopButtonLastRaw[i]) {
      stopButtonLastRaw[i] = raw;
      stopButtonLastChange[i] = millis();
    }

    if (millis() - stopButtonLastChange[i] < BUTTON_DEBOUNCE_MS || raw == stopButtonStable[i]) {
      continue;
    }

    stopButtonStable[i] = raw;

    if (stopButtonStable[i]) {
      stopAlarm(i);
    }
  }
}

void processSosButton() {
  bool raw = readButtonRaw();

  if (raw != sosButtonPressed) {
    if (millis() - lastSosButtonChange < BUTTON_DEBOUNCE_MS) {
      return;
    }

    lastSosButtonChange = millis();
    sosButtonPressed = raw;

    if (sosButtonPressed) {
      sosButtonDownAt = millis();
      sosLongPressHandled = false;
    } else if (!sosLongPressHandled && millis() - sosButtonDownAt < SOS_LONG_PRESS_MS) {
      startSos();
    }
  }

  if (sosButtonPressed && !sosLongPressHandled && millis() - sosButtonDownAt >= SOS_LONG_PRESS_MS) {
    stopSos();
    sosLongPressHandled = true;
  }
}

void processSchedules() {
  if (millis() - lastScheduleCheck < 500) {
    return;
  }
  lastScheduleCheck = millis();

  struct tm t;
  if (!getNow(t)) {
    return;
  }

  int32_t today = (t.tm_year + 1900) * 1000 + t.tm_yday;

  for (uint8_t i = 0; i < 3; i++) {
    Schedule& s = schedules[i];
    if (!s.enabled || s.lastFiredDay == today) {
      continue;
    }
    if (t.tm_hour == s.hour && t.tm_min == s.minute) {
      s.lastFiredDay = today;
      startAlarm(i);
    }
  }
}

void updateDisplay() {
  if (!displayOk || millis() - lastDisplayCheck < 50) {
    return;
  }
  lastDisplayCheck = millis();

  struct tm t;
  bool synced = getNow(t);
  bool idle = !sosActive && !anyRinging() && WiFi.status() == WL_CONNECTED;

  if (idle && synced) {
    if (t.tm_sec == lastDrawnSecond) {
      return;
    }
    lastDrawnSecond = t.tm_sec;
  } else {
    if (millis() - lastDisplay < 500) {
      return;
    }
    lastDrawnSecond = -1;
  }

  lastDisplay = millis();

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  if (sosActive) {
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("SOS ACTIVE");
    display.setTextSize(1);
    display.setCursor(0, 30);
    display.println("Hold button 3 sec");
    display.println("or stop from web");
  } else if (anyRinging()) {
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("MEDICINE");
    display.println("TIME!");
    display.setTextSize(1);
    display.setCursor(0, 40);
    for (uint8_t i = 0; i < 3; i++) {
      if (compartments[i].ringing) {
        display.print(NAMES[i]);
        display.print(" ");
      }
    }
    display.setCursor(0, 54);
    display.print("Hand near sensor");
  } else if (WiFi.status() != WL_CONNECTED) {
    display.setCursor(0, 0);
    display.println("Connecting WiFi...");
  } else {
    if (synced) {
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.print(timeText(t));
      display.setTextSize(1);
      display.setCursor(102, 7);
      display.print(meridiem(t));
      display.setCursor(0, 20);
      display.print(dateText(t));
    } else {
      display.setCursor(0, 0);
      display.println("Syncing time...");
    }
    display.setCursor(0, 40);
    display.print("Open in browser:");
    display.setCursor(0, 53);
    display.print(getLinkText());
  }

  display.display();
}

int indexArg() {
  if (!server.hasArg("index")) {
    return -1;
  }
  int index = server.arg("index").toInt();
  return (index >= 0 && index < 3) ? index : -1;
}

void handleRoot() {
  server.send_P(200, "text/html", PAGE);
}

void handleConfig() {
  struct tm t;
  bool ok = getNow(t);

  String json = "{\"time\":\"";
  json += ok ? dateText(t) + " " + timeText(t) + " " + meridiem(t) : String("Not synchronized");
  json += "\",\"epoch\":" + String(ok ? (long)(time(nullptr) + GMT_OFFSET_SECONDS) : 0L);
  json += ",\"ip\":\"" + getIpAddress() + "\",\"sosActive\":";
  json += sosActive ? "true" : "false";
  json += ",\"compartments\":[";

  for (uint8_t i = 0; i < 3; i++) {
    if (i > 0) {
      json += ",";
    }
    json += "{\"enabled\":";
    json += schedules[i].enabled ? "true" : "false";
    json += ",\"hour\":" + String(schedules[i].hour);
    json += ",\"minute\":" + String(schedules[i].minute);
    json += ",\"state\":\"" + stateName(i) + "\"}";
  }

  json += "]}";
  server.send(200, "application/json", json);
}

void handleSet() {
  int index = indexArg();
  if (index < 0 || !server.hasArg("hour") || !server.hasArg("minute")) {
    server.send(400, "text/plain", "Invalid request");
    return;
  }

  schedules[index].hour = constrain(server.arg("hour").toInt(), 0, 23);
  schedules[index].minute = constrain(server.arg("minute").toInt(), 0, 59);
  schedules[index].enabled = server.hasArg("enabled") && server.arg("enabled") == "1";
  schedules[index].lastFiredDay = -1;

  saveSchedule(index);
  server.send(200, "application/json", "{\"ok\":true}");
}

void handleActivate() {
  int index = indexArg();
  if (index < 0) {
    server.send(400, "text/plain", "Invalid compartment");
    return;
  }
  startAlarm(index);
  server.send(200, "application/json", "{\"ok\":true}");
}

void handleStop() {
  int index = indexArg();
  if (index < 0) {
    server.send(400, "text/plain", "Invalid compartment");
    return;
  }
  stopAlarm(index);
  server.send(200, "application/json", "{\"ok\":true}");
}

void handleSos() {
  if (server.hasArg("active") && server.arg("active") == "1") {
    startSos();
  } else {
    stopSos();
  }
  server.send(200, "application/json", "{\"ok\":true}");
}

void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}

void webTask(void* parameter) {
  for (;;) {
    server.handleClient();
    vTaskDelay(2 / portTICK_PERIOD_MS);
  }
}

void manageWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    if (!networkStarted) {
      configTime(GMT_OFFSET_SECONDS, DAYLIGHT_OFFSET_SECONDS, NTP_SERVER_1, NTP_SERVER_2);

      server.on("/", HTTP_GET, handleRoot);
      server.on("/api/config", HTTP_GET, handleConfig);
      server.on("/set", HTTP_GET, handleSet);
      server.on("/activate", HTTP_GET, handleActivate);
      server.on("/stop", HTTP_GET, handleStop);
      server.on("/sos", HTTP_GET, handleSos);
      server.onNotFound(handleNotFound);
      server.begin();
      xTaskCreatePinnedToCore(webTask, "web", 10240, nullptr, 1, nullptr, 0);

      networkStarted = true;

      Serial.print("Web page: http://");
      Serial.println(getLinkText());
    }
    return;
  }

  if (lastWiFiAttempt == 0 || millis() - lastWiFiAttempt >= 10000) {
    lastWiFiAttempt = millis();
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Connecting to WiFi...");
  }
}

void printSerialStatus() {
  if (millis() - lastSerial < 5000) {
    return;
  }
  lastSerial = millis();

  struct tm t;
  Serial.print("WiFi: ");
  Serial.print(WiFi.status() == WL_CONNECTED ? getLinkText() : String("connecting"));
  Serial.print(" | Time: ");
  Serial.println(getNow(t) ? dateText(t) + " " + timeText(t) + " " + meridiem(t) : String("not synced"));

  for (uint8_t i = 0; i < 3; i++) {
    Serial.print(NAMES[i]);
    Serial.print(": ");
    if (schedules[i].enabled) {
      Serial.print(two(schedules[i].hour) + ":" + two(schedules[i].minute));
    } else {
      Serial.print("off");
    }
    Serial.print(" (");
    Serial.print(stateName(i));
    Serial.println(")");
  }
}

void configurePins() {
  pinMode(MEDICINE_BUZZER_PIN, OUTPUT);
  pinMode(SOS_BUZZER_PIN, OUTPUT);
  digitalWrite(MEDICINE_BUZZER_PIN, LOW);
  digitalWrite(SOS_BUZZER_PIN, LOW);

  for (uint8_t i = 0; i < 3; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }

  pinMode(RGB_RED_PIN, OUTPUT);
  pinMode(RGB_GREEN_PIN, OUTPUT);
  pinMode(RGB_BLUE_PIN, OUTPUT);
  setRgb(false, false, false);

  pinMode(SOS_BUTTON_PIN, SOS_BUTTON_ACTIVE_LOW ? INPUT_PULLUP : INPUT);

  for (uint8_t i = 0; i < 3; i++) {
    pinMode(STOP_BUTTON_PINS[i], STOP_BUTTON_ACTIVE_LOW ? INPUT_PULLUP : INPUT);
  }
}

void configureServos() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  for (uint8_t i = 0; i < 3; i++) {
    compartments[i].servo.setPeriodHertz(50);
    compartments[i].servo.attach(SERVO_PINS[i], 500, 2400);
    compartments[i].ringing = false;
    compartments[i].angle = CLOSED_ANGLE;
    compartments[i].target = CLOSED_ANGLE;
    compartments[i].lastStep = millis();
    compartments[i].ringStart = 0;
    compartments[i].servo.write(CLOSED_ANGLE);
  }
}

void setup() {
  Serial.begin(115200);
  delay(300);

  configurePins();
  configureServos();
  loadSchedules();

  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
  Wire.setClock(400000);
  displayOk = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);

  WiFi.mode(WIFI_STA);

  for (uint8_t i = 0; i < 3; i++) {
    stopButtonLastRaw[i] = readStopButtonRaw(i);
    stopButtonStable[i] = stopButtonLastRaw[i];
    stopButtonLastChange[i] = millis();
  }
  sosButtonPressed = readButtonRaw();

  Serial.println("DailyMed ready.");
}

void loop() {
  manageWiFi();

  processStopButtons();
  processSosButton();
  processSchedules();

  for (uint8_t i = 0; i < 3; i++) {
    updateServo(i);
  }

  updateMedicineBuzzer();
  updateSosOutputs();
  updateDisplay();
  printSerialStatus();
}
