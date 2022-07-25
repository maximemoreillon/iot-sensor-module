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
#define DEVICE_FIRMWARE_VERSION "0.1.1"

#define PIR_PIN D2
#define TEMPERATURE_PIN D6
#define ILLUMINANCE_PIN A0

#define TEMPERATURE_READ_PERIOD 60000
#define ILLUMINANCE_READ_PERIOD 60000


IotKernel iot_kernel(DEVICE_TYPE,DEVICE_FIRMWARE_VERSION); 

OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature temperatureSensor(&oneWire);

void setup() {
  iot_kernel.init();
  temperatureSensor.begin();
  illuminance_setup();
}

void loop() {
  iot_kernel.loop();
  read_PIR();
  read_temperature();
  read_illuminance();
}
