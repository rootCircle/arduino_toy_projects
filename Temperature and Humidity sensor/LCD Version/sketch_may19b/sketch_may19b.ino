
#include "DHT.h"
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  lcd.print("Formulated by:");
  lcd.setCursor(0,1);
  lcd.print("LAB Studios");
  delay(5000);
  lcd.clear();
}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(0,0);
  if (isnan(h) || isnan(t)) {
    lcd.print("Error!");
    return;
  }

  float hic = dht.computeHeatIndex(t, h, false);
  
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(0,1);
  lcd.print(t);
  lcd.print(" C");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Humidity:");
  lcd.setCursor(0,1);
  lcd.print(h);
  lcd.print("%");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);  
  lcd.print("Heat Index:");
  lcd.setCursor(0,1);
  lcd.print(hic);
  lcd.print(" C");
  delay(2000);
  
}
