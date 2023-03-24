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

#include "mikro_port.h"

//enum for status codes, added for library compatibility
typedef enum
{
    DIGITAL_IN_SUCCESS = 0,                 //Success
    DIGITAL_IN_UNSUPPORTED_PIN = (-1)       //Error
} digital_in_err_t;

//struc for the various mikroBUS pins, added for library port compatibility
typedef struct
{
    uint8_t pin;     //structure defining pin base and mask
} digital_in_t;

//digital out functions
int8_t digital_in_init(digital_in_t *in, uint8_t mode);
int32_t digital_in_read(digital_in_t *in);

#endif // _DRV_DIGITAL_IN_H_