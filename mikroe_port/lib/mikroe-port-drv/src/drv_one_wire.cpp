/*
 * Copyright (c) 2023 Particle Industries, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "drv_one_wire.h"


//todo, remove
/*
err_t one_wire_open( one_wire_t *obj ) {
    if ( HAL_PIN_NC == obj->data_pin || obj->state ) {
        return ONE_WIRE_ERROR;
    }

    if ( ONE_WIRE_SUCCESS != hal_one_wire_open( obj ) ) {
        return ONE_WIRE_ERROR;
    } else {
        return ONE_WIRE_SUCCESS;
    }
}
*/

void one_wire_configure_default(one_wire_t *obj) 
{
    //original from MikroE
    /*
    obj->data_pin = 0xFFFFFFFF;
    obj->state = false;
    */


}

int8_t one_wire_reset(one_wire_t *obj) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_reset( obj ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */

   //insert
   return ONE_WIRE_SUCCESS;     //return status
}

int8_t one_wire_read_rom(one_wire_t *obj, one_wire_rom_address_t *device_rom_address) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_read_rom( obj, device_rom_address ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */

   //insert
   return ONE_WIRE_SUCCESS;     //return status
}

int8_t one_wire_skip_rom(one_wire_t *obj) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_skip_rom( obj ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */

   //insert
   return ONE_WIRE_SUCCESS;     //return status
}

int8_t one_wire_match_rom(one_wire_t *obj, one_wire_rom_address_t *device_rom_address) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_match_rom( obj, device_rom_address ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */

   //insert
   return ONE_WIRE_SUCCESS;     //return status
}

int8_t one_wire_search_first_device(one_wire_t *obj, one_wire_rom_address_t *one_wire_device_list) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_search_first_device( obj, one_wire_device_list ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */

   //insert
   return ONE_WIRE_SUCCESS;     //return status
}

int8_t one_wire_search_next_device(one_wire_t *obj, one_wire_rom_address_t *one_wire_device_list) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_search_next_device( obj, one_wire_device_list ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */

   //insert
   return ONE_WIRE_SUCCESS;     //return status
}

int8_t one_wire_write_byte(one_wire_t *obj, uint8_t *write_data_buffer, size_t write_data_length) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_write_byte( obj, write_data_buffer, write_data_length ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */

    //insert
   return ONE_WIRE_SUCCESS;     //return status
}

int8_t one_wire_read_byte(one_wire_t *obj, uint8_t *read_data_buffer, size_t read_data_length) 
{
    //original from MikroE
    /* 
    if ( hal_one_wire_read_byte( obj, read_data_buffer, read_data_length ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */

   //insert
   return ONE_WIRE_SUCCESS;     //return status
}