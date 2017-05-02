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


uint16_t ORP::moyenne(uint8_t* arr, uint8_t number)
{
	uint8_t i;
	 int max,min;
	 uint16_t avg;
	 uint16_t amount=0;

	 if(number<5){  //less than 5, calculated directly statistics
	  for(i=0;i<number;i++){
	    amount+=arr[i];
	  }
	  avg = amount/number;
	  return avg;
	 }else{
	  
	   if(arr[0]<arr[1]){
	    min = arr[0];max=arr[1];
	   }
	   else{
	     min=arr[1];max=arr[0];
	    }
	    
	 for(i=2;i<number;i++){
	  if(arr[i]<min){
	    amount+=min;  //arr<min
	    min=arr[i];
	  }else {
	    if(arr[i]>max){
	      amount+=max;  //arr>max
	      max=arr[i];
	    }else{
	      amount+=arr[i]; //min<=arr<=max
	    }
	  }//if

	 }//for

	 avg = (uint16_t)amount/(number-2);

	 }//if

	 return avg;
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


