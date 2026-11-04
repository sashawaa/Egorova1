const int PIN_NTC = A0;      // Датчик 1 (NTC, аналоговый)
const int PIN_TRIG = 2;      // Датчик 2 (US, триггер)
const int PIN_ECHO = 3;      // Датчик 2 (US, эхо)
const int PIN_SERVO = 4;     // Сервопривод (PWM)
const int PIN_RELAY = 5;     // Исполнительное устройство (Реле)
const int PIN_LED = 6;       // Светодиод (жёлтый)

const unsigned long T = 3000; // Период опроса 3 с
unsigned long lastPoll = 0;
int n = 0;                    // Счётчик измерений
bool isThreshold = false;     // Флаг события перегрева

void setServoAngle(int pin, int angle) {
  angle = constrain(angle, 0, 180);
  int pulseWidth = map(angle, 0, 180, 1000, 2000);
  for (int i = 0; i < 10; i++) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(pin, LOW);
    delayMicroseconds(20000 - pulseWidth);
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_SERVO, OUTPUT);
  
  digitalWrite(PIN_RELAY, LOW);
  digitalWrite(PIN_LED, LOW);
  setServoAngle(PIN_SERVO, 0);
}

void loop() {
  if (millis() - lastPoll >= T) {
    lastPoll = millis();
    n++;
    
    // 1. NTC (s1)
    int raw_ntc = analogRead(PIN_NTC);
    float s1 = (80.0 - 0.0) * raw_ntc / 1023.0;
    
    // 2. US HC-SR04 (s2)
    digitalWrite(PIN_TRIG, LOW); 
    delayMicroseconds(2);
    digitalWrite(PIN_TRIG, HIGH); 
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    
    long duration = pulseIn(PIN_ECHO, HIGH, 30000);
    float s2 = (duration > 0) ? (duration * 0.034 / 2.0) : 401.0;
    
    if (s2 < 2.0) s2 = 2.0;
    if (s2 > 400.0) s2 = 400.0;
    
    // 3. SW (s3) - кнопки нет, поэтому всегда 0
    int s3 = 0;
    
    // Вывод DATA (строго в формате для твоего Node-RED)
    Serial.print("DATA n="); Serial.print(n);
    Serial.print(" s1="); Serial.print(s1, 1);
    Serial.print(" s2="); Serial.print(s2, 0);
    Serial.print(" s3="); Serial.println(s3);
    
    // Логика порога (температура > 40 °C)
    if (s1 > 40.0 && !isThreshold) {
      isThreshold = true;
      digitalWrite(PIN_RELAY, HIGH);
      digitalWrite(PIN_LED, HIGH);
      setServoAngle(PIN_SERVO, 90);
      Serial.print("EVENT n="); Serial.print(n); Serial.println(" type=THRESHOLD");
    }
    else if (s1 <= 40.0 && isThreshold) {
      isThreshold = false;
      digitalWrite(PIN_RELAY, LOW);
      digitalWrite(PIN_LED, LOW);
      setServoAngle(PIN_SERVO, 0);
      Serial.print("EVENT n="); Serial.print(n); Serial.println(" type=NORMAL");
    }
  }
}
