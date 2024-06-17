#include "nvs.h"
#include <string.h>
#include "esp_log.h"

esp_err_t nvs_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    return ret;
}

esp_err_t nvs_set_reboot_count(int32_t reboot)
{
    nvs_handle_t nvs_handle;
    esp_err_t err;

    err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK)
    {
        return err;
    }

    err = nvs_set_i32(nvs_handle, REBOOT_COUNT, reboot);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    err = nvs_commit(nvs_handle);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    nvs_close(nvs_handle);
    return ESP_OK;
}

esp_err_t nvs_get_reboot_count(int32_t *reboot)
{
    nvs_handle_t nvs_handle;
    esp_err_t err;

    err = nvs_open(STORAGE_NAMESPACE, NVS_READONLY, &nvs_handle);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    err = nvs_get_i32(nvs_handle, REBOOT_COUNT, reboot);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND)
    {
        nvs_close(nvs_handle);
        return err;
    }

    nvs_close(nvs_handle);
    return ESP_OK;
}

esp_err_t nvs_get_config(config_t *conf)
{
    size_t required_size;
    nvs_handle_t nvs_handle;
    config_t temp_conf;
    esp_err_t err;

    err = nvs_open(STORAGE_NAMESPACE, NVS_READONLY, &nvs_handle);
    if (err != ESP_OK)
    {
        return err;
    }

    err = nvs_get_u32(nvs_handle, SENSOR_INTERVAL, &conf->sample_interval);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "nvs_get_u32 FAILED");
        nvs_close(nvs_handle);
        return err;
    }

    err = nvs_get_str(nvs_handle, WIFI_SSID, temp_conf.ssid, &required_size);
    if (err != ESP_OK)
    {
        ESP_LOGE("NVS", "nvs_get_str FAILED: 0%x", (int)err);
        nvs_close(nvs_handle);
        return err;
    }

    strcpy(conf->ssid, temp_conf.ssid);

    err = nvs_get_str(nvs_handle, WIFI_PASS, temp_conf.pass, &required_size);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    strcpy(conf->pass, temp_conf.pass);

    err = nvs_get_str(nvs_handle, DATA_URL, temp_conf.data_url, &required_size);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    strcpy(conf->data_url, temp_conf.data_url);

    err = nvs_get_str(nvs_handle, META_URL, temp_conf.meta_url, &required_size);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    strcpy(conf->meta_url, temp_conf.meta_url);

    err = nvs_get_str(nvs_handle, FOTA_URL, temp_conf.fota_url, &required_size);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    strcpy(conf->fota_url, temp_conf.fota_url);

    nvs_close(nvs_handle);
    return ESP_OK;
}

esp_err_t nvs_set_config(config_t *conf)
{
    esp_err_t err;
    nvs_handle_t nvs_handle;

    err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK)
    {
        return err;
    }

    err = nvs_set_u32(nvs_handle, SENSOR_INTERVAL, conf->sample_interval);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND)
    {
        nvs_close(nvs_handle);
        return err;
    }

    err = nvs_set_str(nvs_handle, WIFI_SSID, conf->ssid);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    err = nvs_set_str(nvs_handle, WIFI_PASS, conf->pass);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    err = nvs_set_str(nvs_handle, DATA_URL, conf->data_url);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    err = nvs_set_str(nvs_handle, META_URL, conf->meta_url);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    err = nvs_set_str(nvs_handle, FOTA_URL, conf->fota_url);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    err = nvs_commit(nvs_handle);
    if (err != ESP_OK)
    {
        nvs_close(nvs_handle);
        return err;
    }

    nvs_close(nvs_handle);
    return ESP_OK;
}