#include "drv_digital_out.h"

//function for setting pin as output
int digital_out_init(uint16_t pin, PinMode mode)
{
    if (mode == OUTPUT)
    {
        hal_gpio_mode(pin, OUTPUT);
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

    
//function for setting pin HIGH
void digital_out_high(uint16_t pin)
{
    hal_gpio_write(pin, HIGH);
}

//function for setting pin LOW
void digital_out_low(uint16_t pin)
{
    hal_gpio_write(pin, LOW);
}

//function for toggling pin
void digital_out_toggle(uint16_t pin)
{
    uint8_t value = hal_gpio_read(pin);
    hal_gpio_write(pin, !value);
}

//function for writing pin state
void digital_out_write(uint16_t pin, uint8_t value)
{
    hal_gpio_write(pin, value);
}