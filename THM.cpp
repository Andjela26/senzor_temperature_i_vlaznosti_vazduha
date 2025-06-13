#include "THM.h"

//konstruktor klase
THM::THM(int uiPin){
  pin = uiPin;
}

//Inicijalizacija pina i vremena poslednjeg prijema poruke
void THM::begin(void){
  pinMode(pin,INPUT);
  digitalWrite(pin,HIGH);
  lastReadTime = 0;
}

//preuzimanje rezultata merenja od senzorskog modula
void THM::read(){
  if(millis() - lastReadTime > 2000)  { 
    pinMode(pin, OUTPUT);               
    digitalWrite(pin, LOW);             
    delay(1);                           
    digitalWrite(pin, HIGH);            
    delayMicroseconds(30);  
    pinMode(pin, INPUT);   
    while (digitalRead(pin) == HIGH);
    long startTime1 = micros();
    while(digitalRead(pin) == LOW);
    long stopTime1=micros();
    long startTime2 = micros();
    while(digitalRead(pin) == HIGH);
    long stopTime2 = micros();
    if(((stopTime1-startTime1)==80) && ((stopTime2-startTime2)==80))  
      errorStatus = 0;                                 
    else                                          
      errorStatus = 1;                                 
         
    for(int i = 0; i < 5; i++)  {                       
      data[i] = NULL;                                   
      for(int j = 0; j < 8; j++)  {                    
          while(digitalRead(pin) == LOW);             
          long startTime = micros();                       
          while(digitalRead(pin) == HIGH);               
          long stopTime = micros();
          long Time = stopTime - startTime;
          if((Time) == 26)  {                           
              data[i] <<= 1;                               
          } 
          else if(((Time)) == 70 ) { 
                                            
              data[i] |= 1;
              data[i] <<= 1; 
        }
      }
    }
    if((data[0]+data[1]+data[2]+data[3])==data[4]){
        errorStatus=0;
    }
    else{
        errorStatus=1;
    }
    lastReadTime = millis();
  }

  return;
}
//vraća vrednost temperature u stepenima Celzijusa
float THM::readTemperature(){
  int T;
  read();
  T |= data[3];
  T <<= 8;
  T |= data[2];
  float Tmp = (float)T / 10;
  return T;
}

//vraca vrednost relativne vlaznosti u %
float THM::readHumidity(){
  int H;
  read();
  H |= data[1];
  H <<= 8;
  H |= data[0];
  float Hum = (float)H / 10;
  return Hum;
}
