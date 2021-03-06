//!
//! @file 			LongOptionsWithValuesTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-07-08
//! @last-modified 	2014-10-07
//! @brief 			Contains test functions for MClide command long options with no values.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
// none

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MClideApi.hpp"

using namespace MbeddedNinja::MClideNs;

namespace MClideTest
{

	static bool Callback(Cmd * cmd)
	{
		return true;
	}

	MTEST(OnePosLongOptionWithValueTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption('\0', "long1", NULL, "A test long option.", true);

		// Register option
		cmdTest.RegisterOption(&testOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test --long=optVal";

		// Run rx controller
		rxController.Run(rxBuff);

		CHECK_EQUAL(testOption.isDetected, true);
		CHECK_EQUAL(testOption.value, "optVal");
	}

	MTEST(TwoPosLongOptionWithValuesTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption1('\0', "long1", NULL, "Test option 1.", true);
		Option testOption2('\0', "long2", NULL, "Test option 2.", true);

		// Register options
		cmdTest.RegisterOption(&testOption1);
		cmdTest.RegisterOption(&testOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test --long1=optVal1 --long2=optVal2";
		
		// Run rx controller
		rxController.Run(rxBuff);
		
		CHECK_EQUAL(testOption1.isDetected, true);
		CHECK_EQUAL(testOption1.value, "optVal1");
		CHECK_EQUAL(testOption2.isDetected, true);
		CHECK_EQUAL(testOption2.value, "optVal2");
	}
			
	MTEST(OnePosOneNegOptionWithValuesTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption1('\0', "long1", NULL, "Test option 1.", true);
		Option testOption2('\0', "long2", NULL, "Test option 2.", true);

		// Register options
		cmdTest.RegisterOption(&testOption1);
		cmdTest.RegisterOption(&testOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create input buffer
		char rxBuff[50] = "test --long1=optVal1";

		// Run rx controller
		rxController.Run(rxBuff);
		
		CHECK_EQUAL(testOption1.isDetected, true);
		CHECK_EQUAL(testOption1.value, "optVal1");
		CHECK_EQUAL(testOption2.isDetected, false);
	}
		
} // namespace MClideTest
