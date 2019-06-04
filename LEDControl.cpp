#include "LEDControl.h"
#include "WeatherData.h"

#include "Arduino.h"


int shiftPin = D5;
int storePin = D6;
int dataPin = D7;

int redPin1 = D0;
int bluePin1 = D1;
int redPin2 = D2;
int bluePin2 = D3;


void LEDControl::begin() {
  //Setter pinsene til alle LED'ene til output
  pinMode(redPin1, OUTPUT);
  pinMode(bluePin1, OUTPUT);

  pinMode(redPin2, OUTPUT);
  pinMode(bluePin2, OUTPUT);

  pinMode(storePin, OUTPUT);
  pinMode(shiftPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void LEDControl::setLight(WeatherData &obj) {
    //Denne metoden setter fargen på RGB LED'ene, styrer shift registeret for å sette riktig verdi for å lyse opp de gule og grønne LED'ene utifra dataen på vind og regn
    digitalWrite(storePin, LOW);
    updateRGBLeds(obj.getTemperature().toInt());
    LEDControl::setRainAndWindLEDS(obj.getWindSpeed().toInt(), obj.getPrecipitation().toInt());
    digitalWrite(storePin, HIGH);
}

void LEDControl::setColor(int red, int blue) {
    //Her sendes ett PWM signal med en verdi satt utifra parameterene. JEg benytter kun rød og blå farge, og det blir da kun to verdier vi sender til RGB'en, ikke tre.
  analogWrite(redPin1, red);
  analogWrite(bluePin1, blue);
  analogWrite(redPin2, red);
  analogWrite(bluePin2, blue);
}

void LEDControl::updateRGBLeds(int temp) {
    //Her settes fargen på RGB'ledene utifra temperaturen ved ønsket værstasjon. Fargen endres fra sterk blåfarge på laveste temperatur, og går gradvis opp mot en sterk rødfarge ved høyeste temperatur.
  if (temp >= -50 && temp < -25) {
    setColor(0, 255);
    delay(1000);
  } else if (temp >= -25 && temp < -20) {
    setColor(10, 230);
    delay(1000);
  } else if (temp >= -20 && temp < -15) {
    setColor(30, 210);
    delay(1000);
  } else if (temp >= -15 && temp < -10) {
    setColor(50, 190);
    delay(1000);
  } else if (temp >= -10 && temp < -5) {
    setColor(70, 170);
    delay(1000);
  } else if (temp >= -5 && temp < 0) {
    setColor(90, 150);
    delay(1000);
  } else if (temp >= 0 && temp < 5) {
    setColor(110, 130);
    delay(1000);
  } else if (temp >= 5 && temp < 10) {
    setColor(130, 110);
    delay(1000);
  } else if (temp >= 10 && temp < 15) {
    setColor(150, 90);
    delay(1000);
  } else if (temp >= 15 && temp < 20) {
    setColor(170, 70);
    delay(1000);
  } else if (temp >= 20 && temp < 25) {
    setColor(190, 50);
    delay(1000);
  } else if (temp >= 25 && temp < 30) {
    setColor(210, 30);
    delay(1000);
  } else if (temp >= 30 && temp < 35) {
    setColor(230, 10);
    delay(1000);
  } else if (temp >= 35 && temp < 50) {
    setColor(255, 0);
    delay(1000);
  }
}

void LEDControl::setRainAndWindLEDS(int wind, int rain) {
    //For å styre LED'ene i shift registeret slik jeg ønsket har jeg laget denne metoden med if statements. Hvert statement har en condition om wind og regn data. LED'ene skal lyses opp fra 1-4 for hvor mye vind det er, og fra 5-8 utifra hvor mye regn det er. Det er 26 mulige kombinasjoner(verdier å sende til shift registeret) for å oppnå dette.
    if((wind >= 0 && wind < 0) && (rain >= 0 && rain < 0.1)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 0);
    } else if ((wind >= 0 && wind < 5) && (rain >= 0 && rain < 0.1)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 1);
    } else if ((wind >= 5 && wind < 10) && (rain >= 0 && rain < 0.1)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 3);
    } else if ((wind >= 10 && wind < 20) && (rain >= 0 && rain < 0.1)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 7);
    } else if ((wind >= 20 && wind < 50) && (rain >= 0 && rain < 0.1)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 15);
    } else if ((wind >= 0 && wind < 0) && (rain >= 0 && rain < 5)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 16);
    } else if ((wind >= 0 && wind < 0) && (rain >= 5 && rain < 10)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 48);
    } else if ((wind >= 0 && wind < 0) && (rain >= 10 && rain < 20)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 112);
    } else if ((wind >= 0 && wind < 0) && (rain >= 20 && rain < 50)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 240);
    } else if ((wind >= 0 && wind < 5) && (rain >= 0 && rain < 5)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 17);
    } else if ((wind >= 5 && wind < 10) && (rain >= 5 && rain < 10)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 51);
    } else if ((wind >= 10 && wind < 20) && (rain >= 10 && rain < 20)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 119);
    } else if ((wind >= 20 && wind < 50) && (rain >= 20 && rain < 50)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 255);
    } else if ((wind >= 0 && wind < 5) && (rain >= 0 && rain < 10)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 49);
    } else if ((wind >= 0 && wind < 5) && (rain >= 10 && rain < 20)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 113);
    } else if ((wind >= 0 && wind < 5) && (rain >= 20 && rain < 50)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 241);
    } else if ((wind >= 5 && wind < 10) && (rain >= 0 && rain < 5)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 19);
    } else if ((wind >= 5 && wind < 10) && (rain >= 10 && rain < 20)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 115);
    } else if ((wind >= 5 && wind < 10) && (rain >= 20 && rain < 50)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 243);
    } else if ((wind >= 10 && wind < 20) && (rain >= 0 && rain < 5)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 23);
    } else if ((wind >= 10 && wind < 20) && (rain >= 5 && rain < 10)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 55);
    } else if ((wind >= 10 && wind < 20) && (rain >= 10 && rain < 20)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 119);
    } else if ((wind >= 10 && wind < 20) && (rain >= 20 && rain < 50)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 247);
    } else if ((wind >= 20 && wind < 50) && (rain >= 0 && rain < 5)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 31);
    } else if ((wind >= 20 && wind < 50) && (rain >= 5 && rain < 10)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 63);
    } else if ((wind >= 20 && wind < 50) && (rain >= 10 && rain < 20)) {
        shiftOut(dataPin, shiftPin, MSBFIRST, 127);
    }
    
}