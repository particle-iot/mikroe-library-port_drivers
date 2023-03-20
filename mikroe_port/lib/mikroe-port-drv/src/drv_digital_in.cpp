#include "drv_digital_in.h"

//function for setting pin as input
int8_t digital_in_init(digital_in_t *in, uint8_t mode)
{
    if (mode == INPUT)
    {
        pinMode(in->pin, static_cast<PinMode>(mode));
        return STATUS_SUCCESS;       //return status
    }
    else        //mode other than input selected
    {
        return STATUS_FAILURE;       //return status
    }
}

//function for reading pin state
int32_t digital_in_read(uint8_t pin)
{
    return digitalRead(pin);
}