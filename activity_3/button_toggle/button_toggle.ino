int led_pin = 11;
int button_pin = 2;     // the number of the pushbutton pin
int debounce = 200;

// variables will change:
int button_state = LOW;         // variable for reading the pushbutton status
int button_state_old = LOW;         // variable for reading the pushbutton status
int led_state = HIGH;         // variable for holding/writing the LED state
int time;

void setup()
{
  // initialize the LED pin as an output:
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, led_state);
  // initialize the pushbutton pin as an input:
  pinMode(button_pin, INPUT_PULLUP);  
  // initialize serial communication
  Serial.begin(9600);
}

void loop()
{
  button_state = digitalRead(button_pin);
  Serial.print("Button state= ");
  Serial.println(button_state);
  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (button_state == HIGH && button_state_old == LOW && millis() - time > debounce) {
    if (led_state == HIGH)
      led_state = LOW;
    else
      led_state = HIGH;

    time = millis();    
  }

  digitalWrite(led_pin, led_state);

  button_state_old = button_state;
}
