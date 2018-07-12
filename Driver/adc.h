#ifndef ADC_H
#define	ADC_H
#include "../Helper/dsp_helper.h"

typedef enum adc_channels_t{
    ADC_Battery
}adc_channels_t;

void adc_setup();



Q16_t adc_convert(adc_channels_t);
#define adc_battery() adc


#endif	/* ADC_H */

