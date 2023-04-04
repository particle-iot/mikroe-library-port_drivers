#include "drv_analog_in.h"

//global variables
static uint8_t global_resolution;      //variable for the resolution
static uint16_t global_pin;             //variable for the pin

//configure analog in default
void analog_in_configure_default(analog_in_config_t *config)
{
    //original from MikroE
    /*
    config->input_pin = 0xFFFFFFFF;
    config->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    config->vref_input = ANALOG_IN_VREF_EXTERNAL;
    config->vref_value = -1.0;
    */


   global_resolution = ANALOG_IN_RESOLUTION_12_BIT;        //set global variable to 12-bit
}

//open analog input on pin
int8_t analog_in_open(analog_in_t *obj, analog_in_config_t *config)
{
    //original from MikroE 
    /*
    analog_in_config_t *p_config = &obj->config;
    memcpy( p_config, config, sizeof( analog_in_config_t ) );
    return _acquire( obj, true );
    */
   

   global_pin = config->input_pin;      //set global pin variable to function parameter
   pinMode(global_pin, AN_INPUT);       //set pin as analog input
   return ADC_SUCCESS;                  //return status
}

//set analog resolution
int8_t analog_in_set_resolution(analog_in_t *obj, analog_in_resolution_t resolution)
{
    //original from MikroE
    /*
    if ( _acquire(obj, false) != ACQUIRE_FAIL )
    {
        obj->config.resolution = resolution;
        return hal_adc_set_resolution( &obj->handle, &obj->config );
    } else {
        return ADC_ERROR;
    }
    */


    switch (resolution)
    {
        case ANALOG_IN_RESOLUTION_6_BIT:
        case ANALOG_IN_RESOLUTION_8_BIT:
        case ANALOG_IN_RESOLUTION_10_BIT:
        case ANALOG_IN_RESOLUTION_12_BIT:
                global_resolution = resolution;     //set global variable to function parameter
            return ADC_SUCCESS;                     //return status

        case ANALOG_IN_RESOLUTION_14_BIT:
        case ANALOG_IN_RESOLUTION_16_BIT:
                #warning this resolution is not supported as the max resolution is 12-bit
                global_resolution = resolution;     //set global variable to function parameter
            return ADC_SUCCESS;                     //return status

         default:
            return ADC_ERROR;      //return status
    }
}

//set vref input, not implemented
int8_t analog_in_set_vref_input(analog_in_t *obj, analog_in_vref_t vref)
{
    //original from MikroE
    /*
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.vref_input = vref;
        return hal_adc_set_vref_input( &obj->handle, &obj->config );
    } else {
        return ADC_ERROR;
    }
    */


   #warning analog_in_set_vref_input() function is not implemented
   return ADC_SUCCESS;      //return status

}

//set vref value, not implemented
int8_t analog_in_set_vref_value(analog_in_t *obj, float vref_value)
{
    //original from MikroE
    /*
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        obj->config.vref_value = vref_value;
        hal_adc_set_vref_value( &obj->handle, &obj->config );
        return ADC_SUCCESS;
    } else {
        return ADC_ERROR;
    }
    */

    #warning analog_in_set_vref_value() function is not implemented
    return ADC_SUCCESS;      //return status

}

//read analog input
int8_t analog_in_read(analog_in_t *obj, uint16_t *readDatabuf)
{
    //original from MikroE
    /*
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        return hal_adc_read( &obj->handle, readDatabuf );
    } else {
        return ADC_ERROR;
    }
    */


    uint16_t val = analogRead(global_pin);        //analog read from set pin
    switch (global_resolution)
    {
        case ANALOG_IN_RESOLUTION_6_BIT:
                val = map(val, 0, 4095, 0, 63);                         //change from 12-bit to 6-bit value
                readDatabuf = reinterpret_cast<uint16_t *>(val);        //set value to function parameter
            return ADC_SUCCESS;                                         //return status

        case ANALOG_IN_RESOLUTION_8_BIT:
                val = map(val, 0, 4095, 0, 255);                        //change from 12-bit to 8-bit value
                readDatabuf = reinterpret_cast<uint16_t *>(val);        //set value to function parameter
            return ADC_SUCCESS;                                         //return status

        case ANALOG_IN_RESOLUTION_10_BIT:
                val = map(val, 0, 4095, 0, 1023);                       //change from 12-bit to 10-bit value
                readDatabuf = reinterpret_cast<uint16_t *>(val);        //set value to function parameter
            return ADC_SUCCESS;                                         //return status

        case ANALOG_IN_RESOLUTION_12_BIT:
                readDatabuf = reinterpret_cast<uint16_t *>(val);        //set value to function parameter
            return ADC_SUCCESS;                                         //return status

        case ANALOG_IN_RESOLUTION_14_BIT:
                #warning this resolution is not supported as the max resolution is 12-bit, output may not be valid 
                val = map(val, 0, 4095, 0, 16383);                      //change from 12-bit to 14-bit value
                readDatabuf = reinterpret_cast<uint16_t *>(val);        //set value to function parameter
            return ADC_SUCCESS;                                         //return status

        case ANALOG_IN_RESOLUTION_16_BIT:
                #warning this resolution is not supported as the max resolution is 12-bit, output may not be valid
                val = map(val, 0, 4095, 0, 65535);                      //change from 12-bit to 16-bit value
                readDatabuf = reinterpret_cast<uint16_t *>(val);        //set value to function parameter
            return ADC_SUCCESS;                                         //return status

         default:      
            return ADC_ERROR;      //return status
    }
}

//read analog voltage
int8_t analog_in_read_voltage(analog_in_t *obj, float *readDatabuf)
//int8_t analog_in_read_voltage(analog_in_t *obj, float readDatabuf)
{
    //original from MikroE
    /*
    if ( _acquire( obj, false ) != ACQUIRE_FAIL )
    {
        return hal_adc_read_voltage( &obj->handle, readDatabuf );
    } else {
        return ADC_ERROR;
    }
    */


    int32_t val = analogRead(global_pin);                   //analog read from set pin               
    *readDatabuf = (float) (val * 0.0008);     //convert value to voltage and set to function parameter           
    return ADC_SUCCESS;      //return status
}

//close/clear analog input
void analog_in_close(analog_in_t *obj)
{
    //original from MikroE
    /*
    err_t drv_status;
    drv_status = hal_adc_close( &obj->handle );
    if ( drv_status == ADC_SUCCESS )
    {
        obj->handle = NULL;
        _owner = NULL;
    }
    */


   pinMode(global_pin, INPUT);        //set pin to be input, clear/close analog input

}