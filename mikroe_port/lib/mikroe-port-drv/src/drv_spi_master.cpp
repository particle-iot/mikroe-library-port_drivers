#include "drv_spi_master.h"

static uint8_t cs_polarity;        //CS polarity variable, static as previous value should be retained

//Configures spi_master_config_t struct to default initialization values
void spi_master_configure_default(spi_master_config_t *config) 
{
    //original from MikroE
    /*
    config->default_write_data = 0;
    config->sck = 0xFFFFFFFF;
    config->miso = 0xFFFFFFFF;
    config->mosi = 0xFFFFFFFF;
    config->speed = 100000;
    config->mode = SPI_MASTER_MODE_DEFAULT;
    */
    

    //set default values for pins (CS)
    pinMode(SS, OUTPUT);            //set SS sginal mikroBUS1 as output
    pinMode(SS1, OUTPUT);           //set SS1 sginal mikroBUS2 as output
    digitalWrite(SS, HIGH);         //set SS HIGH
    digitalWrite(SS1, HIGH);        //set SS1 HIGH
    cs_polarity = LOW;              //set CS active low          

    //set default values for spi mode and speed
    SPI.setDataMode(SPI_MASTER_MODE_0);     //set default spi mode
    SPI.setClockSpeed(100, KHZ);            //set default speed, 100kHz

}

//open SPI peripheral
int8_t spi_master_open(spi_master_t *obj, spi_master_config_t *config) 
{   
    //original from MikroE
    /*
    spi_master_config_t *p_config = &obj->config;
    memcpy( p_config, config, sizeof( spi_master_config_t ) );
    return _acquire( obj, true );
    */


    #warning spi_master_open() assumes SPI peripheral will not get stolen by other threads
    pinMode(SS, OUTPUT);                            //set SS sginal mikroBUS1 as output
    pinMode(SS1, OUTPUT);                           //set SS1 sginal mikroBUS2 as output
    digitalWrite(SS, HIGH);                         //set SS HIGH
    digitalWrite(SS1, HIGH);                        //set SS1 HIGH
    SPI.begin(SPI_MODE_MASTER, PIN_INVALID);        //begin SPI transaction, not selecting CS pin
    return SPI_MASTER_SUCCESS;                      //return status
}

//assert chip select
void spi_master_select_device(uint8_t chip_select)
{
    //original from MikroE
    //hal_spi_master_select_device( chip_select );
    

    pinMode(chip_select, OUTPUT);               //set function parameter as output
    digitalWrite(chip_select, cs_polarity);     //assert CS 
}

//de-assert chip select
void spi_master_deselect_device(uint8_t chip_select) 
{
    //original from MikroE
    //hal_spi_master_deselect_device( chip_select );
    

    pinMode(chip_select, OUTPUT);                   //set function parameter as output
    digitalWrite(chip_select, !cs_polarity);        //de-assert CS 
}

//sets chip select polarity
void spi_master_set_chip_select_polarity(uint8_t polarity)
{
    //original from MikroE
    //hal_spi_master_set_chip_select_polarity( polarity );
    

    if ((polarity == LOW) || (polarity == HIGH))        //check for valid function parameter
    {
        cs_polarity = polarity;     //set new CS polarity
    }
}

//set SPI clock speed
int8_t spi_master_set_speed(spi_master_t *obj, uint32_t speed)  
{
    //original from MikroE
    /*
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.speed = speed;
        return hal_spi_master_set_speed( &obj->handle, &obj->config );
    } else {
        return SPI_MASTER_ERROR;
    }
    */
    

    if(SPI.setClockSpeed(speed) == speed)       //set clock speed to function parameter and check to confirm it is set
    {
        return SPI_MASTER_SUCCESS;      //return status
    }
    return SPI_MASTER_ERROR;        //return status
}

//Sets SPI Mode
int8_t spi_master_set_mode(spi_master_t *obj, uint8_t mode)
{
    //original from MikroE
    /*
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.mode = mode;
        return hal_spi_master_set_mode( &obj->handle, &obj->config );
    } else {
        return SPI_MASTER_ERROR;
    }
    */
    

    if((mode >= SPI_MODE0) || (mode <= SPI_MODE3))      //check that paramter input is valid
    {
        SPI.setDataMode(mode);          //set  spi mode to function parameter
        return SPI_MASTER_SUCCESS;      //return status
    }
    return SPI_MASTER_ERROR;        //return status
}

