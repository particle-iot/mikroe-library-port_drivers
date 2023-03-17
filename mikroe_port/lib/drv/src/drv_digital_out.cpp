#include "drv_digital_out.h"

//function for setting pin as output
int8_t digital_out_init(digital_out_t *out, uint8_t mode)
{
    if (mode == OUTPUT)
    {
        pinMode(out->pin, static_cast<PinMode>(mode));
        return STATUS_SUCCESS;       //return status
    }
    else
    {
        return STATUS_FAILURE;       //return status
    }
}

//function for setting pin HIGH
void digital_out_high(digital_out_t *out)
{
    digitalWrite(out->pin, HIGH);
}

//function for setting pin LOW
void digital_out_low(digital_out_t *out)
{
    digitalWrite(out->pin, LOW);
}

//function for toggling pin
void digital_out_toggle(digital_out_t *out)
{
    int32_t value = digitalRead(out->pin);
    digitalWrite(out->pin, !value);
}

//function for writing pin state
void digital_out_write(digital_out_t *out, uint8_t value)
{
    digitalWrite(out->pin, value);
}