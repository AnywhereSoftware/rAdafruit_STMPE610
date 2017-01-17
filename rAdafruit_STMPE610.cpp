
#include "B4RDefines.h"
namespace B4R {
	bool rAdafruitSTMPE610::Initialize(Byte CSPin, SubVoidIntInt TouchSub) {
		stm = new (backend) Adafruit_STMPE610(CSPin);
		return sharedInit(TouchSub, 0x41);
	}
	bool rAdafruitSTMPE610::InitializeI2C(Byte I2CAddress, SubVoidIntInt TouchSub) {
		stm = new (backend) Adafruit_STMPE610();
		return sharedInit(TouchSub, I2CAddress);
	}
	
	bool rAdafruitSTMPE610::sharedInit(SubVoidIntInt TouchSub, Byte i2caddr) {
		this->TouchSub = TouchSub;
		bool b = stm->begin(i2caddr);
		if (b) {
			FunctionUnion fu;
			fu.PollerFunction = looper;
			pollers.add(fu, this);
		}
		return b;
	}
	
	void rAdafruitSTMPE610::looper(void* b) {
		rAdafruitSTMPE610* me = (rAdafruitSTMPE610*)b;
		Adafruit_STMPE610* touch = me->stm;
		uint16_t x, y;
		uint8_t z;
		if (touch->touched()) {
			while (! touch->bufferEmpty()) {
				touch->readData(&x, &y, &z);
				me->TouchSub(x, y);
			}
			touch->writeRegister8(STMPE_INT_STA, 0xFF); // reset all ints
		}
	}
}