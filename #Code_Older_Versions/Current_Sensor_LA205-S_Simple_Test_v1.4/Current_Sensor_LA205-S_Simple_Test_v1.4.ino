/********************************************************************
// Hall Effect Current Sensor Measure Code using LA 205-S
// Version 1.4
// Programme by Jerico Magtaan
// Last Edited on 03/03/20
*********************************************************************
- Pin A0 of Arduino to Pin 1 of LA 205-S Sensor
- GND pin of Arduino to common ground
- 5V supplied to Arduino via USB
- Pin 3 of LA 205-S Sensor to common ground
- Pin 2 of LA 205-S Sensor to +12V supply
- Pin 4 of LA 205-S Sensor no contact
********************************************************************/


/* void setup allows to run once */
void setup()
{
  /* Start serial port to display results on screen */
  Serial.begin(9600);
}
/* End setup */


/* void loop allows to run continuously */
void loop() {
               
  /* Read current and voltages using LA 205-S with Arduino */
  float SensorVoltage = analogRead(A0);     // Voltage stored in pin A0 (14)
  float Voltage = SensorVoltage * (5 / 1023); // 0-1023 to 0-5v
  float Amps = SensorVoltage * 28; // calibration may vary as per your conditions */

  /* Print measured current and voltage values from LA 205-S sensor */
  Serial.print("Current Sensor Measured Voltage: ");
  Serial.print(SensorVoltage);
  Serial.print("\t");
  Serial.print("Current Sensor Measured Amps: ");
  Serial.print(Amps);
  Serial.print("\t");
  delay(1000);    // 1s delay
}
/* End main loop */
/*******************************************************************/
