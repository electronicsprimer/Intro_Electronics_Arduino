#include <Servo.h> 
 
const int servo_pin      = 11;
const int analog_in_pin  = A0;  // Analog input pin that the potentiometer is attached to

int sensor_value = 0;        // value read from the pot
int pos = 0;                 // value output to the PWM (analogWrite)

Servo s;  // create servo object to control a servo 
          // a maximum of eight servo objects can be created 
 
void setup() 
{ 
  s.attach(servo_pin);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600); // initialize the serial communication
} 
 
void loop()
{
  // read the analog in value:
  sensor_value = analogRead(analog_in_pin);            
  // map it to the range of the analog out:
  pos = map(sensor_value, 0, 1023, 0, 180);  
  
  s.write(pos);
  
  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.print(sensor_value);      
  Serial.print("\t output = ");      
  Serial.println(pos);
  delay(2);
} 
