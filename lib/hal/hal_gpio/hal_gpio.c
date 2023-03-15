#include "hal_gpio.h"

//Configure pin as digital input or output
void hal_gpio_configure_pin(uint8_t pin, uint8_t name, PinMode direction)
//void hal_gpio_configure_pin(hal_gpio_pin_t *pin, hal_pin_t name, PinMode direction); 
{
    //hal_gpio_configure(pin, (PinMode) direction);
}

//Reads the current pin input level
uint8_t hal_gpio_read_pin_input(hal_gpio_pin_t *pin)
{
    return hal_gpio_read((hal_pin_t *)pin);
}

//Reads the current pin output level
uint8_t hal_gpio_read_pin_output( hal_gpio_pin_t *pin)
{
    return hal_gpio_read((hal_pin_t *)pin);
}

//Sets the current output logic of the GPIO pin
//void hal_gpio_write_pin_output(hal_gpio_pin_t *pin, uint8_t value)
void hal_gpio_write_pin_output(uint8_t pin, uint8_t value)
{
    hal_gpio_write(pin, value);
}

//Toggles the current output logic of the GPIO pin
void hal_gpio_toggle_pin_output(hal_gpio_pin_t *pin)
{
    uint8_t value = hal_gpio_read((hal_pin_t *)pin);
    hal_gpio_write((hal_pin_t *)pin, !value);
}

//Sets the current output logic of the GPIO pin to HIGH
void hal_gpio_set_pin_output(hal_gpio_pin_t *pin)
{
    hal_gpio_write((hal_pin_t *)pin, HIGH);
}

//Sets the current output logic of the GPIO pin to LOW

void hal_gpio_clear_pin_output(hal_gpio_pin_t *pin)
{
    hal_gpio_write((hal_pin_t *)pin, LOW);
}


//todo, add dvos functions if available

//Configures port as digital input or output
void hal_gpio_configure_port(hal_gpio_port_t *port, hal_pin_t name, uint8_t mask, PinMode direction)
{
    //todo, insert port function 
//    hal_ll_gpio_configure_port( (hal_ll_gpio_port_t *)port, name, mask, (hal_ll_gpio_direction_t)direction );
}

//Reads the current input logic of the GPIO port
hal_gpio_config_t hal_gpio_read_port_input(hal_gpio_port_t *port)
{
    //todo, insert port function
//    return hal_ll_gpio_read_port_input( (hal_ll_gpio_port_t *)port );
    return 0;
}

//Reads the current output logic of the GPIO port
hal_gpio_config_t hal_gpio_read_port_output(hal_gpio_port_t *port)
{
    //todo, insert port function
//    return hal_ll_gpio_read_port_output( (hal_ll_gpio_port_t *)port );
    return 0;
}

//Sets the current output logic of the GPIO port to LOW
void hal_gpio_write_port_output(hal_gpio_port_t *port, hal_gpio_config_t value)
{
    //todo, insert port function
//    hal_ll_gpio_write_port_output( (hal_ll_gpio_port_t *)port, value );
}
