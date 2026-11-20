#include <Adafruit_LiquidCrystal.h>
 
Adafruit_LiquidCrystal lcd(0);
 
const int PINO_GAS    = A0;
const int PINO_TEMP   = A1;
const int PINO_LUZ    = A2;
const int PINO_BUZZER = 8;
 
const int   LIMITE_GAS  = 500;
const float LIMITE_TEMP = 80.0;
const int   LIMITE_LUZ  = 850;
 
void setup() {
  pinMode(PINO_BUZZER, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
}
 
void loop() {
  int gas = analogRead(PINO_GAS);
  int luz = analogRead(PINO_LUZ);
  float tensao = analogRead(PINO_TEMP) * 5.0 / 1024.0;
  float temp = (tensao - 0.5) * 100.0;
 
  bool incendio = (gas > LIMITE_GAS) || (temp > LIMITE_TEMP) || (luz > LIMITE_LUZ);
 
  lcd.setCursor(0, 0);
  if (incendio) {
    lcd.print("!! INCENDIO !!  ");
    tone(PINO_BUZZER, 1000);
  } else {
    lcd.print("Tudo normal     ");
    noTone(PINO_BUZZER);
  }
 
  /*lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print((int)temp);
  lcd.print("C G:");
  lcd.print(gas);
  lcd.print(" luz: ");
  lcd.print(luz);*/
  lcd.setCursor(0, 1);
  lcd.print((int)temp);
  lcd.print(" ");
  lcd.print(gas);
  lcd.print(" ");
  lcd.print(luz);
 
  Serial.println("Temperatura:");
  Serial.println((int)temp);
  Serial.println("Gas:");
  Serial.println(gas);
  Serial.println("Luz:");
  Serial.println(luz);
  delay(200);
}
