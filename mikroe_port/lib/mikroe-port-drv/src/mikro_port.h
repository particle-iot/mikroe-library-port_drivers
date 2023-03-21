/**
 ******************************************************************************
 * @file    mikro_pins.h
 * @authors Erik Fasnacht
 * @version V1.0.0
 * @date    16-Mar-2023
 * @brief   maps mikroBUS pins to Particle pinmap_defines.h values
 ******************************************************************************
 **/

#ifndef _MIKRO_PINS_H_
#define _MIKRO_PINS_H_

#include <stdint.h>
#include <stddef.h>
#include "pinmap_defines.h"
#include "Particle.h"

//used in libraries for pin selection
#define HAL_MODULE_ERROR (uint8_t)(0xFFFFFFFF)         //general module error
#define HAL_CHANNEL_ERROR (uint8_t)(0xFFFFFFFF)        //channel error, (timer, ADC, etc.)
#define HAL_PIN_NC (uint8_t)(0xFFFFFFFF)               //pin error, wrong pin selected
#define HAL_PORT_NC (uint8_t)(0xFFFFFFFF)              //port error, wrong port selected

//function for mikroE delays for libray port compability
inline void Delay_100ms( ) {delay(100);}
inline void Delay_ms(unsigned long ms) {delay(ms);}



//mikroBUS pin mapping first lookup
#define MIKROBUS_AN   AN_PIN
#define MIKROBUS_RST  RST_PIN
#define MIKROBUS_CS   CS_PIN
#define MIKROBUS_SCK  SCK_PIN
#define MIKROBUS_MISO MISO_PIN
#define MIKROBUS_MOSI MOSI_PIN
#define MIKROBUS_PWM  PWM_PIN
#define MIKROBUS_INT  INT_PIN
#define MIKROBUS_RX   RX_PIN
#define MIKROBUS_TX   TX_PIN
#define MIKROBUS_SCL  SCL_PIN
#define MIKROBUS_SDA  SDA_PIN

//mikroBUS pin mapping for actual pin lookup using BUS1
#define MIKROBUS_1          1
#define MIKROBUS_1_AN_PIN   A0
#define MIKROBUS_1_RST_PIN  A2
#define MIKROBUS_1_CS_PIN   SS
#define MIKROBUS_1_SCK_PIN  SCK
#define MIKROBUS_1_MISO_PIN MISO
#define MIKROBUS_1_MOSI_PIN MOSI
#define MIKROBUS_1_PWM_PIN  A5
#define MIKROBUS_1_INT_PIN  S4
#define MIKROBUS_1_RX_PIN   RX
#define MIKROBUS_1_TX_PIN   TX
#define MIKROBUS_1_SCL_PIN  SCL
#define MIKROBUS_1_SDA_PIN  SDA

//mikroBUS pin mapping for actual pin lookup using BUS2
#define MIKROBUS_2          2
#define MIKROBUS_2_AN_PIN   A1
#define MIKROBUS_2_RST_PIN  D7
#define MIKROBUS_2_CS_PIN   SS1
#define MIKROBUS_2_SCK_PIN  SCK
#define MIKROBUS_2_MISO_PIN MISO
#define MIKROBUS_2_MOSI_PIN MOSI
#define MIKROBUS_2_PWM_PIN  D10
#define MIKROBUS_2_INT_PIN  D6
#define MIKROBUS_2_RX_PIN   RX
#define MIKROBUS_2_TX_PIN   TX
#define MIKROBUS_2_SCL_PIN  SCL
#define MIKROBUS_2_SDA_PIN  SDA

//used to define which mikroBUS is used
#define MIKROBUS(index, pinout) MIKROBUS_IMPL(index, pinout)
#define MIKROBUS_IMPL(index, pinout) MIKROBUS_##index##_##pinout

//typedef for various parameters passed through libraries
typedef uint8_t pin_name_t;             //GPIO pin name
typedef uint8_t port_name_t;            //GPIO port name
typedef uint8_t port_size_t;            //GPIO port size
typedef uint16_t hal_base_addr_t;       //Base address, which is size dependant on the architecture
typedef uint16_t hal_channel_t;         //Channel type, which is size dependant on the architecture
typedef uint16_t hal_pin_name_t;        //Pin type, which is size dependant on the architecture
typedef uint16_t hal_port_name_t;       //Port type, which is size dependant on the architecture
typedef uint16_t hal_port_size_t;       //Port width, which is size dependant on the architecture
















#endif // _MIKRO_PINS_H_