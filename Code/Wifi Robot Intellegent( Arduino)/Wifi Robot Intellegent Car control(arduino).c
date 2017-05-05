/*

* Abstract: wifi robot intelligent car control
*/
#include <Servo.h>
#include <EEPROM.h>

int ledpin = 13;//Set the system startup light
int ENA = 5;//L298 Enable A
int ENB = 6;//L298 Enable B
int INPUT2 = 7;//Motor interface 1
int INPUT1 = 8;//Motor interface 2
int INPUT3 = 12;//Motor interface 3
int INPUT4 = 13;//Motor interface 4
int num;//Defines the motor flag

int Echo = A5;  // Define the ultrasonic signal to receive the pin
int Trig = A4;  // Defines the ultrasonic signal firing pin
int Input_Detect_LEFT = A3;    //Define the left side of the car infrared
int Input_Detect_RIGHT = A2;  //Define the right side of the car infrared
int Input_Detect = A1;//Define the car front infrared
int Carled = A0;//Define the car lights interface
int Cruising_Flag = 0;
int Pre_Cruising_Flag = 0 ;
int Left_Speed_Hold = 255;//Defines the left speed variable
int Right_Speed_Hold = 255;//Defines the right speed variable

//The macro defines the direction of the car steering
#define MOTOR_GO_FORWARD  {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}    //Body forward
#define MOTOR_GO_BACK	  {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}    //Body forward
#define MOTOR_GO_RIGHT	  {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}    //Body forward
#define MOTOR_GO_LEFT	  {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}    //Body forward
#define MOTOR_GO_STOP	  {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,LOW);}    //Body forward


void forward(int num)
{
	switch(num)
	{
		case 1:MOTOR_GO_FORWARD;return;
		case 2:MOTOR_GO_FORWARD;return;
		case 3:MOTOR_GO_BACK;return;
		case 4:MOTOR_GO_BACK;return;
		case 5:MOTOR_GO_LEFT;return;
		case 6:MOTOR_GO_LEFT;return;
		case 7:MOTOR_GO_RIGHT;return;
		case 8:MOTOR_GO_RIGHT;return;
		default:return;
	}
}

void back(int num)
{
		switch(num)
	{
		case 1:MOTOR_GO_BACK;return;
		case 2:MOTOR_GO_BACK;return;
		case 3:MOTOR_GO_FORWARD;return;
		case 4:MOTOR_GO_FORWARD;return;
		case 5:MOTOR_GO_RIGHT;return;
		case 6:MOTOR_GO_RIGHT;return;
		case 7:MOTOR_GO_LEFT;return;
		case 8:MOTOR_GO_LEFT;return;
		default:return;
	}
}
void left(int num)
{
		switch(num)
	{
		case 1:MOTOR_GO_LEFT;return;
		case 2:MOTOR_GO_RIGHT;return;
		case 3:MOTOR_GO_LEFT;return;
		case 4:MOTOR_GO_RIGHT;return;
		case 5:MOTOR_GO_FORWARD;return;
		case 6:MOTOR_GO_BACK;return;
		case 7:MOTOR_GO_FORWARD;return;
		case 8:MOTOR_GO_BACK;return;
		default:return;
	}
}
void right(int num)
{
		switch(num)
	{
		case 1:MOTOR_GO_RIGHT;return;
		case 2:MOTOR_GO_LEFT;return;
		case 3:MOTOR_GO_RIGHT;return;
		case 4:MOTOR_GO_LEFT;return;
		case 5:MOTOR_GO_BACK;return;
		case 6:MOTOR_GO_FORWARD;return;
		case 7:MOTOR_GO_BACK;return;
		case 8:MOTOR_GO_FORWARD;return;
		default:return;
	}
}


//Servo servo1;// Create a steering gear # 1
//Servo servo2;// Create a steering gear # 2
Servo servo3;// Create the steering gear # 3
Servo servo4;// Create a steering gear # 4
Servo servo5;// Create a steering gear # 5
Servo servo6;// Create a steering gear # 6
Servo servo7;// Create a steering gear # 7
Servo servo8;// Create a steering gear # 8



//byte angle1=60;//Servo # 1 initial value
//byte angle2=60;//Servo # 2 initial value
byte angle3=60;//Servo # 3 initial value
byte angle4=60;//Servo # 4 initial value
byte angle5=60;//Servo # 5 initial value
byte angle6=120;//Servo # 6 initial value
byte angle7=60;//Servo # 7 initial value
byte angle8=60;//Servo # 8 initial value


int buffer[3];  //The serial port receives the data cache
int rec_flag;   //Serial receive flag
int serial_data;
int Uartcount;
int IR_R;
int IR_L;
int IR;
unsigned long Pretime;
unsigned long Nowtime;
unsigned long Costtime;
float Ldistance;

