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

#ifndef _LOG_H_
#define _LOG_H_

//#include "drv_uart.h"
#include "mikro_port.h"
#include <stdarg.h>

//external variables
extern uint8_t loggerBus;
//uint8_t loggerBus;

//enum for logger level values
typedef enum
{
    LOG_LEVEL_DEBUG   = 0x00,
    //LOG_LEVEL_INFO    = 0x01,     //already defined in DVOS and creates conflict
    LOG_LEVEL_WARNING = 0x02,
    //LOG_LEVEL_ERROR   = 0x03,     //already defined in DVOS and creates conflict
    LOG_LEVEL_FATAL   = 0x04
} log_level_t;

//logger context structure
typedef struct
{
    //uart_t uart;
    log_level_t log_level;
} log_t;

//logger configuration structure
typedef struct
{
    hal_pin_name_t rx_pin;
    hal_pin_name_t tx_pin;
    uint32_t baud;
    log_level_t level;
} log_cfg_t;

//#define for log map to USB UART
#define LOG_MAP_USB_UART(cfg) \
    cfg.rx_pin = HAL_PIN_NC; \
    cfg.tx_pin = HAL_PIN_NC; \
    cfg.baud = 115200; \
    cfg.level = LOG_LEVEL_DEBUG; \
    loggerBus = FALSE;      //set bus to Serial (USB)      
    

//#define for log map to mikrobus config
#define LOG_MAP_MIKROBUS(cfg, mikrobus) \
    cfg.rx_pin = MIKROBUS(mikrobus, MIKROBUS_RX); \
    cfg.tx_pin = MIKROBUS(mikrobus, MIKROBUS_TX); \
    cfg.baud = 9600; \
    cfg.level = LOG_LEVEL_DEBUG; \
    loggerBus = TRUE;       //set bus to serial1 (RX,TX)     
    

//logger functions
void log_init ( log_t *log, log_cfg_t *cfg );
void log_printf ( log_t *log, const char *buffer,... );
void log_clear ( log_t *log );
int8_t log_read ( log_t *log, uint8_t *rx_data_buf, uint8_t max_len );
void log_info ( log_t *log, const char *buffer,... );
void log_error ( log_t *log, const char *buffer,... );
void log_fatal ( log_t *log, const char *buffer,... );
void log_debug ( log_t *log, const char *buffer,... );
void log_warning ( log_t *log, const char *buffer,... );
void log_log ( log_t *log, char *prefix, const char *buffer, ... );

#endif // _LOG_H_