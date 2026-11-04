const int PIN_NTC = A0;
const int PIN_TRIG = 2;
const int PIN_ECHO = 3;
const int PIN_SWITCH = 4;
const int PIN_RELAY = 5;
const int PIN_LED = 6;
const unsigned long T = 3000;
unsigned long lastPoll = 0;
int n = 0;
bool isThreshold = false;
void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_SWITCH, INPUT_PULLUP);
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);
  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_TRIG, LOW);
}
void loop() {
  if (millis() - lastPoll >= T) {
    lastPoll = millis();
    n++;
    // Датчик температуры NTC
    int raw_ntc = analogRead(PIN_NTC);
    float s1 = 80.0 * raw_ntc / 1023.0;
    // Ультразвуковой датчик HC-SR04
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    long duration = pulseIn(PIN_ECHO, HIGH, 30000);
    float s2;
    if (duration > 0) {
      s2 = duration * 0.034 / 2.0;
    } else {
      s2 = 400.0;
    }
    if (s2 < 2.0) s2 = 2.0;
    if (s2 > 400.0) s2 = 400.0;
    // Концевой выключатель крышки
    int s3 = (digitalRead(PIN_SWITCH) == LOW) ? 1 : 0;
    // Контроль температуры
    if (s1 > 40.0) {
      digitalWrite(PIN_RELAY, HIGH);
      digitalWrite(PIN_LED, HIGH);
    } else {
      digitalWrite(PIN_RELAY, LOW);
      digitalWrite(PIN_LED, LOW);
    }
    Serial.print("DATA n=");
    Serial.print(n);
    Serial.print(" s1=");
    Serial.print(s1, 1);
    Serial.print(" s2=");
    Serial.print(s2, 0);
    Serial.print(" s3=");
    Serial.println(s3);
    if (s1 > 40.0 && !isThreshold) {
      isThreshold = true;
      Serial.print("EVENT n=");
      Serial.print(n);
      Serial.println(" type=THRESHOLD");
    }
    else if (s1 <= 40.0 && isThreshold) {
      isThreshold = false;
      Serial.print("EVENT n=");
      Serial.print(n);
      Serial.println(" type=NORMAL");
    }
  }
}
