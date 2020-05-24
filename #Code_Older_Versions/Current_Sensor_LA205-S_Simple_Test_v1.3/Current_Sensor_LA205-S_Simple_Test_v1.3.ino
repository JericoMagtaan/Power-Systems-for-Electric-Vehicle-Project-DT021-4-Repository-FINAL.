/********************************************************************
// Hall Effect Current Sensor Measure Code using LA 205-S
// Version 1.3
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


/* Times from seconds to days converted to ms for Arduino */
long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
long second =  1000; // 1000 milliseconds in a second

double TotalAmps, AmpSec, AmpHour;


/* void setup allows to run once */
void setup()
{
  /* Start serial port to display results on screen */
  Serial.begin(9600);
}
/* End setup */


/* void loop allows to run continuously */
void loop() {
  /* Start grabbing the time for the Arduino i.e. s ,min. , hr */
  long timeNow = millis();          // "millis" to get the time
  int seconds = (((timeNow % day) % hour) % minute) / second;
  int minutes = ((timeNow % day) % hour) / minute ;
  int hours = (timeNow % day) / hour;   
  int days = timeNow / day ;                    

  /* Read current and voltages using LA 205-S with Arduino */
  float VoltageMeasured = ReadSensorVoltage(14); // Read current, LA 205-S connected to pin A0 (14)
  float Amps = VoltageMeasured * 28; // calibration may vary as per your conditions */
  TotalAmps += Amps;
  AmpSec = TotalAmps;
  AmpHour = TotalAmps / 3600;

  /* Print measured current and voltage values from LA 205-S sensor */
  Serial.print("Current Sensor Measured Voltage: ");
  Serial.print(VoltageMeasured);
  Serial.print("\t");
  Serial.print("Current Sensor Measured Amps: ");
  Serial.print(Amps);
  Serial.print("\t");
  Serial.print("Amp/Sec: ");
  Serial.print(AmpSec, 4);
  Serial.print("\t");
  Serial.print("Amp/Hour: ");
  Serial.print(AmpHour, 6);
  Serial.print("\t");*/
  delay(1000);    // 1s delay
}
/* End main loop */


/* Read voltage from sensor, make sure to convert digital to analog */
float ReadSensorVoltage
{
  float SensorVoltage = analogRead(A0);     // Voltage stored in pin A0 (14)
  float Voltage = SensorVoltage * (5 / 1023); // 0-1023 to 0-5v
  return val;
}
/*******************************************************************/
