
---
# AC Current click

AC Current click is a device that is able to measure the alternating current (AC) running through the conductor, using the so-called non-invasive current sensor. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accurrent_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ac-current-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the AcCurrent Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AcCurrent Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void accurrent_cfg_setup ( accurrent_cfg_t *cfg ); 
 
- Initialization function.
> ACCURRENT_RETVAL accurrent_init ( accurrent_t *ctx, accurrent_cfg_t *cfg );


#### Example key functions :

- Gets current value of AC Current in mA.
> float accurrent_get_ma ( accurrent_t *ctx );
 
- Gets current value of AC Current in A.
> float accurrent_get_a ( accurrent_t *ctx );


## Examples Description

> This application measures AC current through a conductor.

**The demo application is composed of two sections :**

### Application Init 

> SPI driver and slick initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    accurrent_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    accurrent_cfg_setup( &cfg );
    ACCURRENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accurrent_init( &accurrent, &cfg );
}
  
```

### Application Task

> Reads the value of AC current and displays it on the USB UART.

```c

void application_task ( void )
{
    float ac_current;

    ac_current = accurrent_get_ma( &accurrent );
    log_printf( &logger, "Current value: %.3f mA\r\n", ac_current );
    Delay_ms( 1000 );
}  

```
## NOTE
> An appropriate AC Current sensor needs to be connected to the click board.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AcCurrent

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
