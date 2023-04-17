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

#include "OneWire.h"
#include "application.h"

//global variables 
uint16_t _pin;
/*
unsigned char rom_num[8];
uint8_t LastDiscrepancy;
uint8_t LastFamilyDiscrepancy;
uint8_t LastDeviceFlag;
*/

//sets pin for 1-wire interface
void oneWire_set_pin(uint16_t pin)
{
    _pin = pin;                  //set global variable equal to pin
    pinMode(_pin, INPUT);        //set pin as input, hal calls pin as output during low-level functions
}

//1-wire reset
uint8_t oneWire_reset(void)
{
    uint8_t temp;                       //local variable for the temp wire value
    uint8_t count = 250;                //local variable for the timeout counter before reset

    noInterrupts();                     //turn off interrupts
    HAL_Pin_Mode(_pin, INPUT);          //set pin as input, let signal float
    interrupts();                       //turn on interrupts
    do 
    {
        if (count <= 0)                 //check for counter timeout   
        {
            return FALSE;               //return error
        }
        count--;                        //decrement the count
        delayMicroseconds(1);           //delay       
    }   while (!pinReadFast(_pin));     //wait until wire goes high before reset sequence

    noInterrupts();                     //turn off interrupts
    pinResetFast(_pin);                 //set pin low
    HAL_Pin_Mode(_pin, OUTPUT);         //set pin as output
    interrupts();                       //turn on interrupts
    delayMicroseconds(512);             //delay for tRSTL = 512us

    noInterrupts();                     //turn off interrupts
    HAL_Pin_Mode(_pin, INPUT);          //set pin as input, let signal float
    delayMicroseconds(70);              //delay
    temp =! pinReadFast(_pin);          //read value, test for shorts/interrupts
    interrupts();                       //turn on interrupts

    delayMicroseconds(442);             //delay for remainder of period, tFILL = 512us
    return temp;                        //return wire value
}

//write a bit
void oneWire_write_bit(uint8_t value)
{
    if ((value & 1) == 1)               //write logic 1
    {
        noInterrupts();                 //turn off interrupts
        pinResetFast(_pin);             //set pin low
        HAL_Pin_Mode(_pin, OUTPUT);     //set pin as output
        delayMicroseconds(8);          //dealy for tLOW1

        HAL_Pin_Mode(_pin, INPUT);      //set pin as input, let signal float
        interrupts();                   //turn on interrupts

        delayMicroseconds(52);          //delay for remainder of tSLOT
    } 
    else                                //write logic 0
    {
        noInterrupts();                 //turn off interrupts
        pinResetFast(_pin);             //set pin low
        HAL_Pin_Mode(_pin, OUTPUT);     //set pin as output
        delayMicroseconds(57);          //delay for tLOW0

        HAL_Pin_Mode(_pin, INPUT);      //set pin as input, let signal float
        interrupts();                   //turn on interrupts

        delayMicroseconds(3);           //delay for remainder of tSLOT
    }
}

//read a bit
uint8_t oneWire_read_bit()
{
    uint8_t temp;                   //local variable for the temp bit value

    noInterrupts();                 //turn off interrupts
    pinResetFast(_pin);             //set pin low
    HAL_Pin_Mode(_pin, OUTPUT);     //set pin as output
    delayMicroseconds(8);           //delay for tLOW1

    HAL_Pin_Mode(_pin, INPUT);      //set pin as input, let signal float
    delayMicroseconds(3);           //delay for tDSO
    temp = pinReadFast(_pin);       //read bit value
    interrupts();                   //turn on interrupts

    delayMicroseconds(49);          //delay for remainder of tSLOT

    return temp;                    //return temp bit value
}

//write a byte
void oneWire_write(uint8_t value, bool pulse) 
{
    for (uint8_t bitMask = 0x01; bitMask; bitMask <<= 1)        //for loop for bit shifting 
    {
        if((bitMask & value) == TRUE)       //if bit is a logic 1
        {
            oneWire_write_bit(TRUE);        //write logic 1
        }
        else                                //value is a logic 0
        {
            oneWire_write_bit(FALSE);       //write logic 0
        }
    }

    //wire may need to remain high after write, ex write cycle of eeprom 
    if (pulse == TRUE)                  
    {
        noInterrupts();                 //turn off interrupts
        pinSetFast(_pin);               //set pin high
        HAL_Pin_Mode(_pin, OUTPUT);     //set pin as output
        interrupts();                   //turn on interrupts        
    }
}

