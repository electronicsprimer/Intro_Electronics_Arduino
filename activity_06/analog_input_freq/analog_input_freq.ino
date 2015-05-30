/*-----------------------------------------------------------------------
  Acrobotic - 01/12/2014
  Author: x1sc0
  Platforms: Arduino Uno R3
  File: analog_input_freq.ino
  ------------------------------------------------------------------------
  Description:
  In this activity we'll generate sounds with our microcontroller that'll
  be played through an attached speaker. We'll modify the frequency of the
  sounds by reading the value from an attached potentiometer.  The
  frequency changes will be heard as changes in the pitch of the sounds.
  
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
const int analog_in_pin  = A0; // Analog input pin for potentiometer
const int analog_out_pin = 11; // PWM pin for LED

// For tracking the readings and frequency we use variables as
// their values will change throughout the code
int read_value = 0;        // value read from the pot
int frequency = 0;         // value output to the PWM (tone)

void setup() {
  // Use the Serial object to initialize serial communications at 9600 bps
  Serial.begin(9600); 
}

void loop() {
  // Read the current value of the potentiometer
  read_value = analogRead(analog_in_pin);            
  // map it to the range of the analog out:
  frequency = map(read_value, 0, 1023, 120, 1500);  
  
  // change the analog out value:
  tone(analog_out_pin, frequency);           
   
  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.print(read_value);      
  Serial.print("\t output = ");      
  Serial.println(frequency);
  
  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);                     
}
