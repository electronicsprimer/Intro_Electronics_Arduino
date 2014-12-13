/*
 * rgb_led_fade sketch
 * controls the brightness of an RGB, common annode LED on "analog" (PWM) output ports.
 */
class rgb_color 
{
  private:
    int _r;
    int _g;
    int _b;
  public:
    rgb_color (int red, int green, int blue)
      :
        _r(255-red),
        _g(255-green),
        _b(255-blue)
    {
    }

    int r() const {return _r;}
    int b() const {return _b;}
    int g() const {return _g;}
};

/*instances of fader can fade between two colors*/
class fader 
{
  private:
    int r_pin;
    int g_pin;
    int b_pin;
  public:
    /* construct the fader for the pins to manipulate.
     * make sure these are pins that support Pulse
     * width modulation (PWM), these are the digital pins
     * denoted with a tilde(~) common are ~3, ~5, ~6, ~9, ~10 
     * and ~11 but check this on your type of arduino. 
     */ 
    fader(int red_pin, int green_pin, int blue_pin)
      :
        r_pin(red_pin),
        g_pin(green_pin),
        b_pin(blue_pin)
    {
    }
    void setColor(const rgb_color& rgb)
    {
        analogWrite( r_pin, rgb.r() );
        analogWrite( g_pin, rgb.g() );
        analogWrite( b_pin, rgb.b() );
    }
    /*fade from rgb_in to rgb_out*/
    void fade( const rgb_color& in,
               const rgb_color& out,
               unsigned n_steps = 256,  //default take 256 steps
               unsigned time    = 10)   //wait 10 ms per step
    {
      int red_diff   = out.r() - in.r();
      int green_diff = out.g() - in.g();
      int blue_diff  = out.b() - in.b();
      for ( unsigned i = 0; i < n_steps; ++i){
        /* output is the color that is actually written to the pins
         * and output nicely fades from in to out.
         */
        rgb_color output ( in.r() + i * red_diff / n_steps,
                           in.g() + i * green_diff / n_steps,
                           in.b() + i * blue_diff/ n_steps);
        /*put the analog pins to the proper output.*/
        analogWrite( r_pin, 255-output.r() );
        analogWrite( g_pin, 255-output.g() );
        analogWrite( b_pin, 255-output.b() );
        delay(time);
      }
    }
};

/* create fader object */
fader f (11, 10, 9);

/* pre-define colors */
rgb_color yellow( 150, 210,   0 );
rgb_color orange( 135, 150,   0 );
rgb_color red   ( 255,   0,   0 );
rgb_color blue  (   0,   0, 255 );
rgb_color pink  ( 200,   0, 255 );
rgb_color purple( 110,   0, 220 );
rgb_color green (   0, 255,   0 );
rgb_color white ( 150, 210, 255 );

void setup()
{
  //pins driven by analogWrite do not need to be declared as outputs
  //colorTest(1000);
}
  
void loop()
{
  /*fade colors*/
  /*
  f.fade( white, yellow);
  f.fade( yellow, orange);
  f.fade( orange, red);
  f.fade( red, blue);
  f.fade( blue, pink);
  f.fade( pink, purple);
  f.fade( purple, green);
  f.fade( green, white);
  */
}

void colorTest(int pause)
{
  f.setColor(yellow);
  delay(pause);
  f.setColor(orange);
  delay(pause);
  f.setColor(red);
  delay(pause);
  f.setColor(blue);
  delay(pause);
  f.setColor(pink);
  delay(pause);
  f.setColor(purple);
  delay(pause);
  f.setColor(green);
  delay(pause);
  f.setColor(white);
  delay(pause);
}
