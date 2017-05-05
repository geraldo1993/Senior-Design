//Geraldo Braho


int potPin = 0; // Define analog interface 0 Connect LM35 temperature sensor
void setup()
{
Serial.begin(9600);// Set the baud rate
}
void loop()
{
int val;// Define the variable
int dat;// Define the variable
val=analogRead(0);// Read the analog value of the sensor and assign it to val
dat=(125*val)>>8;// Temperature calculation formula
Serial.print("Tep:");// The original output shows the Tep string representing the temperature
Serial.print(dat);// Outputs the value of dat
Serial.println("C");// Output the C string as it is
delay(500);// Delay 0.5 seconds
}
