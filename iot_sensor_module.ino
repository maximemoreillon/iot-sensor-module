/*
 * IoT sensor module
 * 
 * Maxime MOREILLON
 * 
 * Board type: Wemos D1 Mini
 * 
 */

#include "IotKernel.h"
#include <OneWire.h> // For the temperature sensor
#include <DallasTemperature.h>

#define DEVICE_TYPE "sensor"
#define DEVICE_FIRMWARE_VERSION "0.0.1"

#define PIR_PIN D2
#define TEMPERATURE_PIN D6

#define TEMPERATURE_READ_PERIOD 10000


IotKernel iot_kernel(DEVICE_TYPE,DEVICE_FIRMWARE_VERSION); 

OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature temperatureSensor(&oneWire);

void setup() {
  iot_kernel.init();
  temperatureSensor.begin();
}

void loop() {
  iot_kernel.loop();
  read_PIR();
  read_temperature();
}
