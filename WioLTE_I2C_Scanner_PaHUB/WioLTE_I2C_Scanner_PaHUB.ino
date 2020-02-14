// --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    https://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
// Version 6, November 27, 2015.
//    Added waiting for the Leonardo serial communication.
//
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//

#include <WioLTEforArduino.h>
#include <Wire.h>

WioLTE Wio;

uint8_t i2c_bus_no;

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
  SerialUSB.println("\nI2C Scanner");
  i2c_bus_no = 0;
  Pa_HUB_Switch(i2c_bus_no);
}


void loop()
{
  byte error, address;
  int nDevices;

  SerialUSB.print("Scanning... BUS:");
  SerialUSB.println(i2c_bus_no);
  Pa_HUB_Switch(i2c_bus_no);
  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    //SerialUSB.print("Address:");
    //SerialUSB.println(address);
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      SerialUSB.print("I2C device found at address 0x");
      if (address < 16)
        SerialUSB.print("0");
      SerialUSB.print(address, HEX);
      SerialUSB.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      SerialUSB.print("Unknown error at address 0x");
      if (address < 16)
        SerialUSB.print("0");
      SerialUSB.println(address, HEX);
    }
  }
  if (nDevices == 0)
    SerialUSB.println("No I2C devices found\n");
  else
    SerialUSB.println("done\n");

  i2c_bus_no++;
  if (i2c_bus_no > 5)
  {
    i2c_bus_no  = 0;
    delay(5000);
  }
  else
  {
    delay(1000);
  }

}
