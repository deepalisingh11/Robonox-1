//reading neccesary libraries

#include <string.h>
#include <SoftwareSerial.h>
#include <Servo.h> //Read library for servo motor

SoftwareSerial BTSerial(11, 12);

#define EN1 3   
#define EN2 4 
#define EN3 5  
#define EN4 6 
#define relay1 7
#define relay2 8

int carSpeed = 200; 

Servo myservo; //Create an object for servo
Servo myservo_rotation; //Create an object for servo for rotation of parcel

int val; // Variable for storing servo angle

void setup() {
  Serial.begin(9600);   //same for both Rpi and arduino

  //motor
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);

  
  //servo
  myservo.attach(11); // Set the digital pin 11 as the command pin for determining the servo angle
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);

  //servo-rotation
  myservo_rotation.attach(2); // Set the digital pin 11 as the command pin for determining the servo angle
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  

  //linear actuator
  //Set pinMode to OUTPUT for the two relay pins
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop() {

    bool new_pincode=false;
    String pincode;

    if (Serial.available() > 0) {

      pincode += Serial.readString();
    
    }


  
    if(pincode=="location1")
    {
      turn_up_30();
      moving_forward();
      delay(1000); //set according to 50m
  
      //After reaching the final spot the bar pushes parcel with linear motor
      push();
      delay(200); //time set according to dimension of bot.
      back();
      delay(200); //time set according to dimension of bot.
    }
    else if(pincode=="location2")
    {
      moving_forward();
      delay(1000); //set according to 50m
  
      //After reaching the final spot the bar pushes parcel with linear motor
      push();
      delay(200); //time set according to dimension of bot.
      back();
      delay(200); //time set according to dimension of bot.
    }
    else if(pincode=="location3")
    {
      turn_down_30();
      moving_forward();
      delay(1000); //set according to 50m
  
      //After reaching the final spot the bar pushes parcel with linear motor
      push();
      delay(200); //time set according to dimension of bot.
      back();
      delay(200); //time set according to dimension of bot.
    }

    rotate(); //If no barrcode is found on the surface then the rotator on bottom rotates it.
  
}


// thid function is used to rotate parcel if no barcode find on that side of parcel

void rotate()
{
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    val = 0;
    myservo_rotation.write(val);
    delay(1500);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    val = +90;
    myservo.write(val);
    delay(1500);
}

// function is defined to push the parcel by bar during unloading parcel after seperation

void push()
{
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
}


void back()
{
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
}

// turn_up_30 is used to to turn up servo motor by 30 to start moving the bot

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

// turn_down_30 is used to to turn down servo motor by 30 to start stop moving bot

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

// moving_forward function is use to start moving bot forward

void moving_forward() {
  // A  
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);

  // B  
  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
}

// moving_backward function is defined to start moving bot backward 

void moving_backward() {
  // A  
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, HIGH);

  // B  
  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
}


// stop_moving function is used to stop the bot during seperation process

void stop_moving() {
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, LOW);
  digitalWrite(EN3, LOW);
  digitalWrite(EN4, LOW);
}   
