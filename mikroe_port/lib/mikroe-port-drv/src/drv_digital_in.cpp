#include "drv_digital_in.h"

//function for setting pin as input
int8_t digital_in_init(digital_in_t *in, uint8_t mode)
{
    if (mode == INPUT)
    {
        pinMode(in->pin, static_cast<PinMode>(mode));
        return DIGITAL_IN_SUCCESS;      //return status
    }
    else        //mode other than input selected
    {
        return DIGITAL_IN_UNSUPPORTED_PIN;      //return status
    }
}

//function for reading pin state
int32_t digital_in_read(digital_in_t *in)
{
    return digitalRead(in->pin);
}