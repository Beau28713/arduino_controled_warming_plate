#include <Adafruit_MAX31856.h>
#include <LiquidCrystal.h>

Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(10, 11, 12, 13);
const int rs = 9, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{
  lcd.begin(20, 4);
  /*Serial.begin(115200);
  while (!Serial) 
  {
    delay(10);
  }
  */
  lcd.print("Hello Beau");

  maxthermo.begin();

  maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);
}

void loop() 
{
  read_and_display_temp();

  delay(1000);
}

void read_and_display_temp()
{
  float thermo_temp = (maxthermo.readThermocoupleTemperature() * 1.8) + 32.0;
  //Serial.println(thermo_temp);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(thermo_temp);
}
