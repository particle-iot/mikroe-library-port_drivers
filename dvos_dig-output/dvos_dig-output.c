#include "dvos_dig-output.h"
/*
err_t digital_out_init( digital_out_t *out, pin_name_t name )
{
    if ( HAL_PIN_NC == name )
    {
        return ERROR;
    }

    //hal_gpio_configure_pin( &out->pin, name, GPIO_DIGITAL_OUTPUT );
    pinMode(&out->pin, OUTPUT);
    return SUCCESS;
}
*/

err_t digital_out_init( digital_out_t *out, pin_name_t name )
{
    if (pinAvailable(name))
    {
            pinMode(&out->pin, OUTPUT);

    return SUCCESS;
    }
    if (hal_pin_type_t HAL_PIN_TYPE_UNKNOWN == name )
    {
        return ERROR;
    }

    //hal_gpio_configure_pin( &out->pin, name, GPIO_DIGITAL_OUTPUT );
    pinMode(&out->pin, OUTPUT);

    return SUCCESS;
}

/*
void digital_out_high( digital_out_t *out )
{
    if ( NULL != out->pin.base )
    {
        hal_gpio_set_pin_output( &out->pin );
    }
}

void digital_out_low( digital_out_t *out )
{
    if ( NULL != out->pin.base )
    {
        hal_gpio_clear_pin_output( &out->pin );
    }
}

void digital_out_toggle( digital_out_t *out )
{
    if ( NULL != out->pin.base )
    {
        hal_gpio_toggle_pin_output( &out->pin );
    }
}

void digital_out_write( digital_out_t *out, uint8_t value )
{
    if ( NULL != out->pin.base )
    {
        hal_gpio_write_pin_output( &out->pin, value );
    }
}
*/