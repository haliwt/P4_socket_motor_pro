#include "bsp.h"
#include "adc.h"

#define SAMPLE_COUNT 6


// ADC相关变量定义
#define ADC_BUFFER_SIZE 1
volatile uint16_t adc_buffer[ADC_BUFFER_SIZE]; // DMA传输缓冲区
//volatile uint8_t adc_conversion_complete = 0;


/* USER CODE BEGIN 0 */


uint16_t motor_detect_voltage ;


static uint16_t compute_voltage(uint16_t raw_value) ;

static uint8_t ADC_DMA_StartConversion(void);
uint16_t mean_fan_buf[SAMPLE_COUNT];


/**********************************************************************
	*
	*Functin Name: void adc_detected_hundler(void)
	*Function :
	*Input Ref:  key of value
	*Return Ref: NO
	*
**********************************************************************/
uint16_t  pinch_adc_detected_value(void)
{
  static uint8_t adc_flag;
  if(ADC_DMA_StartConversion()==0) return 0;

   if(ADC_DMA_StartConversion()){
	  // ADC_GetValues();
	   adc_flag =1;	
   }
   if(adc_flag ==1){
	 adc_flag ++;  
     motor_detect_voltage =	(adc_buffer[0] * 3300 )/4095;

   }

   return motor_detect_voltage ;
}

/*****************************************************************
	*
	*Function Name: static uint8_t ADC_DMA_StartConversion(void)
	*Function : // 启动ADC DMA转换
	*Input Ref: which one ? AC_Channel_?, hexadecimal of average
	*Return Ref: No
	*
*****************************************************************/
static uint8_t ADC_DMA_StartConversion(void)
{
    if(LL_ADC_IsEnabled(ADC1) == 0) {
        return 0; // ADC未使能
    }
    
    if(LL_DMA_IsEnabledChannel(DMA1, LL_DMA_CHANNEL_1)) {
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
    }
    
    // 配置DMA传输
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1,
                          LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
                          (uint32_t)adc_buffer,
                          LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, ADC_BUFFER_SIZE);
    
    
    
    // 使能DMA通道
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
    
    // 启动ADC转换
    LL_ADC_REG_StartConversion(ADC1);
    
    return 1;
}



/*****************************************************************
	*
	*Function Name: 
	*Function ADC input channel be selected "which one channe"
	*Input Ref: which one ? AC_Channel_?, hexadecimal of average
	*Return Ref: No
	*
*****************************************************************/
static uint16_t compute_voltage(uint16_t raw_value) 
{
    uint64_t temp ;
	const uint32_t multiplier = 3462835200U;
   temp = (uint64_t)raw_value * multiplier;
    return (uint16_t)(temp >> 32);  // ��λ��mV
}


#if 0
/*****************************************************************
	*
	*Function Name: 
	*Function :ADC input channel be selected "which one channe"
	*Input Ref: which one ? AC_Channel_?, hexadecimal of average
	*Return Ref: No
	*
*****************************************************************/
static uint16_t ADC_MOTOR_ReadVoltage(void)
{
    uint16_t raw_value;
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_0);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_0, LL_ADC_SAMPLINGTIME_COMMON_1);

	LL_ADC_REG_StartConversion(ADC1);

	while(!LL_ADC_IsActiveFlag_EOC(ADC1));

	raw_value= LL_ADC_REG_ReadConversionData12(ADC1);
	
	LL_ADC_ClearFlag_EOC(ADC1);

	return compute_voltage(raw_value);

}
/*****************************************************************
	*
	*Function Name: static uint16_t ADC_PTC_ReadVoltage(void)
	*Function :
	*Input Ref:
	*Return Ref: No
	*
*****************************************************************/
static uint16_t ADC_PTC_ReadVoltage(void)
{
    uint16_t raw_value;
    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_1);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_1, LL_ADC_SAMPLINGTIME_COMMON_1);

	LL_ADC_REG_StartConversion(ADC1);

	while(!LL_ADC_IsActiveFlag_EOC(ADC1));

	raw_value= LL_ADC_REG_ReadConversionData12(ADC1);
	
	LL_ADC_ClearFlag_EOC(ADC1);

	return compute_voltage(raw_value);

}


#endif 






