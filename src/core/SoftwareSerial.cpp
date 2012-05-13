/*
 * This class is porting arduino's SoftwareSerial for eXodusino
 *
 * Created on: 2012/03/17
 * @author nucho
 */

/*
 SoftwareSerial.cpp (formerly NewSoftSerial.cpp) -
 Multi-instance software serial library for Arduino/Wiring
 -- Interrupt-driven receive and other improvements by ladyada
 (http://ladyada.net)
 -- Tuning, circular buffer, derivation from class Print/Stream,
 multi-instance support, porting to 8MHz processors,
 various optimizations, PROGMEM delay tables, inverse logic and
 direct port writing by Mikal Hart (http://www.arduiniana.org)
 -- Pin change interrupt macros by Paul Stoffregen (http://www.pjrc.com)
 -- 20MHz processor support by Garrett Mace (http://www.macetech.com)
 -- ATmega1280/2560 support by Brett Hagman (http://www.roguerobotics.com/)

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 The latest version of this library can always be found at
 http://arduiniana.org.
 */

#include "SoftwareSerial.h"
#include "gpio.h"
#include "delay.h"
//
// Lookup table
//
typedef struct _DELAY_TABLE {
	long baud;
	unsigned short rx_delay_centering;
	unsigned short rx_delay_intrabit;
	unsigned short rx_delay_stopbit;
	unsigned short tx_delay;
} DELAY_TABLE;

static const DELAY_TABLE table[] = {
//  baud    rxcenter   rxintra    rxstop    tx
		{ 38400, 11, 23, 23, 23, },//no support
		{ 19200, 23, 47, 47, 49, },//no support
		{ 9600, 50,100, 100, 100, },
		{ 4800, 101, 202, 202, 202, },
};


//
// Debugging
//
// This function generates a brief pulse
// for debugging or measuring on an oscilloscope.
inline void DebugPulse(uint8_t pin, uint8_t count) {
	//#if _DEBUG
	//		volatile uint8_t *pport = portOutputRegister(digitalPinToPort(pin));
	//
	//		uint8_t val = *pport;
	//		while (count--)
	//		{
	//			*pport = val | digitalPinToBitMask(pin);
	//			*pport = val;
	//		}
	//#endif
}

//
// Statics
//
SoftwareSerial *SoftwareSerial::active_object = 0;
char SoftwareSerial::_receive_buffer[_SS_MAX_RX_BUFF];
volatile uint8_t SoftwareSerial::_receive_buffer_tail = 0;
volatile uint8_t SoftwareSerial::_receive_buffer_head = 0;

//
// Private methods
//

// This function sets the current object as the "listening"
// one and returns true if it replaces another
bool SoftwareSerial::listen() {
	if (active_object != this) {
		_buffer_overflow = false;

		_receive_buffer_head = _receive_buffer_tail = 0;
		active_object = this;
		return true;
	}

	return false;
}

//
// The receive routine called by the interrupt handler
//
void SoftwareSerial::recv() {
	uint8_t d = 0;

	// If RX line is high, then we don't see any start bit
	// so interrupt is probably not for us
	if (_inverse_logic ? digitalRead(_receivePin) : !digitalRead(_receivePin)) {
		// Wait approximately 1/2 of a bit width to "center" the sample
		delayMicroseconds(_rx_delay_centering);

		DebugPulse(4, 1);

		// Read each of the 8 bits
		for (uint8_t i = 0x1; i; i <<= 1) {
			delayMicroseconds(_rx_delay_intrabit);
			DebugPulse(4, 1);
			uint8_t noti = ~i;
			if (digitalRead(_receivePin))
				d |= i;
			else
				// else clause added to ensure function timing is ~balanced
				d &= noti;
		}

		// skip the stop bit
		delayMicroseconds(_rx_delay_stopbit);
		DebugPulse(4, 1);

		if (_inverse_logic)
			d = ~d;

		// if buffer full, set the overflow flag and return
		if ((_receive_buffer_tail + 1) % _SS_MAX_RX_BUFF
				!= _receive_buffer_head) {
			// save new data in buffer: tail points to where byte goes
			_receive_buffer[_receive_buffer_tail] = d; // save new byte
			_receive_buffer_tail = (_receive_buffer_tail + 1) % _SS_MAX_RX_BUFF;
		} else {
			_buffer_overflow = true;
		}
	}
}
// Interrupt handling
//

/* static */
inline void SoftwareSerial::handle_interrupt() {
	if (active_object) {
		active_object->recv();
	}
}

