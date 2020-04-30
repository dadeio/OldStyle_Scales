// include the library code:
#include <LiquidCrystal.h>
#include "HX711.h"


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 18;
const int LOADCELL_SCK_PIN = 19;

HX711 scale;

const int rs = 15, en = 14, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// constants won't change.
const int buttonPin = 9;

// variables will change:
int iTara = 0;
float fPeso = 0;
int buttonState = 0;
bool bAvvioTara = 0;


void setup() {
  Serial.begin(38400);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
 
  scale.set_scale(438.7);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();
}

void loop() {
  buttonState = digitalRead(buttonPin);
  fPeso = scale.get_units(5), 2;
  if (buttonState == HIGH){
    bAvvioTara=HIGH;
  }
  if (bAvvioTara == HIGH){
    iTara = iTara + (int(fPeso));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tara");
    lcd.setCursor(0, 1);
    lcd.print("in corso . . .");
    scale.tare();
    delay(500);
    lcd.clear();
    bAvvioTara=LOW;
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Peso");
    lcd.setCursor(0, 1);
    lcd.print("          ");
    lcd.setCursor(0, 1);
    lcd.print(int(fPeso));
    lcd.print(" g");
    Serial.print(fPeso);
    Serial.println(" g");
    lcd.setCursor(9, 0);
    lcd.print("Tara");
    lcd.setCursor(9, 1);
    lcd.print(iTara);
    lcd.print(" g");
  }
}
