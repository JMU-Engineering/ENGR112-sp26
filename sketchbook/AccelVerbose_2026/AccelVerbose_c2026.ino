#include <SparkFun_MMA8452Q.h>

/***
 * Simple program for reporting the accelerometer X, Y, and Z axis values.
 * Based upon the MMA8452Q Example program from SparkFun by Jim Lindblom
 * 
 * Rev 1 - Jason Forsyth - 2/17/19
 * Rev 2 - Christine Toh - 2/18/2026
 */

//include Wire Library to access i2c
#include <Wire.h>

//include the MMA8452 library
#include <SparkFun_MMA8452Q.h>

//create a handle to the accelerometer
MMA8452Q accel;


void setup() {
  Serial.begin(9600);

  Serial.println("Hello World! Welcome to the Accel program!");

  /**
   * Initialize the accelerometer to +/- 2g and 800 Hz output
   * Parameters can be changed via library
   */
  accel.init();

    //give the terminal time to catch up
    delay(1000);

    //print out the header for the file
    Serial.println("X,Y,Z");

}

void loop() {

   if (accel.available()) {
    accel.read();

   // Serial.print("X: ");
    Serial.print(accel.cx, 3); //printing accelerometer values in "g" units. Remove "cx" and replace with "x" for raw digital output.
    Serial.print(",");
    
   // Serial.print("  Y: ");
    Serial.print(accel.cy, 3);
    Serial.print(",");

   // Serial.print("  Z: ");
    Serial.println(accel.cz, 3);
    Serial.print(",");

   }

  //delay 20ms for a 50Hz sample rate
  delay(20);

}
