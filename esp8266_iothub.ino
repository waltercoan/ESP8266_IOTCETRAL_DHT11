// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Please use an Arduino IDE 1.6.8 or greater

// You must set the device id, device key, IoT Hub name and IotHub suffix in
// iot_configs.h
#include <SimpleDHT.h>
#include "iot_configs.h"

#include <AzureIoTHub.h>
#if defined(IOT_CONFIG_MQTT)
    #include <AzureIoTProtocol_MQTT.h>
#elif defined(IOT_CONFIG_HTTP)
    #include <AzureIoTProtocol_HTTP.h>
#endif

#include "sample.h"
#include "esp8266/sample_init.h"
#include <SimpleDHT.h>

static char ssid[] = IOT_CONFIG_WIFI_SSID;
static char pass[] = IOT_CONFIG_WIFI_PASSWORD;

int pinDHT11 = 14;
SimpleDHT11 dht11;

void setup() {
    sample_init(ssid, pass);
}

// Azure IoT samples contain their own loops, so only run them once
static bool done = false;
void loop() {
    if (!done)
    {
        // Run the sample
        // You must set the device id, device key, IoT Hub name and IotHub suffix in
        // iot_configs.h
        byte temperature = 0;
        byte humidity = 0;
        int err = SimpleDHTErrSuccess;
        if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
          Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
          return;
        }
        sample_run(temperature, humidity);
        done = true;
    }
    else
    {
      delay(10000);
      done = false;
    }
}
