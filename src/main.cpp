#include <Wire.h>
#include <Adafruit_IS31FL3731.h>
#include <SoftPot.h>
#include <Pong.h>
#include <Button.h>

Adafruit_IS31FL3731 ledMat1 = Adafruit_IS31FL3731();
Adafruit_IS31FL3731 ledMat2 = Adafruit_IS31FL3731();

SoftPot p1 = SoftPot(1);
SoftPot p2 = SoftPot(2);
Pong game = Pong();
Button pb1 = Button(7); //DO NOT USE PINS 0, 1, 13. THEY WILL NOT WORK!!!
Button pb2 = Button(8);

void setup(){
  if(!ledMat1.begin(0x74)){
    Serial.println("ERROR: IS31_1 not found!");
    while(1);
  } else {
    Serial.println("IS31_1 found");
  }
  if(!ledMat2.begin(0x75)){
    Serial.println("ERROR: IS31_2 no found!");
    while(1);
  } else {
    Serial.println("IS31_2 found");
  }
}

void loop(){
  if(true /*both users are readu*/){
    //game.start(); //<- This causes errors
  }
}
