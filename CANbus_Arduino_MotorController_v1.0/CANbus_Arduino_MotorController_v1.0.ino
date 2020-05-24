/*******************************************************************************
// CAN bus Code for the Motor Controller Arduino
// Version 1.0
// Programme by Jerico Magtaan
// Last Edited on 02/05/20
*******************************************************************************/
/*
 * This programme is for the implementation of CAN bus for the Motor Controller Arduino.
 * For this Arduino, there are only two variables that we are interested in which are the:
 * Throttle input percentage and steering input percentage of the motors. 
 * The CAN address structure has already been designed for the EV, thus these variables are given addresses accordingly.

 * Arduino and MCP2515 module connections via SPI and 5V supply pin:
- Pin D10 of Arduino to CS of MCP2515 module
- Pin D11 of Arduino to SI of MCP2515 module
- Pin D12 of Arduino to SO of MCP2515 module
- Pin D13 of Arduino to SCK of MCP2515 module
- Pin 5V of Arduino to VCC of MCP2515 module
- All Arduino and MCP2515 modules connected to a common ground
- 120 Ohm termination resistor at both ends of CAN bus
*******************************************************************************/




/************* Import all needed libraries needed by the Arduino **************/
#include <SPI.h>                // Library used for SPI communication for the CAN module.
#include <mcp_can.h>            // Library used for CAN bus communication.


/*************** Declare pins that will be used on the Arduino ***************/
MCP_CAN CAN(10);            // Digital pin 10 used as default chip select (CS) pin for SPI communication.


/************ Declare variables that will be used on the Arduino *************/
short Steering;   // Variable storing percentage steering input value of motors.
short Throttle;   // Variable storing percentage throttle input value of motors.




/*********************** Void setup allows to run once ***********************/
void setup()
{
  
  // Begin serial communication:
  Serial.begin(9600);

  // Begin CAN bus communication using the CAN bus shield at 100KBPS:
  START_INIT:

    if(CAN_OK == CAN.begin(CAN_100KBPS))
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);   // 0.1 second delay.
        goto START_INIT;
    }
    
}
/********************************* End setup *********************************/




/******************* Void loop allows to run continuously ********************/
void loop()
{ 

  // In this part, we use the CAN library to allocate an address i.e. 0xB, 0x2,etc.. to the
  // variable values, where any Arduino on the network can receive these values by calling
  // the addresses you have implemented, where in our case are:
  CAN.sendMsgBuf(0xB, 0, 2, (const byte *) &Steering);  // Send measured Steering value with address 0xB over CAN bus.
  delay(200); // 0.2 second delay.
  CAN.sendMsgBuf(0xC, 0, 2, (const byte *) &Throttle);  // Send measured Throttle value with address 0xC over CAN bus.
  delay(200); // 0.2 second delay.
                    
}
/**************************** End main loop***********************************/
