/********************************************************************
- Temperature Measurements with Multiple DS18B20 One-Wire Sensor (4x)
- Version 1.0
- Modified by Jerico Magtaan
- Last Edited on 18/03/20
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


/* void setup allows to run once */
void setup()
{
  /* Start serial port to display results on screen */
  Serial.begin(9600);
  Serial.println("Temperature Measurements with DS18B20");
  Serial.println("Temperature Sensor: DS18B20");
}
/* End setup */


/* void loop allows to run continuously */
void loop()
{
  /* Print required text to screen/serial monitor */
  /* Check for no. of devices connected on bus */
  delay(3000);   // 3 seconds delay
  Serial.println();
  Serial.print(" Number of connected Devices on bus: ");  
  Serial.println(sensors.getDeviceCount());   // Display number of connected devices on bus
  Serial.print("Measuring temperatures from all connected sensors... ");  
  Serial.println();   
  Serial.print("Device 1 (index 0) = ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" Degrees C");
}
/* End main loop */

