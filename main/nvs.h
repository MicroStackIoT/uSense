#ifndef _NVS_H_
#define _NVS_H_

#include <stdio.h>
#include <stdint.h>
#include <nvs_flash.h>

#define STORAGE_NAMESPACE "storage"

#define REBOOT_COUNT "reboot_count"
#define SENSOR_INTERVAL "sensor_interval"

#define WIFI_SSID "ssid"
#define WIFI_PASS "pass"
#define DATA_URL "data_url"
#define META_URL "meta_url"
#define FOTA_URL "fota_url"

#define STRING_SHORT 32
#define STRING_LONG 64

typedef struct
{
    uint32_t sample_interval;
    char ssid[STRING_SHORT];
    char pass[STRING_SHORT];
    char data_url[STRING_LONG];
    char meta_url[STRING_LONG];
    char fota_url[STRING_LONG];
} config_t;

esp_err_t nvs_init(void);

esp_err_t nvs_set_reboot_count(int32_t reboot);
esp_err_t nvs_get_reboot_count(int32_t *reboot);

esp_err_t nvs_set_config(config_t *conf);
esp_err_t nvs_get_config(config_t *conf);

#endif