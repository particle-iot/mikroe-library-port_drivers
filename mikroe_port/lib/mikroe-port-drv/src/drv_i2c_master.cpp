#include "drv_i2c_master.h"

//static i2c_master_t *_owner = NULL;
/*
static err_t _acquire( i2c_master_t *obj, bool obj_open_state )
{
    err_t status = ACQUIRE_SUCCESS;

    if ( obj_open_state == true && _owner == obj )
    {
        return ACQUIRE_FAIL;
    }

    if ( _owner != obj )
    {
        status = hal_i2c_master_open( &obj->handle,obj_open_state );

        if ( status != ACQUIRE_FAIL )
        {
            _owner = obj;
        }
    }

    return status;
}
*/



//Configures i2c_master_config_t struct to default initialization values
void i2c_master_configure_default(i2c_master_config_t *config)
{
    /*
    config->addr = 0;                               //set client address to 0
    config->sda = SDA;                              //same for all mikroBUS sockets
    config->scl = SCL;                              //same for all mikroBUS sockets
    config->speed = I2C_MASTER_SPEED_STANDARD;      //set default speed, 100kHz
    config->timeout_pass_count = 10000;             //set default timeout
    */

    Wire.setSpeed(config->speed);                   //set speed, must be done before Wire.begin()

    //todo, not sure if this is needed
    //Wire.begin();
}

//Opens the I2c Master driver object on selected pins
int8_t i2c_master_open( i2c_master_t *obj, i2c_master_config_t *config )
{
    i2c_master_config_t *p_config = &obj->config;
    memcpy( p_config, config, sizeof( i2c_master_config_t ) );

    return I2C_MASTER_SUCCESS;                          //return status
}

//as
int8_t i2c_master_set_speed( i2c_master_t *obj, uint32_t speed )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.speed = speed;
        return hal_i2c_master_set_speed( &obj->handle, &obj->config );
    } else {
        return I2C_MASTER_ERROR;
    }
}

//as
int8_t i2c_master_set_timeout( i2c_master_t *obj, uint16_t timeout_pass_count )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.timeout_pass_count = timeout_pass_count;
        hal_i2c_master_set_timeout( &obj->handle, &obj->config );
        return I2C_MASTER_SUCCESS;
    } else {
        return I2C_MASTER_ERROR;
    }
}

//as
int8_t i2c_master_set_slave_address( i2c_master_t *obj, uint8_t address )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.addr = address;
        hal_i2c_master_set_slave_address( &obj->handle, &obj->config );
        return I2C_MASTER_SUCCESS;
    } else {
        return I2C_MASTER_ERROR;
    }
}

//as
int8_t i2c_master_write( i2c_master_t *obj, uint8_t *write_data_buf, size_t len_write_data )
{
    if(_acquire( obj, false ) != ACQUIRE_FAIL )
    {
        return hal_i2c_master_write( &obj->handle, write_data_buf, len_write_data );
    } else {
        return I2C_MASTER_ERROR;
    }
}

//as
int8_t i2c_master_read(i2c_master_t *obj, uint8_t *read_data_buf, size_t len_read_data )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        return hal_i2c_master_read( &obj->handle, read_data_buf, len_read_data );
    } else {
        return I2C_MASTER_ERROR;
    }
}

//as
int8_t i2c_master_write_then_read( i2c_master_t *obj, uint8_t *write_data_buf, size_t len_write_data, uint8_t *read_data_buf, size_t len_read_data )
{
    if( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        return hal_i2c_master_write_then_read( &obj->handle, write_data_buf, len_write_data,
                                               read_data_buf, len_read_data );
    } else {
        return I2C_MASTER_ERROR;
    }
}

//Closes I2C Master Driver context object
void i2c_master_close( i2c_master_t *obj )
{
    err_t status;

    status = hal_i2c_master_close( &obj->handle );

    if( status == I2C_MASTER_SUCCESS )
    {
        obj->handle = NULL;
        _owner = NULL;
    }
}