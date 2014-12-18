/*-----------------------------------------------------------------------
  Acrobotic - 01/12/2014
  Author: x1sc0
  Platforms: Arduino Uno R3
  File: button_toggle.ino
  ------------------------------------------------------------------------
  Description: 
  We set up a push button and LED so that when the button is pushed the
  LED switches from on to off (or viceversa).  We also use software
  debouncing to prevent false triggers due to button bouncing.
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

// Initialize variable that will hold the button and LED state
int button_state = LOW;         // stores current button state
int button_state_old = LOW;     // stores previous button state
int led_state = LOW;            // stores previous LED state

// Initialize variables used for debouncing the button state
int time = 0;
int bounce_wait = 200;

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
  button_state = digitalRead(button_pin);
  // Check if the input just went from LOW and HIGH (button release).  
  // Also check if this LOW-to-HIGH transition hasn't ocurred in the
  // past 200ms
  if ( (button_state == HIGH) && 
       (button_state_old == LOW) && 
       ((millis() - time) > bounce_wait) ) 
  {
    // Check the previous state of the LED and toggle it
    if (led_state == HIGH)
      led_state = LOW;
    else
      led_state = HIGH;
    // Store the current time for comparison in the next loop iteration 
    time = millis();    
  }
  // Update the led pin
  digitalWrite(led_pin, led_state);
  // Store the button state for comparison in the next loop iteration
  button_state_old = button_state;
}
