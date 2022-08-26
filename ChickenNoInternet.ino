#include "Chikens_init.h"

void setup() {
  Serial.begin(9600);
  Serial.println("\n\n Setup Func \n\n");
  pinSetup();
  DHTSetup();
  parameterSetup();


}

void loop() {
  currentmillis = millis();
  tempFn();
  detectGas();
  controlStatments();
  buttonCheck();
  serialPrints();

}
