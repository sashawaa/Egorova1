const int PIN_NTC = A0;      // Датчик 1 (NTC, аналоговый)
const int PIN_TRIG = 2;     // Датчик 2 (US, триггер)
const int PIN_ECHO = 3;     // Датчик 2 (US, эхо)
const int PIN_SW = 4;       // Датчик 3 (SW, концевик)
const int PIN_RELAY = 5;    // Исполнительное устройство (Реле)
const int PIN_LED = 6;      // Светодиод (жёлтый)

const unsigned long T = 3000; // Период опроса 3 с
unsigned long lastPoll = 0;
int n = 0;                  // Счётчик измерений
bool isThreshold = false;   // Флаг события перегрева

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_SW, INPUT_PULLUP); // Подтяжка к VCC
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);
  digitalWrite(PIN_LED, LOW);
}

void loop() {
  if (millis() - lastPoll >= T) {
    lastPoll = millis();
    n++;
    
    // NTC
    int raw_ntc = analogRead(PIN_NTC);
    float s1 = (80.0 - 0.0) * raw_ntc / 1023.0;
    
    // US HC-SR04
    digitalWrite(PIN_TRIG, LOW); delayMicroseconds(2);
    digitalWrite(PIN_TRIG, HIGH); delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    long duration = pulseIn(PIN_ECHO, HIGH);
    float s2 = duration * 0.034 / 2.0;
    if (s2 < 2.0) s2 = 2.0;
    if (s2 > 400.0) s2 = 400.0;
    
    // 3. SW
    int s3 = !digitalRead(PIN_SW);
    
    // Вывод DATA
    Serial.print("DATA n="); Serial.print(n);
    Serial.print(" s1="); Serial.print(s1, 1);
    Serial.print(" s2="); Serial.print(s2, 0);
    Serial.print(" s3="); Serial.println(s3);
    
    // Логика порога (температура > 40 °C)
    if (s1 > 40.0 && !isThreshold) {
      isThreshold = true;
      digitalWrite(PIN_RELAY, HIGH); // Вкл вентилятор
      digitalWrite(PIN_LED, HIGH);   // Вкл светодиод
      Serial.print("EVENT n="); Serial.print(n); Serial.println(" type=THRESHOLD");
    }
    else if (s1 <= 40.0 && isThreshold) {
      isThreshold = false;
      digitalWrite(PIN_RELAY, LOW);  // Выкл вентилятор
      digitalWrite(PIN_LED, LOW);   // Выкл светодиод
      Serial.print("EVENT n="); Serial.print(n); Serial.println(" type=NORMAL");
    }
  }
}
