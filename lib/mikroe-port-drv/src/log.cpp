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

#include "log.h"

//extern variables
//extern uint8_t loggerBus;

//global variables
static uint32_t global_baud;        //baud rate variable
static LogLevel global_level;       //logger level variable
uint8_t loggerBus;                  //global variable for which bus is selected for logger

//loggerBus = TRUE;

//#if for which logger bus will be used
#if loggerBus
    Serial1LogHandler logHandler(global_baud, global_level);      //select serial1 logger
#else
    SerialLogHandler logHandler(global_level);       //select serial (USB) logger
#endif

//initializes log driver
void log_init (log_t *log, log_cfg_t *cfg)
{
    global_baud = cfg->baud;        //set baud rate global variable to function parameter 
    
    //switch on the incoming logger level to map to particle equivalent
    switch (cfg->level)                             
    {
        case LOG_LEVEL_DEBUG:                       //log level input 
                global_level = LOG_LEVEL_TRACE;     //set incoming level to particle equivalent
            break;                                  //break from switch loop

        case 0x01:                                  //info level input, must use raw value due to conflict 
                global_level = LOG_LEVEL_INFO;      //set incoming level to particle equivalent
            break;                                  //break from switch loop

        case LOG_LEVEL_WARNING:                     //warning level input
                global_level = LOG_LEVEL_WARN;      //set incoming level to particle equivalent
            break;                                  //break from switch loop

        case 0x03:                                  //error level input, must use raw value due to conflict
                global_level = LOG_LEVEL_ERROR;     //set incoming level to particle equivalent
            break;                                  //break from switch loop
        
        case LOG_LEVEL_FATAL:                       //fatal level input
                global_level = LOG_LEVEL_ERROR;     //set incoming level to particle equivalent
            break;                                  //break from switch loop

        default:                                    //unknown input, turn off logger  
                global_level = LOG_LEVEL_NONE;      //set incoming level to particle equivalent
            break;                                  //break from switch loop
    }
}

//printf logger function
void log_printf (log_t *log, const char *buffer,...)
{
    Log.printf(buffer);     //use particle logging function
}

//discard input/output logger buffers
void log_clear (log_t *log)
{
    if(loggerBus == FALSE)      //USB (serial) selected
    {
        Serial.flush();         //flush buffers
    }
    else                        //serial1 selected
    {
        Serial1.flush();        //flush buffers
    }
}

//read bytes from logger buffer
int8_t log_read (log_t *log, uint8_t *rx_data_buf, uint8_t max_len)
{
    if(loggerBus == FALSE)                                  //USB (serial) selected
    {
        if (Serial.available() > 0)                         //if uart is available 
        {
            for (uint8_t ii = 0; ii < max_len; ii++)        //for loop for iterating over array
            {
                rx_data_buf[ii] = Serial.read();            //set pointer parameter to byte read from uart
            }
            return max_len;                                 //return # of bytes read
        }
        return -1;                                          //return error
    }
    else                                                    //serial1 selected
    {
        if (Serial1.available() > 0)                        //if uart is available 
        {
            for (uint8_t ii = 0; ii < max_len; ii++)        //for loop for iterating over array
            {
                rx_data_buf[ii] = Serial1.read();           //set pointer parameter to byte read from uart
            }
            return max_len;                                 //return # of bytes read
        }
        return -1;                                          //return error
    }
}

//logger INFO level printf function
void log_info (log_t *log, const char *buffer,...)
{
    Log.info(buffer);       //use particle logging function
}

//logger ERROR level printf function
void log_error (log_t *log, const char *buffer,...)
{
    Log.error(buffer);      //use particle logging function
}

//logger FATAL level printf function
void log_fatal (log_t *log, const char *buffer,...)
{
    #warning Particle Logger does not have a Fatal level, error level is used instead
    Log.error(buffer);      //use particle logging function
}

//logger DEBUG level printf function
void log_debug (log_t *log, const char *buffer,...)//
{
    Log.trace(buffer);      //use particle logging function
}

//logger WARNING level printf function
void log_warning (log_t *log, const char *buffer,...)
{
    Log.warn(buffer);
}

//logger printf function with variable prefix
void log_log (log_t *log, char * prefix, const char *buffer, ...)
{
    Logger log1(prefix);        //use particle logging function
    log1.trace(buffer);         //use particle logging function
}