```markdown
# ESP32 Alarm Tag | جهاز إنذار ضد فقدان الهاتف

---

## 📌 الوصف | Description

**🇸🇦** جهاز صغير يعمل بـ **ESP32-C3 XIAO**، يستخدم البلوتوث (BLE) للتواصل مع الهاتف عبر تطبيق **RemoteXY**. عند فقدان الاتصال يصدر صوت إنذار قوي عبر بازر متصل بـ `GPIO4`. يمكن أيضًا تشغيل الإنذار يدويًا عبر زر في التطبيق.

**🇬🇧** A compact **ESP32-C3 XIAO** device using BLE to communicate with a phone via **RemoteXY**. When disconnected, it sounds a loud alarm through a buzzer on `GPIO4`. Manual alarm via app button.

---

## 🔧 القطع والتوصيل | Components & Wiring

| # | المكون | Component | التوصيل | Pin |
|---|-------|-----------|---------|-----|
| 1 | ESP32-C3 XIAO | ESP32-C3 XIAO | المتحكم الرئيسي | — |
| 2 | بازر | Buzzer | `BUZZER_PIN` | **GPIO 4** |
| 3 | LED حالة | Status LED | `STATUS_LED_PIN` | **GPIO 2** |
| 4 | زر | Push Button | عبر RemoteXY | — |
| 5 | بطارية 3.7V 110mAh | LiPo Battery | BAT+ / BAT- | خلف اللوحة |
| 6 | مفتاح | Slide Switch | ON/OFF | — |

> 🔋 البطارية تُشحن تلقائيًا عبر USB-C — لا حاجة لدائرة شحن خارجية.

---

## 📚 المكتبات | Libraries

| المكتبة | Library | الوصف | Description |
|---------|---------|-------|-------------|
| RemoteXY | RemoteXY | واجهة BLE | BLE interface |
| BLEDevice | BLEDevice | دعم البلوتوث | Bluetooth support |

```cpp
#define REMOTEXY_MODE__ESP32CORE_BLE
#include <BLEDevice.h>
#define REMOTEXY_BLUETOOTH_NAME "ESP32_Alarm_Tag"
#include <RemoteXY.h>
```

---

🧠 شرح العمل | How It Works

1️⃣ الاتصال → الجهاز يبث باسم ESP32_Alarm_Tag | Connection → broadcasts as ESP32_Alarm_Tag

2️⃣ التسليح → تفعيل مفتاح التسليح | Arming → enable arm switch

3️⃣ المراقبة → يتحقق من connect_flag باستمرار | Monitoring → checks connect_flag

4️⃣ الإنذار → انقطاع (4500Hz) / زر (6000Hz) | Alarm → disconnect (4500Hz) / button (6000Hz)

الحالة State الصوت Sound
STATE_IDLE خامل لا صوت —
STATE_ARMED_SAFE مسلّح وآمن لا صوت —
STATE_ALARM_MANUAL إنذار يدوي 6000Hz Manual
STATE_ALARM_DISCONNECTED انقطاع الاتصال 4500Hz Disconnected

🚀 التشغيل | Setup

1. ثبّت مكتبة RemoteXY | Install RemoteXY
2. اختر اللوحة XIAO_ESP32C3 | Select board
3. ارفع الكود | Upload code
4. اتصل من تطبيق RemoteXY | Connect via app
5. فعّل مفتاح التسليح | Enable arm switch

---

📁 هيكل المشروع | Project Structure

```text
ESP32_Alarm_Tag/
├── README.md
├── LICENSE
├── .gitignore
├── Code/
│   └── ESP32_ALARM_TAG.ino
├── circuit/
│   └── circuit.png
└── 3d_box/
    └── Smooth Snaget.stl
```



---

🛡️ الترخيص | License

المحتوى Content الرخصة License
💻 الكود Code MIT Open Source
🔩 الهاردوير Hardware CERN-OHL-P v2 Open Source
©️ الحقوق Copyright S8R © 2026 Reserved

⚠️ يُمنع الاستخدام التجاري من الآخرين. النشر مفتوح المصدر مسموح بشرط ذكر المؤلف.
⚠️ Commercial use by others is prohibited. Open-source distribution requires attribution.

راجع LICENSE للتفاصيل الكاملة | See LICENSE for full details.

---

👤 المطور والتواصل | Developer & Contact

 
المطور S8R
Developer S8R
الإصدار S8R.0K
Version S8R.0K
التاريخ 2026-10-07
Date 2026-10-07
اللوحة ESP32-C3 XIAO
Board ESP32-C3 XIAO

📬 التواصل | Contact
 

· 💬 Discord: [s8r](https://discord.gg/RgaZgfe483)
- 🐛 **الأعطال** | **Issues:** [GitHub Issues](../../issues)

---
