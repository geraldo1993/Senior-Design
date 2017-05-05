# COMP 4393 Senior Design Project

BUILDING A 4WD AUTONOMOUS CAR WITH ARDUINO

This project involves building a 4WD car with an ultrasonic sensor that can detect nearby objects and change its direction to avoid these objects. The ultrasonic sensor will be attached to a servo motor which is constantly scanning left and right looking for objects in its way.
<br>

I Will  extend this project by adding more sensors such as ultrasonic sensor to the rear so that the car doesn’t reverse into objects, speed detection sensors to determine speed, line following sensors, and LED brake lights. I will even add light sensors and LEDs to turn headlights on in low-light conditions or a Bluetooth/Wifi connection to control the car through a mobile app.

<iframe width="560" height="315" src="https://www.youtube.com/embed/zsYSi3lcXxE" frameborder="0" allowfullscreen></iframe>

### Parts required

Here is what I  will Use:

1. 1x Arduino Uno board
2. 1x 4WD Robotic Car kit (4 wheels, 4 motors, chassis, AA battery enclosure, screws)
3. 6x AA batteries
4. 1x 9V battery
5. 1x 9V battery power cable barrel jack connector
6. 1x L298N Motor Module
7. 1x Arduino Sensor Shield v5.0
8. 1x HC-SR04 Ultrasonic Sensor
9. 1x Servo motor (any small servo motor will do but if you don’t have one you can leave it out)
10. Assorted color wires:
 - 4x female-to-female wires for Ultrasonic Sensor
 - 8x female-to-female wires for the Motor Module to Sensor Shield
 - 8x bare-ended wires to go from the four motors to the Motor Module
 - 2x bare-ended wires to go from the Motor Module to Sensor Shield
 - 3x wires for the servo motor with female end attaching to Sensor Shield (should already be included with the servo motor)
 - 2x bare-ended wires to go from AA Battery enclosure to the motor Module (should already be included with the battery enclosure)
11. Arduino IDE software – free at http://www.arduino.cc
12. 1x USB cable (A male plug to B male plug)
13. A computer to program with

**Note:** Make sure you get a range of different colors for the wires (eg. red for voltage, black for ground, etc.). Some items such as the battery enclosure, motors and servo motor may come with wires so you may not need to purchase these separately. Some motor modules or sensor shields may use different pins (eg. male or female or just bare-ended wires).

Below are images of the main components you need (apart from the wiring and batteries) – the different robot parts, shields, modules and sensors.






The first thing I Did was  to assemble all the car chassis parts and attach the motors to the wheels.


      
Then started Wiring it up( It Took me almost 6 hours to figure out where which wire goes where ). To make your life easier I'm Including the steps here :


## How to Connect the Wires

1. Connect the red wire (voltage) from the battery enclosure to VCC on the L298N Motor Module.
2. Connect the black wire (ground) from the battery enclosure to GND on the Motor Module.
3. Connect the red wire from Motor A1 (rear left) and the red wire from Motor A2 (front left) to OUT1 on the Motor Module (both wires can be twisted together and will go into OUT1 – the wiring diagram further down this page shows how to do this).
4. Connect the black wire from Motor A1 (rear left) and the black wire from Motor A2 (front left) to OUT2 on the Motor Module.
5. Connect the red wire from Motor B1 (rear right) and the red wire from Motor B2 (front right) to OUT3 on the Motor Module.
6. Connect the black wire from Motor B1 (rear right) and the black wire from Motor B2 (front right) to OUT4 on the Motor Module.
7. Connect a female-to-female end wire from ENA (Engine A) on the Motor Module to signal pin 1 on the Sensor Shield (the #2 pin in the S row. There are three rows – S stands for Signal, V for Voltage and G for Ground).
8. Connect a female-to-female end wire from 5V (next to ENA) on the Motor Module to voltage pin 1 on the Sensor Shield (it doesn’t really matter which pin for voltage as long as it is in the V row).
9. Connect a female-to-female end wire from IN1 on the Motor Module to signal pin 2 on the Sensor Shield.
10. Connect a female-to-female end wire from IN2 on the Motor Module to signal pin 3 on the Sensor Shield.
11. Connect a female-to-female end wire from IN3 on the Motor Module to signal pin 4 on the Sensor Shield.
12. Connect a female-to-female end wire from IN4 on the Motor Module to signal pin 5 on the Sensor Shield.
13. Connect a female-to-female end wire from 5V (next to ENB) on the Motor Module to voltage pin 6 on the Sensor Shield (it doesn’t really matter which pin for voltage as long as it is in the V row).
14. Connect a female-to-female end wire from ENB (Engine B) on the Motor Module to signal pin 6 on the Sensor Shield.
15. Connect the signal wire from the servo motor to signal (S) pin 7 on the Sensor Shield, the voltage wire from the servo motor to the voltage (V) pin 7 on the Sensor Shield, and the ground wire from the servo motor to the GND (G) pin 7 on the Sensor Shield.
16. Attach the Ultrasonic Sensor to the servo motor and then attach the servo motor to the front of the car so that it can scan left and right looking for objects in its path.
You can use sticky tape, blu-tack, glue or a 3D printed/laser cut mount or whatever you like to attach everything, as long as everything is firmly mounted.
17. Use female-to-female end plugs to connect the Ultrasonic sensor to the Sensor Shield. Firstly, attach the TRIG pin from the Ultrasonic sensor to signal (S) pin 8 on the Sensor Shield.
18. Attach the ECHO pin from the ultrasonic sensor to signal (S) pin 9 on the Sensor Shield. Attach the VCC pin from the Ultrasonic Sensor to the voltage (V) pin 10 on the Sensor Shield. Lastly, attach the GND pin from the Ultrasonic Sensor to the GND (G) pin 11 on the Sensor Shield.
19. Now attach the Sensor Shield on top of the Arduino Uno board making sure to not bend any pins. Connect a 9V Battery Barrel Jack Connector to a 9V battery and then plug this in to the Arduino’s barrel jack (see diagram below).
That’s it! After all these long steps I put the batteries and started messing around with the code.

