#ifndef CHICKENS_PRIV_H_
#define CHICKENS_PRIV_H_


/*
 * What is missing :
 *                  EEPROM for controller
 *                  LCD
 *                  Switches
 * 
 * 
 * 
 * 
 */
/////////////////////////Variables//////////////////////////////////
float val;

int heater_status = 0;
int heater_status_prev = 5;

int cooler_status = 0;
int cooler_status_prev = 5;

int fan_status=0;
int fan_status_prev = 5;
///////////////////////////////////////////////////////////////////////////

int light_Status = 1;
int buzzer_Status=0;
String string;
String light_prev;
/////////////////mq135/////////////////////
int conductivity = 0;
int conductivity_prev = 0;
String quality = "FF";
int gas;
int Error;
int Error_prev;
int TempSensorErorr = 0;

float Temperature;
float Humidity;
float temp_prev; // save previous to check if there is a change
float hum_prev;
/******************************** button variables ***************************/
int setFlag_h=0;
int negFlag_h=0;
int posFlag_h=0;
int setFlag_l=0;
int negFlag_l=0;
int posFlag_l=0;



/******************************* Timing ************************************/
long long int currentmillis =0;

// temperature
long long int temp_previousMillis = 0;
// gas
long long int gas_previousMillis = 0;
// control
long long int control_previousMillis = 0;
// serial
long long int serial_previousMillis = 0;
// button
long long int button_previousMillis = 0;



#endif CHICKENS_PRIV_H_
