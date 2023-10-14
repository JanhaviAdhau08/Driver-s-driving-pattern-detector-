/*Connect VCC of the ADXL345 to 3.3V on the ESP8266.
Connect GND of the ADXL345 to GND on the ESP8266.
Connect SDA (Serial Data) of the ADXL345 to GPIO4 (D2) on the ESP8266.
Connect SCL (Serial Clock) of the ADXL345 to GPIO5 (D1) on the ESP8266.
*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup(void) {
  Serial.begin(115200);
  if(!accel.begin()) {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    while(1);
  }
  accel.setRange(ADXL345_RANGE_16_G);
}

void loop(void) {
  sensors_event_t event;
  accel.getEvent(&event);

  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;

  Serial.print("X: "); Serial.print(x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(z); Serial.println();

  delay(1000);
}
