#include "WSN.h"
ORP orp(A0);

long temps;
void setup() {
  Serial.begin(9600);
  temps = millis();
}

void loop() {
 orp.updateORP();
 if(millis() - temps > 1000){
  Serial.println(orp.getMesure());
  temps=millis();
 }
 
}
