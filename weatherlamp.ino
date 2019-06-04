#include "LEDControl.h"
#include "TFTScreen.h"
#include "WeatherData.h"

WeatherData wd;
TFTScreen tfts;
LEDControl ledc;

const int buzzer = A7;
bool belowZero = true;

#define updateTime 120000 //Endre denne verdien om du ønsker lengere interval mellom oppdatering av lampen. 120000 = 2 minutter.
bool playSound = true; //Endre denne til false om du ønsker at lampen ikke skal lage en lyd ved skifte til ønsket temperatur.
#define GRAD 0 //Ønsket temperatur når lampen skal spille av en lyd

void setup() {
    
  pinMode(buzzer, OUTPUT); //Setter buzzer pinen til OUTPUT
    
  Serial.begin(115200);

  //Leser webhooken. Kaller wd.getWeatherData() ved svar
  Particle.subscribe("hook-response/soldata", wd.getWeatherData, MY_DEVICES);

  //Venter 10 sekunder for å gi photonen tid til å starte opp før vi ber om data
  for (int i = 0; i < 10; i++) {
    Serial.println("Venter " + String(10 - i) + " sekunder til på at all data skal bli hentet");
    delay(1000);
  }
  
  delay(200);
  ledc.begin(); //Setter pinsene for alle LEDs til output
  tfts.initScreen(); //Gjør klar TFT skjermen

}

void loop() {
  Serial.println("Henter værdata!");
  Particle.publish("soldata");//Henter værdata

  delay(2500);
  
  ledc.setLight(wd); //Setter farge på LED's og hvor mange av LED'ene fra shift registeret som skal lyse opp. RGB utifra temperaturen og de resterende LED'ene settes utifra ving og regn data.
  
  if(playSound) {
    playTone(); //Spiller av en lyd om temperaturen går under ønsker grad
  }
  
  tfts.writeToScreen(wd); //Skriver dataen hentet fra webhooken til TFT skjermen

  delay(updateTime); //Venter 2 minutter før vi spørr etter dataen, setter lys og evt. spiller lyd igjen.
}

void playTone() {
    
    //Denne metoden gir ut ett signal til piezo buzzeren om temperaturen går under ønsket temperatur. Vil kunne lage lyden en gang helt til temperaturen går over ønsket temperatur.
    if((wd.getTemperature().toInt() <= GRAD) && belowZero) {
          belowZero = false;
          tone(buzzer, 1000);
          delay(1000);
          noTone(buzzer);
          delay(1000);
    } else if((wd.getTemperature().toInt() > GRAD) && !belowZero) {
          belowZero = true;
    }
}