#include "stdint.h"
#include "Wheel.h"
#include "Robot.h"

// Left Wheel Ports
uint8_t ENA = 10;
uint8_t IN1 = 9;
uint8_t IN2 = 8;
uint8_t IRA = A3;

// Right Wheel Ports
uint8_t IN3 = 7;   
uint8_t IN4 = 6;  
uint8_t ENB = 5;
uint8_t IRB = A1;

Wheel leftWheel;
Wheel rightWheel;
Robot robot;


 //       note, period, &  frequency.
 #define  C     2100
 #define  D     1870 
 #define  E     1670
 #define  f     1580    // Does not seem to like capital F
 #define  G     1400 
 // Define a special note, 'R', to represent a rest
 #define  R     0

 int speakerOut = 3;

 // MELODY and TIMING  =======================================
 //  melody[] is an array of notes, accompanied by beats[],
 //  which sets each note's relative length (higher #, longer note)
 int melody[] = {E, E, E,R,
 E, E, E,R,
 E, G, C, D, E, R,
 f, f, f,f, f, E, E,E, E, D ,D,E, D, R, G ,R,
 E, E, E,R,
 E, E, E,R,
 E, G, C, D, E, R,
 f, f, f,f, f, E, E, E,  G,G, f, D, C,R };
 int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
 // Set overall tempo
 long tempo = 10000;
 // Set length of pause between notes
 int pause = 1000;
 // Loop variable to increase Rest length
 int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES
 // Initialize core variables
 int tone_ = 0;
 int beat = 0;
 long duration  = 0;
 // PLAY TONE  ==============================================
 // Pulse the speaker to play a tone for a particular duration
 void playTone() {
   long elapsed_time = 0;
   if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
     //  played less long than 'duration', pulse speaker HIGH and LOW
     while (elapsed_time < duration) {
       digitalWrite(speakerOut,HIGH);
       delayMicroseconds(tone_ / 2);
       // DOWN
       digitalWrite(speakerOut, LOW);
       delayMicroseconds(tone_ / 2);
       // Keep track of how long we pulsed
       elapsed_time += (tone_);
     }
   }
   else { // Rest beat; loop times delay
     for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
       delayMicroseconds(duration); 
     } 
   }                                
 }




void setup()
{
  Serial.begin(9600);
  
  pinMode(speakerOut, OUTPUT);
  
  rightWheel.setup(ENB, IN3, IN4, IRB, 1);
  leftWheel.setup(ENA, IN1, IN2, IRA, 0.75); // 0.75    0.7826086957
  robot.setup(&leftWheel, &rightWheel);
}


int val = 0;
char command[4];

int getLeftWheelSpeed(int rightWheelSpeed)
{
  // 90 / 115 - 0.7826086957
  // 90 / 114 - 0.7894736842
  return 0.75 * rightWheelSpeed;
}

