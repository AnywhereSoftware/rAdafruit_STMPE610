#pragma once
#include "B4RDefines.h"
#include "Adafruit_STMPE610.h"
//~version: 1.00
//~event: Touch (X As Int, Y As Int)
namespace B4R {
	typedef void (*SubVoidIntInt)(Int X, Int Y) ;
	//~shortname: AdafruitSTMPE610
	class rAdafruitSTMPE610 {
		private:
			Adafruit_STMPE610* stm;
			uint8_t backend[sizeof(Adafruit_STMPE610)];
			SubVoidIntInt TouchSub;
			static void looper(void* b);
			bool sharedInit(SubVoidIntInt TouchSub, Byte i2caddr);
		public:
			//Initializes the object (SPI). Returns true if successful.
			//CSPin - Chip Select pin (8 by default).
			//TouchSub - Sub that will handle the Touch event.
			bool Initialize(Byte CSPin, SubVoidIntInt TouchSub);
			//Initialzies the object (I2C). Returns true if successful.
			//I2CAddress - 0x41 by default.
			//TouchSub - Sub that will handle the Touch event.
			bool InitializeI2C(Byte I2CAddress, SubVoidIntInt TouchSub);
			
	};
}