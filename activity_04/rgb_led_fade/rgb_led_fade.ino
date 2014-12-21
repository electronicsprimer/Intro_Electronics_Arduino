/*-----------------------------------------------------------------------
  Acrobotic - 01/12/2014
  Author: x1sc0
  Platforms: Arduino Uno R3
  File: rgb_led_fade.ino
  ------------------------------------------------------------------------
  Description: 
  We use PWM to control the brightness of each of the three LEDs (R,G,B) 
  in an RGB LED.  By combining two or more LEDs at various intensity
  levels, we generate different colors.
  
  We first define the colors, and adjust them as we deem appropriate. Once
  the colors are setup we can press the pushbutton and the main part of 
  the code will run smoothly transitioning between them according to our 
  specified sequence! 
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

// We can change this to false if we do not want to test the pre-defined
// colors
#define testing true

// Initialize variables for the pins we'll be using later
int r_led_pin =  9;
int g_led_pin = 10;
int b_led_pin = 11;

#if testing == true
 int button_pin = 2;
 bool test_flag = true;
 bool in_loop = false;
#endif

// We're going to use a structure type with 3 field members, which will
// hold the brightness level of the LED
struct RGB {
  byte r;
  byte g;
  byte b;
};

// Pre-define colors by the intensity of their {R,G,B} LEDs
// These can and should be adjusted by the user to resemble
// colors more accurately
RGB green  = {   0, 255,   0 };
RGB yellow = { 255, 50,   0 };
RGB orange = { 255, 10,   0 };
RGB red    = { 255,   0,   0 };
RGB pink   = { 200,   0, 155 };
RGB purple = { 110,   0, 220 };
RGB blue   = {   0,   0, 255 };
RGB cyan   = {   0,  70, 255 };
RGB white  = { 150, 210, 255 };

// Helper function for fading from one color to another (rgb_in to rgb_out).
// Because we're passing arguments as references, we need to define
// this function before using it.  Otherwise we would need to at least declare
// it and that opens a whole 'nother can of worms.
void fade( const RGB &in,
           const RGB &out,
           unsigned n_steps = 256,  // default take 256 steps
           unsigned time    = 10)   // wait 10 ms per step
{
// Allows us to escape from the color test if the button is pressed
#if testing == true
  if(!in_loop && !test_flag)
    return;
#endif
  // We calculate the difference between the R, G, B values of the "from" and "to"
  // colors
  int red_diff   = out.r - in.r;
  int green_diff = out.g - in.g;
  int blue_diff  = out.b - in.b;
  
  for ( unsigned i = 0; i < n_steps; ++i) // taking as many steps as we need
  {
    // We divide the difference by the number of steps iterate until all steps are 
    // taken towards the new color. Note that the color difference can be either 
    // positive or negative, depending on whether we need to increase or decrease
    // brightness on each LED to display the new color!
    RGB output = { in.r + i * red_diff / n_steps,
                   in.g + i * green_diff / n_steps,
                   in.b + i * blue_diff/ n_steps
                 };
    // Set the brightness of each LED by using PWM!
    analogWrite( r_led_pin, 255-output.r );
    analogWrite( g_led_pin, 255-output.g );
    analogWrite( b_led_pin, 255-output.b );
    delay(time);
  }
}


void setup()
{
  // Pins driven by analogWrite do not need to be declared as outputs

  // These are only necessary if we're checking the colors
#if testing == true 
  // As usual, we wire up a push button so that when it's pressed it
  // sends a GND signal to the pin.  We use the internal pullup
  // resistors to make the default state HIGH
  pinMode(button_pin, INPUT_PULLUP);

  // We want to run the color test until the button is pressed.  Thus,
  // we attacha an interrupt to pin 2 (int.0 on the Arduino Uno; cf., 
  // http://arduino.cc/en/Reference/attachInterrupt).
  // 
  // The interrupt is triggered on a FALLING edge (HIGH to LOW change)
  // and calls the function endTest
  attachInterrupt(0, endTest, FALLING);
  while(test_flag)
  {
    colorTest();
  }
#endif
}

void loop()
{
#if testing == true
  // Update this variable to let the fade function know that we're now inside
  // the loop and the color test has concluded
  if(!in_loop)
    in_loop = true;
#endif

  // Fade from one color to the next by calling our fade function.  We use the 
  // default values for the 3rd (steps) and 4th (time) arguments of the function
  fade( white, green );
  fade( green, yellow );
  fade( yellow, orange );
  fade( orange, red );
  fade( red, pink );
  fade( pink, purple );
  fade( purple, blue );
  fade( blue, cyan );
  fade( cyan, white );
}

#if testing == true
 // To check the colors we've predefined, we run a fade with the same color for 
 // "in" and "out" (only that color will be displayed) and adjust the brightness
 // values above if needed.e 
 void colorTest()
 {
   fade( green,green );
   fade( yellow,yellow );
   fade( orange,orange );
   fade( red,red );
   fade( pink,pink );
   fade( purple,purple );
   fade( blue,blue );
   fade( cyan,cyan );
   fade( white,white );
 }
 
 // This function is called when a FALLING (HIGH to LOW) transition occurs on pin
 // 2.  We update the test_flag to let the fade function know we're done testing
 // and we detach the interrupt to avoid future triggers!
 void endTest()
 {
   test_flag = false;
   detachInterrupt(0);
 }
#endif
