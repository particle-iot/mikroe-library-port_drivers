#ifndef _DRV_DIGITAL_OUT_H_
#define _DRV_DIGITAL_OUT_H_

#ifdef __cplusplus
extern "C"{
#endif

//#include "gpio_hal.h"
#include "spark_wiring.h"

//#include "drv_name.h"
//#include "hal_gpio.h"

#define SUCCESS 0
#define ERROR (-1)
#define LOW 0
#define HIGH 1

int digital_out_init(uint16_t pin, PinMode mode);
void digital_out_high(uint16_t pin);
void digital_out_low(uint16_t pin);
void digital_out_toggle(uint16_t pin);
void digital_out_write(uint16_t pin, uint8_t value);


#ifdef __cplusplus
}
#endif

#endif // _DRV_DIGITAL_OUT_H_
// ------------------------------------------------------------------------- END
