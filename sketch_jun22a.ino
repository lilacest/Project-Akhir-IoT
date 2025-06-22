#define BLYNK_TEMPLATE_ID "TMPL6nfQoD2rB"
#define BLYNK_TEMPLATE_NAME "BMP280 Monitor"
#define BLYNK_AUTH_TOKEN "XM7SVPz3sPPU22sPqLNCEly4eXrWxhYK"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Zee";         
char pass[] = "cihuy124";    

BlynkTimer timer;
Adafruit_BMP280 bmp;

void sendSensor() {
  float suhu = bmp.readTemperature();
  float tekanan = bmp.readPressure() / 100.0F;

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" °C | Tekanan: ");
  Serial.print(tekanan);
  Serial.println(" hPa");

  Blynk.virtualWrite(V0, suhu);     // Kirim suhu ke V0
  Blynk.virtualWrite(V1, tekanan);  // Kirim tekanan ke V1
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  if (!bmp.begin()) {
    Serial.println("Sensor BMP280 tidak terdeteksi!");
    while (1); // Berhenti di sini kalau sensor gagal
  }

  timer.setInterval(2000L, sendSensor); // Kirim data tiap 2 detik
}

void loop() {
  Blynk.run();
  timer.run();
}
