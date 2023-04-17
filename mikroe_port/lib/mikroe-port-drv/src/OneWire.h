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

#ifndef OneWire_h
#define OneWire_h

#include <inttypes.h>
#include "application.h"



//1-wire low-level functions
  void oneWire_set_pin(uint16_t pin);
  uint8_t oneWire_reset();
  void oneWire_write_bit(uint8_t value);
  uint8_t oneWire_read_bit();
  void oneWire_write(uint8_t value, bool pulse = 0);
  uint8_t oneWire_read();

  //todo, remove
  /*
  void oneWire_depower();

//1-wire ROM functions
  void oneWire_rom_read (uint8_t *buffer);
  void oneWire_rom_select(const uint8_t *buffer);
  void oneWire_rom_skip();

//1-wire transaction functions
  
  void oneWire_write_bytes(const uint8_t *buffer, uint16_t count, bool pulse = 0);
  
  void oneWire_read_bytes(uint8_t *buf, uint16_t count);

//1-wire search functions
  void oneWire_reset_search();
  void oneWire_target_search(uint8_t family_code);
  uint8_t oneWire_search(uint8_t *newAddr);

//1-wire CRC functions
  static uint8_t oneWire_crc8(uint8_t *addr, uint8_t len);
  static uint16_t oneWire_crc16(const uint8_t* input, uint16_t len, uint16_t crc = 0);
  static bool oneWire_check_crc16(const uint8_t* input, uint16_t len, const uint8_t* inverted_crc, uint16_t crc = 0);
*/
    
#endif // OneWire_h