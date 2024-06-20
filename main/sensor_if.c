#include "sensor_if.h"
#include <string.h>
#include "esp_log.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"

i2c_master_dev_handle_t dev_handle;

void sensor_if_init(void)
{
    i2c_master_bus_handle_t bus_handle;

    i2c_master_bus_config_t i2c_bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = PORT_NUMBER,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .glitch_ignore_cnt = 7,
    };

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = 0x44,
        .scl_speed_hz = MASTER_FREQUENCY,
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_config, &bus_handle));
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));
}

void sensor_if_get_data(float *at, float *rh, float *lx)
{
    int temp;
	float scratch;
    uint8_t cmd[1] = {0xFD};
    uint8_t data[6] = {0};

    i2c_master_transmit(dev_handle, cmd, 1, TIMEOUT);
    vTaskDelay(1);
    i2c_master_receive(dev_handle, data, 6, TIMEOUT);

    temp = (data[0] * 256 + data[1]);
	scratch = temp *175;
	scratch /= 0xffff;
	*at = (float)(-45 + scratch);

	temp = (data[3] * 256 + data[4]);
	scratch= temp * 100;
	scratch /= 0xffff;
	*rh = (float) scratch;

    *lx = *at + *rh;

}


