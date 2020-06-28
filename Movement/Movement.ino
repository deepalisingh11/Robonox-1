#include <SoftwareSerial.h>
#include <Servo.h> //Read library for servo motor

SoftwareSerial BTSerial(11, 12);

#define EN1 3 
#define EN2 4 

#define EN3 6  
#define EN4 7 

int carSpeed = 200; 


Servo myservo; //Create an object for servo
int val; // Variable for storing servo angle

void setup() {
  BTSerial.begin(9600);   

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);

  myservo.attach(11); // Set the digital pin 11 as the command pin for determining the servo angle
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {

  int pincode;
//  pincode = /read("scan_barcode.py") //scan and read pincode

  
  if(pincode==1)
  {
    turn_up_30();
    moving_forward();
    delay(1000); //set according to 50m
  }
  else if(pincode==2)
  {
    moving_forward();
    delay(1000); //set according to 50m
  }
  else if(pincode==3)
  {
    turn_down_30();
    moving_forward();
    delay(1000); //set according to 50m
  }
  
}

void turn_up_30()
{
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    val = 0;
    myservo.write(val);
    delay(1500);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    val = -30;
    myservo.write(val);
    delay(1500);
}

void turn_down_30()
{
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    val = 0;
    myservo.write(val);
    delay(1500);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    val = +30;
    myservo.write(val);
    delay(1500);
}

void moving_forward() {
  // A  
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);

  // B  
  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
}

void moving_backward() {
  // A  
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, HIGH);

  // B  
  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
}


void stop_moving() {
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, LOW);
  digitalWrite(EN3, LOW);
  digitalWrite(EN4, LOW);
}   
