/********************************************************************
- EV SD Card Data Logging Programme (4x Temperature and Dummy Variables)
  (Version Includes: BMS Temperature)
- Version 1.0
- Modified by Jerico Magtaan
- Last Edited on 31/03/20
********************************************************************/
/*
 * Four DS18B20 sensors are used to measure temperature
 * The wiring for each sensor are connected as followed:
- Pin 1 (GND) of DS18B20 sensors are connected to common ground
- Pin 2 (DQ) of DS18B20 sensors can be connected to any digital pin of Arduino
- Pin 3 (Vdd) of DS18B20 sensors can be connected to the 5V pin of the Arduino
- 4.7k pull-up resistor connected between DQ and Vdd of DS18B20 sensors
 * Arduino Uno mounted with an Ethernet Shield 2 for the SD card (SPI):
- Pin D4 of Arduino as CS of SD card
- Pin D11 of Arduino for SPI SI pin
- Pin D12 of Arduino for SPI SO pin
- Pin D13 of Arduino for SPI SCK pin
- GND pin of Arduino to common ground
********************************************************************/


/******* Import the needed libraries for the sensor to work ********/
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>

/* Create Excel file called "EV_Data.CSV" on the SD Card */
File myFile;
char filename[] = "EV_Data.CSV";

/* Data wire from all sensors are plugged into pin 2 of the Arduino */
#define ONE_WIRE_BUS_PIN 2

/* Set up a oneWire instance to communicate with any OneWire device */
OneWire oneWire(ONE_WIRE_BUS_PIN);

/*** Allow Dallas Temperature Library to utilize oneWire Library ***/
DallasTemperature sensors(&oneWire);

/*** Chip Select Signal Pin is pin 4  ***/
const int chipSelect = 4;

/*** Variables stored into the SD card ***/
float tempC, Temp01, Temp02, Temp03, Temp04;  // BMS Individual Sensor Variables
float BMSTempAVG, BMSVoltage, BMSCurrent; // BMS Temp., BMS Current and BMS Voltage Variables
float MotorVoltage, MotorCurrent, TSPower;  // CT Current, Voltage and Power Variables

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
 
  /* Always make pin 10 an output even when not using */
  //pinMode(10, OUTPUT);

  /* Start up the SD card */
if (!SD.begin(chipSelect)) 
  {
  Serial.print(" SD Card FAILED to Start ");
    delay (1000);
    return;
  }
  Serial.println(" SD Card Ready ");
  myFile = SD.open("EV_Data.CSV", FILE_WRITE);
  myFile.println("Sensor01(degC),Sensor02(degC),Sensor03(degC),Sensor04(degC),BMS Average Temperature(degC)");      
  myFile.close();
  
  /* DS18B20 sensor configuration and library startup */
  // 9 bit resolution, 93.75 ms conversion time
  // 10 bit resolution, 187.5 ms conversion time
  // 11 bit resolution, 375 ms conversion time
  // 12 bit resolution, 750 ms conversion time
  Serial.print("Starting up Temperature Control Library ");
  Serial.println(DALLASTEMPLIBVERSION);
  Serial.println("-------------------------------------");
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
  delay(1000);   // 1 second delay
  Serial.println();
  Serial.print("Number of connected Devices on bus: ");  
  Serial.println(sensors.getDeviceCount());   // Display number of connected devices on bus

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

  /* BMS variable measurements and SD card data logging */
  myFile = SD.open("EV_Data.CSV", FILE_WRITE);
  /* Sensor01 temperature data logging */
  Temp01 = sensors.getTempC(Sensor01);
  myFile.print(Temp01);
  myFile.print(",");
  /* Sensor02 temperature data logging */
  Temp02 = sensors.getTempC(Sensor02);
  myFile.print(Temp02);
  myFile.print(",");
  /* Sensor03 temperature data logging */
  Temp03 = sensors.getTempC(Sensor03);
  myFile.print(Temp03);
  myFile.print(",");  
  /* Sensor04 temperature data logging */
  Temp04 = sensors.getTempC(Sensor04);
  myFile.print(Temp04);
  myFile.print(",");  
  /* BMS average temperature data logging */
  BMSTempAVG = (Temp01 + Temp02 + Temp03 + Temp04)/4; 
  Serial.print(" Average temperature:   ");
  Serial.print(BMSTempAVG);
  Serial.print("  (degC)");
  Serial.println();   
  myFile.print(BMSTempAVG);
  myFile.print(",");
  myFile.println();
  myFile.close();   // Close the file after all measurements have been logged
  Serial.println(" Data Logged ");  // Let user know that data has been logged
}
/* End main loop */


/* DS18B20 sensor configuration for sensor measurements */
void printTemperature(DeviceAddress deviceAddress)
{
/* If sensors read -127degC it means the wiring or code is wrong */
/* Print if there's an error, otherwise allow sensors to read temperature */
tempC = sensors.getTempC(deviceAddress);

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
