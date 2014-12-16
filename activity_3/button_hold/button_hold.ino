/*-----------------------------------------------------------------------
  Acrobotic - 01/12/2014
  Author: x1sc0
  Platforms: Arduino Uno R3
  File: blink_compare.ino
  ------------------------------------------------------------------------
  Description: 
  We compare a fully on LED against one that is blinking very rapidly 
  (imperceptible to our eyes at a first glance)
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

// Initialize 2 variables for the pins we'll be using later
int led_pin = 11;
int button_pin = 2;

// Initialize variable that will hold the push button state
int button_state = LOW;

void setup() 
{
  // Initialize the LED pin as an output:
  pinMode(led_pin, OUTPUT);
  // Initialize the pushbutton pin as an input that is internally pulled up
  // to 5V using the built-in 20~50K resistors (ATmega328p on the Arduino Uno)
  pinMode(button_pin, INPUT_PULLUP);  
}

void loop()
{
  // Read the state of the pushbutton value:
  button_state = digitalRead(button_pin); // pulled up to 5V by default 
  
  // Check if the push button is pressed. If it is, the button state is 
  // LOW because the button is connected to ground:
  if (button_state == LOW) 
  {
    // Turn LED on:    
    digitalWrite(led_pin, HIGH);  
  }
  // otherwise (i.e., if button_state is HIGH)
  else 
  {
    // Turn LED off:
    digitalWrite(led_pin, LOW); 
  }
}
