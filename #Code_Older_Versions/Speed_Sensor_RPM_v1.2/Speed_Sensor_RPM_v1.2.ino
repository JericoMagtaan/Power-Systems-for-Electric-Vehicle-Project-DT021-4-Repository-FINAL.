/*******************************************************************************
- Speed Measurement (RPM) with a Digital Speed Sensor using Interrupt
- Version 1.2
- Modified by Jerico Magtaan
- Last Edited on 26/04/20
*******************************************************************************/
/*
 * The purpose of this code is to implement an RPM measurement for the speed sensor
 * that will be implemented on the electric car.
 * For this version, this will be done by measuring the period duration between pulses
 * to calculate the RPM, where the number of readings will vary depending on the RPM, where
 * fewer readings will be taken at lower RPM and more readings at higher RPM for accuracy.
 
 * Speed sensor and Arduino will be connected as follows:
- Pin D3 of Arduino to the output pin of the speed sensor
- Pin 5V of Arduino to Vsupply pin of the speed sensor
- GND pin of speed sensor to common ground
- GND pin of Arduino to common ground
*******************************************************************************/




/************ Declare variables that will be used on the Arduino *************/
              // Calbration variables (adjustable to suit the system)
              
const byte PulsesPerRevolution = 1;  // Set how many pulses there are on each revolution. Default: 2.


// If the period between pulses is too high or pulses stopped, then we would get stuck showing the last value instead of 0.
// This value is used for maximum duration between pulses to detect if the vehicle has stopped.
// Setting a low value is going to allow the detection of stop situations faster, but it will prevent having low RPM readings.
const unsigned long ZeroTimeout = 100000;  // For high response time i.e. 100000.
                                           // For reading very low RPM i.e. 300000.

// Calibration for smoothing RPM:
const byte numReadings = 2;  // Number of samples for smoothing. The higher, the more smoothing but reacts slower to change.



/******************************************************************************/
              // Fixed variables needed for calculations, etc...

volatile unsigned long LastTimeWeMeasured;  // Stores the last time we measured a pulse so we can calculate the period.
volatile unsigned long PeriodBetweenPulses = ZeroTimeout + 1000;  // Variable storing the period between pulses in microseconds.
volatile unsigned long PeriodAverage = ZeroTimeout + 1000;        // Variable storing averaged period between pulses.
unsigned long FrequencyRaw;    // Variable storing calculated frequency with lots of decimals.
unsigned long FrequencyReal;   // Variable storing calculated frequency without decimals.
unsigned long RPM;             // Variable storing calculated RPM without smoothing.
unsigned int PulseCounter = 1; // Variable storing amount of pulse readings we took so we can average multiple pulses before calculating the period.
unsigned long PeriodSum;       // Variable storing calculated the summation of all the periods to get an average period reading.
unsigned long LastTimeCycleMeasure = LastTimeWeMeasured;  // Variable storing the last time we measure a pulse in that cycle.
unsigned long CurrentMicros = micros();    // Variable storing the micros in that cycle.
unsigned int AmountOfReadings = 1;  // Variable storing number of readings we will be using for RPM calculation and display
unsigned int ZeroDebouncingExtra;   // Variable storing the extra value added to the ZeroTimeout to debounce it.
                                    // The ZeroTimeout needs debouncing so when the value is close to the threshold it
                                    // doesn't jump from 0 to the value. This extra value changes the threshold a little
                                    // when we show a 0.

// Variables for RPM measurement for data smoothing:
unsigned long readings[numReadings];  // Variable storing the input.
unsigned long readIndex;              // Variable storing the index of the current reading.
unsigned long total;                  // Variable storing the running total.
unsigned long average;                // Variable storing the calculated RPM with smoothing.




/*********************** Void setup allows to run once ***********************/
void setup()
{

  // Begin serial communication:
  Serial.begin(9600);

  // Digital Pin 3 Set As An Interrupt for the Arduino Uno:
  attachInterrupt(digitalPinToInterrupt(3), Pulse_Event, RISING);

  delay(1000);  // 1 second delay.

}
/********************************* End setup *********************************/




/******************* Void loop allows to run continuously ********************/
void loop()
{
  // The following is going to store the two values that might change in the middle of the cycle.
  // We are going to do math and functions with those values and they can create glitches if they change in the
  // middle of the cycle.
  LastTimeCycleMeasure = LastTimeWeMeasured;  // Store the LastTimeWeMeasured in a variable.
  CurrentMicros = micros();  // Store the micros() in a variable.


  // CurrentMicros should always be higher than LastTimeWeMeasured:
  if(CurrentMicros < LastTimeCycleMeasure)
  {
    LastTimeCycleMeasure = CurrentMicros;
  }

  // Calculate the frequency:
  FrequencyRaw = 10000000000 / PeriodAverage;  // Calculate the frequency using the period between pulses.

  // Detect if pulses stopped or frequency is too low, so we can show 0 Frequency:
  if(PeriodBetweenPulses > ZeroTimeout - ZeroDebouncingExtra || CurrentMicros - LastTimeCycleMeasure > ZeroTimeout - ZeroDebouncingExtra)
  {
    FrequencyRaw = 0;  // Set frequency as 0.
    ZeroDebouncingExtra = 2000;  // Change the threshold a little so it doesn't bounce.
  }
  else
  {
    ZeroDebouncingExtra = 0;  // Reset the threshold to the normal value so it doesn't bounce.
  }

  FrequencyReal = FrequencyRaw / 10000;  // Get frequency without decimals.
                                          // This is not used to calculate RPM but we remove the decimals just in case
                                          // you want to print it.
  // Calculate the RPM:
  RPM = FrequencyRaw / PulsesPerRevolution * 60;  // Frequency divided by amount of pulses per revolution multiply by
                                                  // 60 seconds to get minutes.
  RPM = RPM / 10000;  // Remove the decimals.

  // Print information on the serial monitor:
  Serial.print("Period: ");
  Serial.print(PeriodBetweenPulses);
  Serial.println();
  Serial.print("Readings: ");
  Serial.print(AmountOfReadings);
  Serial.println();
  Serial.print("Frequency: ");
  Serial.print(FrequencyReal);
  Serial.println();
  Serial.print("RPM: ");
  Serial.print(RPM);
  Serial.println();
  delay(500);
}
/**************************** End main loop***********************************/




/********************* Event interrupt for pulse event ***********************/
void Pulse_Event()
{

  PeriodBetweenPulses = micros() - LastTimeWeMeasured;  // Current "micros" minus the old "micros" when the last pulse happens.
                                                        // This will result with the period (microseconds) between both pulses.
                                                        
  LastTimeWeMeasured = micros();  // Stores the current micros so the next time we have a pulse we would have something to compare with.


  if(PulseCounter >= AmountOfReadings)  // If counter for amount of readings reach the set limit:
  {
    PeriodAverage = PeriodSum / AmountOfReadings;  // Calculate the final period dividing the sum of all readings by the
                                                   // amount of readings to get the average.
    PulseCounter = 1;  // Reset the counter to start over. The reset value is 1 because its the minimum setting allowed (1 reading).
    PeriodSum = PeriodBetweenPulses;  // Reset PeriodSum to start a new averaging operation.
  }
  else
  {
    PulseCounter++;   // Increase the counter for amount of readings by 1.
    PeriodSum = PeriodSum + PeriodBetweenPulses;  // Add the periods so later we can average.
  }

}
/******************* End event interrupt for pulse event *********************/
