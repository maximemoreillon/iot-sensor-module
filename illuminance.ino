void illuminance_setup(){
  pinMode(ILLUMINANCE_PIN, INPUT);
}
void read_illuminance(){
  static long last_read_time;

  if(millis() - last_read_time > ILLUMINANCE_READ_PERIOD){
    last_read_time = millis();

    int adc_value = analogRead(ILLUMINANCE_PIN);
    
    Serial.print("[Illuminance] ");
    Serial.print(adc_value);
    Serial.println("");

    StaticJsonDocument<200> outbound_JSON_message;
    outbound_JSON_message["illuminance"] = adc_value;

    // Serialize JSON into a char array
    char JSONmessageBuffer[100];
    serializeJson(outbound_JSON_message, JSONmessageBuffer, sizeof(JSONmessageBuffer));

    // Send the char array with MQTT
    Serial.println(F("[MQTT] publish of illuminance measurement"));
    String topic = iot_kernel.mqtt_base_topic + "/illuminance";
    iot_kernel.mqtt.publish(topic.c_str(), JSONmessageBuffer, MQTT_RETAIN);
  }
}
