/* WiFi station Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "wifi_sta.h"
#include "sensor_if.h"
#include "main.h"
#include "nvs.h"
#include "led.h"

static const char *TAG = "MicroSense";

static config_t config;

void app_main(void)
{
    wifi_config_t wifi = {0};
    int32_t reboot_count = 0;

    nvs_init();

    led_init();
    
    led_set_color_white();

    nvs_get_reboot_count(&reboot_count);
    reboot_count++;
    nvs_set_reboot_count(reboot_count);

    static config_t w_config;
    w_config.sample_interval = 5;
    strcpy(w_config.ssid, "eggsmart");
    strcpy(w_config.pass, "Geeta@1756");
    strcpy(w_config.data_url, "https://eggsmart.app/api/sensor_data");
    strcpy(w_config.meta_url, "https://eggsmart.app/api/meta_data");
    strcpy(w_config.fota_url, "https://eggsmart.app/api/fota_data");

    nvs_set_config(&w_config);

    nvs_get_config(&config);

    ESP_LOGE(TAG, "Sample interval:%ld", config.sample_interval);
    ESP_LOGE(TAG, "SSID:%s", config.ssid);
    ESP_LOGE(TAG, "PASS:%s", config.pass);
    ESP_LOGE(TAG, "DATA URL:%s", config.data_url);
    ESP_LOGE(TAG, "META URL:%s", config.meta_url);
    ESP_LOGE(TAG, "FOTA URL:%s", config.fota_url);
    
    strcpy((char *)wifi.sta.ssid, config.ssid);
    strcpy((char *)wifi.sta.password, config.pass);
    wifi_sta_init(&wifi);

    config.sample_interval += config.sample_interval*50; 

    TickType_t xLastWakeTime;
    const TickType_t xFrequency = config.sample_interval;
    xLastWakeTime = xTaskGetTickCount();

    float at, rh, lx;
    sensor_if_init();
    while(1)
    {
        vTaskDelayUntil( &xLastWakeTime, xFrequency);
        ESP_LOGE(TAG, "Sending data to :%s", config.data_url);
        sensor_if_get_data(&at, &rh, &lx);
        ESP_LOGE(TAG, "at:%f\trh:%f\tlx:%f", at, rh, lx);
    };
}