void loop()
{ 
//robot.moveFor(Wheel::convertMillimetersToSteps(326), Wheel::FORWARD);

//  int index = 0;
//  while (Serial.available()) 
//  {
//    delay(10); 
//    if (Serial.available() > 0) 
//    {
//      command[index] = Serial.read();
//      index++;
//    }
//  }
//
//  if (strlen(command) != 0)
//  {
//    Serial.println(command);
//    
//    char function = command[0];
//    uint16_t param = (100 * (command[1] - '0')) + (10 * (command[2] - '0')) + (1 * (command[3] - '0'));
//
//    Serial.println(function);
//    Serial.println(param);
//  
//    switch(function)
//    {
//      case 'w':
//        robot.moveFor(Wheel::convertMillimetersToSteps(param), Wheel::FORWARD);
//        robot.stop();
//        break;
//      case 'd':
//        robot.turnRight(param);
//        robot.stop();
//        break;
//      case 'a':
//        robot.turnLeft(param);
//        robot.stop();
//        break;
//    }
//  }
//
//  command[0] = 0;
//  command[1] = 0;
//  command[2] = 0;
//  command[3] = 0;







  delay(5000);

  robot.moveFor(Wheel::convertMillimetersToSteps(270), Wheel::FORWARD);
  robot.stop(); delay(1000);
//  
  robot.turnRight(60);  // 60
  robot.stop(); delay(1000);
//  
  robot.moveFor(Wheel::convertMillimetersToSteps(40), Wheel::FORWARD);
  robot.stop(); delay(1000);
  
  robot.turnRight(60); // 60 
  robot.stop(); delay(1000);
//  
  robot.moveFor(Wheel::convertMillimetersToSteps(30), Wheel::FORWARD);
  robot.stop(); delay(1000);

  robot.turnLeft(80);
  robot.stop(); delay(1000);
  
  robot.moveFor(Wheel::convertMillimetersToSteps(100), Wheel::FORWARD);
  robot.stop(); delay(1000);
////  
////  robot.turnRight(50);
////  robot.stop(); delay(1000);
////  
////  robot.moveFor(Wheel::convertMillimetersToSteps(120), Wheel::FORWARD);
////  robot.stop(); delay(1000);
//  
////  robot.turnRight(50);
////  robot.stop(); delay(1000);
////  
////  robot.moveFor(Wheel::convertMillimetersToSteps(120), Wheel::FORWARD);
////  robot.stop(); delay(1000);
////  
////  robot.turnRight(40);
////  robot.stop(); delay(1000);
////  
////  robot.moveFor(Wheel::convertMillimetersToSteps(500), Wheel::FORWARD);
////  robot.stop(); delay(1000);
//
  robot.twerking();
  robot.stop(); delay(1000);

  for (int i=0; i<MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = 50;

    duration = beat * tempo; // Set up timing

    playTone();
    // A pause between notes...
    delayMicroseconds(pause);
  }
  
  delay(5000);delay(5000);delay(5000);
        
        
  















  
  
  
//  Serial.println(analogRead(A3));
//    Serial.println(analogRead(A1));
//    delay(10);

//delay(5000);
//robot.moveFor(Wheel::convertMillimetersToSteps(326), Wheel::FORWARD);
//robot.turnRight(45);
//robot.stop();
//delay(5000);
//
//  delay(5000);
//  robot.spinInRight(75);
//  robot.stop();
//    
//  delay(5000);
////  robot.moveFor(250, Wheel::FORWARD);
//
//  Serial.println("robot.startSmoothly(255);");
//  robot.startSmoothly(255);
//
//  Serial.println("robot.moveFor(Wheel::convertMillimetersToSteps(326), Wheel::FORWARD);");
//  robot.moveFor(Wheel::convertMillimetersToSteps(326), Wheel::FORWARD);
//
//  Serial.println("robot.followCircleInRight(380, Wheel::convertMillimetersToSteps(233));");
//  robot.followCircleInRight(380, Wheel::convertMillimetersToSteps(233));
//
//  Serial.println("robot.followCircleInRight(300, Wheel::convertMillimetersToSteps(233));");
//  robot.followCircleInLeft(300, Wheel::convertMillimetersToSteps(233));

//  Serial.println("robot.followCircleInRight(360, Wheel::convertMillimetersToSteps(233));");
//  robot.followCircleInRight(360, Wheel::convertMillimetersToSteps(197));
//
//  Serial.println("robot.moveFor(Wheel::convertMillimetersToSteps(326), Wheel::FORWARD);");
//  robot.moveFor(Wheel::convertMillimetersToSteps(150), Wheel::FORWARD); // 150
//
//  Serial.println("robot.turnRight(45);");
//  robot.turnRight(45);
//
//  Serial.println("robot.moveFor(Wheel::convertMillimetersToSteps(257), Wheel::FORWARD);");
//  robot.moveFor(Wheel::convertMillimetersToSteps(257), Wheel::FORWARD);
//
//  Serial.println("robot.turnRight(53);");
//  robot.turnRight(53);
//
//  Serial.println("robot.moveFor(Wheel::convertMillimetersToSteps(650), Wheel::FORWARD);");
//  robot.moveFor(Wheel::convertMillimetersToSteps(650), Wheel::FORWARD);
  
//  robot.stop();
//  delay(5000);
//  
//  leftWheel.move(Wheel::FORWARD, 90);
//  rightWheel.move(Wheel::FORWARD, 114);  
//  delay(5000);
//  delay(5000);
//  delay(5000);

//  int speed = 200;
//
//  delay(5000);
//
//  for (int i = 0; i < speed; i++)
//  {
//    leftWheel.move(Wheel::FORWARD, getLeftWheelSpeed(i));
//    rightWheel.move(Wheel::FORWARD, i);  
//    delay(10);
//  }
//  
//  delay(1000);
//  leftWheel.move(Wheel::FORWARD, getLeftWheelSpeed(speed));
//  rightWheel.move(Wheel::FORWARD, speed);
////  delay(1000);
//
//  for (int i = speed; i > 0; i--)
//  { 
//    leftWheel.move(Wheel::FORWARD, getLeftWheelSpeed(i));
//    rightWheel.move(Wheel::FORWARD, i);  
//    delay(10);
    
//
//    unsigned long j = millis() + 100;
//
//    while (j > millis())
//    {
//      leftWheel->updateDistance();
//      rightWheel->updateDistance(); 
//    }
//  }
  
  
//  leftWheel.move(Wheel::FORWARD, 50);
//  delay(30);
//  leftWheel.move(Wheel::FORWARD, 85);
//  delay(5000);

   
//  for (int i = 0; i < this->normalSpeed; i++)
//  { 
//    leftWheel->move(Wheel::FORWARD, i);
//    rightWheel->move(Wheel::FORWARD, (i + 50) < 255 ? i + 50 : 255);  
//
//    unsigned long j = millis() + 100;
//
//    while (j > millis())
//    {
//      leftWheel->updateDistance();
//      rightWheel->updateDistance(); 
//    }
//  }
  









  
//  char buffer[50];
//  sprintf(buffer, "Left: %d Right: %d", analogRead(IRA), analogRead(IRB));
//  Serial.println(analogRead(IRA));
//  Serial.println(analogRead(IRB));
//  
//  delay(100);
  
//  leftWheel.move(Wheel::FORWARD, 200);
//  rightWheel.move(Wheel::BACKWARD, 50);
  
//  digitalWrite(12, HIGH);

//  rightWheel.move(Wheel::FORWARD, 50);
//  val = analogRead(IRB);
//  Serial.println(val);
//  delay(100);

//  robot.move(Wheel::BACKWARD);
//robot.moveFor(Wheel::convertMilimitersToSteps(200), Wheel::FORWARD);
//robot.moveFor(3, Wheel::BACKWARD);
//robot.moveFor(100, Wheel::BACKWARD);
//robot.moveFor(100, Wheel::FORWARD);
//robot.stop();
//delay(5000);

//  val = analogRead(IR_LED_PIN);
//  
//  if (val < 200){
//    Serial.print("L\n");
//  }
//  else{
//    Serial.print("H\n");
//  }
  
//  rightWheel.stop();
//  leftWheel.stop();
//  delay(3000);
//  rightWheel.move(Wheel::FORWARD, 200);
//  delay(3000);
//  rightWheel.move(Wheel::BACKWARD, 200);
//  delay(3000);
//  rightWheel.stop();
//  leftWheel.move(Wheel::FORWARD, 200);
//  delay(3000);
//  leftWheel.move(Wheel::BACKWARD, 200);
//  delay(3000);

//  robot.moveForward();

//  robot.turnLeft(32);
//  robot.moveFor(Wheel::convertMilimitersToSteps(200), Wheel::FORWARD);
//  robot.followCircleInRight(180, Wheel::convertMilimitersToSteps(100));
//  uint16_t steps = 2 * PI * 300 * 180 / 360 ;
//  Serial.println(steps);

 
//  robot.followCircleInRight(180, Wheel::convertMilimitersToSteps(233));
//  robot.stop();
//  delay(5000);
//  
//  robot.followCircleInLeft(180, Wheel::convertMilimitersToSteps(233));
//  robot.stop();
//  delay(5000);

//

//leftWheel.move(255);
//
//  Serial.print("Left: ");
//  Serial.println(analogRead(A3));
//  Serial.print(" Right: ");
//  Serial.println(analogRead(A1));
//  Serial.println();

//  robot.moveFor(100, Wheel::FORWARD);
//  robot.stop();
//  delay(5000);

//  robot.turnRight(60);
//  robot.stop();
//  delay(1000);
//
//  robot.turnRight(60);
//  robot.stop();
//  delay(1000);
//
//  robot.moveFor(Wheel::convertMilimitersToSteps(100), Wheel::FORWARD);
//  robot.stop();
//  delay(1000);
//  
//  robot.followCircleInRight(180, Wheel::convertMilimitersToSteps(233));
//  robot.stop();
//  delay(1000);
//
//  robot.followCircleInRight(180, Wheel::convertMilimitersToSteps(233));
//  robot.stop();
//  delay(1000);
//  
//  robot.followCircleInLeft(180, Wheel::convertMilimitersToSteps(233));
//  robot.stop();
//  delay(1000);
//  
//  robot.followCircleInRight(180, Wheel::convertMilimitersToSteps(197));
//  robot.stop();
//  delay(1000);
//  
//  robot.moveFor(Wheel::convertMilimitersToSteps(300), Wheel::FORWARD);
//  robot.stop();
//  delay(1000);
//
//  robot.turnRight(45);
//  robot.stop();
//  delay(1000);
//
//  robot.moveFor(Wheel::convertMilimitersToSteps(257), Wheel::FORWARD);
//  robot.stop();
//  delay(1000);
//
//  robot.turnRight(53);
//  robot.stop();
//  delay(1000);
//
//  robot.moveFor(Wheel::convertMilimitersToSteps(650), Wheel::FORWARD);
//  robot.stop();
//  delay(1000);

//  robot.moveFor(96, Wheel::FORWARD);
//
////  robot.followCircleInRight(180, Wheel::convertMilimitersToSteps(233));
////  robot.stop();
//  delay(10000);

//  rightWheel.move(Wheel::FORWARD, 200);
//  Serial.println(analogRead(A1));
//  delay();
}
