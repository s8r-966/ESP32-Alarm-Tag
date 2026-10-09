
/*
 *  ____________________________________________________
 * |                                                    |
 * |    ███████╗  █████╗  ██████╗                       |
 * |    ██╔════╝ ██╔══██╗ ██╔══██╗                      |
 * |    ███████╗ ╚█████╔╝ ██████╔╝                      |
 * |    ╚════██║ ██╔══██╗ ██╔══██╗                      |
 * |    ███████║ ╚█████╔╝ ██║  ██║                      |
 * |    ╚══════╝  ╚════╝  ╚═╝  ╚═╝                      |
 * |                                                    |
 * |  PROJECT   : ESP32_ALARM_TAG                       |
 * |  VERSION   : S8R.0K                                |
 * |  DEVELOPER : S8R                                   |
 * |  DATE      : 2026-10-07                            |
 * |____________________________________________________|
 */

 
#define REMOTEXY_MODE__ESP32CORE_BLE
#include <BLEDevice.h>
#define REMOTEXY_BLUETOOTH_NAME "ESP32_Alarm_Tag"
#include <RemoteXY.h>

// ============== إعدادات الأطراف ==============
#define BUZZER_PIN 4
#define STATUS_LED_PIN 2 // LED حالة الاتصال

// ============== إعدادات النغمات القوية ==============
#define TONE_ALARM 6000 // أعلى صوت ممكن
#define TONE_DISCONNECTED 4500 // نغمة قوية لفصل الاتصال

// RemoteXY GUI configuration
#pragma pack(push, 1)
uint8_t const PROGMEM RemoteXY_CONF_PROGMEM[] =
{ 255,2,0,1,0,63,0,19,0,0,0,0,31,1,106,200,1,1,3,0,
1,39,82,24,24,0,1,31,0,2,30,31,44,22,0,2,26,31,31,216,
170,216,180,216,186,217,138,217,132,0,216,167,216,186,217,132,216,167,217,130,
0,70,43,132,18,18,16,26,37,0 };

struct {
uint8_t alarm_btn;
uint8_t arm_switch;
uint8_t alarm_led;
uint8_t connect_flag;
} RemoteXY;
#pragma pack(pop)

// ============== متغيرات الحالة ==============
enum AlarmState {
STATE_IDLE,
STATE_ARMED_SAFE,
STATE_ALARM_MANUAL,
STATE_ALARM_DISCONNECTED
};

AlarmState currentState = STATE_IDLE;

// ============== تحديد الحالة ==============
void updateState() {

if (!RemoteXY.connect_flag) {
currentState = STATE_ALARM_DISCONNECTED;
return;
}

if (!RemoteXY.arm_switch) {
currentState = STATE_IDLE;
return;
}

currentState = (RemoteXY.alarm_btn) ? STATE_ALARM_MANUAL : STATE_ARMED_SAFE;
}

void updateBuzzer() {

switch (currentState) {

case STATE_IDLE:
case STATE_ARMED_SAFE:
noTone(BUZZER_PIN);
break;

case STATE_ALARM_MANUAL:
tone(BUZZER_PIN, TONE_ALARM);
 break;

case STATE_ALARM_DISCONNECTED:
tone(BUZZER_PIN, TONE_DISCONNECTED);
break;
}
}

// ============== تحديث المؤشرات ==============
void updateIndicators() {

RemoteXY.alarm_led = (currentState == STATE_ALARM_MANUAL ||
currentState == STATE_ALARM_DISCONNECTED) ? 1 : 0;

digitalWrite(STATUS_LED_PIN, RemoteXY.connect_flag ? HIGH : LOW);
}

// ============== Setup ==============
void setup() {
pinMode(BUZZER_PIN, OUTPUT);
pinMode(STATUS_LED_PIN, OUTPUT);
digitalWrite(STATUS_LED_PIN, LOW);

RemoteXY_Init();
}

// ============== Loop ==============
void loop() {
RemoteXY_Handler();

updateState();
updateBuzzer();
updateIndicators();
}