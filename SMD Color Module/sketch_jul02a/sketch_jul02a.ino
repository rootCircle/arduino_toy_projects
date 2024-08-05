// RGB LED KY-009 Module

int Led_Green = 9;
int Led_Blue = 10;
int Led_Red = 11;

int r,g,b;

void setup () {
  Serial.begin(9600);
  //Output pin initialization for the LEDs
  pinMode (Led_Red, OUTPUT);
  pinMode (Led_Green, OUTPUT);
  pinMode (Led_Blue, OUTPUT);
}
void loop () {
  // In this for-loop, the 3 LEDs will get different PWM-values
  // Via mixing the brightness of the different LEDs, you will get different colors.
  for (r = 255; r > 0; r--){
    for (g = 255; g > 0; g--) {
      for (b = 255; b > 0; b--) {
        
        analogWrite (Led_Blue, b);
        analogWrite (Led_Green, g);
        analogWrite (Led_Red, r);
        Serial.print(r);
        Serial.print(g);
        Serial.println(b);
        delay (10);
      }
    }

  }
  // You will go backwards through the color range in this second for loop.
  for (r = 0; r <255; r++){
    for (g = 0; g <255; g++) {
      for (b = 0; b<255; b++) {
        
        analogWrite (Led_Blue, b);
        analogWrite (Led_Green, g);
        analogWrite (Led_Red, r);
        delay (10);
      }
    }

  }
}
