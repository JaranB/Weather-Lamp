#include "TFTScreen.h"
#include "WeatherData.h"

#include "Arduino.h"
#include <Adafruit_ST7735.h>

#define cs   A2
#define dc   A1
#define rst  A0

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

void TFTScreen::initScreen() {
  
  tft.initR(INITR_BLACKTAB); //Initialiserer TFT skjermen
  tft.fillScreen(ST7735_WHITE); //Skriver skjermen hvit

}

void TFTScreen::writeToScreen(WeatherData &obj) {

    //Denne metoden skriver dataen hentet fra ønsket værstasjon på TFT skjermen.

  tft.fillScreen(ST7735_WHITE); //Skriver skjermen hvit

  tft.setTextSize(1); //Setter tekst størrelse
  tft.setTextColor(ST7735_RED); //Setter farge på teksten

  tft.setCursor(centerText(obj.getPlace(), "", 0, 1), 10); //Setter cursoren på skjermen til ønsket posisjon hvor jeg vil starte å skrive. Benytter en centerText metode jeg har laget for å regne ut riktig cursor plass for å sentrere teksten.
  tft.print(obj.getPlace()); //Skriver teksten til skjermen

  tft.setCursor(centerText(obj.translateWeather(obj.getWeatherID().toInt()), "", 0, 1), 30);
  tft.print(obj.translateWeather(obj.getWeatherID().toInt()));

  tft.setTextSize(3);
  tft.setCursor(centerText(obj.getTemperature(), "",  2, 3), 55);
  tft.print(obj.getTemperature());
  tft.print((char)247);
  tft.print("C");

  tft.setTextSize(1);

  tft.setCursor(centerText(obj.getWindSpeedDesc(), "", 0, 1), 90);
  tft.print(obj.getWindSpeedDesc());

  tft.setTextSize(2);
  char mpsTwoDecimals[10];
  sprintf(mpsTwoDecimals, "%d.%02d", (int)obj.getMpsFloat(), (int)(obj.getMpsFloat() * 100) % 100);
  tft.setCursor(centerText((String)(mpsTwoDecimals), "", 3, 2), 110);

  tft.print(mpsTwoDecimals);
  tft.print("m/s");

  tft.setCursor(centerText(String(obj.getWindDeg()), String(obj.getWindDir()), 2, 2), 135);
  tft.print(obj.getWindDeg());
  tft.print((char)247);
  tft.print(" ");
  tft.print(obj.getWindDir());

}

int TFTScreen::centerText(String str, String str2, int extraChars, int fontSize) {

    //Denne metoden tar imot flere parametere og regner ut verdien vi trenger for å sentrere ønsket tekst som skal skrives til TFT skjermen.
    //Vi må vite hvor mange characters det er i strengen(mulighet for å sende to strenger om man vil ha to strenger/verdier på samme linje).
    //Skal man skrive noe ekstra på samme linje kan man oppgi hvor mange characters det man vil legge til er i extraChars. Si man skal legge til ett mellomrom på samme linjen setter man extraChars til 1.
    //Til slutt må vi sette tekst størrelsen på det vi vil sentrere.

  int i;
  i = strlen(str) + strlen(str2) + extraChars;

  if (fontSize == 1) {
    if ((i % 2) == 0) {
      if (str2 == "") {
        return (tft.width() / 2) - (((strlen(str) + extraChars) / 2) * 6);
      } else {
        return (tft.width() / 2) - ((((strlen(str) + strlen(str2)) + extraChars) / 2) * 6);
      }
    } else {
      if (str2 == "") {
        return (tft.width() / 2) - (((strlen(str) + extraChars) / 2) * 6 + 3);
      } else {
        return (tft.width() / 2) - ((((strlen(str) + strlen(str2)) + extraChars) / 2) * 6 + 3);
      }
    }

  } else if (fontSize == 2) {
    if ((i % 2) == 0) {
      if (str2 == "") {
        return (tft.width() / 2) - (((strlen(str) + extraChars) / 2) * 12);
      } else {
        return (tft.width() / 2) - ((((strlen(str) + strlen(str2)) + extraChars) / 2) * 12);
      }
    } else {
      if (str2 == "") {
        return (tft.width() / 2) - (((strlen(str) + extraChars) / 2) * 12 + 6);
      } else {
        return (tft.width() / 2) - ((((strlen(str) + strlen(str2)) + extraChars) / 2) * 12 + 6);
      }
    }

  } else if (fontSize == 3) {
    if ((i % 2) == 0) {
      if (str2 == "") {
        return (tft.width() / 2) - (((strlen(str) + extraChars) / 2) * 18);
      } else {
        return (tft.width() / 2) - ((((strlen(str) + strlen(str2)) + extraChars) / 2) * 18);
      }
    } else {
      if (str2 == "") {
        return (tft.width() / 2) - (((strlen(str) + extraChars) / 2) * 18 + 9);
      } else {
        return (tft.width() / 2) - ((((strlen(str) + strlen(str2)) + extraChars) / 2) * 18 + 9);
      }
    }

  }

}