//sets SPI default value, not implemented
int8_t spi_master_set_default_write_data(spi_master_t *obj, uint8_t  default_write_data) 
{
    //original from MikroE
    /*
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.default_write_data = default_write_data;
        hal_spi_master_set_default_write_data( &obj->handle, &obj->config );
        return SPI_MASTER_SUCCESS;
    } else {
        return SPI_MASTER_ERROR;
    }
    */
    

    #warning spi_master_set_default_write_data() function is not implemented
    return SPI_MASTER_SUCCESS;      //return status
}

//write byte(s) to SPI bus
int8_t spi_master_write(spi_master_t *obj, uint8_t *write_data_buffer, size_t write_data_length)
{
    //original from MikroE
    /*
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        return  hal_spi_master_write( &obj->handle, write_data_buffer, write_data_length );
    } else {
        return SPI_MASTER_ERROR;
    }
    */
    

    #warning spi_master_write() assumes the fist element of write_data_buffer is the first byte to be transmitted, IE the opcode/register if required
    
    //create dummy array size of write fill with zeros
    uint8_t write_dummy[write_data_length] = {0};     //required for SPI.transfer read/write arrays must be of same size
    if(SPI.beginTransaction() == SPI_MASTER_ERROR)      //setup fail
    {
        return SPI_MASTER_ERROR;        //return status
    }
    
    SPI.transfer(write_data_buffer, write_dummy, write_data_length, NULL);      //spi transaction for write (read = NULL)
    SPI.endTransaction();                                                       //end transaction and release spi peripheral lock
    return SPI_MASTER_SUCCESS;                                                  //return status
}

//Reads byte(s) from SPI bus
int8_t spi_master_read(spi_master_t *obj, uint8_t *read_data_buffer, size_t read_data_length)  
{

    //original from MikroE
    /*
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        return hal_spi_master_read( &obj->handle, read_data_buffer, read_data_length );
    } else {
        return SPI_MASTER_ERROR;
    }
    */

    
    #warning spi_master_read() assumes the read immediately occurs on first SCK. If data needs to be transmitted before read, use spi_master_write_then_read() instead
    
    //create dummy array size of read fill with zeros
    uint8_t read_dummy[read_data_length] = {0};     //required for SPI.transfer read/write arrays must be of same size  

    if(SPI.beginTransaction() == SPI_MASTER_ERROR)      //setup fail
    {
        return SPI_MASTER_ERROR;        //return status
    }

    SPI.transfer(read_dummy, read_data_buffer, read_data_length, NULL);     //spi transaction for read (write = NULL)
    SPI.endTransaction();                                                   //end transaction and release spi peripheral lock
    return SPI_MASTER_SUCCESS;                                              //return status
}

//write a sequence of byte(s) to SPI bus followed by read
int8_t spi_master_write_then_read(spi_master_t *obj, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data)   
{
    //original from MikroE
    /*
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
     {
        return hal_spi_master_write_then_read( &obj->handle, write_data_buffer,length_write_data,read_data_buffer,length_read_data );
     } else {
        return SPI_MASTER_ERROR;
    }
    */
    

    #warning spi_master_write_then_read() assumes the fist element of write_data_buffer is the first byte to be transmitted, IE the opcode/register if required

    //create dummy array size of write fill with zeros
    uint8_t write_dummy[length_write_data] = {0};     //required for SPI.transfer read/write arrays must be of same size  

    //create dummy array size of read fill with zeros
    uint8_t read_dummy[length_read_data] = {0};     //required for SPI.transfer read/write arrays must be of same size  

    if(SPI.beginTransaction() == SPI_MASTER_ERROR)      //setup fail
    {
        return SPI_MASTER_ERROR;        //return status
    }
    
    SPI.transfer(write_data_buffer, write_dummy, length_write_data, NULL);      //spi transaction for write (read = NULL)
    SPI.transfer(read_dummy, read_data_buffer, length_read_data, NULL);         //spi transaction for read (write = NULL)
    SPI.endTransaction();                                                       //end transaction and release spi peripheral lock
    return SPI_MASTER_SUCCESS;                                                  //return status                                         
}                                                           
                                                             
//close SPI peripheral
void spi_master_close(spi_master_t *obj) 
{
    //original from MikroE
    /*
    err_t status;

    status = hal_spi_master_close( &obj->handle );

    if ( status == SPI_MASTER_SUCCESS )
    {
        obj->handle = NULL;
        _owner = NULL;
    }
    */
    
    
    SPI.end();      //close spi peripheral
}

