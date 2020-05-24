/*******************************************************************************
// CAN bus Code for the Power and Instrumentation Arduino
// Version 1.0
// Programme by Jerico Magtaan
// Last Edited on 02/05/20
*******************************************************************************/
/*
 * This programme is for the implementation of CAN bus for the Power and Instrumentation Arduino.
 * Most of the EV tractive system variables are measured in this Arduino,this includes the following:
 * BMS voltage, current and temperature, motor voltages and currents, tractive system power and wheel speeds.
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
// Variables for all EV signals measured on the Power and Instrumentation Arduino that will be sent over CAN bus:
short BMSTemp, BMSVoltage, BMSCurrent; // Variables storing measured BMS Temp, BMS current and BMS voltage values.
short MotorVoltageFL, MotorCurrentFL;  // Variables storing measured front left motor voltage and current values.
short MotorVoltageFR, MotorCurrentFR;  // Variables storing measured front right motor voltage and current values.
short TSPower;      // Variable storing measured total tractive system power values.
short CarSpeed;     // Variable storing measured average wheel speed sensor values.




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
  CAN.sendMsgBuf(0x2, 0, 2, (const byte *) &BMSTemp);         // Send measured BMSTemp value with address 0x2 over CAN bus.
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x3, 0, 2, (const byte *) &CarSpeed);        // Send measured CarSpeed value with address 0x3 over CAN bus.
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x4, 0, 2, (const byte *) &BMSVoltage);      // Send measured BMSVoltage value with address 0x4 over CAN bus.
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x5, 0, 2, (const byte *) &BMSCurrent);      // Send measured BMSCurrent value with address 0x5 over CAN bus.
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x6, 0, 2, (const byte *) &TSPower);         // Send measured TSPower value with address 0x6 over CAN bus.
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x7, 0, 2, (const byte *) &MotorVoltageFL);  // Send measured MotorVoltageFL value with address 0x7 over CAN bus.
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x8, 0, 2, (const byte *) &MotorVoltageFR);  // Send steering MotorVoltageFR value with address 0x8 over CAN bus.
  delay(200); //200ms delay
  CAN.sendMsgBuf(0x9, 0, 2, (const byte *) &MotorCurrentFL);  // Send steering MotorCurrentFL value with address 0x9 over CAN bus.
  delay(200); //200ms delay
  CAN.sendMsgBuf(0xA, 0, 2, (const byte *) &MotorCurrentFR);  // Send steering MotorCurrentFR value with address 0xA over CAN bus.
                    
}
/**************************** End main loop***********************************/
