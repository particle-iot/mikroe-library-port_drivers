#include "drv_digital_in.h"

//function for setting pin as input
uint8_t digital_in_init(uint16_t pin, uint8_t mode)
{
    if (mode == 0)
    {
        pinMode(pin, mode);
    }
    return 0;
}

//function for reading pin state
int32_t digital_in_read(uint16_t pin)
{
    return digitalRead(pin);
}

// ------------------------------------------------------------------------- END
