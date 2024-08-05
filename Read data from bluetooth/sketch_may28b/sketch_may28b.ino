char data = 0;                //Variable for storing received data
void setup() 
{
Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
       //Sets digital pin 13 as output pin
}
void loop()
{
if(Serial.available() > 0)  // Send data only when you receive data:
{
data = Serial.read();      //Read the incoming data and store it into variable data
Serial.println(data);        //Print Value inside data in Serial monitor 
              
}
}
