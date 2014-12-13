#include <Servo.h> 
 
int servo_pin = 11;

int value = 0,
    value_max = 180,
    number_of_steps = 50,
    step_delay_ms = 15,
    cycle_delay_ms = 1000;

Servo s;  // create servo object to control a servo 
          // a maximum of eight servo objects can be created 
 
int step_size = max( (int)value_max/number_of_steps, 1 );

 
void setup() 
{ 
  s.attach(servo_pin);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop()
{
  s.write(value);  
  delay(step_delay_ms);  
  value+=step_size;

  if( (value >= value_max)||(value<0) )
    step_size *= -1;
  if(value < 0)
  {
    value = 0;
    delay(cycle_delay_ms);
  }
} 