/*
*********************************************************************************************************
** Function name ：Open_Light()
** Function: Open the headlights
** Entry parameters: none
** Export parameters: none
*********************************************************************************************************
*/
void Open_Light()//Open headlights
    {
      digitalWrite(Carled,HIGH);   //Pull low, positive connected to the power supply, negative Io mouth
      delay(1000);
    }
/*
*********************************************************************************************************
** Function name ：Close_Light()
** Function: off the lights
**Entry parameters: none
** Export parameters: none
*********************************************************************************************************
*/
void Close_Light()//Off the lights
    {
      digitalWrite(Carled, LOW);   //Pull low, positive connected to the power supply, negative Io mouth
      delay(1000);
    }
/*
*********************************************************************************************************
** Function name  ：Avoiding()
** Function function: infrared obstacle avoidance function
** Entry parameters: none
** Export parameters: none
*********************************************************************************************************
*/
void  Avoiding()//Infrared obstacle avoidance function
    {
      IR = digitalRead(Input_Detect);
       if((IR == HIGH))
       {
          forward(num);;//Direct line
          return;
       }
       if((IR == LOW))
       {
            MOTOR_GO_STOP;//stop
            return;
       }
    }


/*
*********************************************************************************************************
** Function name ：FollowLine()
** Function function: line inspection mode
** Entry parameters: none
** Export parameters: none
*********************************************************************************************************
*/
void FollowLine()   // Line inspection mode
    {
      IR_L = digitalRead(Input_Detect_LEFT);//Read the left sensor value
      IR_R = digitalRead(Input_Detect_RIGHT);//Read the right sensor value

      if((IR_L == LOW) && (IR_R == LOW))//Both sides simultaneously detect obstacles
      {
        forward(num);//Direct line
        return;

      }
      if((IR_L == LOW) && (IR_R == HIGH))//The right side of the obstacles
      {
        left(num);//Turn Left
        return;

      }
      if((IR_L == HIGH) &&( IR_R == LOW))//Obstruction on the left
      {
        right(num);//Turn right
        return;

      }
      if((IR_L == HIGH) && (IR_R == HIGH))//Are detected around, as in the video as encountered in a cross tape
      {
        MOTOR_GO_STOP;//Stop
        return;
       }
    }
/*
*********************************************************************************************************
** Function name ：Get_Distence()
** Function: Ultrasonic measurement of distance
** Entry parameters: none
** Export parameters: none
*********************************************************************************************************
*/
char Get_Distence()//Measure the distance
 {
      digitalWrite(Trig, LOW);   // Let the ultrasonic emission low voltage 2μs
      delayMicroseconds(2);
      digitalWrite(Trig, HIGH);  // So that ultrasonic emissions of high voltage 10μs, where at least 10μs
      delayMicroseconds(10);
      digitalWrite(Trig, LOW);    // Maintain ultrasonic emission Low voltage
      Ldistance = pulseIn(Echo, HIGH);  // Reading difference time difference
      Ldistance= Ldistance/5.8/10;      // Change the time to distance (in centimeters)
    //  Serial.println(Ldistance);      //Show distance
      return Ldistance;

  }
/*
*********************************************************************************************************
** Function name ：Avoid_wave()
** Function: Ultrasonic obstruction
** Entry parameters: none
* ** export parameters: none
* *********************************************************************************************************
*/
void Avoid_wave()//Ultrasonic obstacle avoidance function
{
  Get_Distence();
  if(Ldistance < 15)
      {
          MOTOR_GO_STOP;
      }
      else
      {
           forward(num);
      }
}

/*
*********************************************************************************************************
** Function name ：Send_Distance()
** Function function: Ultrasonic distance PC side display
** Entry parameters: none
** Export parameters: none
*********************************************************************************************************
*/
void Send_Distance()//The ultrasonic distance is displayed on the PC side
{
  int dis= Get_Distence();
  Serial.write(0xff);
  Serial.write(0x03);
  Serial.write(0x00);
  Serial.write(dis);
  Serial.write(0xff);
  delay(1000);
}
/*
*********************************************************************************************************
** Function name ：Delayed()
** Function: Delayed program
** Entry parameters: none
** Export parameters: none
*********************************************************************************************************
*/
void  Delayed()    //Delay 40 seconds and other WIFI module started
{
    int i;
    for(i=0;i<20;i++)
    {
        digitalWrite(ledpin,LOW);
        delay(1000);
        digitalWrite(ledpin,HIGH);
        delay(1000);
    }
}

