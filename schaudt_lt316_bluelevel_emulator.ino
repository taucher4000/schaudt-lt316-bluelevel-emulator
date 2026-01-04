/* 
 * ESP32 Wassertank-Emulator für Schaudt LT 316
 * Eingang: BlueLevel+ (0V = 0%, 2.5V = 100%) an GPIO 34
 * Ausgang: 4-Kanal Optokoppler an GPIO 26, 25, 33, 32
 */

const int sensorPin = 34;    // Analog-Eingang für BlueLevel+
const int optoPins[] = {26, 25, 33, 32};  // Für das LC-Relay-ESP32-4R-A2 Board sind die Relais an diesen GPIOs

void setup() {
  Serial.begin(115200);
  
  // Optokoppler-Pins als Ausgänge definieren
  for (int i = 0; i < 4; i++) {
    pinMode(optoPins[i], OUTPUT);
    digitalWrite(optoPins[i], LOW); // Initial aus
  }

  // ADC Konfiguration: 12-Bit Auflösung, Dämpfung für 0-3.3V Bereich
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db); 
}

void loop() {
  int rawValue = analogRead(sensorPin);

  // 2.5V entsprechen bei 12-Bit (4095) und 3.3V Referenz ca. 3102 Einheiten
  float voltage = (rawValue * 3.3) / 4095.0;
  float percent = (voltage / 2.5) * 100.0;

  Serial.printf("Spannung: %.2fV | Fuellstand: %.1f%%\n", voltage, percent);

  // Steuerung der Optokoppler (Kaskadierend wie bei einer Stabsonde)
  // LT 316 erwartet oft, dass bei 50% auch der 25%-Kontakt geschlossen bleibt.
  digitalWrite(optoPins[0], (percent >= 25.0) ? HIGH : LOW);
  digitalWrite(optoPins[1], (percent >= 50.0) ? HIGH : LOW);
  digitalWrite(optoPins[2], (percent >= 75.0) ? HIGH : LOW);
  digitalWrite(optoPins[3], (percent >= 95.0) ? HIGH : LOW);

  delay(1000); // Messung jede Sekunde
}
