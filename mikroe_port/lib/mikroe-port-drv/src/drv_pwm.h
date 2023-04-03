/**
 ******************************************************************************
 * @file    drv_pwm.h
 * @authors Erik Fasnacht
 * @version V1.0.0
 * @date    28-Mar-2023
 * @brief   PWM driver layer to interface with MikroE CLICK libraries
 ******************************************************************************
 **/

#ifndef _DRV_PWM_H_
#define _DRV_PWM_H_

#include "mikro_port.h"

//enum for status codes, added for library compatibility
typedef enum
{
    PWM_SUCCESS = 0,        //Success
    PWM_ERROR = (-1)        //Error
} pwm_err_t;

//struct for various PWM function parameters
typedef struct
{
    pin_name_t pin;         //PWM pin
    uint32_t freq_hz;       //PWM Frequency in Hz
} pwm_config_t;

//struc for PWM configuration
typedef struct
{
    pwm_config_t config;        //PWM driver configuration structure
} pwm_t;

//PWM functions
void pwm_configure_default(pwm_config_t *config);
int8_t pwm_open(pwm_t *obj, pwm_config_t *config);
int8_t pwm_set_freq(pwm_t *obj, uint32_t freq_hz);
int8_t pwm_start(pwm_t *obj);
int8_t pwm_set_duty(pwm_t *obj, float duty_ratio);
int8_t pwm_stop(pwm_t *obj);
void pwm_close(pwm_t *obj);


#endif // _DRV_PWM_H_