/*
*********************************************************************************************************
** Function name ：setup().Init_Steer()
**Function: System initialization (serial port, motor, servo, light initialization).
** Entry parameters: none
** Export parameters: none
*********************************************************************************************************
*/
void Init_Steer()//The steering machine is initialized (the angle is the last saved value)
{
   // angle1 = EEPROM.read(0x01);//Read the value in register 0x01
   // angle2 = EEPROM.read(0x02);//Read the value in register 0x02
    angle3 = EEPROM.read(0x03);//Read the value in register 0x04
    angle4 = EEPROM.read(0x04);//Read the value in register 0x05
    angle5 = EEPROM.read(0x05);//Read the value in register 0x06
    angle6 = EEPROM.read(0x06);//Read the value in register 0x07
    angle7 = EEPROM.read(0x07);//Read the value in register 0x08
    angle8 = EEPROM.read(0x08);//Read the value in register 0x09

    if(angle7 == 255 && angle8 == 255)
    {
       // EEPROM.write(0x01,60);//The initial perspective into the address 0x01 inside
       // EEPROM.write(0x02,60);//The initial perspective into the address 0x02 inside
        EEPROM.write(0x03,60);//The initial perspective into the address 0x03 inside
        EEPROM.write(0x04,60);//The initial perspective into the address 0x04 inside
        EEPROM.write(0x05,60);//The initial perspective into the address 0x05 inside
        EEPROM.write(0x06,120);//The initial perspective into the address 0x06 inside
        EEPROM.write(0x07,60);//The initial perspective into the address 0x07 inside
        EEPROM.write(0x08,60);//The initial perspective into the address 0x08 inside
        return;
    }

   // servo1.write(angle1);//Assign the saving angle to the servo 1
   // servo2.write(angle2);//Assign the save angle to the servo 2
    servo3.write(angle3);//Assign the saving angle to the steering gear 3
    servo4.write(angle4);//Assign the saving angle to the steering gear 4
    servo5.write(angle5);//Assign the saving angle to the servo 5
    servo6.write(angle6);//Assign the saving angle to the steering gear  6
    servo7.write(angle7);//Assign the saving angle to the steering gear 7
    servo8.write(angle8);//Assign the saving angle to the servo 8
    num = EEPROM.read(0x10);//Read the value in register 0x10
    if(num==0xff)EEPROM.write(0x10,1);
}

void setup()
{
    pinMode(ledpin,OUTPUT);
    pinMode(ENA,OUTPUT);
    pinMode(ENB,OUTPUT);
    pinMode(INPUT1,OUTPUT);
    pinMode(INPUT2,OUTPUT);
    pinMode(INPUT3,OUTPUT);
    pinMode(INPUT4,OUTPUT);
    pinMode(Input_Detect_LEFT,INPUT);
    pinMode(Input_Detect_RIGHT,INPUT);
    pinMode(Carled, OUTPUT);
    pinMode(Input_Detect,INPUT);
    pinMode(Echo,INPUT);
    pinMode(Trig,OUTPUT);

    Delayed();//Delay 40 seconds and other WIFI module started
    analogWrite(ENB,Left_Speed_Hold);//Assign value to L298 enable B
    analogWrite(ENA,Right_Speed_Hold);//Assign value to L298 enabled side A
    digitalWrite(ledpin,LOW);
    //servo1.attach(SDA);//Define the steering gear 1 control port
    //servo2.attach(SCL);//Define the steering gear 2 control port
    servo3.attach(3);//Define the steering gear 3 control port
    servo4.attach(4);//Define the steering gear 4 control port
    servo5.attach(2);//Define the steering gear 5 control port
    servo6.attach(11);//Define the steering gear 6 control port
    servo7.attach(9);//Define the steering gear 7 control port
    servo8.attach(10);//Define the steering gear 8 control port
    Serial.begin(9600);//The serial port baud rate is set to 9600 bps
    Init_Steer();
}
/*
*********************************************************************************************************
** Function name: loop ()
** Function: Main function
** Entry parameters: none
** Export parameters: none
*********************************************************************************************************
*/
void Cruising_Mod()//Mode function switching function
    {

	 if(Pre_Cruising_Flag != Cruising_Flag)
	 {
	     if(Pre_Cruising_Flag != 0)
		 {
		     MOTOR_GO_STOP;
		 }

    	 Pre_Cruising_Flag =  Cruising_Flag;
	 }
	switch(Cruising_Flag)
	  {

	   case 2:FollowLine(); return;//Line inspection mode
	   case 3:Avoiding(); return;//Obstacle avoidance mode
	   case 4:Avoid_wave();return;//Ultrasonic obstacle avoidance mode
           case 5:Send_Distance();//The ultrasonic distance is displayed on the PC side
	   default:return;
	  }

}

void loop()
  {
    while(1)
    {
        Get_uartdata();
        UartTimeoutCheck();
        Cruising_Mod();
     }
  }



