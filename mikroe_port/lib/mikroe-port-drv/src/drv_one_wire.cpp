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

//global variables
unsigned char rom_num[8];
uint8_t LastDiscrepancy;
uint8_t LastFamilyDiscrepancy;
uint8_t LastDeviceFlag;

//set defaul config for 1-wire
void one_wire_configure_default(one_wire_t *obj) 
{
    //original from MikroE
    /*
    obj->data_pin = 0xFFFFFFFF;
    obj->state = false;
    */


   #warning one_wire_configure_default() function does not do anything since there are no global variables that need to be set
}

//open 1-wire on function parameter pin
int8_t one_wire_open( one_wire_t *obj ) 
{
    //original from MikroE
    /*
    if ( HAL_PIN_NC == obj->data_pin || obj->state ) {
        return ONE_WIRE_ERROR;
    }

    if ( ONE_WIRE_SUCCESS != hal_one_wire_open( obj ) ) {
        return ONE_WIRE_ERROR;
    } else {
        return ONE_WIRE_SUCCESS;
    }
    */


    oneWire_set_pin(obj->data_pin);
    return ONE_WIRE_SUCCESS;     //return status 
}

//1-wire reset
int8_t one_wire_reset(one_wire_t *obj) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_reset( obj ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */


   if(oneWire_reset() == TRUE)     //function returns a 1 if device is present, 0 otherwise
   {
        return ONE_WIRE_SUCCESS;     //return status
   }
   return ONE_WIRE_ERROR;     //return status
}

//1-wire write operation
int8_t one_wire_write_byte(one_wire_t *obj, uint8_t *write_data_buffer, size_t write_data_length) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_write_byte( obj, write_data_buffer, write_data_length ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */


    for (uint16_t ii = 0 ; ii < write_data_length ; ii++)
    {
        oneWire_write(write_data_buffer[ii]);       //write rom bytes
    }
    return ONE_WIRE_SUCCESS;                        //return status
}

//1-wire read operation
int8_t one_wire_read_byte(one_wire_t *obj, uint8_t *read_data_buffer, size_t read_data_length) 
{
    //original from MikroE
    /* 
    if ( hal_one_wire_read_byte( obj, read_data_buffer, read_data_length ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */


    for (uint16_t ii = 0 ; ii < read_data_length; ii++)
    {
        read_data_buffer[ii] = oneWire_read();        //index pointer array and set to byte read
    }
    return ONE_WIRE_SUCCESS;     //return status
}

//read ROM of connected device
int8_t one_wire_read_rom(one_wire_t *obj, one_wire_rom_address_t *device_rom_address) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_read_rom( obj, device_rom_address ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */


    oneWire_write(ROM_MATCH);                           //wite Choose ROM cmd
    for (uint16_t ii = 0 ; ii < 8 ; ii++)               //loop for number of bytes (count)
    {
        device_rom_address->address[ii] = oneWire_read();        //index pointer array and set to byte read
    }
    return ONE_WIRE_SUCCESS;                            //return status
}

//skip read ROM
int8_t one_wire_skip_rom(one_wire_t *obj) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_skip_rom( obj ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */


    oneWire_write(ROM_SKIP);        //write Skip ROM cmd
    return ONE_WIRE_SUCCESS;        //return status
}

//MATCH ROM
int8_t one_wire_match_rom(one_wire_t *obj, one_wire_rom_address_t *device_rom_address)
{
    //original from MikroE
    /*
    if ( hal_one_wire_match_rom( obj, device_rom_address ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */


    oneWire_write(ROM_MATCH);                       //wite Choose ROM cmd
    for (uint16_t ii = 0 ; ii < 8 ; ii++)           //loop for number of bytes (count)
    {
        oneWire_write(device_rom_address->address[ii]);      //write rom bytes
    }
    return ONE_WIRE_SUCCESS;                        //return status
}

//search for first device on 1-wire bus
int8_t one_wire_search_first_device(one_wire_t *obj, one_wire_rom_address_t *one_wire_device_list) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_search_first_device( obj, one_wire_device_list ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */


    //reset the search state
    LastDiscrepancy = 0;
    LastDeviceFlag = FALSE;
    LastFamilyDiscrepancy = 0;

    //zero out the array for the ROM address
    for(uint8_t ii = 0; ii < 8; ii++) 
    {
        rom_num[ii] = 0x00;
    }

    if (oneWire_search(one_wire_device_list->address) == TRUE)
    {
        return ONE_WIRE_SUCCESS;     //return status
    }   
    return ONE_WIRE_ERROR;     //return status
}

