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

//initializes log driver
void log_init (log_t *log, log_cfg_t *cfg)
{
    //local variables
    LogLevel tempLevel;              //log level variable

    switch (cfg->level)                             //switch on the incoming logger level
    {
        case LOG_LEVEL_DEBUG:                       //log level input 
                tempLevel = LOG_LEVEL_TRACE;        //set incoming level to particle equivalent
            break;                                  //break from switch loop

        case LOG_LEVEL_INFO:                        //info level input 
                tempLevel = LOG_LEVEL_INFO;         //set incoming level to particle equivalent
            break;                                  //break from switch loop

        case LOG_LEVEL_WARNING:                     //warning level input
                tempLevel = LOG_LEVEL_WARN;         //set incoming level to particle equivalent
            break;                                  //break from switch loop

        case LOG_LEVEL_ERROR:                       //error level input
                tempLevel = LOG_LEVEL_ERROR;        //set incoming level to particle equivalent
            break;                                  //break from switch loop
        
        case LOG_LEVEL_FATAL:                       //fatal level input
                tempLevel = LOG_LEVEL_PANIC;        //set incoming level to particle equivalent
            break;                                  //break from switch loop

        default:                                    //unknown input, turn off logger  
                tempLevel = LOG_LEVEL_NONE;         //set incoming level to particle equivalent
            break;                                  //break from switch loop
    }

    if(loggerBus == FALSE)      //USB (serial) selected
    {
        SerialLogHandler logHandler(115200, tempLevel);      //pass 115200 baud as value is ignored and level
    }
    else        //serial1 selected
    {
        Serial1LogHandler logHandler(cfg->baud, tempLevel);     //pass baud rate and level
    }
}

//printf logger function
//void log_printf (log_t *log, const code char * __generic_ptr f,...)
//void log_printf (log_t *log, const char * __generic_ptr f,...)
void log_printf (log_t *log, const char *buffer,...)
{
    if(loggerBus == FALSE)      //USB (serial) selected
    {
        Serial.printf(buffer);     //check to make sure all bytes were written
    }
    else        //serial1 selected
    {
        Serial1.printf(buffer);     //check to make sure all bytes were written
    }
}

//discard input/output logger buffers
void log_clear (log_t *log)
{
    if(loggerBus == FALSE)      //USB (serial) selected
    {
        Serial.flush();        //flush buffers
    }
    else        //serial1 selected
    {
        Serial1.flush();        //flush buffers
    }
}

//read bytes from logger buffer
int8_t log_read (log_t *log, uint8_t *rx_data_buf, uint8_t max_len)
{
    if(loggerBus == FALSE)      //USB (serial) selected
    {
        if (Serial.available() > 0)                         //if uart is available 
        {
            for (uint8_t ii = 0; ii < max_len; ii++)       //for loop for iterating over array
            {
                rx_data_buf[ii] = Serial.read();            //set pointer parameter to byte read from uart
            }
            return max_len;                                 //return # of bytes read
        }
        return UART_ERROR;   
    }
    else        //serial1 selected
    {
        if (Serial1.available() > 0)                         //if uart is available 
        {
            for (uint8_t ii = 0; ii < max_len; ii++)       //for loop for iterating over array
            {
                rx_data_buf[ii] = Serial1.read();            //set pointer parameter to byte read from uart
            }
            return max_len;                                 //return # of bytes read
        }
        return UART_ERROR;
    }
    //todo return number of bytes read or -1 if error occurs
    return TRUE;
}

//logger INFO level printf function
//void log_info (log_t *log, const code char * __generic_ptr f,...)
//void log_info (log_t *log, const char * __generic_ptr f,...)
void log_info (log_t *log, const char *buffer,...)
{
    Log.info(buffer);
}

//logger ERROR level printf function
//void log_error (log_t *log, const code char * __generic_ptr f,...)
//void log_error (log_t *log, const char * __generic_ptr f,...)
void log_error (log_t *log, const char *buffer,...)
{
    Log.error(buffer);
}

//logger FATAL level printf function
//void log_fatal (log_t *log, const code char * __generic_ptr f,...)
//void log_fatal (log_t *log, const char * __generic_ptr f,...)
void log_fatal (log_t *log, const char *buffer,...)
{
    #warning Particle does not have a Fatal level, error level is used instead
    Log.error(buffer);
}

//logger DEBUG level printf function
//void log_debug (log_t *log, const code char * __generic_ptr f,...)
//void log_debug (log_t *log, const char * __generic_ptr f,...)
void log_debug (log_t *log, const char *buffer,...)//
{
    Log.trace(buffer);
}

//logger WARNING level printf function
//void log_warning (log_t *log, const code char * __generic_ptr f,...)
//void log_warning (log_t *log, const char * __generic_ptr f,...)
void log_warning (log_t *log, const char *buffer,...)
{
    Log.warn(buffer);
}

//logger printf function with variable prefix
//void log_log (log_t *log, char * prefix, const code char * __generic_ptr f, ...)
//void log_log (log_t *log, char * prefix, const char * __generic_ptr f, ...)
void log_log (log_t *log, char * prefix, const char *buffer, ...)
{
    Logger log1(prefix);
    log1.trace(buffer);
}