#include "adc.h"
#include "../Setting/configuration.h"

/* configurationよりADC_USEが設定されている場合のみコードが生成されるようにする。
 */


#ifdef ADC_USE
void adc_setup(){
   
    
    
}
#else
void adc_setup(){}//中身がないコードを生成する。
#endif

#ifdef ADC_USE
Q16_t adc_convert(adc_channels_t ch){
    
    
    
    
    
}
#else
Q16_t adc_convert(adc_channels_t ch){return 0;}//中身がないコードを生成する。
#endif