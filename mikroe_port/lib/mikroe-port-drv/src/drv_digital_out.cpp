#include "drv_digital_out.h"

//function for setting pin as output
int8_t digital_out_init(digital_out_t *out, uint8_t mode)
{
    //original from MikroE
    /*
    if ( HAL_PIN_NC == name )
    {
        return DIGITAL_OUT_UNSUPPORTED_PIN;
    }

    hal_gpio_configure_pin( &out->pin, name, GPIO_DIGITAL_OUTPUT );
    return DIGITAL_OUT_SUCCESS;
    */
    

    if (mode == OUTPUT)
    {
        pinMode(out->pin, static_cast<PinMode>(mode));
        return DIGITAL_OUT_SUCCESS;     //return status
    }
    else
    {
        return DIGITAL_OUT_UNSUPPORTED_PIN;       //return status
    }
}

//function for setting pin HIGH
void digital_out_high(digital_out_t *out)
{
   //original from MikroE
    /*
    if ( NULL != out->pin.base )
    {
        hal_gpio_set_pin_output( &out->pin );
    }
    */

    
    digitalWrite(out->pin, HIGH);
}

//function for setting pin LOW
void digital_out_low(digital_out_t *out)
{
    //original from MikroE
    /*
    if ( NULL != out->pin.base )
    {
        hal_gpio_clear_pin_output( &out->pin );
    }
    */

    
    digitalWrite(out->pin, LOW);
}

//function for toggling pin
void digital_out_toggle(digital_out_t *out)
{
    //original from MikroE
    /*
    if ( NULL != out->pin.base )
    {
        hal_gpio_toggle_pin_output( &out->pin );
    }
    */

    
    int32_t value = digitalRead(out->pin);
    digitalWrite(out->pin, !value);
}

//function for writing pin state
void digital_out_write(digital_out_t *out, uint8_t value)
{
    //original from MikroE
    /*
    if ( NULL != out->pin.base )
    {
        hal_gpio_write_pin_output( &out->pin, value );
    }
    */

    
    digitalWrite(out->pin, value);
}