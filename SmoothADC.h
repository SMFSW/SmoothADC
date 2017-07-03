//	SmoothADC.h - ADC filtering on ADC Pin of choice

#ifndef SmoothADC_h
#define SmoothADC_h

#include <inttypes.h>

//#define		DEBUG

#define		DEF_NB_ACQ		4U				//!< Number of acquisitions (specifies also size of tab)

typedef struct{
	uint16_t		ADCTab[DEF_NB_ACQ];		//!< Acquisition tab
	uint16_t		Average;				//!< Averaged value
	uint8_t			NumAcq;					//!< Index of acquisition (number of Acq valid on MSB)
} SmoothADCAcq_t;


typedef SmoothADCAcq_t ADCId;				//!< Alias name for Acquisition struct


// class containing the required methods for ADC averaging
class SmoothADC
{
private:
	// Private variables
	// consts
	uint16_t	ADCPin;					//!< ACD Pin used
	uint16_t	AcqPeriod;				//!< Acquisition Period
	// working vars
	ADCId		ADCChannel;				//!< Acquisition struct
	uint16_t	MemTimeAcq;				//!< Last Acquisition time
	bool		En;						//!< Module enabled/disable
	
	// Private methods
	bool TestAcqRate();
	void Filtering();

public:
	void init(uint16_t Pin, uint16_t Period);
	void serviceADCPin();
	void dbgInfo();			// needs SCI initialized in sketch setup
	
	uint16_t getADCVal();/* __attribute__((always_inline)) {
		return ADCChannel.Average;
	}*/
	
	void setPin(uint16_t Pin) __attribute__((always_inline)) {
		ADCPin = Pin;
	}
	
	void setPeriod(uint16_t Period) __attribute__((always_inline)) {
		AcqPeriod = Period;
	}
	
	uint16_t getPin() __attribute__((always_inline)) {
		return ADCPin;
	}
	
	uint16_t getPeriod() __attribute__((always_inline)) {
		return AcqPeriod;
	}
	
	void enable() __attribute__((always_inline)) {
		En = true;
		SmoothADC::init(ADCPin, AcqPeriod);		// Reinit with same Pin & Period
	}
	
	void disable() __attribute__((always_inline)) {
		En = false;
	}
	
	bool isEnabled() __attribute__((always_inline)) {
		return En;
	}
	
	bool isDisabled() __attribute__((always_inline)) {
		return (En == true ? false : true);
	}
};


/*==============================================================================
 * MACROS
 *============================================================================*/

/* public */


#endif /* SmoothADC_h */

