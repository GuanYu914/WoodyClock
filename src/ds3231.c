#include <avr/io.h>
#include "i2c.h"
#include "ds3231.h"

uint8_t DS3231Read(uint8_t address,uint8_t *data)
{
	// i2c function result
	uint8_t res;
	// start
	I2cStart();
	// SLA+W (for dummy write to set register pointer)
	res=I2cWriteByte(0b11010000);	//DS3231 address + W
	//	error
	if(!res){return FALSE;}
	// now send the address of required register
	res=I2cWriteByte(address);
	// error
	if(!res){return FALSE;}
	// repeat start
	I2cStart();
	// SLA + R
	res=I2cWriteByte(0b11010001);	//DS3231 Address + R
	// error
	if(!res){return FALSE;}
	// now read the value with NACK
	res=I2cReadByte(data, 0);
	// error
	if(!res){return FALSE;}
	// stop
	I2cStop();
	return TRUE;
}

uint8_t DS3231Write(uint8_t address,uint8_t data)
{
	// i2c fuction result
	uint8_t res;
	// start
	I2cStart();
	// SLA+W
	res=I2cWriteByte(0b11010000);	//DS3231 address + W
	// error
	if(!res){return FALSE;}
	// now send the address of required register
	res=I2cWriteByte(address);
	// error
	if(!res){return FALSE;}
	// now write the value
	res=I2cWriteByte(data);
	// error
	if(!res){return FALSE;}
	// stop
	I2cStop();
	return TRUE;
}
	
	

