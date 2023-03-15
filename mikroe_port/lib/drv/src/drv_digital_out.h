/**
 ******************************************************************************
 * @file    drv_digital_out.h
 * @authors Erik Fasnacht
 * @version V1.0.0
 * @date    14-Mar-2023
 * @brief   Digital Out driver layer to interface with MikroE CLICK libraries
 ******************************************************************************
 **/

#ifndef _DRV_DIGITAL_OUT_H_
#define _DRV_DIGITAL_OUT_H_

#ifdef __cplusplus
    extern "C"{
#endif

#include <stdint.h>
#include "mikro_pins.h"

uint8_t digital_out_init(uint16_t pin, uint8_t mode);
void digital_out_high(uint16_t pin);
void digital_out_low(uint16_t pin);
void digital_out_toggle(uint16_t pin);
void digital_out_write(uint16_t pin, uint8_t value);


#ifdef __cplusplus
}
#endif

#endif // _DRV_DIGITAL_OUT_H_