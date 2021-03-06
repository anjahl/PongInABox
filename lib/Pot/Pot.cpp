#include <Adafruit_IS31FL3731.h>
#include <Arduino.h>
#include <Pot.h>

//#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))


/**
@class Pot
    the soft potentiometer. Defines all of the necessary methods.

@param pin
    the pin of the potentiometer. Please use Reference.
@param display
    the *pointer* to the display that is associated with this potentiometer (make sure that the display, potentiometer and button all belong to the same Player).
@param inverse
    true if the output should be reverse, false otherwise

@todo use Adafruit_IS31FL3731::drawPixel() instead of Adafruit_IS31FL3731::setLEDPWM();

@author Irina Lavryonova (katabeta)
*/
Pot::Pot(uint8_t pin, Adafruit_IS31FL3731* display/* bool inverse*/){
  this->display = display;
  this->pin = pin;
  //this->inverse = inverse;
}

/*public*/
/**
returns the LED number along the bottom of the display that the current status of this pot would light up.

@return the LED number (0-15) that the current status of this pot would light up.
*/
int Pot::getLEDNumRead(){
  int ledNum = inverse ? 15 - 15 * getNormalizedRead() : 15 * getNormalizedRead();
  //return ledNum > 15 ? -1 : ledNum;
  int stuff = ledNum > 15 ? -2 : ledNum;
  //Serial.println(stuff);
  //return ledNum > 15 ? -1 : ledNum;
  return stuff;
}
/**
returns the LED number along the bottom of the display that the current status of this pot would light up.
This method exists mainly for testing and you shouldn't have to use it.

@param min
    the minimum raw value possible for the pot, some margin acceptable. Please use Reference.
@param max
    the maximum raw value possible for the pot, some margin acceptable. Please use Reference.

@return the LED number (0-15) that the current status of this pot would light up.
*/
int Pot::getLEDNumRead(double min, double max){
  int ledNum = inverse ? 15 - 15 * getNormalizedRead(min, max) : 15 * getNormalizedRead(min, max);
  return ledNum > 15 ? -1 : ledNum;
}

/**
Draws the paddle three pixels wide
*/
void Pot::drawPaddle(){
  int x0 = getCoord();
  int y0 = 0;
  int x1 = this->getCoord() +2;
  int y1 = 0;
  display->drawLine(x0,y0,x1,y1,reference.qBright);
  clear(x0, y0, x1, y1);

}

/**
returns paddle coordinate, dumb dumb
*/
int Pot::getCoord(){
  return this->getLEDNumRead() - 1;
}


void Pot::clear(int x0, int y0, int x1, int y1){
  // for(int i=0;i<2;i++){
  //   display->setLEDPWM(getCoord() + i, 0);
  // }
  display->drawLine(x0,y0,x1,y1,0);

}

/*private*/
/**
normalizes the raw reading from the potentiometer. It ranges the output from 0 to 1,
effectively giving the percentage.
See: http://stats.stackexchange.com/questions/70801/how-to-normalize-data-to-0-1-range for more details.
Feeds the getLEDNumRead() method.

@return normalized reading.
*/
double Pot::getNormalizedRead(){
  return (double)(analogRead(pin)-reference.potMin)/(reference.potMax-reference.potMin);
}
/**
normalizes the raw reading from the potentiometer. It ranges the output from 0 to 1,
effectively giving the percentage.
See: http://stats.stackexchange.com/questions/70801/how-to-normalize-data-to-0-1-range for more details.
Feeds the getLEDNumRead() method.
This method exists mainly for testing and you shouldn't have to use it.

@param min
    the minimum raw value possible for the pot, some margin acceptable. Please use Reference.
@param max
    the maximum raw value possible for the pot, some margin acceptable. Please use Reference.

@return normalized reading
*/
double Pot::getNormalizedRead(double min, double max){
  return (double)(analogRead(pin)-min)/(max-min);
}
