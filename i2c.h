#ifndef I2C_H
#define I2C_H

#define TRUE 1
#define FALSE 0

void I2cInit();
void I2cClose();

void I2cStart();
void I2cStop();

uint8_t I2cWriteByte(uint8_t data);
uint8_t I2cReadByte(uint8_t *data,uint8_t ack);	

#endif



