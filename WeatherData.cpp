#include "WeatherData.h"

#include "Arduino.h"

String place;
String temperature;
String weatherID;
String precipitation;
String windDeg;
String windDir;
String windSpeed;
String windSpeedDesc;
float mpsFloat;

void WeatherData::getWeatherData(const char *name, const char *data) {

    //Denne metoden tar imot dataen hentet fra værstasjonen. Vi deler opp dataen i flere strenger med kun de verdiene vi ønsker å bruke.

  String str = String(data); //Setter all dataen i en streng

    //Setter strengenes verdi til det som befinner seg mellom de to strengene angitt.
  place = tryExtractString(str, "place", "municipality");
  temperature = tryExtractString(str, "value", "}}]}}");
  weatherID = tryExtractString(str, "numberEx", "precipitation");
  precipitation = tryExtractString(str, "precipitation", "windDirection");
  windDeg = tryExtractString(str, "deg", "code");
  windDir = tryExtractString(str, "code", "id");
  windSpeed = tryExtractString(str, "mps", "temperature");
  windSpeedDesc = tryExtractString(str, "mps", "temperature");

  place.remove(0, 3); //Fjerner de tre første tegnene i strengen.
  place[place.length() - 3] = '\0'; //Fjerner de tre siste tegnene i strengen

  temperature.remove(0, 3);
  temperature[temperature.length() - 1] = '\0';

  weatherID.remove(0, 3);
  char buf[50]; //Char array for å skrive strengen over til en char array
  weatherID.toCharArray(buf, 50);
  weatherID = atoi(buf); //Benytter atoi for å hente ut integer verdien i strengen

  precipitation.remove(0, 3);
  precipitation[precipitation.length() - 3] = '\0'; *

  windDeg.remove(0, 3);
  windDeg[windDeg.length() - 3] = '\0';

  windDir.remove(0, 3);
  windDir[windDir.length() - 3] = '\0';

  windSpeed.remove(0, 3);
  memset(buf, 0, sizeof buf); //Tømmer char arrayen 'buf'
  windSpeed.toCharArray(buf, 50);
  mpsFloat = atof(buf); //Benytter atof for å få float/double verdien i strengen

  int charsToRemove = 16;
  if (windSpeed.toInt() > 9) { //Fjerner 16 eller 17 chars avhengig av vind verdien
    charsToRemove = 17;
  }

  windSpeedDesc.remove(0, charsToRemove);
  windSpeedDesc[windSpeedDesc.length() - 4] = '\0';

    //Om dataen har blitt funnet printes den ut i serial loggen
  if (place != NULL) {
    Serial.println("Sted: " + place);
  }

  if (temperature != NULL) {
    Serial.println("Temperatur: " + temperature);
  }

  if (weatherID != NULL) {
    Serial.println("Vær: " + weatherID);
  }
  
  if (precipitation != NULL) {
    Serial.println("Nedbør: " + precipitation);
  }

  if (windDeg != NULL) {
    Serial.println("Vindretning°: " + windDeg);
  }

  if (windDir != NULL) {
    Serial.println("Vindretning: " + windDir);
  }

  if (windSpeed != NULL) {
    Serial.println("Vindhastighet: " + String(mpsFloat));
  }

  if (windSpeedDesc != NULL) {
    Serial.println("Vind tekst: " + windSpeedDesc);
  }

}

String WeatherData::tryExtractString(String str, const char* start, const char* end) {
    //Metode som leter mellom to strenger som settes i parameterene og returnerer verdien
  if (str == NULL) {
    return "";
  }

  int idx = str.indexOf(start);
  if (idx < 0) {
    return "";
  }

  int endIdx = str.indexOf(end);
  if (endIdx < 0) {
    return "";
  }

  return str.substring(idx + strlen(start), endIdx);
}

