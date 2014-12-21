/*-----------------------------------------------------------------------
  Acrobotic - 01/12/2014
  Author: x1sc0
  Platforms: Arduino Uno R3
  File: heartbeat.ino
  ------------------------------------------------------------------------
  Description: 
  Using the fucntion analogWrite(), we control the brightness of an LED by
  modulating the duty cycle of a rectangular wave signal (PWM).
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

// Initialize variable with the pin number which we'll be using. Ensure
// that it's a PWM pin.
int led_pin = 11;

// Initialize a few variables that we'll be using in our loop function
// for controlling LED brightness
int value = 0, // current brigthness
    value_max = 128,  // maximum brightness (brightness doesn't change 
                      // much above this value)
    number_of_steps = 256, // steps taken between fully OFF and fully ON
    step_delay_ms = 5, // wait 5ms at each intensity value
    cycle_delay_ms = 1000; // stay off for 1000ms between cycles

void setup()
{
  // Technically, the next line is unnecessary.  Because we'll be driving
  // the pin with the function analogWrite(), we don't need to set it as
  // an OUTPUT.  It doesn't hurt to do it anyway.
  pinMode(led_pin, OUTPUT);
}

// Most variables can be initialized outside the setup and loop functions
// though above the point where they're first used
int step_size = max( (int)value_max/number_of_steps, 1 );

void loop()
{
  analogWrite(led_pin, value); //set the current LED brightness  
  delay(step_delay_ms); //hold the value for a short time
  value+=step_size; //increase the current value for the next iteration

  // if we've reached the maximum or minimum value, change direction of
  // change in brightness (i.e., increasing -> decreasing or viceversa)
  if( (value>value_max)||(value<0) )
  {
    step_size *= -1;
    value+=step_size; // ensure that value stays within bounds
    if(value == 0)
      delay(cycle_delay_ms); // hold 1 second off starting each cycle
  }
}
