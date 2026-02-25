/**
   Combining basic examples from the CCS and BME boards by
   Nathan Seidle and Marshall Taylor into a single file.
   Code is based upon SparkFun examples and is
   not my own. See CCS and BME libraries for original source.

   Rev 1. - Jason Forsyth 2/6/19
*/

//include the Wire library to access the i2c interface
#include <Wire.h>

//include the libraries for the BME (humdity, pressure, altitude, and temperature)
//and the CCS (CO2 and TVOC) sensors
//#include "SparkFunCCS811.h"
#include "SparkFunBME280.h"
#include "SparkFun_ENS160.h"  // Click here to get the library: http://librarymanager/All#SparkFun_ENS160


//define the default I2C address of the CCS. Is not needed for BME
//as is already in library
#define CCS811_ADDR 0x5B //Default I2C Address

//create handles to the two sensors
BME280 bmeSensor;
SparkFun_ENS160 ensSensor; 
//CCS811 ccsSensor(CCS811_ADDR);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin();

  if (bmeSensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("Could not access the BME sensor. Please check wiring.");
    while (1); //Freeze
  }

	if( !ensSensor.begin() )
	{
		Serial.println("Could not communicate with the ENS160, check wiring.");
		while(1);
	}

  // Reset the indoor air quality sensor's settings.
	if( ensSensor.setOperatingMode(SFE_ENS160_RESET) )
		Serial.println("Ready.");

	delay(100);

	// Device needs to be set to idle to apply any settings.
	// myENS.setOperatingMode(SFE_ENS160_IDLE);

	// Set to standard operation
	// Others include SFE_ENS160_DEEP_SLEEP and SFE_ENS160_IDLE
	ensSensor.setOperatingMode(SFE_ENS160_STANDARD);

	// There are four values here: 
	// 0 - Operating ok: Standard Operation
	// 1 - Warm-up: occurs for 3 minutes after power-on.
	// 2 - Initial Start-up: Occurs for the first hour of operation.
  //												and only once in sensor's lifetime.
	// 3 - No Valid Output
	//ensStatus = ensSensor.getFlags();
	Serial.print("Gas Sensor Status Flag (0 - Standard, 1 - Warm up, 2 - Initial Start Up): ");
	Serial.println(ensSensor.getFlags());


}

void loop() {
  // put your main code here, to run repeatedly:

  ////////////////////// Get Data from the BME Board //////////////////////
  float humidity = bmeSensor.readFloatHumidity();
  float pressure = bmeSensor.readFloatPressure();
  float altitude = bmeSensor.readFloatAltitudeFeet();
  float temp = bmeSensor.readTempF();

  Serial.print("Humidity: ");
  Serial.print(humidity, 0); //print with no decimal places

  Serial.print(" Pressure: ");
  Serial.print(pressure, 0); //print with no decimal places

  Serial.print(" Alt: ");
  Serial.print(altitude, 1); //print with one decimal place

  Serial.print(" Temp: ");
  Serial.print(temp, 2); // print with two decimal places

  ////////////////////// Get Data from the ENS Board //////////////////////

  //create init variables for CO2 and TVOC. Give them some initial value
  //so we can know if they are not "fresh" data from the sensor.
  int CO2 = -1;
  int TVOC = -1;
		Serial.print("Air Quality Index (1-5) : ");
		Serial.println(ensSensor.getAQI());

		Serial.print("Total Volatile Organic Compounds: ");
		Serial.print(ensSensor.getTVOC());
		Serial.println("ppb");

		Serial.print("CO2 concentration: ");
		Serial.print(ensSensor.getECO2());
		Serial.println("ppm");

	Serial.print("Gas Sensor Status Flag (0 - Standard, 1 - Warm up, 2 - Initial Start Up): ");
    Serial.println(ensSensor.getFlags());

		Serial.println();




  ////////////////////// Print Out the Time //////////////////////

  //get the number of milliseconds since the processor was turned on
  long runTime = millis(); 

  Serial.print(" Time: ");
  Serial.println(runTime); //print out the time as a new line to end this line


  //take a 1000ms break. Don't overwhelm the bus and print screen
  //You can "go faster" but the CCS sensor won't be ready except every 1s (approx.)
  delay(1000);

}
