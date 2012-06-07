#include "Wire.h"
#include <stdio.h>
#include <string.h>
#include <string>

void i2c_startbit(int sda, int scl);
void i2c_stopbit(int sda, int scl);
void i2c_begin_transmission(int sda, int scl, unsigned char address);
uint8_t i2c_request_from(int sda, int scl, unsigned char address, unsigned char* data, unsigned char counter);
uint8_t i2c_recv_byte(int sda, int scl, WIRE_ACK_STATE ack);
uint8_t i2c_read(int sda, int scl, uint8_t addr, uint8_t* data, uint8_t nbytes);
WIRE_ACK_STATE i2c_write(int sda, int scl, uint8_t addr, uint8_t* data, uint8_t nbytes);
WIRE_ACK_STATE i2c_send_byte(int sda, int scl, uint8_t data);
WIRE_ACK_STATE i2c_ping(int sda, int scl,uint8_t addr);

inline void WAIT(void);
inline int SCL_IN(int scl);
inline int SDA_IN(int sda);
inline void SDA_REL(int sda);
inline void SCL_REL(int scl);
inline void SDA_PUL(int sda);
inline void SCL_PUL(int scl);
inline void SCL_SDA_PUL(int scl,int sda);

uint8_t TwoWire::rxBuffer[BUFFER_LENGTH];
uint8_t TwoWire::rxBufferIndex = 0;
uint8_t TwoWire::rxBufferLength = 0;

uint8_t TwoWire::txAddress = 0;
uint8_t TwoWire::txBuffer[BUFFER_LENGTH];
uint8_t TwoWire::txBufferIndex = 0;
uint8_t TwoWire::txBufferLength = 0;

uint8_t TwoWire::transmitting = 0;
void (*TwoWire::user_onRequest)(void);
void (*TwoWire::user_onReceive)(int);

// Initialize Class Variables //////////////////////////////////////////////////
TwoWire::TwoWire()
{
//	rxAddress = 0;
//	rxBuffer[BUFFER_LENGTH];
//	rxBufferIndex = 0;
//	rxBufferLength = 0;
//
//	txAddress = 0;
//	txBuffer[BUFFER_LENGTH];
//	txBufferIndex = 0;
//	txBufferLength = 0;
//
//	transmitting = 0;
//	user_onRequest = NULL;
//	user_onReceive = NULL;
}


void TwoWire::begin(void)
{
	rxBufferIndex = 0;
	rxBufferLength = 0;

	txBufferIndex = 0;
	txBufferLength = 0;

	sda = 18;
	scl = 19;		//Arduino's default TWI pins(D18,D19)

	begin(sda, scl);
}

void TwoWire::begin(int sda,int scl)
{
	rxBufferIndex = 0;
	rxBufferLength = 0;

	txBufferIndex = 0;
	txBufferLength = 0;

	this->sda = sda;
	this->scl = scl;

	digitalWrite(sda,LOW);	// 出力に設定したらLowが出力されるようにしておく
	digitalWrite(scl,LOW);

	pinMode(sda,INPUT);		// 入力(Hi-Z)にしておく
	pinMode(sda,INPUT);

}

// Slave
void TwoWire::begin(uint8_t address)
{
//	twi_setAddress(address);
//	twi_attachSlaveTxEvent(onRequestService);
//	twi_attachSlaveRxEvent(onReceiveService);
	begin();
}

// Slave
void TwoWire::begin(int address)
{
	begin((uint8_t)address);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
	// clamp to buffer length
	if(quantity > BUFFER_LENGTH){
		quantity = BUFFER_LENGTH;
	}
	// perform blocking read into buffer
	uint8_t read = i2c_request_from(sda, scl, address, rxBuffer, quantity);

	// set rx buffer iterator vars
	rxBufferIndex = 0;
	rxBufferLength = read;

	return read;
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
	return requestFrom((uint8_t)address, (uint8_t)quantity);
}

void TwoWire::beginTransmission(uint8_t address)
{
	// indicate that we are transmitting
	transmitting = 1;
	// set address of targeted slave
	txAddress = address;
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;
}

void TwoWire::beginTransmission(int address)
{
	beginTransmission((uint8_t)address);
}

