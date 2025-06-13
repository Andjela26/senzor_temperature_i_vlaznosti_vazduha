#ifndef THM_H
#define THM_H

#include "Energia.h"

class THM {
 private:
  unsigned char data[5];  //niz u koji se smestaju bajtovi poruke
  int pin;                //pin TH senzorskog modula
  void read(void);        //prijem poruke TH senzorskog modula
  unsigned long lastReadTime;  //vreme poslednjeg ocitavanja TH modula

 public:
  THM(int uiPin);      //konstruktor klase
  void begin(void);    //inicijalizacija 
  float readTemperature(void);  //citanje vrednosti temperature
  float readHumidity(void);     //citanje vrednosti vlaznosti
  int errorStatus;   //kod greske: 
                     //  0 - OK, 
                     //  razlicito od 0 - greska u prijemu poruke
};
#endif
