#include<Servo.h> //include the servo library
Servo servo; //create a servo object
int button1 = 6;   //pin of the first button
int button2 = 7;  //pin of the second button
int pos = 0;  //initial position
void setup() {
  // put your setup code here, to run once:
  servo.attach(9);  //pin used by the servo motor
  pinMode(button1, INPUT_PULLUP);  //define first button as input pullup
  pinMode(button2, INPUT_PULLUP); //define second button as input pullup
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(button1) == LOW) {
    pos++;  //rotate to left
    delay(5);
    servo.write(pos); 
  }
  if (digitalRead(button2) == LOW) {
    pos--;  //rotate to right
    delay(5);
    servo.write(pos);
  }
}
