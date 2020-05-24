/********************************************************************
- Arduino to Arduino I2C Serial Communication Test (I2C Master Code)
- Version 1.0
- Modified by Jerico Magtaan
- Last Edited on 20/03/20
********************************************************************/
/*
 * The purpose of this code is to investigate if I2C can be used as a
 * handshake protocol for the LVCSS to Lowry's Arduino (speed sensors, etc)
 * Two Arduinos are connected to each other using built-in I2C pins:
- Pin A4 (SDA) of Master Arduino to Pin A4 (SDA) of Slave Arduino
- Pin A5 (SCL) of Master Arduino to Pin A5 (SCL) of Slave Arduino
- GND pin of both Arduinos connected to a common ground
********************************************************************/


/******* Import the needed libraries for the sensor to work ********/
#include <Wire.h>

/************** Declare variables that will be used ***************/
int x = 0;


/* void setup allows to run once */
void setup()
{
  /* Start serial port to display results on screen */
  Serial.begin(9600);
  Serial.println("| I2C Master Initiated |");
  Serial.println("Setting up I2C bus and library...");
  /* Start up the I2C bus */
  Wire.begin();
  Serial.println("-------------------------------------------");
}
/* End setup */


/* void loop allows to run continuously */
void loop()
{
  /* Use the I2C bus to send data from the Master to the Slave */
  Serial.println(">>Master Arduino transmitting to Slave Address 5<<");
  Wire.beginTransmission(5);  // Transmit to device with address 5
  Wire.write(x);              // Send variable x
  Wire.endTransmission();     // Stop transmission
  Serial.println(">>Variable successfully transmitted to Address 5<<");

  /* Variable x configuration to show how I2C works for Slave Arduino */
  x++;                        // Variable x incremented by 1 each time
  delay (2000);               // 2 second delay
  if (x > 9)                  // If variable x greater than 9, x=0
  {
    x = 0;
  }
  Serial.println("-------------------------------------------");
}
/* End main loop */
/*******************************************************************/
