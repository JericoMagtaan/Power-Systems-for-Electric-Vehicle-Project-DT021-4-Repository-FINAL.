/********************************************************************
- Temperature Measurements with Multiple (4) Analog LM35 Sensors
- Version 1.0
- Programme by Jerico Magtaan
- Last Edited on 26/03/20
********************************************************************/
/*
 * Two analog LM35 sensors are used to measure temperature
 * The wiring for each sensor are connected as followed:
- Pin 1 (Vs) of LM35 sensors can be supplied 4 to 20V (5V from Arduino)
- Pin 2 (Vout) of LM35 sensors can be connected to any analog pin of Arduino
- Pin 3 (GND) of LM35 sensors can be connected to GND pin of Arduino
********************************************************************/


/******* Define all variables that will be used for temp. *********/
float tempC1;
float tempC2;
float tempC3;
float tempC4;
float tempdegC1;
float tempdegC2;
float tempdegC3;
float tempdegC4;
int tempPin1 = A0;
int tempPin2 = A1;
int tempPin3 = A2;
int tempPin4 = A3;


/* void setup allows to run once */
void setup ()
{
  /* Start serial port to display results on screen */
  Serial.begin(9600);
  Serial.print("| LM35 Sensor Measurements Started |");
  Serial.println();
  Serial.println("-------------------------------------");
}
/* End setup */


/* void loop allows to run continuously */
void loop()
{
  /* Sensor temperature ADC calculations */
  tempC1 = analogRead(tempPin1);                // Read from A0
  tempdegC1 = (5.0 * tempC1 * 100.0) / 1024.0;  // A0 temp. ADC
  tempC2 = analogRead(tempPin2);                // Read from A1
  tempdegC2 = (5.0 * tempC2 * 100.0) / 1024.0;  // A1 temp. ADC
  tempC3 = analogRead(tempPin3);                // Read from A2
  tempdegC3 = (5.0 * tempC3 * 100.0) / 1024.0;  // A2 temp. ADC
  tempC4 = analogRead(tempPin4);                // Read from A3
  tempdegC4 = (5.0 * tempC4 * 100.0) / 1024.0;  // A3 temp. ADC
  
  /* Print sensor measurements to serial monitor */
  Serial.print("Sensor01 temperature:   ");
  Serial.print(tempdegC1, 1);
  Serial.println();
  Serial.print("Sensor02 temperature:   ");
  Serial.print(tempdegC2, 1);
  Serial.println();
  Serial.print("Sensor03 temperature:   ");
  Serial.print(tempdegC3, 1);
  Serial.println();
  Serial.print("Sensor04 temperature:   ");
  Serial.print(tempdegC4, 1);
  Serial.println();
  Serial.println("-------------------------------------");
  delay(1000);      // 1 second delay
}
/* End main loop */
/*******************************************************************/
