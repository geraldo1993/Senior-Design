// Geraldo Braho



int servopin=9;  // Define the digital interface 9 to connect the servo servo signal cable
int myangle;  // Define the angle variable
int pulsewidth; // Define pulse width variables
int val;
void servopulse(int servopin,int myangle) // Define a pulse function
{
pulsewidth=(myangle*11)+500;  // The angle is converted to the pulse width value of 500-2480
digitalWrite(servopin,HIGH);  // The steering gear interface level is high
delayMicroseconds(pulsewidth);  // Delayed pulse width of the number of microseconds
digitalWrite(servopin,LOW); // The steering gear interface level to low
delay(20-pulsewidth/1000);
}
void setup()
{
pinMode(servopin,OUTPUT); // Set the servo interface as the output interface
Serial.begin(9600); // Connect to the serial port with a baud rate of 9600
Serial.println("servo=o_seral_simple ready" ) ;
}
void loop() //Change the number of 0 to 9 to 0 to 180 and let the LED flash the number of times
{
val=Serial.read();  //Read the value of the serial port
if(val>'0'&&val<='9')
{
val=val-'0';  // Transforms the feature quantity into a numerical variable
val=val*(180/9);  // Convert the number to an angle
Serial.print("moving servo to ");
Serial.print(val,DEC);
Serial.println();
for(int i=0;i<=50;i++) // Give the steering gear enough time to turn it to the specified angle
{
servopulse(servopin,val); // Reference pulse function
}
}
}
