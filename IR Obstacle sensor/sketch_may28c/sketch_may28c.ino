// IR Obstacle Collision Detection Module
// Henry's Bench

int isObstaclePin = A0;  // This is our input pin
int isObstacle;  // HIGH MEANS NO OBSTACLE

void setup() {
  pinMode(isObstaclePin, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  isObstacle = analogRead(isObstaclePin);
 
    Serial.println(isObstacle);
  
  delay(200);
}
