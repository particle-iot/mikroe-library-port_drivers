/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "pwmdriver.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR   0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pwmdriver_cfg_setup ( pwmdriver_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->pwm = HAL_PIN_NC;
    
    // Additional gpio pins

	cfg->dev_pwm_freq 	  = 5000;
}

PWMDRIVER_RETVAL pwmdriver_init ( pwmdriver_t *ctx, pwmdriver_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;
    
    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    return PWMDRIVER_OK;
}

void pwmdriver_set_duty_cycle ( pwmdriver_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void pwmdriver_pwm_stop ( pwmdriver_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void pwmdriver_pwm_start ( pwmdriver_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

// ------------------------------------------------------------------------- END

