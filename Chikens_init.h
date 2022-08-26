#ifndef CHICKENS_H_
#define CHICKENS_H_
#include "Chickens_priv.h"
#include "Chikens_config.h"

#include <EEPROM.h>
#include "DHT.h"


#define DHTTYPE DHT11
DHT dht1(DHT1Pin, DHTTYPE);

void tempFn(void);
void detectGas();
void controlStatments(void);
void serialPrints(void);

String eeprom_read(int address, int stringLength);
void eeprom_Write(int address, char*ptr, int stringLength);
void EEPROMWriteInt(int p_address, int p_value);
unsigned int EEPROMReadInt(int p_address);



void pinSetup(void);
void DHTSetup(void);
void EEPROMSetup(void);
void parameterSetup(void);


#endif CHICKENS_H_
