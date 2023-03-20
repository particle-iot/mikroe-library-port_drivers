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

#include "mikro_pins.h"

//struc for the various mikroBUS pins, added for library port compatibility
typedef struct
{
    uint16_t pin;    //Structure defining pin base and mask
} digital_out_t;

//digital out functions
int8_t digital_out_init(digital_out_t *out, uint8_t mode);
void digital_out_high(digital_out_t *out);
void digital_out_low(digital_out_t *out);
void digital_out_toggle(digital_out_t *out);
void digital_out_write(digital_out_t *out, uint8_t value);

#endif // _DRV_DIGITAL_OUT_H_