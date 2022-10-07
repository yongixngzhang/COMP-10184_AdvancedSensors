#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/**
 * StAuth10187: I Yongxing zhang, 000766325 certify that this material is my original work. 
 * No other person's work has been used without due acknowledgement. 
 * I have not made my work available to anyone else.
*/
const int oneWireBus = D3;
OneWire onewaire(oneWireBus);
DallasTemperature DS18B20(&onewaire);
DeviceAddress DS18B20Adrs;
bool KeepLoop = false;

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 0x10)
      Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Start the DS18B20 sensor
  DS18B20.begin();
  // Serial.println(tempSensor, DEC);
  DS18B20.getAddress(DS18B20Adrs, 0);
  Serial.println("Temperature Applicnation ");
  if (DS18B20.isConnected(DS18B20Adrs))
  {
    KeepLoop = true;
    Serial.print("Found DS182B20 sensor with address:");
    printAddress(DS18B20Adrs);
    Serial.println();
  }
  else
  {
    KeepLoop = false;
    Serial.println("No DS182B20 temperautre sensor is installed");
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
    if (DS18B20.isConnected(DS18B20Adrs))
  {
    KeepLoop = true;
  }
  else
  {
    KeepLoop = false;
    Serial.println("No DS182B20 temperautre sensor is installed");
  }
  if (KeepLoop)
  {
    float fTemp;
    DS18B20.requestTemperatures();
    fTemp = DS18B20.getTempCByIndex(0);
    String out;

    if (fTemp < 10)
    {
      out = "Cold!";
    }
    else if (fTemp <= 15)
    {
      out = "Cool!";
    }
    else if (fTemp <= 25)
    {
      out = "Perfect!";
    }
    else if (fTemp <= 30)
    {
      out = "Warm!";
    }
    else if (fTemp <= 35)
    {
      out = "Hot!";
    }
    else if (fTemp > 35)
    {
      out = "too Hot!";
    }

    Serial.println("Current tempercure is " + String(fTemp) + "°C or very " + out);
    // ask DS18B20 for the current temperature

    
  }delay(5000);
}