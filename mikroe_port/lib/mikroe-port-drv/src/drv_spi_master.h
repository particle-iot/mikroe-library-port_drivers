/**
 ******************************************************************************
 * @file    drv_spi_master.h
 * @authors Erik Fasnacht
 * @version V1.0.0
 * @date    16-Mar-2023
 * @brief   SPI Master driver layer to interface with MikroE CLICK libraries
 ******************************************************************************
 **/

#ifndef _DRV_SPI_MASTER_H_
#define _DRV_SPI_MASTER_H_

#include "mikro_pins.h"

//struct for SPI configuration
typedef struct
{
    uint8_t         default_write_data;     //SPI Master default write data
    uint8_t         sck;                    //SCK pin
    uint8_t         miso;                   //MISO pin
    uint8_t         mosi;                   //MOSI pin
    uint32_t        speed;                  //SPI clock speed
    uint8_t         mode;                   //SPI mode
} spi_master_config_t;

//struc for spi master configuration
typedef struct
{
    spi_master_config_t config;     //SPI Master Driver configuration structure
} spi_master_t;

//enum for various SPI modes, added for library port compatibility
typedef enum {
    SPI_MASTER_MODE_0 = 0,                          //SPI MODE 0
    SPI_MASTER_MODE_1 = 1,                          //SPI MODE 1
    SPI_MASTER_MODE_2 = 2,                          //SPI MODE 2
    SPI_MASTER_MODE_3 = 3,                          //SPI MODE 3
    SPI_MASTER_MODE_DEFAULT = SPI_MASTER_MODE_0     //Default SPI mode - MODE 0
} spi_master_mode_t;

//enum chip select polarity, added for library port compatibility
typedef enum
{
    SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW = LOW,       //Chip Select Polarity - Active Low
    SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH = HIGH,     //Chip Select Polarity - Active High
    SPI_MASTER_CHIP_SELECT_DEFAULT_POLARITY = LOW           //Chip Select Default Polarity - Active Low
} spi_master_chip_select_polarity_t;

//enum for status codes, added for library compatibility
typedef enum
{
    SPI_MASTER_SUCCESS = 0,     //Success
    SPI_MASTER_ERROR = (-1)     //Error
} spi_master_err_t;

//spi functions
void spi_master_configure_default(spi_master_config_t *config);                                                                                                     //Configures #spi_master_config_t structure to default initialization values
int8_t spi_master_open(spi_master_t *obj, spi_master_config_t *config);                                                                                             //Opens the SPI Master driver object on selected pins
void spi_master_select_device(uint8_t chip_select);                                                                                                                 //Sets digital output individual slave pin to logic 0
void spi_master_deselect_device(uint8_t chip_select);                                                                                                               //Sets digital output individual slave pin to logic 1
void spi_master_set_chip_select_polarity(uint8_t polarity);                                                                                                         //sets SPI Master chip select polarity either to active low or active high
int8_t spi_master_set_speed(spi_master_t *obj, uint32_t speed);                                                                                                     //Sets SPI Master module speed to passed value if possible
int8_t spi_master_set_mode(spi_master_t *obj, uint8_t mode);                                                                                                        //Sets SPI Master module mode to passed value if possible
int8_t spi_master_set_default_write_data(spi_master_t *obj, uint8_t default_write_data);                                                                            //Default write data is sent by driver when the data transmit buffer is shorter than data receive buffer
int8_t spi_master_write(spi_master_t *obj, uint8_t *write_data_buffer, size_t write_data_length);                                                                   //Writes byte to SPI bus in blocking mode                                        
int8_t spi_master_read(spi_master_t *obj, uint8_t *read_data_buffer, size_t read_data_length);                                                                      //Reads byte from SPI bus in blocking mode                                             
int8_t spi_master_write_then_read(spi_master_t *obj, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data);     //Writes a sequence of bytes to SPI bus, followed by a corresponding read                                                                                      
void spi_master_close(spi_master_t *obj);                                                                                                                           //Closes SPI Master Driver context object

#endif // _DRV_SPI_MASTER_H_