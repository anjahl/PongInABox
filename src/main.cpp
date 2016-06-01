#include <Adafruit_IS31FL3731.h>
#include <Arduino.h>
#include <string.h>
#include <Reference.h>
#include <Pot.h>
#include <Ball.h>
#include <Player.h>
#include <Game.h>

Reference reference = Reference();
Adafruit_IS31FL3731 ledmatrix74 = Adafruit_IS31FL3731();
Adafruit_IS31FL3731 ledmatrix75 = Adafruit_IS31FL3731();
Button button1 = Button(reference.dPin74R);
Button button2 = Button(reference.dPin75R);
Button confButton = Button(reference.dPin0);
Pot pot1 = Pot(reference.aPin74,&ledmatrix74);
Pot pot2 = Pot(reference.aPin75,&ledmatrix75);
Player player1 = Player(&button1, &pot1, &ledmatrix74, 1);
Player player2 = Player(&button2, &pot2, &ledmatrix75, 2);
Ball ball = Ball(0,0,&player1,&player2);
long lastTime = 0;


Pot pots[] = {Pot(reference.aPin74, &ledmatrix74), Pot(reference.aPin75, &ledmatrix75)};
Game game = Game(&player1, &player2, &confButton, &ball, false, 5);

void setup(){
  Serial.begin(9600);
  Serial.println("On/Off");

  if(!ledmatrix74.begin(reference.address74) || !ledmatrix75.begin(reference.address75)){
    Serial.println("Error! Display not found!");
    while(1);
  }
  Serial.println("Display found");
  ledmatrix75.setRotation(2);
}

  //TODO create a calibration method
  void loop(){
    //ledmatrix74.setLEDPWM(pots[0].getLEDNumRead(reference.potMin, reference.potMax), 254);
    //delay(05);
    //ledmatrix74.clear();
    //ledmatrix75.setLEDPWM(pots[1].getLEDNumRead(reference.potMin, reference.potMax), 254);
    //delay(05);
    // ledmatrix74.clear();
    // ledmatrix75.clear();

    if(millis() - lastTime > 100) {
       lastTime = millis();
       if(!game.gameEnd()){
      ball.drawBall();
    }




    // ledmatrix74.setLEDPWM(pot1.getLEDNumRead(), 254);
    player1.pot->drawPaddle();
    player2.pot->drawPaddle();

    if(game.gameEnd()){
      Serial.println(player1.score);
      Serial.println(player2.score);
      if (player1.score > player2.score){
        game.drawLoseAnim(&player2);
        game.drawWinAnim(&player1);

      }
      if (player2.score > player1.score){
        game.drawLoseAnim(&player1);
        game.drawWinAnim(&player2);

      }

    }
      //Serial.println(String(analogRead(reference.aPin75)));
  }
}