//
// Constructor
//
SoftwareSerial::SoftwareSerial(uint8_t receivePin, uint8_t transmitPin,
		bool inverse_logic /* = false */) :
	_rx_delay_centering(0), _rx_delay_intrabit(0), _rx_delay_stopbit(0),
			_tx_delay(0), _buffer_overflow(false),
			_inverse_logic(inverse_logic) {
	setTX(transmitPin);
	setRX(receivePin);
}

//
// Destructor
//
SoftwareSerial::~SoftwareSerial() {
	end();
}

void SoftwareSerial::setTX(uint8_t tx) {
	if (tx >= 0) {
		pinMode(tx, OUTPUT);
		digitalWrite(tx, HIGH);
	}
	_transmitPin = tx;
}

void SoftwareSerial::setRX(uint8_t rx) {
	if (rx >= 0) {
		pinMode(rx, INPUT);
		if (!_inverse_logic) {
			digitalWrite(rx, HIGH);//rx pin is pull up
		} else {
			digitalWrite(rx, LOW);//rx pin is inactive
		}
	}
	_receivePin = rx;
}

//
// Public methods
//

void SoftwareSerial::begin(long speed) {
	_rx_delay_centering = _rx_delay_intrabit = _rx_delay_stopbit = _tx_delay
			= 0;

	for (unsigned i = 0; i < sizeof(table) / sizeof(table[0]); ++i) {
		long baud = table[i].baud;
		if (baud == speed) {
			_rx_delay_centering = table[i].rx_delay_centering;
			_rx_delay_intrabit = table[i].rx_delay_intrabit;
			_rx_delay_stopbit = table[i].rx_delay_stopbit;
			_tx_delay = table[i].tx_delay;
			break;
		}
	}
	// Set up RX interrupts, but only if we have a valid RX baud rate
	if (_rx_delay_stopbit && _receivePin > 0) {
		attachInterrupt(_receivePin, SoftwareSerial::handle_interrupt, FALLING);
		delayMicroseconds(_tx_delay);// if we were low this establishes the end
	}

	listen();
}

void SoftwareSerial::end() {
	if (_receivePin > 0) {
		detachInterrupt(_receivePin);
	}
}

// Read data from buffer
int SoftwareSerial::read() {
	if (!isListening())
		return -1;

	// Empty buffer?
	if (_receive_buffer_head == _receive_buffer_tail)
		return -1;

	// Read from "head"
	uint8_t d = _receive_buffer[_receive_buffer_head]; // grab next byte
	_receive_buffer_head = (_receive_buffer_head + 1) % _SS_MAX_RX_BUFF;
	return d;
}

int SoftwareSerial::available() {
	if (!isListening())
		return 0;

	return (_receive_buffer_tail + _SS_MAX_RX_BUFF - _receive_buffer_head)
			% _SS_MAX_RX_BUFF;
}

void SoftwareSerial::write(const char c) {
	if (_tx_delay == 0) {
		return;
	}
	if (_transmitPin < 0) {
		return;
	}

	// Write the start bit
	digitalWrite(_transmitPin, _inverse_logic ? HIGH : LOW);
	delayMicroseconds(_tx_delay);

	// Write each of the 8 bits
	if (_inverse_logic) {
		for (uint8_t mask = 0x01; mask; mask <<= 1) {
			if (c & mask) // choose bit
				digitalWrite(_transmitPin, LOW); // send 1
			else
				digitalWrite(_transmitPin, HIGH); // send 0

			delayMicroseconds(_tx_delay);
		}

		digitalWrite(_transmitPin, LOW); // restore pin to natural state
	} else {
		for (uint8_t mask = 0x01; mask; mask <<= 1) {
			if (c & mask) // choose bit
				digitalWrite(_transmitPin, HIGH); // send 1
			else
				digitalWrite(_transmitPin, LOW); // send 0

			delayMicroseconds(_tx_delay);
		}

		digitalWrite(_transmitPin, HIGH); // restore pin to natural state
	}

	delayMicroseconds(_tx_delay);
}

void SoftwareSerial::flush() {
	if (!isListening())
		return;

	_receive_buffer_head = _receive_buffer_tail = 0;
}

int SoftwareSerial::peek() {
	if (!isListening())
		return -1;

	// Empty buffer?
	if (_receive_buffer_head == _receive_buffer_tail)
		return -1;

	// Read from "head"
	return _receive_buffer[_receive_buffer_head];
}
