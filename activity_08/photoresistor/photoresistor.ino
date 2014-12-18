/* Simple test of the functionality of the photo resistor

----------------------------------------------------

           PhotoR     10K
 +5     o---/\/\/--.--/\/\/---o GND
                   |
 Pin A0 o-----------

----------------------------------------------------
*/

int photo_pin      = 0;      //define a pin for Photo resistor
int led_pin        = 11;     //define a pin for LED
int sensor_value   = 0;
int led_brightness = 0;

void setup()
{
    Serial.begin(9600);  //Begin serial communcation
    pinMode( led_pin, OUTPUT );
}

void loop()
{
  // read the analog in value:
  sensor_value = analogRead(photo_pin);            
  // map it to the range of the analog out:
  led_brightness = map(sensor_value, 100, 700, 0, 255);  
  led_brightness = max(0, led_brightness);
  // change the analog out value:
  analogWrite(led_pin, led_brightness);
   
  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.print(sensor_value);      
  Serial.print("\t output = ");      
  Serial.println(led_brightness);
  
  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);    
}
