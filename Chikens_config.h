#ifndef CONFIG_H_
#define CONFIG_H_

//////////////////////Config Settings//////////////////////
// Timing intervals
int temp_interval=500;
int gas_interval=500;
int control_interval = 100;
int serial_interval = 2000;
int button_interval = 50;

#define Heater 19
#define GAS1   A4
#define Buzzer 17
#define SW_N   16
#define SW_P   15
#define SW_S   14
#define LCD_RS 13
#define LCD_E  12
#define LCD_D1 11
#define LCD_D2 10
#define LCD_D3 9
#define LCD_D4 8
#define WLS1   7
#define WLS2   6
uint8_t DHT1Pin = 5;
#define Cooler 4
#define Light  3
#define Fan    2
#define TX     1
#define RX     0




#define EEPROM_SIZE 512
float MinTemp_Trigger = 25;
float MaxTemp_Trigger = 35;
float MinVent_Trigger = 350;
float MaxVent_Trigger = 400;
float Hum_Trigger = 50;

#endif CONFIG_H_
