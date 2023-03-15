/**
 ******************************************************************************
 * @file    drv_digital_in.h
 * @authors Erik Fasnacht
 * @version V1.0.0
 * @date    14-Mar-2023
 * @brief   Digital In driver layer to interface with MikroE CLICK libraries
 ******************************************************************************
 **/

#ifndef _DRV_DIGITAL_IN_H_
#define _DRV_DIGITAL_IN_H_

#ifdef __cplusplus
    extern "C"{
#endif

#include <stdint.h>
#include "mikro_pins.h"


uint8_t digital_in_init(uint16_t pin, uint8_t mode);
int32_t digital_in_read(uint16_t pin);


#ifdef __cplusplus
}
#endif

#endif // _DRV_DIGITAL_IN_H_