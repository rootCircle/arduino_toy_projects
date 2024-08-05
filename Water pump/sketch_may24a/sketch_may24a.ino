const int liquid_level_sensor=0;
const int water_pump=12;
const int buzzer=10;
void setup() {
  Serial.begin(9600);
  pinMode(liquid_level_sensor,INPUT);
  pinMode(water_pump,OUTPUT);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  if(analogRead(liquid_level_sensor)>300){
    digitalWrite(water_pump,HIGH); 
    noTone(buzzer);
  }
  else{
    digitalWrite(water_pump,LOW);
    tone(buzzer,1000);
  }

   delay(2000);
}
