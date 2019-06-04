#ifndef TFTScreen_h
#define TFTScreen_h

#include "Arduino.h"
#include "WeatherData.h"

class TFTScreen {

  public:
    void initScreen();
    void writeToScreen(WeatherData &obj);
    int centerText(String str, String str2, int extraChars, int fontSize);
  private:


};

#endif