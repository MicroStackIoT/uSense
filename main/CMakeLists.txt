idf_component_register(SRCS "led.c" "main.c" "nvs.c" "sensor_if.c" "wifi_sta.c" "sht40x/sensirion_common.c" "sht40x/sensirion_i2c_hal.c" "sht40x/sensirion_i2c.c" "sht40x/sht4x_i2c.c" 
                    INCLUDE_DIRS "." "sht40x")
