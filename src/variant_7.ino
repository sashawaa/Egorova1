/*
  Курсовой проект ПМ.02 — вариант 7
  Сценарий: платёжный терминал
  Датчики: NTC (0–80 °C), HC-SR04, SW
  Порог: температура > 40 °C; период опроса 3000 мс
  Примечание: преобразование NTC в этом учебном макете линейное.
  Для физического термистора следует использовать калибровочную таблицу
  или уравнение Стейнхарта—Харта, соответствующее конкретному датчику.
*/
const byte PIN_NTC = A0;
const byte PIN_TRIG = 2;
const byte PIN_ECHO = 3;
const byte PIN_SWITCH = 4;
const byte PIN_RELAY = 5;
const byte PIN_LED = 6;

const unsigned long PERIOD_MS = 3000UL;
const float S1_MIN = 0.0;
const float S1_MAX = 80.0;
const float THRESHOLD_C = 40.0;
const float S2_MIN = 2.0;
const float S2_MAX = 400.0;

unsigned long lastSample = 0;
unsigned long n = 0;
bool alarmActive = false;

float readS1() {
  int raw = analogRead(PIN_NTC);
  // Учебное допущение из методички: линейное отображение 0..1023 в 0..80 °C.
  return S1_MIN + (S1_MAX - S1_MIN) * raw / 1023.0;
}

float readS2() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  unsigned long duration = pulseIn(PIN_ECHO, HIGH, 30000UL);
  if (duration == 0) return 400.0; // эхо не получено: безопасное верхнее значение
  float cm = duration * 0.0343 / 2.0;
  if (cm < S2_MIN || cm > S2_MAX) return -1.0; // маркер вне диапазона
  return cm;
}

int readS3() {
  // INPUT_PULLUP: замкнутый на GND контакт даёт LOW.
  // Инверсия формирует логическое значение 1 при открытой крышке.
  return digitalRead(PIN_SWITCH) == LOW ? 1 : 0;
}

void actuatorOn() {
  digitalWrite(PIN_RELAY, HIGH);
  digitalWrite(PIN_LED, HIGH);
}

void actuatorOff() {
  digitalWrite(PIN_RELAY, LOW);
  digitalWrite(PIN_LED, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_SWITCH, INPUT_PULLUP);
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  actuatorOff();
  digitalWrite(PIN_TRIG, LOW);
}

void loop() {
  unsigned long now = millis();
  if (now - lastSample < PERIOD_MS) return;
  lastSample = now;
  ++n;

  float s1 = readS1();
  float s2 = readS2();
  int s3 = readS3();

  Serial.print("DATA n=");
  Serial.print(n);
  Serial.print(" s1=");
  Serial.print(s1, 2);
  Serial.print(" s2=");
  Serial.print(s2, 1);
  Serial.print(" s3=");
  Serial.println(s3);

  bool overheat = s1 > THRESHOLD_C;
  if (overheat && !alarmActive) {
    alarmActive = true;
    actuatorOn();
    Serial.print("EVENT n=");
    Serial.print(n);
    Serial.println(" type=THRESHOLD");
  } else if (!overheat && alarmActive) {
    alarmActive = false;
    actuatorOff();
    Serial.print("EVENT n=");
    Serial.print(n);
    Serial.println(" type=NORMAL");
  }
}
