/**
 ******************************************************************************
 * @file    mikro_pins.h
 * @authors Erik Fasnacht
 * @version V1.0.0
 * @date    14-Mar-2023
 * @brief   maps mikroBUS pins to Particle pinmap_defines.h values
 ******************************************************************************
 **/

#ifndef _MIKRO_PINS_H_
#define _MIKRO_PINS_H_

#ifdef __cplusplus
    extern "C"{
#endif

#include <stdint.h>
#include "pinmap_defines.h"

//used in libraries for pin selection
#define HAL_MODULE_ERROR (hal_base_addr_t)(0xFFFFFFFF) /*!< @def General module error. */
#define HAL_CHANNEL_ERROR (hal_channel_t)(0xFFFFFFFF) /*!< @def Channel error. ( Timer, ADC... ) */
#define HAL_PIN_NC (hal_pin_name_t)(0xFFFFFFFF) /*!< @def Pin error. ( Wrong pin selected ) */
#define HAL_PORT_NC (hal_port_name_t)(0xFFFFFFFF) /*!< @def Port error. ( Wrong port selected ) */

//used to define which mikroBUS is used
//typedef uint8_t bus_selected;

typedef struct {
    uint8_t bus_selected;
}mikro_bus;




#define MIKROBUS(bus_selected, pinout) MIKROBUS_IMPL(s\bus_selected pinout)
#define MIKROBUS_IMPL(bus_selected, pinout) MIKROBUS_##bus_selected##_##pinout

//original from mikro source code
//#define MIKROBUS(index, pinout) MIKROBUS_IMPL(index, pinout)
//#define MIKROBUS_IMPL(index, pinout) MIKROBUS_##index##_##pinout


//mikroBUS pin mapping
#define MIKROBUS_AN   A0
#define MIKROBUS_RST  A2
#define MIKROBUS_CS   SS
#define MIKROBUS_SCK  SCK
#define MIKROBUS_MISO MISO
#define MIKROBUS_MOSI MOSI
#define MIKROBUS_PWM  A5
#define MIKROBUS_INT  S4
#define MIKROBUS_RX   RX
#define MIKROBUS_TX   TX
#define MIKROBUS_SCL  SCL
#define MIKROBUS_SDA  SDA

#define MIKROBUS_1      1
#define MIKROBUS_1_AN   A0
#define MIKROBUS_1_RST  A2
#define MIKROBUS_1_CS   SS
#define MIKROBUS_1_SCK  SCK
#define MIKROBUS_1_MISO MISO
#define MIKROBUS_1_MOSI MOSI
#define MIKROBUS_1_PWM  A5
#define MIKROBUS_1_INT  S4
#define MIKROBUS_1_RX   RX
#define MIKROBUS_1_TX   TX
#define MIKROBUS_1_SCL  SCL
#define MIKROBUS_1_SDA  SDA

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   A1
#define MIKROBUS_2_RST  D7
#define MIKROBUS_2_CS   SS1
#define MIKROBUS_2_SCK  SCK
#define MIKROBUS_2_MISO MISO
#define MIKROBUS_2_MOSI MOSI
#define MIKROBUS_2_PWM  D10
#define MIKROBUS_2_INT  D6
#define MIKROBUS_2_RX   RX
#define MIKROBUS_2_TX   TX
#define MIKROBUS_2_SCL  SCL
#define MIKROBUS_2_SDA  SDA

#ifdef __cplusplus
}
#endif

#endif // _MIKRO_PINS_H_