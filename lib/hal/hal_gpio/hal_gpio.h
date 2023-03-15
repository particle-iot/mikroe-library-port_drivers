/**
 ******************************************************************************
 * @file    hal_gpio.c
 * @authors Erik Fasnacht
 * @version V1.0.0
 * @date    14-March-2023
 * @brief   hardware address layer for porting mikroE libraries
 ******************************************************************************
 **/

#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "gpio_hal.h"
//#include "spark_wiring_constants.h"
#define LOW 0
#define HIGH 1

/*
enum PinState {
    LOW = 0,
    HIGH = 1
};
*/

typedef struct hal_pin_info_t hal_gpio_pin_t;  //Forward declaration of the gpio pin typedef to dvos pinmap_hal.h
typedef struct hal_pin_info_t hal_gpio_port_t; //Forward declaration of the gpio port typedef to dvos pinmap_hal.h

//mikroe HAL functions
    void hal_gpio_configure_pin(uint8_t pin, uint8_t name, PinMode direction);                        //updated to dvos typedefs, Configure pin as digital input or output

    uint8_t hal_gpio_read_pin_input(hal_gpio_pin_t *pin);                                                       //Reads the current pin input level
    uint8_t hal_gpio_read_pin_output(hal_gpio_pin_t *pin);                                                      //Reads the current pin output level

    void hal_gpio_write_pin_output(uint8_t pin, uint8_t value);                                         //Sets the current output logic of the GPIO pin


    void hal_gpio_toggle_pin_output(hal_gpio_pin_t *pin);                                                       //Toggles the current output logic of the GPIO pin
    void hal_gpio_set_pin_output(hal_gpio_pin_t *pin);                                                          //Sets the current output logic of the GPIO pin to HIGH
    void hal_gpio_clear_pin_output(hal_gpio_pin_t *pin);                                                        //Sets the current output logic of the GPIO pin to LOW

    void hal_gpio_configure_port(hal_gpio_port_t *port, hal_pin_t name, uint8_t mask, PinMode direction);       //updated to dvos typedefs, Configures port as digital input or output
    hal_gpio_config_t hal_gpio_read_port_input(hal_gpio_port_t *port);                                          //updated to dvos typedefs, Reads the current input logic of the GPIO port
    hal_gpio_config_t hal_gpio_read_port_output(hal_gpio_port_t *port);                                         //updated to dvos typedefs, Reads the current output logic of the GPIO port
    void hal_gpio_write_port_output(hal_gpio_port_t *port, hal_gpio_config_t value);                            //updated to dvos typedefs, Sets the current output logic of the GPIO port to LOW



//mikroe HAL functions
/*
    void hal_gpio_configure_pin(hal_gpio_pin_t *pin, hal_pin_t name, PinMode direction);                        //updated to dvos typedefs, Configure pin as digital input or output

    uint8_t hal_gpio_read_pin_input(hal_gpio_pin_t *pin);                                                       //Reads the current pin input level
    uint8_t hal_gpio_read_pin_output(hal_gpio_pin_t *pin);                                                      //Reads the current pin output level

    void hal_gpio_write_pin_output(hal_gpio_pin_t *pin, uint8_t value);                                         //Sets the current output logic of the GPIO pin
    void hal_gpio_toggle_pin_output(hal_gpio_pin_t *pin);                                                       //Toggles the current output logic of the GPIO pin
    void hal_gpio_set_pin_output(hal_gpio_pin_t *pin);                                                          //Sets the current output logic of the GPIO pin to HIGH
    void hal_gpio_clear_pin_output(hal_gpio_pin_t *pin);                                                        //Sets the current output logic of the GPIO pin to LOW

    void hal_gpio_configure_port(hal_gpio_port_t *port, hal_pin_t name, uint8_t mask, PinMode direction);       //updated to dvos typedefs, Configures port as digital input or output
    hal_gpio_config_t hal_gpio_read_port_input(hal_gpio_port_t *port);                                          //updated to dvos typedefs, Reads the current input logic of the GPIO port
    hal_gpio_config_t hal_gpio_read_port_output(hal_gpio_port_t *port);                                         //updated to dvos typedefs, Reads the current output logic of the GPIO port
    void hal_gpio_write_port_output(hal_gpio_port_t *port, hal_gpio_config_t value);                            //updated to dvos typedefs, Sets the current output logic of the GPIO port to LOW    
*/

///////////////////////////////////////////////////////////////////////////////////////
//device-os
/*
//pulled from pinmap_hal.h
typedef struct hal_pin_info_t hal_pin_info_t;

typedef uint16_t hal_pin_t;
typedef hal_pin_t pin_t; // __attribute__((deprecated("Use hal_pin_t instead")));

//pulled from pinmap_impl.h
typedef struct hal_pin_info_t {
    uint8_t      gpio_port; // port0: 0; port: 1;
    uint8_t      gpio_pin;  // range: 0~31;
    PinMode      pin_mode;  // GPIO pin mode
    PinFunction  pin_func;
    uint8_t      adc_channel;
    uint8_t      pwm_instance;   // 4 instances on nRF52, range: 0~3
    uint8_t      pwm_channel;    // 4 channels in each instance, range: 0~3
    uint8_t      pwm_resolution; // default 8bit, max 15bit
    uint8_t      exti_channel;   // 16 channels
#if HAL_PLATFORM_IO_EXTENSION
    hal_pin_type_t type;
#endif // HAL_PLATFORM_IO_EXTENSION
    uint32_t     user_data;
} hal_pin_info_t;
*/



///////////////////////////////////////////////////////////////////////////////////////
//mikroe
/*
#include "hal_target.h"
#include "hal_ll_gpio.h"

typedef handle_t hal_gpio_base_t; //Handle type
typedef hal_ll_gpio_mask_t hal_gpio_mask_t; //Mask type

typedef struct hal_gpio_t
{
    hal_pin_info_t port;
    hal_pin_info_t gpio_pin;  
    //hal_gpio_base_t base; //Port base address
    //hal_gpio_mask_t mask; //Port bit mask
};

typedef struct hal_gpio_t hal_gpio_pin_t;  //Forward declaration of the gpio pin typedef
typedef struct hal_gpio_t hal_gpio_port_t; //Forward declaration of the gpio port typedef

//use PinMode from pinmap_hal.h
typedef enum
{
    HAL_GPIO_DIGITAL_INPUT = 0, //GPIO as digital input
    HAL_GPIO_DIGITAL_OUTPUT = 1 //GPIO as digital output
} hal_gpio_direction_t;

*/

#ifdef __cplusplus
}
#endif

#endif // _HAL_GPIO_H_
// ------------------------------------------------------------------------- END