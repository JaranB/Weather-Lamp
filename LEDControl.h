#ifndef LEDControl_h
#define LEDControl_h

#include "Arduino.h"
#include "WeatherData.h"

class LEDControl {
    
  public:
    void begin();
    void setLight(WeatherData &obj);
    void setColor(int red, int blue);
    void updateRGBLeds(int temp);
    void setRainAndWindLEDS(int wind, int rain);
    
  private:
    
    
};

#endif