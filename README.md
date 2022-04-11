# Servo-Motor-Control
This is the midterm project for ECE 387 - Basic Chip/Peripheral Interfacing. My topic is Servo Motor and Control. 
## What is a Servo Motor
A servo motor is a self-contained electrical device, that rotate parts of a machine with high efficiency and with great precision. The output shaft of this motor can be moved to a particular angle, position and velocity that a regular motor does not have. Not like rotate continuously like DC/AC motors, servo motor is used to move to a particular position and then stopped and held there. Most servo motors can rotate about 90 to 180 degree. In this project, I choose SG90 Servo Motor because it is cheap and very easy to use. 
## Servo Motor SG90
![image](https://user-images.githubusercontent.com/98714679/162656191-089c8173-14a3-440d-9e0b-5d8811a9b20b.png)

I found a SG90 in Arduino Starter Kit, and here is its component:

![image](https://user-images.githubusercontent.com/98714679/162656402-46175482-bad5-4120-a1fe-1748e845e066.png)

SG90 as a micro servo motor, it can only rotate approximately 180 degrees(0 to 180 drgrees).

## Datasheet of SG90

![image](https://user-images.githubusercontent.com/98714679/162656725-45bea092-9e21-40bd-b867-c607d5e09384.png)

If you would like to create a simple project using Arduino Board by own. This datasheet is very helpful, you may know how to wire this with an Arduino Board. 

Given Orange = signal 
input. Red = +5V, Brown = 0V. We can know brown should connect to the ground, red 
should connect to the 5V power cable, and orange should connect to the digital pin.

## How a Servo Motor Rotate its Position
After connected to Arduino Board, servo motor sends an electrical pulse of variable width, or PWM, through the control wire.
Based on the duration of the pulse sent, the rotor will turn to the desired position. Which means when a PWM signal is applied to its control pin, the shaft rotates to a specific angle depending on the pulse’s duty cycle.

![image](https://user-images.githubusercontent.com/98714679/162657817-4228fcde-6cf2-414f-bed2-b11431128c22.png)

Searching the datasheet, we found for SG90:

- 0 ms = 0 degree.
- 1.5 ms = 90 degrees. (Neutral position)
- 2 ms = 180 degrees.

## My Arduino Connection
Here is a simple program to display how to control a servo motor with two push-buttons. 

![image](https://user-images.githubusercontent.com/98714679/162658856-80f03c51-9d93-4b07-9844-fe5e94e69f6d.png)

There are two code for my project: 

Arduino code by Arduino IDE(Servo.ino): Button 1 to control motor rotate to left(90 degrees to 0 degrees), button 2 to control motor rotate to right(90 degrees to 180 degrees). Max 90 degree each position. But you can stop its rotation at any time, which means when you pressed button 1, motor statred to rotate to left, when you see it rotate to 30 degree or 45 degree or 76 degree, you can released button 1, and the rotation will stop. 

C code(Servo.c): When you pressed button 1, the motor will automatically rotate to 0 degree, when you pressed button 2, the motor will automatically rotate to 180 degrees. it cannot stop during ritation process. 

Note: The Arduino code works good, but C code meets some problem, I will still work on the C code in the future. 

## Guide to Compile
Please Note that in the wire diagram, the two buttons connect to pin 5 and pin 6 on Arduino Board, but in my code, I define a diferent pin. So when you try to wire by yourself, please refer to my code not the wire diagram. 
1. For C programs, that are compilable with avr-gcc:

Download the Servo_C_Program file to your computer, put the Servo.c file to your correct path:\avr-gcc\bin.

Open Windows Power Shell, Type the following command:
- avr-gcc.exe -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o Servo.o Servo.c
- avr-gcc.exe -mmcu=atmega328p Servo.o -o Servo
- avr-objcopy.exe -O ihex -R .eeprom Servo Servo.hex
- avrdude.exe -patmega328p -Pcom3 -carduino -D -U flash:w:Servo.hex:i

2. For Servo.ino file:

Download Servo_Arduino file, and open it on Arduino IDE. 
(Note here that com3 was the port that connected to my Arduino and please find the right com port of your Arduino.)

##Video Demo
Youtube Link: https://youtu.be/FjnOG83n8Nk

## Reference
- http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf

- https://www.jameco.com/Jameco/workshop/Howitworks/how-servo-motors-work.html

- https://wired.chillibasket.com/2020/05/servo-trajectory/

- https://embedds.com/controlling-servo-motor-with-avr/

- https://mechatrofice.com/arduino/servo-motor-push-button-control
