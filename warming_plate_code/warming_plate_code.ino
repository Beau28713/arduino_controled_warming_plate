#include <Adafruit_MAX31856.h>
#include <LiquidCrystal.h>

Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(10, 11, 12, 13);

const int rs = 9, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int relay_pin = 7;
int increment_button = 6;
int decrement_button = A1;
int change_temp_button = A0;
float temp_setpoint = 100.0;

void setup() 
{
  pinMode(relay_pin, OUTPUT);
  pinMode(increment_button, INPUT);
  pinMode(decrement_button, INPUT);
  pinMode(change_temp_button, INPUT);
  
  lcd.begin(20, 4);

  maxthermo.begin();

  maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);
}

void loop() 
{
  delay(3000);
  float surface_temp = read_and_display_temp();
  delay(500);
  
  int temp_button = digitalRead(change_temp_button);
  delay(200);
  
  if(temp_button == HIGH)
  {
    digitalWrite(relay_pin, LOW);
    change_temp();
  }
  else if(surface_temp >= 200.0)
  {
    digitalWrite(relay_pin, LOW);
  }
  else if(surface_temp < temp_setpoint - 20.0)
  {
    digitalWrite(relay_pin, HIGH);
    delay(6000);
    digitalWrite(relay_pin, LOW);
  }
  else if (surface_temp <= temp_setpoint - 10)
  {
    digitalWrite(relay_pin, HIGH);
    delay(3000);
    digitalWrite(relay_pin, LOW);
  }
  else if(surface_temp <= temp_setpoint - 5)
  {
    digitalWrite(relay_pin, HIGH);
    delay(1500);
    digitalWrite(relay_pin, LOW);
  }
  else
  {
    digitalWrite(relay_pin, LOW);
  }
}


float read_and_display_temp()
{
  float thermo_temp = (maxthermo.readThermocoupleTemperature() * 1.8) + 32.0;
  lcd.setCursor(0, 0);
  lcd.print("Surface Temp:");
  lcd.setCursor(14, 0);
  lcd.print(thermo_temp);
  lcd.setCursor(0, 1);
  lcd.print("Set Point:");
  lcd.setCursor(11, 1);
  lcd.print(temp_setpoint);
  return thermo_temp;
}

void change_temp()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Tempature");
  
  do
  {
    lcd.setCursor(0, 1);
    lcd.print("Set Point:");
    lcd.setCursor(11, 1);
    lcd.print(temp_setpoint);
    
    int temp_up = digitalRead(increment_button);
    int temp_down = digitalRead(decrement_button);

    if(temp_up == HIGH)
    {
      temp_setpoint += 1;
      delay(500);
    }
    else if(temp_down == HIGH)
    {
      temp_setpoint -= 1;
      delay(500);
    }
  }
  while(digitalRead(change_temp_button) == HIGH);

  lcd.clear();
  lcd.print("Temp has been set");
  delay(500);
  lcd.clear();
}
