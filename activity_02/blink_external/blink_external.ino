/*-----------------------------------------------------------------------
  Acrobotic - 01/12/2014
  Author: x1sc0
  Platforms: Arduino Uno R3
  File: blink_external.ino
  ------------------------------------------------------------------------
  Description: 
  This program is identical to the built-in Blink example. The idea is
  for those using an Arduino Uno board to connect an external LED using 
  the accompanying wiring diagram as a guide.
  
  We'll observe that when using pin 13, both the built-in LED, as well as
  the externally connected one will blink simultaneously!
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
// Using an external LED, we'll notice that both the internal 
// and external LEDs blink at the same rate!
int led = 13; 

// the setup routine runs once when you press reset: 
void setup()
{
  // initialize the digital pin as an output.  
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop()
{
  digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)  
  delay(1000); // wait for a second  
  digitalWrite(led, LOW); // turn the LED off by making the voltage LOW  
  delay(1000); // wait for a second 
}
