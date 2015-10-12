# SmoothADC
Arduino library for smooth ADC results

The SmoothADC library helps filtering ADC values when smoother evolution of values is needed (getting rid of pikes for example).
4 values, average on mid ones.

I tried to keep the lib as tiny as possible.
Sorry if somewhat messy, it's my first ino lib...

Feel free to share your thoughts @ xgarmanboziax@gmail.com about:
	- issues encountered
	- optimisations
	- improvements & new functionalities



Here is an example sketch:

This example defines A0 & A1 (analog inputs) to be handled by SmoothADC library
Samples every 50ms for A0
Samples every 100ms for A1
Every second, the average value from A0 & A1 are sent to serial port

#include <SmoothADC.h>

SmoothADC		ADC0;				// SmoothADC instance for Pin 0
SmoothADC		ADC1;				// SmoothADC instance for Pin 1
unsigned int	ADC0Value = 0;		// ADC0 final value
unsigned int	ADC1Value = 0;		// ADC1 final value

unsigned int	MemoTimeSerial;

void setup()
{
	Serial.begin(9600);

	ADC0.init(A0, 50);	// Init ADC0 attached to A0 with a 50ms acquisition period
	if (ADC0.isDisabled())	{ ADC0.enable(); }
	ADC1.init(A1, 100);	// Init ADC1 attached to A1 with a 100ms acquisition period
	if (ADC1.isDisabled())	{ ADC1.enable(); }
}

void loop()
{
	unsigned int tempTime = millis();
	
	(void) ADC0.serviceADCPin();
	(void) ADC1.serviceADCPin();
	
	if ((tempTime - MemoTimeSerial) > 1000)
	{
		MemoTimeSerial = tempTime;
		
		ADC0Value = ADC0.getADCVal();
		ADC0Value = ADC1.getADCVal();
		
		Serial.print("ADC Channel 0:\t");
		Serial.print(ADC0Value);
		Serial.print("\tADC Channel 1:\t");
		Serial.println(ADC1Value);
	}
}


Functional reference:

instName.init(Pin, Period);
	Description: Init the smoothADC instance instName on pin "Pin" with a sample rate of "Period" ms

instName.serviceADCPin
	Description: Method to service the ADC pin when module is enabled (should be placed somewhere in the main loop)

instName.getADCVal
	Description: Get the average ADC pin value (should replace usual analogRead)


instName.setPin
	Description: Set ADC pin to sevice

instName.setPeriod
	Description: Set sample rate of servicing (in ms)

instName.getPin
	Description: Get the serviced ADC pin

instName.getPeriod
	Description: Get the sample rate of the serviced pin

instName.enable
	Description: Enable ADC smoothing module

instName.disable
	Description: Disable ADC smoothing module

instName.isEnabled
	Description: Test if ADC smoothing is enabled

instName.isDisabled
	Description: Test if ADC smoothing is disabled



FAQ
N/A Yet