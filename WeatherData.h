#ifndef Weatherdata_h
#define Weatherdata_h

#include "Arduino.h"

class WeatherData {
    
  public:
    static void getWeatherData(const char *name, const char *data);
    static String tryExtractString(String str, const char* start, const char* end);
    static String translateWeather(int ID);
    
    void setPlace(String placeStr);
    String getPlace();
    
    void setTemperature(String tempStr);
    String getTemperature();
    
    void setWeatherID(String weatherIDStr);
    String getWeatherID();
    
    void setPrecipitation(String precipitationStr);
    String getPrecipitation();
    
    void setWindDeg(String windDegStr);
    String getWindDeg();
    
    void setWindDir(String windDirStr);
    String getWindDir();
    
    void setWindSpeed(String windSpeedStr);
    String getWindSpeed();
    
    void setWindSpeedDesc(String windSpeedDescStr);
    String getWindSpeedDesc();
    
    void setMpsFloat(float mpsFloatFloat);
    float getMpsFloat();
    
  private:
    
    
};

#endif