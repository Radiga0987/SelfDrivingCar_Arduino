
/*Required libraries are imported*/
#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

/*Required Constants are created*/
#define TRIG_PIN A0
#define ECHO_PIN A1  
#define MAXSPEED 125 // maximum speed of DC  motors
#define REVERSE_MAXSPEED 90 // maximum speed of DC motors for reversing

NewPing sonar(TRIG_PIN, ECHO_PIN, 200); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int spd = 0;

/*Initial setup of the system*/
void setup() {

  myservo.attach(10);  
  myservo.write(125); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

/*This loop runs infinitely*/
void loop() {
 int Distance_right = 0;
 int Distance_left =  0;
 delay(40);
 
 /*If distance in front is less than 17, we stop, move back a little and check right and left for object distances*/
 if(distance<=17) 
 {
  Stop();
  delay(80);
  move_backward();
  delay(200);
  Stop();
  delay(150);
  Distance_right = sensor_turn_right(); //sensor turns right and gets distance
  delay(200);
  Distance_left = sensor_turn_left();  //sensor turns left and gets distance
  delay(200);

  /*Depending on whether right side object distance is more or left side, the car moves in that direction by calling the right_turn() or left_turn() functions*/
  if(Distance_right>=Distance_left)
  {
    right_turn();
    Stop();
  }else
  {
    left_turn();
    Stop();
  }
 }else
 {
  move_forward();
 }
 distance = readPing();
}

/*This function is used to obtain the distance of the objects in front*/
int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

/*Function to make sensor turn right and get distance*/
int sensor_turn_right()
{
    myservo.write(55); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(125); 
    return distance;
}

/*Function to make sensor turn left and get distance*/
int sensor_turn_left()
{
    myservo.write(220); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(125); 
    return distance;
    delay(100);
}

/*Function to stop the car*/
void Stop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  } 

/*Function to make car move forward*/  
void move_forward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
   for (spd = 0; spd < MAXSPEED ; spd +=2) // slowly increase speed to preventing battery from loading up
   {
    motor1.setSpeed(spd);
    motor2.setSpeed(spd);
    motor3.setSpeed(spd);
    motor4.setSpeed(spd);
    delay(4);
   }
  }
}

/*Function to make car move backward*/ 
void move_backward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
  for (spd = 0; spd < REVERSE_MAXSPEED; spd +=2) // slowly increase speed to preventing battery from loading up
  {
    motor1.setSpeed(spd);
    motor2.setSpeed(spd);
    motor3.setSpeed(spd);
    motor4.setSpeed(spd);
    delay(4);
  }
}  

/*Function to make car turn right*/ 
void right_turn() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);     
  delay(500);      
} 
 
/*Function to make car turn left*/ 
void left_turn() {
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);  
  motor3.run(FORWARD);
  motor4.run(FORWARD);   
  delay(500);
}
