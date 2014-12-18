int b_led_pin =  9;
int g_led_pin = 10;
int r_led_pin = 11;

int value = 0,
    value_max = 128,
    number_of_steps = 255,
    step_delay_ms = 5,
    cycle_delay_ms = 1000;

void setup()
{
  pinMode(r_led_pin, OUTPUT);
  pinMode(g_led_pin, OUTPUT);
  pinMode(b_led_pin, OUTPUT);

  digitalWrite(g_led_pin, HIGH);

  // Simple test to double-check the wiring.
  // After uploading the program you should see
  // both the Blue and Red LED light-up for 2 seconds
  // each (first blue then red).
  // Check your wiring with the diagram if this is not the case!
  digitalWrite(r_led_pin, LOW);
  digitalWrite(b_led_pin, HIGH);
  delay(2000);
  digitalWrite(b_led_pin, LOW);
  digitalWrite(r_led_pin, HIGH);
  delay(2000);

}

int step_size = max( (int)value_max/number_of_steps, 1 );

int pin_array[3] = {r_led_pin, g_led_pin, b_led_pin},
    pin = pin_array[0],
    index = 1;
    
void loop()
{
  analogWrite(pin, 255-value);  
  delay(step_delay_ms);  
  value+=step_size;
  
  if( (value >= value_max)||(value<0) )
    step_size *= -1;
  if(value < 0)
  {
    value = 0;
    delay(cycle_delay_ms);
    pin = pin_array[index++];
    index%=3;
  }
}
