#include "WSNORPSensor.h"

ORP::ORP()
{
	_sensorPin = SensorPin;
	_offset = Offset;
	_intervalMesure = intervalMesure;
	_intervalConvertion = intervalConvertion;
	_tailleEchantillon = tailleEchantillon;
	ORPValue = 0;
	tableauORP[_tailleEchantillon];
	indexORP=0; 
};

ORP::ORP(uint8_t pin)
{
	_sensorPin = pin;
	_offset = Offset;
	_intervalMesure = intervalMesure;
	_intervalConvertion = intervalConvertion;
	_tailleEchantillon = tailleEchantillon;
	ORPValue = 0;
	tableauORP[_tailleEchantillon];
	indexORP=0; 
};

void ORP::init(uint8_t offset, uint8_t mesure, uint32_t Convertion,uint8_t taille)
{
	_offset = offset;
	_intervalMesure = mesure;
	_intervalConvertion = Convertion;
	_tailleEchantillon = taille;
	tableauORP[_tailleEchantillon];
	indexORP=0; 
};

uint8_t ORP::getMesure()
{
	return ORPValue;
};


void ORP::updateORP()
{
	static uint16_t orpTimer=millis();   //analog sampling interval
  //static unsigned long printTime=millis();
  if(millis() >= orpTimer)
  {
    orpTimer=millis()+20;
    tableauORP[indexORP++]=analogRead(_sensorPin);    //read an analog value every 20ms
    if (indexORP==_tailleEchantillon) {
      indexORP=0;
    }   
    ORPValue=((30*(double)VOLTAGE*1000)-(75*moyenne(tableauORP, _tailleEchantillon)*VOLTAGE*1000/1024))/75-_offset; 
}
};


