/* Configuration
 * 
 * LED to analog A0 to A6
 * rs = A5, en = A4, d4 = A3, 
 * d5 = A2, d6 = A1, d7 = A0
 * 
 * 4x4 Matrix Keypad to 13 to 6
 *      (Leftmost ->13 in order to rightmost ->6)
 *      
 * Active buzzer on 2
 * 
 * Red LED on 4
 * Green LED on 3
 */

#include <Keypad.h>
#include <LiquidCrystal.h>


const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int rs = A5, en = A4, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int buzzerPin = 2;

String txt = "";


void setup() {
  lcd.begin(16, 2);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(buzzerPin,OUTPUT);
}


void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  char key = keypad.getKey();
  
  switch (key) {
    case '#':
    lcd.clear();
     lcd.setCursor(0, 0);
      if(txt=="123456"){
        
        lcd.print("Success!");
        tone(buzzerPin,10000);
        digitalWrite(3,HIGH);
        delay(500);
        noTone(buzzerPin);
        delay(100);
      }
      else{
        lcd.print("Try Again");
        tone(buzzerPin,1000);
        digitalWrite(4,HIGH);
        delay(500);
        noTone(buzzerPin);
        digitalWrite(4,LOW);
        delay(100);
      }
      delay(1000);
      break;
    case 'C': lcd.clear();
      txt = ""; break;
    case 'D': txt = txt.substring(0, txt.length() - 1);
    lcd.clear();
      break;
    default: txt += String(key);
  }
  digitalWrite(3,LOW);
  
  lcd.setCursor(0, 1);
  lcd.print(txt);
}
