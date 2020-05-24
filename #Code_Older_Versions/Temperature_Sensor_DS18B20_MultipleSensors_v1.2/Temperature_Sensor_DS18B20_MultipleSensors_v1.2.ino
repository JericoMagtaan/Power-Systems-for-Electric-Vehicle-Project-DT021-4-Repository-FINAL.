/********************************************************************
- Temperature Measurements with Multiple DS18B20 One-Wire Sensor (4x)
- Version 1.2
- Modified by Jerico Magtaan
- Last Edited on 27/03/20
********************************************************************/
/*
 * Four DS18B20 sensors are used to measure temperature
 * The wiring for each sensor are connected as followed:
- Pin 1 (GND) of DS18B20 sensors are connected to GND pin of Arduino
- Pin 2 (DQ) of DS18B20 sensors can be connected to any digital pin of Arduino
- Pin 3 (Vdd) of DS18B20 sensors can be connected to either 5V or 3.3V pin of Arduino
- 4.7k pull-up resistor connected between DQ and Vdd of DS18B20 sensors
********************************************************************/


/******* Import the needed libraries for the sensor to work ********/
#include <OneWire.h>
#include <DallasTemperature.h>

/* Data wire from all sensors are plugged into pin 2 of the Arduino */
#define ONE_WIRE_BUS_PIN 2

/* Set up a oneWire instance to communicate with any OneWire device */
OneWire oneWire(ONE_WIRE_BUS_PIN);

/*** Allow Dallas Temperature Library to utilize oneWire Library ***/
DallasTemperature sensors(&oneWire);

/* Giving each sensor a name by assigning the serial numbers obtained
   from previous code (e.g. Sensor Name = { Serial Number of Sensor}; */
DeviceAddress Sensor01 = { 0x28, 0x50, 0x87, 0x3B, 0x0A, 0x00, 0x00, 0x1C }; 
DeviceAddress Sensor02 = { 0x28, 0x6E, 0x75, 0x3B, 0x0A, 0x00, 0x00, 0xC7 };
DeviceAddress Sensor03 = { 0x28, 0x22, 0x70, 0x3B, 0x0A, 0x00, 0x00, 0x1D };
DeviceAddress Sensor04 = { 0x28, 0xF7, 0x87, 0x3B, 0x0A, 0x00, 0x00, 0xC5 };


/* void setup allows to run once */
void setup()
{
  /* Start serial port to display results on screen */
  Serial.begin(9600);
  Serial.print("Starting up Temperature Control Library ");
  Serial.println(DALLASTEMPLIBVERSION);
  
  /* Start up the DallasTemperature library */
  /* Set resolution of sensors */
  // 9 bit resolution, 93.75 ms conversion time
  // 10 bit resolution, 187.5 ms conversion time
  // 11 bit resolution, 375 ms conversion time
  // 12 bit resolution, 750 ms conversion time
  sensors.begin();
  sensors.setResolution(Sensor01, 10);
  sensors.setResolution(Sensor02, 10);
  sensors.setResolution(Sensor03, 10);
  sensors.setResolution(Sensor04, 10);
}
/* End setup */


/* void loop allows to run continuously */
void loop()
{
  /* Print required text to screen/serial monitor */
  /* Check for no. of devices connected on bus */
  delay(2000);   // 2 seconds delay
  Serial.println();
  Serial.print("Number of connected Devices on bus: ");  
  Serial.println(sensors.getDeviceCount());   // Display number of connected devices on bus
  Serial.print("Measuring temperatures from all connected sensors... ");  
  Serial.println();

  /* Request temperature measurements from all connected DS18B20 sensors */
  sensors.requestTemperatures();  

  /* Print sensor measurements to serial monitor */
  Serial.print("Sensor01 temperature:   ");
  printTemperature(Sensor01);
  Serial.println();

  Serial.print("Sensor02 temperature:   ");
  printTemperature(Sensor02);
  Serial.println();
 
  Serial.print("Sensor03 temperature:   ");
  printTemperature(Sensor03);
  Serial.println();
   
  Serial.print("Sensor04 temperature:   ");
  printTemperature(Sensor04);
  Serial.println();   

  /* DS18B20 sensor average measurements */
  float Temp1 = sensors.getTempC(Sensor01);
  float Temp2 = sensors.getTempC(Sensor02);
  float Temp3 = sensors.getTempC(Sensor03);
  float Temp4 = sensors.getTempC(Sensor04);
  float TempAVG = (Temp1 + Temp2 + Temp3 + Temp4)/4; 
  Serial.print(" Average temperature:   ");
  Serial.print(TempAVG);
  Serial.print("  (degC)");
  Serial.println();   
}
/* End main loop */


/* DS18B20 sensor configuration for sensor measurements */
void printTemperature(DeviceAddress deviceAddress)
{

/* If sensors read -127degC it means the wiring or code is wrong */
/* Print if there's an error, otherwise allow sensors to read temperature */
float tempC = sensors.getTempC(deviceAddress);

   if (tempC == -127.00) 
   {
   Serial.print("Error getting temperature  ");
   } 
   else
   {
   Serial.print(tempC);
   Serial.print("  (degC)");
   } 
}
/*******************************************************************/
