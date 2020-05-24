/********************************************************************
// Hall Effect Current Sensor Measure Code using LA 205-S
// Version 1.5
// Programme by Jerico Magtaan
// Last Edited on 09/03/20
*********************************************************************
- Pin 1 of LA 205-S Sensor to +12V supply
- Pin 2 of LA 205-S Sensor to A0 of Arduino (Then to 33Ohm then GND)
- Pin 3 of LA 205-S Sensor to common ground
- Pin 4 of LA 205-S Sensor no contact
- GND pin of Arduino to common ground
- 5V supplied to Arduino via USB
********************************************************************/


/* void setup allows to run once */
void setup()
{
  /* Start serial port to display results on screen */
  Serial.begin(9600);
  pinMode(A0, INPUT);
}
/* End setup */


/* void loop allows to run continuously */
void loop() 
{               
  /* Read current and voltages using LA 205-S with Arduino */
  int SensorCurrentdU = analogRead(A0);     // Current Sensor measured in pin A0 (14)
  float SensorAmpsdU = 1023 / 300;          // Current range 0-300A, dU range 0-1023, get A/dU
  float SensorCurrentAmps = SensorCurrentdU * SensorAmpsdU; // dU from analog multiplied by A/dU 
  
  //float SensorCurrent = SensorCurrentdU * (5 / 1023); // 0-1023 to 0-5v
  //float Amps = SensorCurrent * 33; // calibration may vary as per your conditions


  /* Print measured current and voltage values from LA 205-S sensor */
  Serial.print("Current Sensor Measured Current (dU): ");
  Serial.print(SensorCurrentdU);
  Serial.print("\t");
  Serial.print("Current Sensor Measured Current (A): ");
  Serial.print(SensorCurrentAmps);
  Serial.print("\t");
  delay(1000);    // 1s delay
}
/* End main loop */
/*******************************************************************/
