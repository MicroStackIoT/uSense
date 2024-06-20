#ifndef _SENSOR_IF_H_
#define _SENSOR_IF_H_

#define I2C_MASTER_SCL_IO   4        
#define I2C_MASTER_SDA_IO   2       
#define MASTER_FREQUENCY    100000
#define PORT_NUMBER         -1
#define TIMEOUT             -1

void sensor_if_init(void);
void sensor_if_get_data(float *temp, float *humid, float *lux);

#endif