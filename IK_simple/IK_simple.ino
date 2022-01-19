 /*
  testBraccio90.ino

 testBraccio90 is a setup sketch to check the alignment of all the servo motors
 This is the first sketch you need to run on Braccio
 When you start this sketch Braccio will be positioned perpendicular to the base
 If you can't see the Braccio in this exact position you need to reallign the servo motors position

 Created on 18 Nov 2015
 by Andrea Martino

 This example is in the public domain.
 */

#include <Braccio.h>
#include <Servo.h>

float L1 = 190;
float L2 = 125;
float L3 = 125;

float x;
float y;
float le;
float theta4;
float theta5;
float theta6;
float theta7;
float theta8;

float ThetaA;
float ThetaB;
float ThetaC;



Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;


void setup() {  
  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  //Base (M1):90 degrees
  //Shoulder (M2): 45 degrees
  //Elbow (M3): 180 degrees
  //Wrist vertical (M4): 180 degrees
  //Wrist rotation (M5): 90 degrees
  //gripper (M6): 10 degrees
  Braccio.begin();
  Serial.begin(9600);
}

void loop() {
  /*
   Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
   M1=base degrees. Allowed values from 0 to 180 degrees
   M2=shoulder degrees. Allowed values from 15 to 165 degrees
   M3=elbow degrees. Allowed values from 0 to 180 degrees
   M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
   M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
   M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  */
  
  // the arm is aligned upwards  and the gripper is closed
  
                       //(step delay, M1, M2, M3, M4, M5, M6);
  //Braccio.ServoMovement(20,         90, 45,180,160,90,10);  

	IK(0,150,200);
  delay(2000);
  IK(5*DEG_TO_RAD,150,200);
  delay(2000);
  
  
}

void IK(float theta, float X, float Y){

  x = X - L1 * cos(theta);
  y = Y + L1 * sin(theta);
  
  le = sqrt(sq(x)+sq(y));
  theta4 = atan(y/x);
  theta5 = atan(x/y);

  theta6 = acos((sq(le)+sq(L2)-sq(L3))/(2 * L2 * le));
  theta7 = acos((sq(L3)+sq(le)-sq(L2))/(2 * L3 * le));
  theta8 = acos((sq(L2)+sq(L3)-sq(le))/(2 * L2 * L3));

  ThetaA = PI + theta4 + theta7;
  ThetaB = theta8 - HALF_PI;
  ThetaC = theta6 + theta5 - theta;

  /*
  Serial.print(ThetaA * RAD_TO_DEG);
  Serial.print(", ");
  Serial.print(ThetaB * RAD_TO_DEG);
  Serial.print(", ");
  Serial.print(ThetaC * RAD_TO_DEG);
  Serial.println(", ");
  */
  Braccio.ServoMovement(20,90,ThetaA* RAD_TO_DEG,ThetaB* RAD_TO_DEG,ThetaC* RAD_TO_DEG,90,10);
  }
