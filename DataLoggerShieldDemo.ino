/*
    Lemontech DataLogger Shield    
    Demo sketch

    v 1.0 - 17/06/2014
*/


#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

#define RELAY1_PIN      5
#define RELAY2_PIN      6
#define RELAY3_PIN      7
#define RELAY4_PIN      8

#define SD_CHIPSELECT  10

void setup() {                
  
  // Initialize relay pins
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  pinMode(RELAY4_PIN, OUTPUT);
  
  // Initialize SD CS pin
  pinMode(SD_CHIPSELECT, OUTPUT);
    
  Serial.begin(9600);
  Serial.println("Lemontech DataLogger Shield - Demo sketch");
  Serial.println();
  delay(2000);
  
  // Run the different demo procedures
  relayTest();
  sdTest();
  rtcTest();
}

void loop() {}


// Relay test: turn all the 4 relays ON and OFF
void relayTest() {

  Serial.println("Testing relays...");
  
  digitalWrite(RELAY1_PIN, HIGH);
  Serial.println(" - relay 1 ON");
  delay(1000);
  digitalWrite(RELAY1_PIN, LOW);
  Serial.println(" - relay 1 OFF");
  delay(1000);

  digitalWrite(RELAY2_PIN, HIGH);
  Serial.println(" - relay 2 ON");
  delay(1000);
  digitalWrite(RELAY2_PIN, LOW);
  Serial.println(" - relay 2 OFF");
  delay(1000);

  digitalWrite(RELAY3_PIN, HIGH);
  Serial.println(" - relay 3 ON");
  delay(1000);
  digitalWrite(RELAY3_PIN, LOW);
  Serial.println(" - relay 3 OFF");
  delay(1000);

  digitalWrite(RELAY4_PIN, HIGH);
    Serial.println(" - relay 4 ON");
  delay(1000);
  digitalWrite(RELAY4_PIN, LOW);
  Serial.println(" - relay 4 OFF");
  delay(1000); 
 
  Serial.println("... done!"); 
  Serial.println();
}

// SD test: init, get type and size
void sdTest() {
  
  Sd2Card card;
  SdVolume volume;
  uint32_t volumesize;
  
  Serial.println("Testing SD card...");

  if (!card.init(SPI_HALF_SPEED, SD_CHIPSELECT)) {
    Serial.println(" - unable to initialize the card :(");
    Serial.println("... done!"); 
    Serial.println();
    return;
  }
  Serial.println(" - card initialized");
  
  Serial.print(" - card type: ");
  switch(card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("unknown :(");
  }
  
  if (!volume.init(card)) {
    Serial.println(" - unable to open card's partition :(");
    Serial.println("... done!"); 
    Serial.println();
  }
  Serial.print(" - partition type: FAT");
  Serial.println(volume.fatType(), DEC);
  
  volumesize = volume.blocksPerCluster();
  volumesize *= volume.clusterCount();
  volumesize *= 512;
  volumesize /= 1048576;
  Serial.print(" - volume size (Mbytes): ");
  Serial.println(volumesize);
  
  Serial.println("... done!"); 
  Serial.println();  
}

// RTC test: init, check if running and get actual time
void rtcTest() {

  RTC_DS1307 RTC;

  Wire.begin();
  RTC.begin();

  Serial.println("Testing Realtime clock...");
  
  if (! RTC.isrunning()) {
    RTC.adjust(DateTime(__DATE__, __TIME__));
    Serial.println(" - RTC was not running, time set");    
  }

  DateTime now = RTC.now();
  Serial.print(" - actual time: ");
  printTime(now);
  Serial.println(" - waiting 5 seconds");
  delay(5000);
  now = RTC.now();
  Serial.print(" - actual time: ");
  printTime(now);  

  Serial.println("... done!"); 
  Serial.println();  
}

void printTime(DateTime now) {
  
  char buf[50]; 
  sprintf(buf, "%02d:%02d:%02d %02d/%02d/%4d", now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); 
  Serial.println(buf);
}
