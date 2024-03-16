#define BLYNK_TEMPLATE_ID "TMPL61JvPXC2e"
#define BLYNK_TEMPLATE_NAME "Iot Based Project"
#define BLYNK_AUTH_TOKEN "tb639Lb0uBZz2oK43d9UZxawj_1kvxfO"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Abhishek ";
char pass[] = "12345679";

BlynkTimer timer;

void sendSensor()
{
  if(mpu.getMotionInterruptStatus()) {
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    /* Print out the values */
    Serial.print("AccelX:");
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print("AccelY:");
    Serial.print(a.acceleration.y);
    Serial.print(",");
    Serial.print("AccelZ:");
    Serial.print(a.acceleration.z);
    Serial.print(", ");
    Serial.print("GyroX:");
    Serial.print(g.gyro.x);
    Serial.print(",");
    Serial.print("GyroY:");
    Serial.print(g.gyro.y);
    Serial.print(",");
    Serial.println("\n");
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, a.acceleration.x);
    Blynk.virtualWrite(V1, a.acceleration.y);
    Blynk.virtualWrite(V2, a.acceleration.z);
    Blynk.virtualWrite(V3,g.gyro.x);
    Blynk.virtualWrite(V4,g.gyro.y);
   delay(200);
  }
}
void setup()
{   
  
   Serial.begin(115200);
    while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // WiFi.mode(WIFI_STA);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  //setupt motion detection
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true); // Keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  Serial.println("");
  delay(100);
 
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, sendSensor);
 
  }

void loop()
{
  Blynk.run();
  timer.run();
 }