/*
*********************************************************************************************************
** Function name: Communication_Decode ()
** Function: Serial command decode
** Entry parameters: none
** Export parameters: none
*********************************************************************************************************
*/
void Communication_Decode()
{
    if(buffer[0]==0x00)
    {
        switch(buffer[1])   //Motor command
        {
            case 0x01:MOTOR_GO_FORWARD; return;
	    case 0x02:MOTOR_GO_BACK;    return;
	    case 0x03:MOTOR_GO_LEFT;    return;
            case 0x04:MOTOR_GO_RIGHT;   return;
	    case 0x00:MOTOR_GO_STOP;    return;
           default: return;
        }
    }
   else if(buffer[0]==0x01)//Steering command
    {
        if(buffer[2]<1)return;
        switch(buffer[1])
        {
           // case 0x01:angle1 = buffer[2];servo1.write(angle1);return;
           // case 0x02:angle2 = buffer[2];servo2.write(angle2);return;
            case 0x01:if(buffer[2]>170)return;angle3 = buffer[2];servo3.write(angle3);return;
            case 0x02:if(buffer[2]>170)return;angle4 = buffer[2];servo4.write(angle4);return;
            case 0x03:if(buffer[2]>170)return;angle5 = buffer[2];servo5.write(angle5);return;
            case 0x04:if((buffer[2]<110)||(buffer[2]>178))return;angle6 = buffer[2];servo6.write(angle6);return;
            case 0x07:if(buffer[2]>170)return;angle7 = buffer[2];servo7.write(angle7);return;
            case 0x08:if(buffer[2]>170)return;angle8 = buffer[2];servo8.write(angle8);return;
            default:return;
        }
    }

   else if(buffer[0]==0x02)//Speed control
	{
		if(buffer[2]>10)return;

		if(buffer[1]==0x01)//Left gear
		{
                        Left_Speed_Hold=buffer[2]*16+95;//Speed stall is 0 ~ 10 converted into pwm speed pwm less than 95 motor does not turn
                        analogWrite(ENB,Left_Speed_Hold);
		}
                if(buffer[1]==0x02)//On the right
                {
                        Right_Speed_Hold=buffer[2]*16+95;//Speed stall is 0 ~ 10 converted into pwm speed pwm less than 95 motor does not turn
                        analogWrite(ENA,Right_Speed_Hold);
                }else return;
        }
    else if(buffer[0]==0x33)//Read the steering angle and assign the value
	{
		 Init_Steer();return;
        }
    else if(buffer[0]==0x32)//Save command
    {
       // EEPROM.write(0x01,angle1);
       // EEPROM.write(0x02,angle2);
        EEPROM.write(0x03,angle3);
        EEPROM.write(0x04,angle4);
        EEPROM.write(0x05,angle5);
        EEPROM.write(0x06,angle6);
        EEPROM.write(0x07,angle7);
        EEPROM.write(0x08,angle8);
        return;
    }
    	else if(buffer[0]==0x13)//Mode switch
	{
	    switch(buffer[1])
		{

                  case 0x02: Cruising_Flag = 2; return;//巡线
		  case 0x03: Cruising_Flag = 3; return;//Avoidance
		  case 0x04: Cruising_Flag = 4; return;//Radar obstacle avoidance
                  case 0x05: Cruising_Flag = 5; return;//The ultrasonic distance is displayed on the PC side
                  case 0x00: Cruising_Flag = 0; return;//Normal mode
		  default:Cruising_Flag = 0; return;//Normal mode
		}
	}
        else if(buffer[0]==0x05)
    {
        switch(buffer[1])   //
        {
            case 0x00:Open_Light(); return;
	    case 0x01:Close_Light(); return;
            default: return;
        }
    }
        else if(buffer[0]==0x40)//存储电机标志
	{
	   num=buffer[1];
	   EEPROM.write(0x10,num);
	}
}
/*
*********************************************************************************************************
** Function name: Get_uartdata ()
** Function: Read the serial command
** Entry parameters: none
** Export parameters: none
*********************************************************************************************************
*/
void Get_uartdata(void)
{
    static int i;

    if (Serial.available() > 0) //Determines whether the serial buffer is loaded
    {
        serial_data = Serial.read();//Read the serial port
        if(rec_flag==0)
        {
            if(serial_data==0xff)
            {
                rec_flag = 1;
                i = 0;
               Costtime = 0;
            }
        }
        else
        {
            if(serial_data==0xff)
            {
                rec_flag = 0;
                if(i==3)
                {
                    Communication_Decode();
                }
                i = 0;
            }
            else
            {
                buffer[i]=serial_data;
                i++;
            }
        }
    }
}
/*
*********************************************************************************************************
** Function name: UartTimeoutCheck ()
** Function: Serial timeout detection
** Entry parameters: none
** Export parameters: none
*********************************************************************************************************
*/
void UartTimeoutCheck(void)
{
    if(rec_flag == 1)
    {
       Costtime++;
      if(Costtime == 100000)
      {
           rec_flag = 0;
      }
    }
}
