#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

void I2cInit()
{
	// set up TWI Module
	TWBR = 2;
	TWSR |=((1<<TWPS1)|(1<<TWPS0));
	// enable the TWI Module
	TWCR|=(1<<TWEN);
}

void I2cClose()
{
	// disable the module
	TWCR&=(~(1<<TWEN));
}

void I2cStart()
{
	// put start condition on Bus
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	// wait to clear TWINT
	while(!(TWCR & (1<<TWINT)));
}

void I2cStop()
{
	// put stop condition on bus
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	// wait for stop to finish
	while(TWCR & (1<<TWSTO));
}

uint8_t I2cWriteByte(uint8_t data)
{	
	TWDR=data;	
	// initiate Transfer
	TWCR=(1<<TWEN)|(1<<TWINT);
	// wait to clear TWINT
	while(!(TWCR & (1<<TWINT)));
	// check Status
	if((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x28 || (TWSR & 0xF8) == 0x40)
	{
		// SLA+W transmitted and ACK received
		// or
		// SLA+R transmitted and ACK received
		// or
		// DATA transmitted and ACK recived
		return TRUE;
	}
	else
		return FALSE;	// error
}

uint8_t I2cReadByte(uint8_t *data,uint8_t ack)
{
	// set up ACK
	if(ack)
	{
		// return ACK after reception
		TWCR|=(1<<TWEA);
	}
	else
	{
		// return NACK after reception
		// Signals slave to stop giving more data
		// usually used for last byte read.
		TWCR&=(~(1<<TWEA));
	}

	// now enable reception of data by clearing TWINT
	TWCR|=(1<<TWINT);

	// wait to clear TWINT
	while(!(TWCR & (1<<TWINT)));

	// check status
	if((TWSR & 0xF8) == 0x58 || (TWSR & 0xF8) == 0x50)
	{
		// Data received and ACK returned
		// or
		// Data received and NACK returned
		// Read the data
		*data=TWDR;
		return TRUE;
	}
	else
	{
		return FALSE;	// error
	}
}



