/**
 ******************************************************************************
 * @file    drv_i2c_master.h
 * @authors Erik Fasnacht
 * @version V1.0.0
 * @date    20-Mar-2023
 * @brief   I2C Master driver layer to interface with MikroE CLICK libraries
 ******************************************************************************
 **/


#ifndef _DRV_I2C_MASTER_H_
#define _DRV_I2C_MASTER_H_

#include "mikro_pins.h"
//todo, confirm these aren't needed
//#include "drv_name.h"
//#include "hal_i2c_master.h"


//enum for status codes, added for library compatibility
typedef enum
{
    I2C_MASTER_SUCCESS = 0,     //Success
    I2C_MASTER_ERROR = (-1)     //Error
} i2c_master_err_t;

//enum for various clock frequencies
typedef enum
{
    I2C_MASTER_SPEED_STANDARD = 0,      //standard clock frequency, 100kHz
    I2C_MASTER_SPEED_FULL = 1,          //fast mode clock frequency, 400kHz
    I2C_MASTER_SPEED_FAST = 2           //fast mode Plus clock frequency, 1MHz
} i2c_master_speed_t;

//struct for various I2C function parameters
typedef struct
{
    uint8_t addr;                       //client address
    pin_name_t sda;                     //SDA pin
    pin_name_t scl;                     //SCL pin
    uint32_t speed;                     //SCL clock rate
    uint16_t timeout_pass_count;        //timeout value , # of retries
} i2c_master_config_t;

//struc for i2c master configuration
typedef struct
{
 //   handle_t handle; //I2C Master handle
    i2c_master_config_t config;     //I2C configuration structure
} i2c_master_t;

//i2c functions
void i2c_master_configure_default(i2c_master_config_t *config);
int8_t i2c_master_open(i2c_master_t *obj, i2c_master_config_t *config);
int8_t i2c_master_set_speed(i2c_master_t *obj, uint32_t speed );
int8_t i2c_master_set_timeout(i2c_master_t *obj, uint16_t timeout_pass_count);
int8_t i2c_master_set_slave_address(i2c_master_t *obj, uint8_t address );
int8_t i2c_master_write(i2c_master_t *obj, uint8_t *write_data_buf, size_t len_write_data);
int8_t i2c_master_read(i2c_master_t *obj, uint8_t *read_data_buf, size_t len_read_data);
int8_t i2c_master_write_then_read(i2c_master_t *obj, uint8_t *write_data_buf, size_t len_write_data, uint8_t *read_data_buf, size_t len_read_data);
void i2c_master_close(i2c_master_t *obj);

#endif // _DRV_I2C_MASTER_H_