#include "drv_analog_in.h"

//todo, remove
/*
static analog_in_t *_owner = NULL;

static err_t _acquire( analog_in_t *obj, bool obj_open_state )
{
    err_t status = ACQUIRE_SUCCESS;

    if ( obj_open_state == true && _owner == obj )
    {
        return ACQUIRE_FAIL;
    }
    if ( _owner != obj )
    {
        status = hal_adc_open( &obj->handle, obj_open_state );

        if ( status != ACQUIRE_FAIL )
            _owner = obj;
    }

    return status;
}
*/

void analog_in_configure_default( analog_in_config_t *config )
{
    //original from MikroE
    /*
    config->input_pin = 0xFFFFFFFF;
    config->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    config->vref_input = ANALOG_IN_VREF_EXTERNAL;
    config->vref_value = -1.0;
    */
}

err_t analog_in_open( analog_in_t *obj, analog_in_config_t *config )
{
    //original from MikroE 
    /*
    analog_in_config_t *p_config = &obj->config;
    memcpy( p_config, config, sizeof( analog_in_config_t ) );
    return _acquire( obj, true );
    */


}

err_t analog_in_set_resolution( analog_in_t *obj, analog_in_resolution_t resolution )
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


}

err_t analog_in_set_vref_input( analog_in_t *obj, analog_in_vref_t vref )
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


}

err_t analog_in_set_vref_value( analog_in_t *obj, float vref_value )
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



}

err_t analog_in_read( analog_in_t *obj, uint16_t *readDatabuf )
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


}

err_t analog_in_read_voltage( analog_in_t *obj, float *readDatabuf )
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


}

void analog_in_close( analog_in_t *obj )
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


}