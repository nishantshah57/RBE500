/*
The sensor outputs provided by the library are the raw 16-bit values
obtained by concatenating the 8-bit high and low gyro data registers.
They can be converted to units of dps (degrees per second) using the
conversion factors specified in the datasheet for your particular
device and full scale setting (gain).

Example: An L3GD20H gives a gyro X axis reading of 345 with its
default full scale setting of +/- 245 dps. The So specification
in the L3GD20H datasheet (page 10) states a conversion factor of 8.75
mdps/LSB (least significant bit) at this FS setting, so the raw
reading of 345 corresponds to 345 * 8.75 = 3020 mdps = 3.02 dps.
*/
/*
Wiring: SDA-A4, SCL-A5, VDD-3.3V, GND-GND
*/

#include <Wire.h>
#include <L3G.h>
#include <LSM303.h>

L3G gyro;
LSM303 compass;

char report[80];

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();

  compass.init();
  compass.enableDefault();

  // Setup code for the button ISR
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), BtnISR, FALLING);
}

void loop() {
    while(millis() < 10000) {
      gyro.read();
      compass.read();

      // Serial.print("G ");
      // Serial.print("X: ");
      Serial.print((int)gyro.g.x);
      Serial.print(", ");
      // Serial.print(" Y: ");
      Serial.print((int)gyro.g.y);
      Serial.print(", ");
      // Serial.print(" Z: ");
      Serial.print((int)gyro.g.z);
      Serial.print(", ");

      Serial.print((int)compass.a.x);
      Serial.print(", ");
      Serial.print((int)compass.a.y);
      Serial.print(", ");
      Serial.print((int)compass.a.z);
      Serial.print(", ");
      Serial.print((int)compass.m.x);
      Serial.print(", ");
      Serial.print((int)compass.m.y);
      Serial.print(", ");
      Serial.println((int)compass.m.z);
      // snprintf(report, sizeof(report), "A: %6d %6d %6d    M: %6d %6d %6d",
      //   compass.a.x, compass.a.y, compass.a.z,
      //   compass.m.x, compass.m.y, compass.m.z);
      // Serial.println(report);

      delay(100);
    }
}

void BtnISR() {
    Serial.println("Button pressed");
}
