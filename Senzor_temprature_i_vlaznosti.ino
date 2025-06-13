#include "THM.h"

const int THM_PIN = 24;  //pin senzorskog modula

THM thm(THM_PIN); //instanciranje objekta klase THM

void setup()
{
  thm.begin();   //inicijalizacija objekta thm
  Serial.begin(9600);
}

void loop()
{
  float temperature = thm.readTemperature(); //citanje temperature
  float humidity = thm.readHumidity();       //citanje vlaznosti
  if(thm.errorStatus != 0){
    Serial.print("Error: ");
    Serial.println(thm.errorStatus);
  } else{
    Serial.print("T = ");
    Serial.print(temperature);
    Serial.print("  H = ");
    Serial.println(humidity); 
  }
  delay(1000);
}
