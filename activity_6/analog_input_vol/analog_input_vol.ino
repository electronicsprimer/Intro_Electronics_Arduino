// These constants won't change.  They're used to give names
// to the pins used:
const int analog_in_pin  = A0;  // Analog input pin that the potentiometer is attached to
const int analog_out_pin = 11; // Analog output pin that the LED is attached to

int sensor_value = 0;        // value read from the pot
int volume = 0;              // value output to the PWM (analogWrite)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
  sensor_value = analogRead(analog_in_pin);            
  // map it to the range of the analog out:
  volume = map(sensor_value, 0, 1023, 0, 255);  
  
  // change the analog out value:
  analogWrite(analog_out_pin, volume);
   
  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.print(sensor_value);      
  Serial.print("\t output = ");      
  Serial.println(volume);
  
  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);                     
}