String WeatherData::translateWeather(int ID) {
    //Denne metoden inneholder ett switch statement som tar imot en int som representerer statusen på været. Er statusen rapportert fra værstasjonen 1 vil metoden returnere "Sol".
  switch (ID) {
    case 1:
      return "Sol";
      break;
    case 2:
      return "Lyse skyer";
      break;
    case 3:
      return "Delvis skyet";
      break;
    case 4:
      return "Skyer";
      break;
    case 5:
      return "Lett regn og sol";
      break;
    case 6:
      return "Lett regn,sol,torden";
      break;
    case 7:
      return "Sludd og sol";
      break;
    case 8:
      return "Snø og sol";
      break;
    case 9:
      return "Lett regn";
      break;
    case 10:
      return "Regn";
      break;
    case 11:
      return "Regn og torden";
      break;
    case 12:
      return "Sludd";
      break;
    case 13:
      return "Snø";
      break;
    case 14:
      return "Snø og torden";
      break;
    case 15:
      return "Tåke";
      break;
    case 20:
      return "Sludd, sol, torden";
      break;
    case 21:
      return "Snø, sol, torden";
      break;
    case 22:
      return "Lett regn, torden";
      break;
    case 23:
      return "Sludd og torden";
      break;
    case 24:
      return "Duskregn,torden,sol";
      break;
    case 25:
      return "Regn, torden, sol";
      break;
    case 26:
      return "Torden,sol,lett sludd";
      break;
    case 27:
      return "Torden,sol,mye sludd";
      break;
    case 28:
      return "Torden,sol,lett snø";
      break;
    case 29:
      return "Torden,sol,mye snø";
      break;
    case 30:
      return "Duskregn og torden";
      break;
    case 31:
      return "Torden og lett sludd";
      break;
    case 32:
      return "Torden, kraftig sludd";
      break;
    case 33:
      return "Torden og lett snø";
      break;
    case 34:
      return "Torden og mye snø";
      break;
    case 40:
      return "Duskregn og sol";
      break;
    case 41:
      return "Regn og sol";
      break;
    case 42:
      return "Lett sludd og sol";
      break;
    case 43:
      return "Mye sludd og sol";
      break;
    case 44:
      return "Sol og lett snø";
      break;
    case 45:
      return "Sol og mye snø";
      break;
    case 46:
      return "Duskregn";
      break;
    case 47:
      return "Lett sludd";
      break;
    case 48:
      return "Mye sludd";
      break;
    case 49:
      return "Lett snø";
      break;
    case 50:
      return "Mye snø";
      break;
    default:
      break;
  }

}

//set og get metoder for alle verdiene vi vil ha tilgang til fra en annen klasse
void WeatherData::setPlace(String placeStr) {
  place = placeStr;
}

String WeatherData::getPlace() {
  return place;
}

void WeatherData::setTemperature(String tempStr) {
  temperature = tempStr;
}

String WeatherData::getTemperature() {
  return temperature;
}

void WeatherData::setWeatherID(String weatherIDStr) {
  weatherID = weatherIDStr;
}

String WeatherData::getWeatherID() {
  return weatherID;;
}

void WeatherData::setPrecipitation(String precipitationStr) {
  precipitation = precipitationStr;
}

String WeatherData::getPrecipitation() {
  return precipitation;
}

void WeatherData::setWindDeg(String windDegStr) {
  windDeg = windDegStr;
}

String WeatherData::getWindDeg() {
  return windDeg;
}

void WeatherData::setWindDir(String windDirStr) {
  windDir = windDirStr;
}

String WeatherData::getWindDir() {
  return windDir;
}

void WeatherData::setWindSpeed(String windSpeedStr) {
  windSpeed = windSpeedStr;
}

String WeatherData::getWindSpeed() {
  return windSpeed;
}

void WeatherData::setWindSpeedDesc(String windSpeedDescStr) {
  windSpeedDesc = windSpeedDescStr;
}

String WeatherData::getWindSpeedDesc() {
  return windSpeedDesc;
}

void WeatherData::setMpsFloat(float mpsFloatFloat) {
  mpsFloat = mpsFloatFloat;
}

float WeatherData::getMpsFloat() {
  return mpsFloat;
}