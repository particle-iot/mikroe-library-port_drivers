#include "drv_spi_master.h"

static spi_master_t *_owner = NULL;


//Configures #spi_config struct to default initialization values
void spi_master_configure_default(spi_config *config) 
{
    config->default_write_data = 0;
    config->sck =   MIKROBUS_1_SCK;
    config->miso =  MIKROBUS_1_MISO;
    config->mosi =  MIKROBUS_1_MOSI;
    config->speed = 100000;
    config->mode = SPI_MODE0;

    //todo, eaf, not sure this is needed
    //SPISettings(config->speed, 1, config->mode);     //'1' is for MSBFIRST
}

//Opens the SPI Master driver object on selected pins
uint8_t spi_master_open(spi_master_t *obj, spi_config *config) 
{   
//    spi_config *p_config = &obj->config;
//    memcpy( p_config, config, sizeof(spi_config) );

    //SPI.begin(SPI_MODE_MASTER);
    return 0;
}

//Sets digital output individual slave pin to logic 0
void spi_master_select_device(uint8_t chip_select)
{
//    hal_spi_master_select_device( chip_select );
}

//Sets digital output individual slave pin to logic 1
void spi_master_deselect_device(uint8_t chip_select) 
{
//    hal_spi_master_deselect_device( chip_select );
}

//sets SPI Master chip select polarity either to active low or active high
void spi_master_set_chip_select_polarity(uint8_t polarity)
{
//    hal_spi_master_set_chip_select_polarity( polarity );
}

//Default write data is sent by driver when the data transmit buffer is shorter than data receive buffer
uint8_t spi_master_set_speed(spi_master_t *obj, spi_config speed)  
{
//    obj->config.speed = speed;
//     hal_spi_master_set_speed( &obj->handle, &obj->config );
    return 0;
}

//Sets SPI Master module speed to passed value if possible
uint8_t spi_master_set_mode(spi_master_t *obj, spi_config mode)
{
//    obj->config.mode = mode;
//    hal_spi_master_set_mode( &obj->handle, &obj->config );
    return 0;
}

//Sets SPI Master module mode to passed value if possible
uint8_t spi_master_set_default_write_data(spi_master_t *obj, spi_config default_write_data) 
{
//    obj->config.default_write_data = default_write_data;
//    hal_spi_master_set_default_write_data( &obj->handle, &obj->config );
    return 0;
}

//Writes byte to SPI bus in blocking mode
uint8_t spi_master_write(spi_master_t *obj, uint8_t *write_data_buffer, size_t write_data_length)
{
//    hal_spi_master_write( &obj->handle, write_data_buffer, write_data_length );
    return 0;
}

//Reads byte from SPI bus in blocking mode
uint8_t spi_master_read(spi_master_t *obj, uint8_t *read_data_buffer, size_t read_data_length)  
{
//    hal_spi_master_read( &obj->handle, read_data_buffer, read_data_length );
    return 0;
}

//Writes a sequence of bytes to SPI bus, followed by a corresponding read 
uint8_t spi_master_write_then_read(spi_master_t *obj, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data)   
{
//    hal_spi_master_write_then_read( &obj->handle, write_data_buffer, length_write_data, read_data_buffer, length_read_data );            
    return 0;                                            
}                                                           
                                                             
//Closes SPI Master Driver context object
void spi_master_close(spi_master_t *obj) 
{
//    hal_spi_master_close( &obj->handle );
}

