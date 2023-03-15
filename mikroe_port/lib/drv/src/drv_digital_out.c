#include "drv_digital_out.h"

//function for setting pin as output
uint8_t digital_out_init(uint16_t pin, uint8_t mode)
{
    if (mode == 1)
    {
        pinMode(pin, mode);
    }
    return 0;
}

//function for setting pin HIGH
void digital_out_high(uint16_t pin)
{
    digitalWrite(pin, 1);
}

//function for setting pin LOW
void digital_out_low(uint16_t pin)
{
    digitalWrite(pin, 0);
}

//function for toggling pin
void digital_out_toggle(uint16_t pin)
{
    int32_t value = digitalRead(pin);
    digitalWrite(pin, !value);
}

//function for writing pin state
void digital_out_write(uint16_t pin, uint8_t value)
{
    digitalWrite(pin, value);
}