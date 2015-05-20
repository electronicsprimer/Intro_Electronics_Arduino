/*-----------------------------------------------------------------------
  Acrobotic - 01/12/2014
  Author: x1sc0
  Platforms: Arduino Uno R3
  File: tilt_detector.ino
  ------------------------------------------------------------------------
  Description:
  We make use of one of the simplest digital sensors, a tilt detector. 
  This sensor behaves like a push button and creates a closed (short) or 
  open circuit between its 2 pins depending on the physical inclination of
  the sensor relative to the earth's gravitational field vector.
  
  We take the opportunity to introduce the concept of interrupts, and
  explore the microcontroller's low-power (sleep) modes.
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

// We'll include the Power Management/Reduction and Sleep Mode libraries
// from the avr-libc, a high quality C library to use with Atmel AVR 
// microcontrollers.
#include <avr/sleep.h>

// Initialize variable with the pin numbers we'll be using
int led_pin = 11;
int detector_pin = 2;

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
  // Initialize the pushbutton pin as an input that is internally pulled up
  // to 5V using the built-in 20~50K resistors (ATmega328p on the Arduino Uno)  
  pinMode(detector_pin, INPUT_PULLUP);
  
  // The Arduino Uno has two external interrupts: number 0 (on pin 2) and 1 
  // (on pin 3). We use the function attachInterrupt() to specify another
  // function that will be called when the interrupt occurs (referred to as
  // an Interrupt Service Routine (ISR)).
  // 
  // In this case, the function enableSleep() (can't have arguments/parameters)
  // will be called when the state of pin 2 (interrupt 0) _changes_ from HIGH
  // to LOW or viceversa.
  attachInterrupt(0, enableSleep, CHANGE);
}

// Most variables can be initialized outside the setup and loop functions
// though above the point where they're first used
int step_size = max( (int)value_max/number_of_steps, 1 );

// Initialize the variable that'll help us monitor whether to enter sleep
// mode or not
volatile bool sleep_flag = true;

void loop()
{
  // Check whether the flag has been enabled by the ISR (true for the first
  // run)
  if (sleep_flag)
    system_sleep(); // function to configure and execute low power mode

  // Code only gets to this point if/when the sleep flag is false, indicating 
  // that an interrupt event was generated
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

void system_sleep()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode
  digitalWrite(led_pin, LOW); // Make sure the LED is turned off
  sleep_mode(); // System sleeps here
  //
  // Code resumes here on wake!
  //
  sleep_flag = false; //Reset sleep flag on wake
}

// Named Interrupt Service Routine attached to int.0 will
// set the sleep_flag variable to true, thus the main
void enableSleep()
{
  sleep_flag = true;
}