uint8_t TwoWire::endTransmission(void)
{
	WIRE_ACK_STATE st;

	// transmit buffer (blocking)
	i2c_startbit(sda, scl);
	st = i2c_write(sda, scl, txAddress, txBuffer, txBufferLength);

	unsigned char res = 0; //return value (0:OK, 1:BUFFER OV, 2:ADDRESS NAK, 3:DATA NAK, 4:Another error)
	i2c_stopbit(sda, scl);
	switch(st)
	{
		case ACK:		res = 0; break;
		case BUFF_OV:	res = 1; break;
		case ADDR_NAK:	res = 2; break;
		case DATA_NAK:	res = 3; break;
		case AND_MORE:	res = 4; break;
		default:		res = 4;
	}
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;
	// indicate that we are done transmitting
	transmitting = 0;
	return res;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
void TwoWire::write(int8_t data)
{
	if(transmitting){
	// in master transmitter mode
		// don't bother if buffer is full
		if(txBufferLength >= BUFFER_LENGTH){
			return;
		}
		// put byte in tx buffer
		txBuffer[txBufferIndex] = data;
		++txBufferIndex;
		// update amount in buffer
		txBufferLength = txBufferIndex;
	}else{
	// in slave send mode
		// reply to master
		//twi_transmit(&data, 1);
	}
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
void TwoWire::send(uint8_t* data, uint8_t quantity)
{
	if(transmitting){
		// in master transmitter mode
		//ここではデータをバッファに蓄積しているだけ
		for(uint8_t i = 0; i < quantity; ++i){
			write(data[i]);
		}


	}else{
	// in slave send mode
		// reply to master
		//twi_transmit(data, quantity);
	}
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
void TwoWire::send(int8_t* data)
{
	send((uint8_t *)data, strlen((const char*)data));
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
void TwoWire::send(int data)
{
	write((uint8_t)data);
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
uint8_t TwoWire::available(void)
{
	return rxBufferLength - rxBufferIndex;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
uint8_t TwoWire::receive(void)
{
	// default to returning null int8_t
	// for people using with int8_t strings
	uint8_t value = '\0';

	// get each successive byte on each call
	if(rxBufferIndex < rxBufferLength){
		value = rxBuffer[rxBufferIndex];
		++rxBufferIndex;
	}

	return value;
}

// behind the scenes function that is called when data is received
void TwoWire::onReceiveService(uint8_t* inBytes, int numBytes)
{
	// don't bother if user hasn't registered a callback
	if(!user_onReceive){
		return;
	}
	// don't bother if rx buffer is in use by a master requestFrom() op
	// i know this drops data, but it allows for slight stupidity
	// meaning, they may not have read all the master requestFrom() data yet
	if(rxBufferIndex < rxBufferLength){
		return;
	}
	// copy twi rx buffer into local read buffer
	// this enables new reads to happen in parallel
	for(uint8_t i = 0; i < numBytes; ++i){
		rxBuffer[i] = inBytes[i];
	}
	// set rx iterator vars
	rxBufferIndex = 0;
	rxBufferLength = numBytes;
	// alert user program
	user_onReceive(numBytes);
}

// behind the scenes function that is called when data is requested
void TwoWire::onRequestService(void)
{
	// don't bother if user hasn't registered a callback
	if(!user_onRequest){
		return;
	}
	// reset tx buffer iterator vars
	// !!! this will kill any pending pre-master sendTo() activity
	txBufferIndex = 0;
	txBufferLength = 0;
	// alert user program
	user_onRequest();
}

// sets function called on slave write
void TwoWire::onReceive( void (*function)(int) )
{
	user_onReceive = function;
}

// sets function called on slave read
void TwoWire::onRequest( void (*function)(void) )
{
	user_onRequest = function;
}

// Preinstantiate Objects

TwoWire Wire = TwoWire();

//-------------------------------------------------------------------------------
// Lowlevel
//-------------------------------------------------------------------------------

uint8_t i2c_request_from(int sda, int scl, unsigned char address, unsigned char* data, unsigned char counter)
{
	i2c_startbit(sda, scl);
	//i2c_ping(sda, scl, address);
	uint8_t result_bytes = i2c_read(sda, scl, address, data, counter); //counterは受信要求バイト数
	i2c_stopbit(sda, scl);
	return result_bytes; // 実際に受信できたバイト数
}

void i2c_begin_transmission(int sda, int scl, unsigned char address)
{
	//i2c_ping(sda, scl, address);
	i2c_startbit(sda, scl);
	//
}
WIRE_ACK_STATE i2c_write(int sda, int scl, uint8_t addr, uint8_t* data, uint8_t nbytes)
{
	uint8_t* data_end = data + nbytes;
	if(i2c_send_byte(sda, scl, (addr << 1) | 0x00) != ACK)
	{
		return ADDR_NAK;
	}
	while(data != data_end){
		if(i2c_send_byte(sda, scl, *data++) != ACK)
		{
			return DATA_NAK;
		}
	}
	return ACK;
}

//戻り値は読み込めたバイト数
uint8_t i2c_read(int sda, int scl, uint8_t addr, uint8_t* data, uint8_t nbytes)
{
	uint8_t counter = 0;
	uint8_t* data_end = data + nbytes;
	if(i2c_send_byte(sda, scl, (addr << 1) | 0x01) != 0)
	{
		return counter;
	}
	while(data != data_end){
		*data = i2c_recv_byte(sda, scl, (data != data_end - 1)?ACK:NAK);
		data++;
		counter++;
	}
	return counter;
}

void i2c_startbit(int sda, int scl)
{
	WAIT();
	if(!SCL_IN(scl) || !SDA_IN(sda))
	{
		if(SCL_IN(scl)){
			SCL_PUL(scl);
			WAIT();
		}
		if(!SDA_IN(sda)){
			SDA_REL(sda);
			WAIT();
		}
		SCL_REL(scl);
		WAIT();
	}

	SDA_PUL(sda);
	WAIT();
	SCL_PUL(scl);
	WAIT();
	/* SCL = SDA = L */
}

WIRE_ACK_STATE i2c_send_byte(int sda, int scl, uint8_t data)
{
	/* assume SCL = SDA = L */
	WIRE_ACK_STATE ack;
	volatile int i;
	for(i = 0; i < 8; i++)
	{
		if(data & 0x80)
			 SDA_REL(sda);
		else SDA_PUL(sda);
		WAIT();
		WAIT();
		SCL_REL(scl);
		WAIT();
		WAIT();
		if(i != 7)
			data <<= 1;
		SCL_PUL(scl);
	}
	WAIT();
	WAIT();
	SDA_REL(sda);
	SCL_REL(scl);
	WAIT();
	while(SCL_IN(scl) == 0);	/* スレーブによるクロックの引き延ばし */
	ack = (SDA_IN(sda)==0)? ACK:NAK;
	WAIT();
	WAIT();
	SCL_PUL(scl);
	/* SCL = SDA = L */
	return ack;
}

void i2c_stopbit(int sda, int scl)
{
	/* assume SCL = SDA = L */
	WAIT();
	SCL_REL(scl);
	WAIT();
	SDA_REL(sda);
	WAIT();
	/* SCL = SDA = H */
}

uint8_t i2c_recv_byte(int sda, int scl, WIRE_ACK_STATE ack)
{

	/* SCL = SDA = L */
	volatile uint8_t data;
	volatile int i;
	SDA_REL(sda);
	for(i = 0, data = 0; i < 8; i++){
		WAIT();
		WAIT();
		SCL_REL(scl);
		if(SDA_IN(sda))
			 data |= 0x01;
		else data &= ~0x01;
		WAIT();
		WAIT();
		if(i != 7)
			data <<= 1;
		SCL_PUL(scl);
	}
	if(ack)				/* ack送信 */
		 SDA_REL(sda);
	else
		SDA_PUL(sda);
	WAIT();
	WAIT();
	SCL_REL(scl);
	WAIT();
	WAIT();
	SCL_PUL(scl);
	SDA_PUL(sda);
	/* SCL = SDA = L */
	return data;
}



WIRE_ACK_STATE i2c_ping(int sda, int scl,uint8_t addr)
{
	WIRE_ACK_STATE ack;
	i2c_startbit(sda, scl);
	ack = i2c_send_byte(sda, scl, (addr << 1) | 0x00);
	i2c_stopbit(sda, scl);
	return ack;
}

//ピンの制御
//Sxx_PUL = Low
//Sxx_REL = Hi-Z
inline void WAIT(void)
{
	delay(1);
}

inline int SCL_IN(int scl)
{
	return digitalRead(scl);
}

inline int SDA_IN(int sda)
{
	return digitalRead(sda);
}

inline void SDA_REL(int sda)
{
	pinMode(sda, INPUT); //入力=Hi-Z
	//digitalWrite(sda, HIGH);
}

inline void SCL_REL(int scl)
{
	pinMode(scl, INPUT); //入力=Hi-Z
	//digitalWrite(scl,HIGH);
}

inline void SDA_PUL(int sda)
{
	pinMode(sda,INPUT);
	digitalWrite(sda,LOW);	// pullup disable
	pinMode(sda,OUTPUT);
	digitalWrite(sda, LOW);
}

inline void SCL_PUL(int scl)
{
	pinMode(scl,INPUT);
	digitalWrite(scl, LOW);
	pinMode(scl, OUTPUT); //出力=Low
	digitalWrite(scl, LOW);
}

inline void SCL_SDA_PUL(int scl,int sda)
{
	pinMode(sda,INPUT);
	digitalWrite(sda, LOW);
	pinMode(scl,INPUT);
	digitalWrite(scl, LOW);
	pinMode(scl, OUTPUT); //出力=Low
	pinMode(sda, OUTPUT); //出力=Low
}

