#ifndef __BSP_USB_METER_H
#define __BSP_USB_METER_H
#include "main.h"


#define USB_POWER_ENABLE()        LL_GPIO_ResetOutputPin(USB_EN_GPIO_Port,USB_EN_Pin)
#define USB_POWER_DISABLE()       LL_GPIO_SetOutputPin(USB_EN_GPIO_Port,USB_EN_Pin)

#define USB_OVERLOAD_WANING()     LL_GPIO_IsInputPinSet(USB_OVERLOAD_GPIO_Port,USB_OVERLOAD_Pin)

#endif 

