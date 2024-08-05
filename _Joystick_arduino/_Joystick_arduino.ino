
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int VRx = A0;
int VRy = A1;
int SW = 8;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

byte customChar[] = {
  B00001,
  B00011,
  B00111,
  B00011,
  B00001,
  B00000,
  B00000,
  B00000
};

byte character_1[] = {
  B00001,
  B00011,
  B00111,
  B00011,
  B00001,
};

int base_column = 0;
int c = 0;

void createArray(int pos, int col) {
  c = (col == 0) ? 0 : c;
  for (int i = 0; i < 8; i++) {
    if ((i >= pos - 2) && (i <= pos + 2)||((c!=0)&&(c<5))) {
      customChar[i] = character_1[c];
      c++;
    }
    else {
      customChar[i] = B00000;
    }
  }
}

void base(int cor) {
  int pos = (int)(cor / 64);
  Serial.println(pos);
  for (int i = 0; i < 2; i++) {
    createArray(pos, i);
    Serial.print("Array:");
    for(int j=0;j<=7;j++){
    Serial.print(customChar[j]);
    }
    Serial.println();
    lcd.createChar(i, customChar);
    lcd.setCursor(15, i);
    lcd.write((byte)i);
  }
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
}

void loop() {
  lcd.clear();
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  lcd.setCursor(0, 0);
  lcd.print(mapX);
  lcd.setCursor(5, 0);
  lcd.print(SW_state);
  lcd.setCursor(0, 1);
  lcd.print(mapY);

  base(yPosition);

  delay(500);
}
