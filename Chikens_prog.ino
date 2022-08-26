#include "Chikens_init.h"


String eeprom_read(int address, int stringLength)
{
  char in[stringLength + 1];
  Serial.println("Starting Reading");
  for (int i = 0; i < address + stringLength; i++)
  {
    in[i] = EEPROM.read(address + i);
    if (in[i] == '\0')
      break;
  }
  Serial.print(" readeeprom  ");
  Serial.println(in);
  return String(in);
}
void eeprom_Write(int address, const char*ptr, int stringLength)
{
  Serial.println("Starting Writing");
  int i = 0;
  for ( ; i < (address + stringLength); i++)
  {
    EEPROM.write((i + address), ptr[i]);
  }
  EEPROM.write(address + i, '\0');
  //  Serial.print("Commit : ");
  //  Serial.println(EEPROM.commit());
}
void EEPROMWriteInt(int p_address, int p_value)
{
  byte lowByte = ((p_value >> 0) & 0xFF);
  byte highByte = ((p_value >> 8) & 0xFF);

  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);
  //Serial.print("Commit : ");
  //Serial.println(EEPROM.commit());
}
unsigned int EEPROMReadInt(int p_address)
{
  byte lowByte = EEPROM.read(p_address);
  byte highByte = EEPROM.read(p_address + 1);

  return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}

