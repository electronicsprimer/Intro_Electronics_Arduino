/*-----------------------------------------------------------------------
  Acrobotic - 01/12/2014
  Author: MakerBro
  Platforms: Arduino Uno R3
  File: rgb_led_cycle.ino
  ------------------------------------------------------------------------
  Description: 
  We set up a push button and a common-anode RGB LED. The push button is 
  used to ensure that the wiring of the Red, Green, and Blue is as we 
  expect it.
  
  The wiring check code will blink a single LED, starting with Red. If the
  user sees another LED blinking, she will adjust the wire to pin 9 until
  the Red LED blinks. Once this is done she will hold down the button for 
  about 2 seconds then release it.  
  
  The Green LED should start blinking now. In case the Blue LED is 
  blinking, the user will need to reverse the wires connected to pin 10 
  and 11. Once this is done, the user can hold downi the button for 
  another 2 seconds and release it.  

  Finally, she should see a quick blink sequence: Red-Green-Blue,
  followed by the main part of the program.  That is, a heartbeat on each 
  color.
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

// We can change this to false if we do not want to test the wiring
// of the LED
#define testing true

// Initialize variables for the pins we'll be using later
int r_led_pin =  9;
int g_led_pin = 10;
int b_led_pin = 11;

// Only used for checking the wiring
#if testing == true
 int button_pin = 2,
     button_state = HIGH,
     bounce_wait = 200,
     time = 0,
     button_state_old = HIGH;
#endif

// Initialize a few variables that we'll be using in our loop function
// for controlling LED brightness
int value = 0,
    value_max = 128,
    number_of_steps = 255,
    step_delay_ms = 5,
    cycle_delay_ms = 1000,
    step_size = max( (int)value_max/number_of_steps, 1 );

int pin_array[3] = {r_led_pin, g_led_pin, b_led_pin},
    index = 0;
    
void setup()
{
  // Configure the pin modes
  pinMode(r_led_pin, OUTPUT);
  pinMode(g_led_pin, OUTPUT);
  pinMode(b_led_pin, OUTPUT);

  // Because the RGB LED is common-anode, we turn OFF the individual LEDs 
  // by writing a HIGH value to the pin. The default state of an output
  // pin is LOW so we need this!
  digitalWrite(r_led_pin, HIGH);
  digitalWrite(g_led_pin, HIGH);
  digitalWrite(b_led_pin, HIGH);

  // These are only necessary if we're checking the wiring
#if testing == true 
  pinMode(button_pin, INPUT_PULLUP);
  testWiring();
#endif
}

  // This operation is similar than the code in our Hearbeat demo (see Activity 02 - LEDs).
void loop()
{
  analogWrite(pin_array[index], 255-value); //set the  LED brightness (255 is OFF)  
  delay(step_delay_ms); //hold the value for a short time
  value+=step_size; //increase the current value for the next iteration

  // If we've reached the maximum or minimum value, change direction of
  // change in brightness (i.e., increasing -> decreasing or viceversa).
  if( (value>value_max)||(value<0) )
  {
    step_size *= -1;
    value+=step_size; // ensure that value stays within bounds
    // We also check if we're at the end of an ON-OFF cycle to switch LED color
    // and stop for 1 second.
    if(value == 0)
    {
      delay(cycle_delay_ms); // hold 1 second off starting each cycle
      // This line first increases our pin array's index (++)
      // and then it performs the modulus operation index = index%3 so that
      // the index of the 3-element array remains within the acceptable values:
      // 0, 1, or 2. 
      ++index%=3;
    }
  }
}

// We only define our wiring-check function if we're checking the wiring :)
#if testing == true 
 void testWiring()
 {
   int n = 0; // a variable to help us know when we're done with the test
   // We want to remain in this function while the wiring is incorrect
   while(n<2)
   {
     // If there has been a button press this will read LOW otherwise HIGH
     button_state = digitalRead(button_pin);
     // Similar check than in our Activity #3 - Buttons
     if ( (button_state == HIGH) && 
          (button_state_old == LOW) && 
          ((millis() - time) > bounce_wait) ) 
     {
       time = millis();
       n++; // if the user has pressed the button, switch to next LED
     }
     // Blink a single LED until the user gets the color right.
     switch(n)
     {
       // Start with Red. If another color is blinking the user will need
       // to adjust her wiring.
       case 0:
         blinkLed(r_led_pin, 500);
         break;
       // Once the user sees the Red LED blinking, she will press the button
       // and we'll start blinking the next LED. In case the user doesn't 
       // see the Green LED blinking, she'll need to reverse the remaining 
       // wires.
       case 1:
         blinkLed(g_led_pin, 500);
         break;
       // Once the wiring is correct, we show a short R-G-B sequence
       case 2:
         blinkLed(r_led_pin, 250);
         blinkLed(g_led_pin, 250);
         blinkLed(b_led_pin, 250);
         break;
       default:
         break;
     }
     // We keep track of the previous state of the button for debouncing
     // purposes
     button_state_old = button_state;
   }
 }

 // Helper function for avoiding typing these 4 lines multiple times!
 void blinkLed(int pin, int t)
 {
   digitalWrite(pin, LOW);
   delay(t);
   digitalWrite(pin, HIGH);
   delay(t);
 }
#endif
