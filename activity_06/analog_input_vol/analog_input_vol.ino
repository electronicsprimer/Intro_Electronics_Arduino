/*-----------------------------------------------------------------------
  Acrobotic - 01/12/2014
  Author: x1sc0
  Platforms: Arduino Uno R3
  File: analog_input_vol.ino
  ------------------------------------------------------------------------
  Description:
  In this activity we'll generate sounds with our microcontroller that'll
  be played through an attached speaker. We'll modify the volume of the
  sounds by reading the value from an attached potentiometer.
  
  We'll also use the Serial object from the Arduino libraries to send 
  messages back to the computer via USB.  After the code is uploaded to
  the microcontroller, these messages can be displayed on a computer by 
  opening the Serial Monitor window in the Arduino IDE.
  ------------------------------------------------------------------------
  Please consider buying products from Acrobotic to help fund future
  Open-Source projects like this! We’ll always put our best effort in every
  project, and release all our design files and code for you to use. 
  http://acrobotic.com/
  ------------------------------------------------------------------------
  License:
  Beerware License; if you find the code useful, and we happen to cross 
  paths, you're encouraged to buy us a beer. The code is distributed hoping
  that you in fact find it useful, but  without warranty of any kind.
------------------------------------------------------------------------*/

// Instead of using variables, we'll use constant types to give names to
// the pins used as these won't change throughout the code.
const int analog_in_pin  = A0;  // Analog input pin that the potentiometer is attached to
const int analog_out_pin = 11;  // Analog output pin that the LED is attached to

// For tracking the readings and volume we use variables as
// their values will change throughout the code
int read_value = 0;          // value read from the pot
int volume = 0;              // value output to the PWM (analogWrite)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  // Read the current value of the potentiometer
  read_value = analogRead(analog_in_pin);            
  // map it to the range of the analog out:
  volume = map(read_value, 0, 1023, 0, 255);  
  
  // change the analog out value:
  analogWrite(analog_out_pin, volume);
   
  // print the results to the serial monitor:
  Serial.print("read = " );                       
  Serial.print(read_value);      
  Serial.print("\t output = ");      
  Serial.println(volume);
  
  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);                     
}
