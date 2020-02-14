#include <WioLTEforArduino.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor_bus0;
VL53L0X sensor_bus1;
WioLTE Wio;

void Pa_HUB_Switch(uint8_t bus)
{
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}
 
void setup()
{
  Wio.Init();
  Wio.PowerSupplyGrove(true);
  delay(3000);
  Wire.begin();

  SerialUSB.begin(9600);
  SerialUSB.println("");
  SerialUSB.println("--- START ---------------------------------------------------");

  // Initialize Bus No.0
  Pa_HUB_Switch(0);
  sensor_bus0.setTimeout(500);
  if (!sensor_bus0.init())
  {
    SerialUSB.println("Failed to detect and initialize sensor on Bus 0!");
    while (1) {}
  }
  sensor_bus0.setMeasurementTimingBudget(200000);

  delay(10);
  
  Pa_HUB_Switch(1);
  sensor_bus1.setTimeout(500);
  if (!sensor_bus1.init())
  {
    SerialUSB.println("Failed to detect and initialize sensor on Bus 1!");
    while (1) {}
  }
  sensor_bus1.setMeasurementTimingBudget(200000);
  
}

void loop()
{
  Pa_HUB_Switch(0);
  SerialUSB.print("0:");
  SerialUSB.print(sensor_bus0.readRangeSingleMillimeters());
  if (sensor_bus0.timeoutOccurred()) { SerialUSB.print(" TIMEOUT"); }

  delay(10);

  Pa_HUB_Switch(1);
  SerialUSB.print("/1:");
  SerialUSB.print(sensor_bus1.readRangeSingleMillimeters());
  if (sensor_bus1.timeoutOccurred()) { SerialUSB.print(" TIMEOUT"); }

  SerialUSB.println();

  delay(100);
}
