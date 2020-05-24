/********************************************************************
- Arduino to Arduino I2C Serial Communication Test (I2C Slave Code)
- Version 1.0
- Modified by Jerico Magtaan
- Last Edited on 20/03/20
********************************************************************/
/*
 * The purpose of this code is to investigate if I2C can be used as a
 * handshake protocol for the LVCSS to Lowry's Arduino (speed sensors, etc)
 * Two Arduinos are connected to each other using built-in I2C pins:
- Pin A4 (SDA) of Slave Arduino to Pin A4 (SDA) of Master Arduino
- Pin A5 (SCL) of Slave Arduino to Pin A5 (SCL) of Master Arduino
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
  Serial.println("| I2C Slave Initiated |");
  Serial.println("Setting up I2C bus and library...");
  
  /* Start up the I2C bus */
  Wire.begin(5);    // Slave address of 5
  Wire.onReceive(receiveEvent);
  Serial.println("------------------------------------------");
}
/* End setup */


/* void loop allows to run continuously */
void loop()
{
  /* If value received is 1 print to serial monitor */
  if (x = 1) 
  {
    Serial.println(">>Value received = 1<<");
    Serial.print("Actual value from I2C = ");
    Serial.println(x);
    delay(2000);  // 2 second delay
    Serial.println("------------------------------------------");
  }

  /* If value received is 3 print to serial monitor */
  if (x = 3) 
  {
    Serial.println(">>Value received = 3<<");
    Serial.print("Actual value from I2C = ");
    Serial.println(x);
    delay(2000);    // 2 second delay
    Serial.println("------------------------------------------");
  }

  /* If value received is 8 print to serial monitor */
  if (x = 8) 
  {
    Serial.println(">>Value received = 8<<");
    Serial.print("Actual value from I2C = ");
    Serial.println(x);
    delay(2000);    // 2 second delay
    Serial.println("------------------------------------------");
  }
}
/* End main loop */


/* Function to read values for variable x from I2C bus */
void receiveEvent(int bytes)
{
  x = Wire.read();
}
/*******************************************************************/
