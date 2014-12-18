int led_pin = 11;
int button_pin = 2;     // the number of the pushbutton pin

// variables will change:
int button_state = LOW;         // variable for reading the pushbutton status

void setup() 
{
  // initialize the LED pin as an output:
  pinMode(led_pin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(button_pin, INPUT_PULLUP);  
}

void loop()
{
  // read the state of the pushbutton value:
  button_state = digitalRead(button_pin); 
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (button_state == HIGH) 
  {
    // turn LED on:    
    digitalWrite(led_pin, HIGH);  
  } 
  else 
  {
    // turn LED off:
    digitalWrite(led_pin, LOW); 
  }
}
