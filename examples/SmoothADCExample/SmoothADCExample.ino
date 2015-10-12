/*
 * SmoothADCExample.ino
 *
 * This example defines A0 & A1 (analog inputs) to be handled by SmoothADC library
 *
 *
 * Samples every 50ms for A0
 * Samples every 100ms for A1
 *
 * Every second, the average value from A0 & A1 are sent to serial port
 */

#include <SmoothADC.h>

SmoothADC		ADC0;				// SmoothADC instance for Pin 0
SmoothADC		ADC1;				// SmoothADC instance for Pin 1
unsigned int	ADC0Value = 0;		// ADC0 final value
unsigned int	ADC1Value = 0;		// ADC1 final value

unsigned int	MemTimeSerial;

void setup()
{
	Serial.begin(9600);

	ADC0.init(A0, 50);	// Init ADC0 attached to A0 with a 50ms acquisition period
	if (ADC0.isDisabled())	{ ADC0.enable(); }
	ADC1.init(A1, 20);	// Init ADC1 attached to A1 with a 20ms acquisition period
	if (ADC1.isDisabled())	{ ADC1.enable(); }
}

void loop()
{
	unsigned int	tempTime = millis();
	String			toSerial = "";
	
	ADC0.serviceADCPin();
	ADC1.serviceADCPin();
	
	if ((tempTime - MemTimeSerial) > 1000)
	{
		MemTimeSerial = tempTime;
		
		#ifdef DEBUG
		ADC0.dbgInfo();
		ADC1.dbgInfo();
		#endif
		
		ADC0Value = ADC0.getADCVal();
		ADC1Value = ADC1.getADCVal();
		
		toSerial += "ADC Channel 0:\t";
		toSerial += ADC0Value;
		toSerial += "\tADC Channel 1:\t";
		toSerial += ADC1Value;
		Serial.println(toSerial);
	}
}

