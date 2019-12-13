
#ifndef _ZIGBEE_H_
#define _ZIGBEE_H_
#include "freertos/FreeRTOS.h"

double Temperature ;
double Humidity ;
double mq2 ;

int TemperatureType;
int mq2Type;
int HumidityType;
int PhoneType;

int up_time;


extern void ZIGBEE_Init(void);


#endif