//search for next device on 1-wire bus
int8_t one_wire_search_next_device(one_wire_t *obj, one_wire_rom_address_t *one_wire_device_list) 
{
    //original from MikroE
    /*
    if ( hal_one_wire_search_next_device( obj, one_wire_device_list ) ) {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
    */


   if (oneWire_search(one_wire_device_list->address) == TRUE)
    {
        return ONE_WIRE_SUCCESS;     //return status
    }
    return ONE_WIRE_ERROR;     //return status
}

//search device ROM
uint8_t oneWire_search(uint8_t *newAddr)
{
    //local variables
    uint8_t id_bit_number = 1;
    uint8_t last_zero = 0;
    uint8_t count = 0;
    uint8_t search_result = 0;
    uint8_t id_bit, cmp_id_bit;
    unsigned char rom_byte_mask = 1;
    unsigned char search_direction = 0;

    //if the last call was not the last one
    if (!LastDeviceFlag)
    {
        
        if (!oneWire_reset())       //1-Wire reset
        {
            //reset the search global variables
            LastDiscrepancy = 0;
            LastDeviceFlag = FALSE;
            LastFamilyDiscrepancy = 0;
            return FALSE;
        }

        oneWire_write(ROM_SEARCH);      //issue the search command

        // loop to do the search
        do
        {
            // read a bit and its complement
            id_bit = oneWire_read_bit();
            cmp_id_bit = oneWire_read_bit();

            // check for no devices on 1-wire
            if ((id_bit == 1) && (cmp_id_bit == 1))
            {
                break;      //break from while loop since no devies are present
            }
            else
            {
                // all devices coupled have 0 or 1
                if (id_bit != cmp_id_bit)
                {
                    search_direction = id_bit;  // bit write value for search
                }
                else
                {
                    // if this discrepancy if before the Last Discrepancy
                    // on a previous next then pick the same as last time
                    if (id_bit_number < LastDiscrepancy)
                    {
                        search_direction = ((rom_num[count] & rom_byte_mask) > 0);
                    }
                    else
                    {
                        // if equal to last pick 1, if not then pick 0
                        search_direction = (id_bit_number == LastDiscrepancy);
                    }

                    // if 0 was picked then record its position in LastZero
                    if (search_direction == 0)
                    {
                        last_zero = id_bit_number;

                        // check for Last discrepancy in family
                        if (last_zero < 9)
                        {
                            LastFamilyDiscrepancy = last_zero;
                        }
                    }
                }

                // set or clear the bit in the ROM byte count
                // with mask rom_byte_mask
                if (search_direction == 1)
                {
                  rom_num[count] |= rom_byte_mask;
                }
                else
                {
                  rom_num[count] &= ~rom_byte_mask;
                }

                // serial number search direction write bit
                oneWire_write_bit(search_direction);

                // increment the byte counter id_bit_number
                // and shift the mask rom_byte_mask
                id_bit_number++;
                rom_byte_mask <<= 1;

                // if the mask is 0 then go to new SerialNum byte count and reset mask
                if (rom_byte_mask == 0)
                {
                    count++;
                    rom_byte_mask = 1;
                }
            }
        }
        while(count < 8);  // loop until through all ROM bytes 0-7

        // if the search was successful then
        if (!(id_bit_number < 65))
        {
            // search successful so set LastDiscrepancy,LastDeviceFlag,search_result
            LastDiscrepancy = last_zero;

            // check for last device
            if (LastDiscrepancy == 0)
            {
                LastDeviceFlag = TRUE;
            }

            search_result = TRUE;
        }
    }

    // if no device found then reset counters so next 'search' will be like a first
    if (!search_result || !rom_num[0])
    {
        LastDiscrepancy = 0;
        LastDeviceFlag = FALSE;
        LastFamilyDiscrepancy = 0;
        search_result = FALSE;
    }

    for (int i = 0; i < 8; i++) 
    {
        newAddr[i] = rom_num[i];
    }
    
    return search_result;
}