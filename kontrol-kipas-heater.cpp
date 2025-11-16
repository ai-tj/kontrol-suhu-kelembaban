#include <DHTesp.h>            // Library untuk sensor DHT
#include <LiquidCrystal_I2C.h> // Library untuk LCD I2C

const int DHT_PIN = 15;
const int fan = 2;
const int heater = 4;

DHTesp dhtSensor;
LiquidCrystal_I2C lcd(0x27, 16, 4); // Alamat LCD 0x27, 16 kolom, 4 baris

void sendSensor() {
    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    float temperature = data.temperature;
    float humidity = data.humidity;

    lcd.setCursor(13, 2);
    lcd.print(temperature);
    lcd.setCursor(13, 3);
    lcd.print(humidity);

if (temperature > 30 && humidity < 40) {
    digitalWrite(fan, HIGH);      // Kipas ON
    digitalWrite(heater, LOW);    // Heater OFF
    lcd.setCursor(0, 0); lcd.print("Fan   : ON");
    lcd.setCursor(0, 1); lcd.print("Heater : OFF");
} else if (temperature >= 21 && temperature <= 30 && humidity >= 40 && humidity < 69) {
    digitalWrite(fan, LOW);       // Kipas OFF
    digitalWrite(heater, LOW);    // Heater OFF
    lcd.setCursor(0, 0); lcd.print("Fan   : OFF");
    lcd.setCursor(0, 1); lcd.print("Heater : OFF");
} else if (temperature < 21 && humidity >= 69) {
    digitalWrite(fan, LOW);       // Kipas OFF
    digitalWrite(heater, HIGH);   // Heater ON
    lcd.setCursor(0, 0); lcd.print("Fan   : OFF");
    lcd.setCursor(0, 1); lcd.print("Heater : ON");
} else {
    digitalWrite(fan, LOW);
    digitalWrite(heater, LOW);
    lcd.setCursor(0, 0); lcd.print("Fan   : OFF");
    lcd.setCursor(0, 1); lcd.print("Heater : OFF");
}

void setup() {
    pinMode(fan, OUTPUT);
    pinMode(heater, OUTPUT);

    lcd.init();
    lcd.backlight();

    dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
    Serial.begin(115200);
    delay(1000);
}

void loop() {
    sendSensor();      // Baca sensor & update LCD
    delay(1000);       // Tunggu 1 detik

    // Optional: Print ke Serial Monitor
    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    float temperature = data.temperature;
    float humidity = data.humidity;

    Serial.print("Suhu: "); Serial.print(temperature,1); Serial.print(" C ");
    Serial.print("Kelembaban: "); Serial.print(humidity,1); Serial.println(" %");
}


