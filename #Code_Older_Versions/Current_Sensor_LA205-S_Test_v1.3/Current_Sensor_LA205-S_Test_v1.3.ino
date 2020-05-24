/********************************************************************
// Hall Effect Current Sensor Measure Code using LA 205-S
// Version 1.3
// Programme by Jerico Magtaan
// Last Edited on 26/02/20
*********************************************************************
- Pin A0 of Arduino to Pin 4 of LA 205-S Sensor
- GND pin of Arduino to common ground
- 5V supplied to Arduino via USB
- Pin 2 of LA 205-S Sensor to common ground
- Pin 3 of LA 205-S Sensor to +12V supply
- Pin 1 of LA 205-S Sensor no contact
********************************************************************/
                              /*
  ----------------------------- |
  Analog Value  Current reading |
  ------------ | -------------- |
  0.49-0.52    |    13.5-14.0   |
  1.01-1.10    |    27.8-28.0   |
  ------------------------------|
                               */

/* Times from seconds to days converted to ms for Arduino */
long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
long second =  1000; // 1000 milliseconds in a second

double totalAmps, ampSec, ampHour;


/* void setup allows to run once */
void setup()
{
  /* Make sure variables are equal to 0 before starting */
  ampSec = 0.0;
  ampHour = 0.0;

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
  float curSen = readcellvoltage(14); // Read current, LA 205-S connected to pin A0 (14)
  float cell = readcellvoltage(15);   // Read cell voltage, lead cell connected to A1 (15)
  
  /* Offset calibrations using multimeter readings */
  float offSet = 0.06;
  cell = cell - 0.22;
  curSen = curSen + offSet;

  /* Calibration using clampmeter current values *
  float amps = curSen * 28; // calibration may vary as per your conditions */
  totalAmps += amps;
  ampSec = totalAmps;
  ampHour = totalAmps / 3600;

  Serial.print("Current Sensor: ");
  Serial.print(curSen);
  Serial.print("\t");
  Serial.print("Measured Amps: ");
  Serial.print(amps);
  Serial.print("\t");
  Serial.print("Cell Voltage: ");
  Serial.print(cell);
  Serial.print("\t");
  Serial.print("Amp/Sec: ");
  Serial.print(ampSec, 4);
  Serial.print("\t");
  Serial.print("Amp/Hour: ");
  Serial.print(ampHour, 6);
  Serial.print("\t");
  /*Serial.print(minutes);
  Serial.print(":");
  Serial.print(seconds);
  Serial.println();*/

  delay(1000);    // 1s delay
}

/* Read the cell voltage, make sure to convert digital to analog */
float readcellvoltage(int a)
{
  float readVoltage = analogRead(a);     // Voltage stored in pin A0 (14)
  float val = (readVoltage * 5 ) / 1023; // 0-1023 to 0-5v
  return val;
}
/* End main loop */
/*******************************************************************/