void tempFn(void)
{
  if((currentmillis - temp_previousMillis >= temp_interval)||(currentmillis < temp_previousMillis))
  { 
    temp_previousMillis = currentmillis; 
    Temperature = dht1.readTemperature(); // Gets the values of the temperature
    Humidity = dht1.readHumidity(); // Gets the values of the humidity
  
    /////////////////////////////////protection/////////////////////////////////////
    if (isnan(Temperature))
    {
      Temperature = 00.0;
      TempSensorErorr = 1;
    }
    if (isnan(Humidity))
    {
      Humidity = 00.0;
      TempSensorErorr = 1;
    }
  
    val = (int)(Temperature * 10 + 0.5);
    Temperature = (float) val / 10;
    val = (int)(Humidity * 10 + 0.5);
    Humidity = (float) val / 10;
    if (Temperature > 80)
      Temperature = 80;
    if (Humidity > 120)
      Humidity = 120;
//    Serial.print("Temperature: "); Serial.println(Temperature);
//    Serial.print("Humidity: "); Serial.println(Humidity);
  }
}
void detectGas()
{
  if((currentmillis - gas_previousMillis >= gas_interval)||(currentmillis < gas_previousMillis))
  {  
    gas_previousMillis = currentmillis;
    gas = analogRead(GAS1);
    conductivity = round(((float)gas / 1023) * 100);
    if (isnan(conductivity))
      conductivity = 00.0;
  
    quality = "Good";
    if (gas <= MinVent_Trigger)
    {
      quality = "Good";
    }
    else if (gas <= MaxVent_Trigger)
    {
      quality = "Moderate";
    }
    else
    {
      quality = "Poor";
    }
//    Serial.print("gas: "); Serial.println(gas);
//    Serial.print("conductivity: "); Serial.println(conductivity);
//    Serial.print("quality: "); Serial.println(quality);
  }
}
void controlStatments(void)
{
  if((currentmillis - control_previousMillis >= control_interval)||(currentmillis < control_previousMillis))
  {
    control_previousMillis = currentmillis;
    /************************************************/
    if ((gas > MaxVent_Trigger) && (Temperature > MinTemp_Trigger) || (Temperature > MaxTemp_Trigger + 3))
    {
      digitalWrite(Fan, 1);
      fan_status = 1;
    }
    else if ((Temperature < MinTemp_Trigger) || (gas < MinVent_Trigger))
    {
      digitalWrite(Fan, 0);
      fan_status = 0;
    }
    /************************************************/
    if (Temperature > MaxTemp_Trigger + 3)
    {
      digitalWrite(Cooler, 1);
      cooler_status = 1;
    }
    else
    {
      digitalWrite(Cooler, 0);
      cooler_status = 0;
    }
  
    /************************************************/
    if (Temperature <= MinTemp_Trigger)
    {
      //HeaterA
      digitalWrite(Heater, 1);
      heater_status = 1;
    }
    else if (Temperature > MaxTemp_Trigger)
    {
      //HeaterA
      digitalWrite(Heater, 0);
      heater_status = 0;
    }
  }
}
void serialPrints(void)
{
  if((currentmillis - serial_previousMillis >= serial_interval)||(currentmillis < serial_previousMillis))
  {
    serial_previousMillis = currentmillis;
    Serial.print("cooler_status: "); Serial.println(cooler_status);
    Serial.print("heater_status: "); Serial.println(heater_status);
    Serial.print("Temperature: "); Serial.println(Temperature);
    Serial.print("Humidity: "); Serial.println(Humidity);
    Serial.print("gas: "); Serial.println(gas);
    Serial.print("Light_Status: "); Serial.println(light_Status);
    Serial.print("MinVent_Trigger: "); Serial.println(MinVent_Trigger);
    Serial.print("MaxVent_Trigger: "); Serial.println(MaxVent_Trigger);
    Serial.print("MinTemp_Trigger: "); Serial.println(MinTemp_Trigger);
    Serial.print("MaxTemp_Trigger: "); Serial.println(MaxTemp_Trigger);
  }
}
void buttonUpdate()
{
  if((setFlag_l)&&(setFlag_h))
  {
    Serial.println("// make the process of set");
    setFlag_l=0;
    setFlag_h=0;
    buzzer_Status = ! buzzer_Status;
    digitalWrite(Buzzer,buzzer_Status);
  }
  if((negFlag_l)&&(negFlag_h))
  {
    Serial.println("// make the process of neg");
    negFlag_l=0;
    negFlag_h=0;
    buzzer_Status = ! buzzer_Status;
    digitalWrite(Buzzer,buzzer_Status);
  }
  
  if((posFlag_l)&&(posFlag_h))
  {
    Serial.println("// make the process of pos");
    posFlag_l=0;
    posFlag_h=0;
    buzzer_Status = ! buzzer_Status;
    digitalWrite(Buzzer,buzzer_Status);
  }
}
void buttonCheck(void)
{
    if((currentmillis - button_previousMillis >= button_interval)||(currentmillis < button_previousMillis))
  {
    button_previousMillis = currentmillis;
    //  Check if button goes low set the first flag
    if (digitalRead(SW_S)==0)
    {
      delay(50);
      if (digitalRead(SW_S)==0)
      {
        setFlag_l = 1;
      }
    }
    if (digitalRead(SW_N)==0)
    {
      delay(50);
      if (digitalRead(SW_N)==0)
      {
        negFlag_l = 1;
      }
    }
    if (digitalRead(SW_P)==0)
    {
      delay(50);
      if (digitalRead(SW_P)==0)
      {
        posFlag_l = 1;
      }
    }
  
    // Check if it back high set the second flag 
  
    if ((digitalRead(SW_S)==1)&&(setFlag_l==1))
    {
      delay(50);
      if ((digitalRead(SW_S)==1)&&(setFlag_l==1))
      {
        setFlag_h = 1;
      }
    }
    if ((digitalRead(SW_N)==1)&&(negFlag_l==1))
    {
      delay(50);
      if ((digitalRead(SW_N)==1)&&(negFlag_l==1))
      {
        negFlag_h = 1;
      }
    }
    if ((digitalRead(SW_P)==1)&&(posFlag_l==1))
    {
      delay(50);
      if ((digitalRead(SW_P)==1)&&(posFlag_l==1))
      {
        posFlag_h = 1;
      }
    }
    buttonUpdate();
  }
}



/********************************************** Setup Functions *********************************************************/
void pinSetup(void)
{
  pinMode(GAS1, INPUT);
  pinMode(SW_N, INPUT_PULLUP);
  pinMode(SW_P, INPUT_PULLUP);
  pinMode(SW_S, INPUT_PULLUP);
  pinMode(WLS1, INPUT);
  pinMode(WLS2, INPUT);
  pinMode(DHT1Pin, INPUT);
  pinMode(Cooler, OUTPUT);
  pinMode(Fan, OUTPUT);
  pinMode(Heater, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_E, OUTPUT);
  pinMode(LCD_D1, OUTPUT);
  pinMode(LCD_D2, OUTPUT);
  pinMode(LCD_D3, OUTPUT);
  pinMode(LCD_D4, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Light, OUTPUT);
  pinMode(TX, OUTPUT);
  pinMode(RX, INPUT);



  digitalWrite(Heater, 0);

}
void DHTSetup(void)
{
  dht1.begin();
}
void parameterSetup(void)
{
  MinVent_Trigger = EEPROMReadInt(300);
  MaxVent_Trigger = EEPROMReadInt(310);
  MaxTemp_Trigger = EEPROMReadInt(320);
  MinTemp_Trigger = EEPROMReadInt(330);
}





