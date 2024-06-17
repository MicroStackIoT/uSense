/* WiFi station Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "wifi_sta.h"
#include "main.h"
#include "nvs.h"
#include "led.h"

static const char *TAG = "MicroSense";
static config_t w_config;
static config_t r_config;

void app_main(void)
{
    esp_err_t err;
    wifi_config_t wifi ={0};
    int32_t reboot_count = 0;

    nvs_init();
    led_init();
    led_set_color_white();

    nvs_get_reboot_count(&reboot_count);
    reboot_count++;
    nvs_set_reboot_count(reboot_count);

    // w_config.sample_interval = 5;
    // strcpy(w_config.ssid, "eggsmart");
    // strcpy(w_config.pass, "Geeta@1756");
    // strcpy(w_config.data_url, "https://eggsmart.app/api/sensor_data");
    // strcpy(w_config.meta_url, "https://eggsmart.app/api/meta_data");
    // strcpy(w_config.fota_url, "https://eggsmart.app/api/fota_data");

    // nvs_set_config(&w_config);
    nvs_get_config(&r_config);
    ESP_LOGE(TAG, "Sample interval:%ld", r_config.sample_interval);
    ESP_LOGE(TAG, "SSID:%s", r_config.ssid);
    ESP_LOGE(TAG, "PASS:%s", r_config.pass);
    ESP_LOGE(TAG, "DATA URL:%s", r_config.data_url);
    ESP_LOGE(TAG, "META URL:%s", r_config.meta_url);
    ESP_LOGE(TAG, "FOTA URL:%s", r_config.fota_url);
    
    strcpy((char *)wifi.sta.ssid, r_config.ssid);
    strcpy((char *)wifi.sta.password, r_config.pass);

    wifi_sta_init(&wifi);

    while (1)
    {
        vTaskDelay(10);
    };
}