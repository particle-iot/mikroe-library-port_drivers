#ifndef DVOS_GPIO_H
#define DVOS_GPIO_H

#ifdef __cplusplus
extern "C"{
#endif

#include "spark_wiring.h"

#define HAL_PIN_NC (pin_name_t)(0xFFFFFFFF) /*!< @def Pin error. ( Wrong pin selected ) */

//enum for codes
typedef enum        
{
    SUCCESS = 0,    //success
    ERROR = (-1)    //error
} status_code_t;

//struct for pin
typedef struct               
{
    hal_pin_t pin       //from spark.h, structure defining pin
} digital_out_t;


//typedef uint8_t hal_gpio_pin_t;     //unsigned 8-bit int for gpio pin
typedef uint8_t pin_name_t;         //unsigned 8-bit int for pin name


err_t digital_out_init( digital_out_t *out, pin_name_t name );      //initialize GPIO pin as an output

void digital_out_high( digital_out_t *out );                        //set pin state logical HIGH
void digital_out_low( digital_out_t *out );                         //set pin state logical LOW
void digital_out_toggle( digital_out_t *out );                      //toggle pin state
void digital_out_write( digital_out_t *out, uint8_t value );        //set pin state


#ifdef __cplusplus
}
#endif

#endif // _DVOS_DIG-OUTPUT_H_
// ------------------------------------------------------------------------- END