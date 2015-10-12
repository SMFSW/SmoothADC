/*
	SmoothADC.cpp - Get ADC to return averaged values
	Copyright (c) 2015-2015 SMFSW.
	
	Feel free to share your thoughts @ xgarmanboziax@gmail.com about:
		- issues encountered
		- optimisations
		- improvements & new functionalities

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
*/
 
/*
	12 October 2015		- First test release
*/

extern "C" {
#include <string.h> // for memcpy
}

#if ARDUINO > 22
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#ifdef DEBUG
#include <HardwareSerial.h>
#endif

#include "SmoothADC.h"


void SmoothADC::init(uint16_t Pin, uint16_t Period)
{
	pinMode(Pin, INPUT);
	ADCPin = Pin;
	AcqPeriod = Period;
	ADCChannel.NumAcq = 0;
}


bool SmoothADC::TestAcqRate()
{
	uint16_t	tempTime = millis();
	
	if ((tempTime - MemTimeAcq) >= AcqPeriod)
	{
		MemTimeAcq = tempTime;
		return true;
	}
	
	return false;
}


void SmoothADC::Filtering()
{
	uint16_t	temp[DEF_NB_ACQ], swap;
	uint8_t		c;
	
	memcpy(temp, ADCChannel.ADCTab, sizeof(temp));	// Tab copy before average calc
	
	// Retrieve max value on 0 idx tab
	for (c = 1 ; c < DEF_NB_ACQ ; c++)
	{
		if (temp[0] < temp[c])
		{
			swap = temp[0];
			temp[0] = temp[c];
			temp[c] = swap;
		}
	}
	
	// Retrieve min value on 3 idx tab
	for (c = 1 ; c < (DEF_NB_ACQ-1) ; c++)
	{
		if (temp[DEF_NB_ACQ-1] > temp[c])
		{
			swap = temp[DEF_NB_ACQ-1];
			temp[DEF_NB_ACQ-1] = temp[c];
			temp[c] = swap;
		}
	}
	
	// Average calc
	ADCChannel.Average = ((temp[1] + temp[2]) / 2);
}

#define		DEF_BIT_ACQ		0x80U						//!< Bit used to specify all acquisitions ok (MSB)
#define		DEF_MSQ_NumAcq	(uint8_t) (~DEF_BIT_ACQ)	//!< Other bits in NumAcq (7 LSBs)

void SmoothADC::serviceADCPin()
{
	if (En == true)
	{
		if (TestAcqRate() == true)
		{
			ADCChannel.ADCTab[ADCChannel.NumAcq & DEF_MSQ_NumAcq] = analogRead(ADCPin);
			
			if (((++ADCChannel.NumAcq) & DEF_MSQ_NumAcq) >= DEF_NB_ACQ)	{ ADCChannel.NumAcq = DEF_BIT_ACQ; }
		}
	}
}

uint16_t SmoothADC::getADCVal()
{
	if (ADCChannel.NumAcq & DEF_BIT_ACQ)	{ Filtering(); }
	
	return ADCChannel.Average;
}

void SmoothADC::dbgInfo()			// needs SCI initialized in sketch setup
{
	#ifdef DEBUG
	String		dbgInfo = "";
	uint8_t		c;
	
	dbgInfo += "!> ";
	dbgInfo += "Pin A";
	dbgInfo += (getPin() - A0);
	dbgInfo += ",\tRate: ";
	dbgInfo += getPeriod();
	dbgInfo += "ms";
	Serial.println(dbgInfo);
	dbgInfo.remove(0);
	dbgInfo += "!> ";
	dbgInfo += "Tab :\t";
	for (c = 0 ; c < DEF_NB_ACQ ; c++)
	{
		dbgInfo += ADCChannel.ADCTab[c];
		dbgInfo += "\t";
	}
	Serial.println(dbgInfo);
	#endif
}