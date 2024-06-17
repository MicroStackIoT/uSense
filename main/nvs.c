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
    esp_err_t err;

    err = nvs_open(STORAGE_NAMESPACE, NVS_READONLY, &nvs_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE("NVS", "nvs_open FAILED: 0%x", (int)err);
        return err;
    }

    err = nvs_get_blob(nvs_handle, "config", NULL, &required_size);

    ESP_LOGE("NVS", "required size: %d", required_size);    

    err = nvs_get_blob(nvs_handle, "config", conf, &required_size);
    if (err != ESP_OK)
    {
        ESP_LOGE("NVS", "nvs_get_blob FAILED: 0%x", (int)err);
        return err;
    }

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
        ESP_LOGE("NVS", "nvs_open FAILED: 0%x", (int)err);
        return err;
    }

    err = nvs_set_blob(nvs_handle, "config", conf, sizeof(config_t));
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "nvs_set_blob FAILED: 0%x", (int)err);
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