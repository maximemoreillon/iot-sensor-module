void read_temperature(){
  static long last_read_time;

  if(millis() - last_read_time > TEMPERATURE_READ_PERIOD){
    last_read_time = millis();
    temperatureSensor.requestTemperatures(); 
    float temperatureC = temperatureSensor.getTempCByIndex(0);
    Serial.print("[Temperature] ");
    Serial.print(temperatureC);
    Serial.println("ºC");

    StaticJsonDocument<200> outbound_JSON_message;
    outbound_JSON_message["temperature"] = temperatureC;

    // Serialize JSON into a char array
    char JSONmessageBuffer[100];
    serializeJson(outbound_JSON_message, JSONmessageBuffer, sizeof(JSONmessageBuffer));

    // Send the char array with MQTT
    Serial.println(F("[MQTT] publish of temperature measurement"));
    String topic = iot_kernel.mqtt_base_topic + "/temperature";
    iot_kernel.mqtt.publish(topic.c_str(), JSONmessageBuffer, MQTT_RETAIN);
  }
  
}