//read a byte
uint8_t oneWire_read() 
{
    uint8_t temp = 0;                                           //local variable for the various bit values
    for (uint8_t bitMask = 0x01; bitMask; bitMask <<= 1)        //for loop for bit shifting
    {
        if (oneWire_read_bit() == TRUE)                         //if bit = logic 1 
        {
            temp |= bitMask;                                    //or bitmask with temp variable
        }
    }
    return temp;                                                //return byte read
}

//todo, remove
//de-power 1-wire device, low-level
/*
void oneWire_depower()
{
    noInterrupts();                 //turn off interrupts
    HAL_Pin_Mode(_pin, INPUT);      //set pin as input, let signal float
    interrupts();                   //turn on interrupts
}

//read ROM 
void oneWire_rom_read (uint8_t *buffer)
{
    oneWire_write(ROM_MATCH);           //wite Choose ROM cmd
    oneWire_read_bytes(buffer, 8);      //read 8 ROM bytes
}

//select ROM
void oneWire_rom_select(const uint8_t *buffer)
{
    oneWire_write(ROM_MATCH);           //wite Choose ROM cmd
    oneWire_write_bytes(buffer, 8);        //write rom bytes

}

//skip ROM
void oneWire_rom_skip()
{
    oneWire_write(ROM_SKIP);        //write Skip ROM cmd
}


//write multiple bytes
void oneWire_write_bytes(const uint8_t *buffer, uint16_t count, bool pulse) 
{
    for (uint16_t ii = 0 ; ii < count ; ii++)       //loop for number of bytes (count) to be written
    {
        oneWire_write(buffer[ii]);                  //write bytes by indexing pointer array
    }     

    //wire may need to remain high after write, ex write cycle of eeprom
    if (pulse == TRUE)                  
    {
        noInterrupts();                 //turn off interrupts
        pinSetFast(_pin);               //set pin high
        HAL_Pin_Mode(_pin, OUTPUT);     //set pin as output
        interrupts();                   //turn on interrupts
    }
}

//read mutliple bytes
void oneWire_read_bytes(uint8_t *buffer, uint16_t count) 
{
    for (uint16_t ii = 0 ; ii < count ; ii++)       //loop for number of bytes (count)
    {
        buffer[ii] = oneWire_read();                //index pointer array and set to byte read
    }
}


//reset search for device
void oneWire_reset_search()
{
    // reset the search state
    LastDiscrepancy = 0;
    LastDeviceFlag = FALSE;
    LastFamilyDiscrepancy = 0;

    //zero out the array for the ROM address
    for(uint8_t ii = 0; ii < 8; ii++) 
    {
        rom_num[ii] = 0x00;
    }
}


//search for target device
void oneWire_target_search(uint8_t family_code)
{

   rom_num[0] = family_code;

   for (uint8_t i = 1; i < 8; i++)
   {
      rom_num[i] = 0;
   }

   LastDiscrepancy = 64;
   LastFamilyDiscrepancy = 0;
   LastDeviceFlag = FALSE;
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

        //todo, move to #define value
        oneWire_write(0xF0);      //issue the search command

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
*/

//todo, remove
/*
//calculate 8-bit CRC
uint8_t oneWire_crc8( uint8_t *addr, uint8_t len)
{
    uint8_t crc = 0;

    while (len--) 
    {
        uint8_t inbyte = *addr++;
        for (uint8_t i = 8; i; i--) 
        {
            uint8_t mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix) crc ^= 0x8C;
                inbyte >>= 1;
        }
    }

    return crc;
}

//check 16-bit CRC
uint16_t oneWire_crc16(const uint8_t* input, uint16_t len, uint16_t crc)
{
    static const uint8_t oddparity[16] =
        { 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };

    for (uint16_t i = 0 ; i < len ; i++) 
    {
        // Even though we're just copying a byte from the input,
        // we'll be doing 16-bit computation with it.
        uint16_t cdata = input[i];
        cdata = (cdata ^ crc) & 0xff;
        crc >>= 8;

        if (oddparity[cdata & 0x0F] ^ oddparity[cdata >> 4])
        {
            crc ^= 0xC001;
        }

        cdata <<= 6;
        crc ^= cdata;
        cdata <<= 1;
        crc ^= cdata;
    }

    return crc;
}

//calculate 16-bit CRC
bool oneWire_check_crc16(const uint8_t* input, uint16_t len, const uint8_t* inverted_crc, uint16_t crc)
{
    crc = ~oneWire_crc16(input, len, crc);
    return (crc & 0xFF) == inverted_crc[0] && (crc >> 8) == inverted_crc[1];
}
*/