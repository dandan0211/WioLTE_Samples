/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <WioLTEforArduino.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;
WioLTE Wio;

void setup()
{
  Wio.Init();
  Wio.PowerSupplyGrove(true);
  delay(3000);
  Wire.begin();

  SerialUSB.begin(9600);
  SerialUSB.println("");
  SerialUSB.println("--- START ---------------------------------------------------");

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    SerialUSB.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void loop()
{
  SerialUSB.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred()) { SerialUSB.print(" TIMEOUT"); }

  SerialUSB.println();
}
