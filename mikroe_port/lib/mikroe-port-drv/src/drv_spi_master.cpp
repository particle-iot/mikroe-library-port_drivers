#include "drv_spi_master.h"

//spi global variables
uint8_t cs_polarity = LOW;        //CS polarity variable, active low by default

//todo, create object that holds all the values for SPI, IE hal translation layer

//Configures spi_master_config_t struct to default initialization values
void spi_master_configure_default(spi_master_config_t *config) 
{
    //set default values for pins (CS)
    pinMode(SS, OUTPUT);                            //set SS sginal mikroBUS1 as output
    pinMode(SS1, OUTPUT);                           //set SS1 sginal mikroBUS2 as output
    digitalWrite(SS, HIGH);                         //set SS HIGH
    digitalWrite(SS1, HIGH);                        //set SS1 HIGH

    //set default values for spi mode and speed
    SPI.setDataMode(config->mode);                  //set default spi mode
    SPI.setClockSpeed(config->speed);               //set default speed

}

//Opens the SPI Master driver object on selected pins
int8_t spi_master_open(spi_master_t *obj, spi_master_config_t *config) 
{       
    //compiler warning indicating assumption
    #warning spi_master_open() assumes SPI peripheral will not get stolen by otrher threads

    //todo, add thread check protection

    pinMode(SS, OUTPUT);                            //set SS sginal mikroBUS1 as output
    pinMode(SS1, OUTPUT);                           //set SS1 sginal mikroBUS2 as output
    digitalWrite(SS, HIGH);                         //set SS HIGH
    digitalWrite(SS1, HIGH);                        //set SS1 HIGH
    SPI.begin(SPI_MODE_MASTER, PIN_INVALID);        //begin SPI transaction, not selecting CS pin
    return SPI_MASTER_SUCCESS;                      //return status
}

//Sets digital output individual slave pin to logic 0
void spi_master_select_device(uint8_t chip_select)
{
    pinMode(chip_select, OUTPUT);               //set function parameter as output
    digitalWrite(chip_select, cs_polarity);     //assert CS 
}

//Sets digital output individual slave pin to logic 1
void spi_master_deselect_device(uint8_t chip_select) 
{
    pinMode(chip_select, OUTPUT);                   //set function parameter as output
    digitalWrite(chip_select, !cs_polarity);        //de-assert CS 
}

//sets SPI Master chip select polarity either to active low or active high
void spi_master_set_chip_select_polarity(uint8_t polarity)
{
    if ((polarity == LOW) || (polarity == HIGH))        //check for valid function parameter
    {
        cs_polarity = polarity;     //set new CS polarity
    }
}

//Default write data is sent by driver when the data transmit buffer is shorter than data receive buffer
int8_t spi_master_set_speed(spi_master_t *obj, uint32_t speed)  
{
    if(SPI.setClockSpeed(speed/2) == speed)       //set clock speed to function parameter and check to confirm it is set
    {
        return SPI_MASTER_SUCCESS;      //return status
    }
    return SPI_MASTER_ERROR;        //return status
}

//Sets SPI Master module speed to passed value if possible
int8_t spi_master_set_mode(spi_master_t *obj, uint8_t mode)
{
    if((mode >= SPI_MODE0) || (mode <= SPI_MODE3))      //check that paramter input is valid
    {
        SPI.setDataMode(mode);          //set  spi mode to function parameter
        return SPI_MASTER_SUCCESS;      //return status
    }
    return SPI_MASTER_ERROR;        //return status
}

//Sets SPI Master module mode to passed value if possible
int8_t spi_master_set_default_write_data(spi_master_t *obj, uint8_t  default_write_data) 
{
    //obj->config.default_write_data = default_write_data;
    #warning spi_master_set_default_write_data() function is not implemented
    return SPI_MASTER_SUCCESS;      //return status
}

//Writes byte to SPI bus in blocking mode
int8_t spi_master_write(spi_master_t *obj, uint8_t *write_data_buffer, size_t write_data_length)
{
    //compiler warning indicating assumption
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

//Reads byte from SPI bus in blocking mode
int8_t spi_master_read(spi_master_t *obj, uint8_t *read_data_buffer, size_t read_data_length)  
{
    //compiler warning indicating assumption
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

//Writes a sequence of bytes to SPI bus, followed by a corresponding read 
int8_t spi_master_write_then_read(spi_master_t *obj, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data)   
{
    //compiler warning indicating assumption
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
                                                             
//Closes SPI Master Driver context object
void spi_master_close(spi_master_t *obj) 
{
    SPI.end();      //close spi peripheral
}

