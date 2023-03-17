/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/Erik-Home/Documents/GitHub/mikroe_port/mikroe_port/src/mikroe_port.ino"
/**
 ******************************************************************************
 * @authors Erik Fasnacht
 * @version V1.0.0
 * @date    17-Mar-2023
 * @brief   ino file for CLICK library testing
 ******************************************************************************
 **/

#include "accurrent.h"
#include "eeprom7.h"

void setup();
void loop();
void ACcurrent_main();
void eeprom7_main();
#line 13 "/Users/Erik-Home/Documents/GitHub/mikroe_port/mikroe_port/src/mikroe_port.ino"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

//from accurrent main.c
static accurrent_t accurrent;

//from eeprom7 main.c
static eeprom7_t eeprom7;

// setup() runs once, when the device is first turned on.
void setup() 
{

  Serial.begin(9600);
  Particle.disconnect();
  WiFi.off();

//from ac current
  accurrent_cfg_t cfg;
  accurrent_cfg_setup( &cfg ); 
  ACCURRENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
  accurrent_init( &accurrent, &cfg );

//from eeprom7
  eeprom7_cfg_t eeprom7_cfg;  //Click config object
  eeprom7_cfg_setup( &eeprom7_cfg );
  EEPROM7_MAP_MIKROBUS( eeprom7_cfg, MIKROBUS_2 );
  eeprom7_init( &eeprom7, &eeprom7_cfg );
  eeprom7_default_cfg ( &eeprom7 );

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

  ACcurrent_main();
  delay(1s);

  eeprom7_main();
  delay(3s);


}

void ACcurrent_main()
{
  float ac_current;
  ac_current = accurrent_get_ma( &accurrent );
  Serial.print("value: ");
	Serial.print(ac_current, DEC); 
	Serial.println("");
}

void eeprom7_main()
{
  static uint8_t demo_data[ 9 ] = { 'm', 'i', 'k', 'r', 'o', 'E', 13 ,10 , 0 };
  static uint8_t read_data[ 9 ];
  static uint8_t check_status;
  
  //wren 
  eeprom7_send_cmd( &eeprom7, EEPROM7_OPCODE_STATUS_WREN );
  delay(100);
  
  //write data
  eeprom7_write_memory( &eeprom7, 0x00001234, &demo_data[ 0 ], 9 );
  delay(100);

  //serial print data
  Serial.print(" > Write data: ");
  for (uint8_t ii = 0; ii < 9; ii++)
  {
    Serial.print(demo_data[ii], HEX); 
  }
	Serial.println("");

  //polling routine
  while ( eeprom7_is_device_ready( &eeprom7 ) == EEPROM7_DEVICE_IS_READY ) {
      check_status = eeprom7_send_cmd( &eeprom7, EEPROM7_OPCODE_STATUS_WRBP );
      delay(1);
  }

  //read data 
  eeprom7_read_memory( &eeprom7, 0x00001234, &read_data[ 0 ], 9 );
  delay(100);

  //serial print data
  Serial.print(" > Read data: ");
  for (uint8_t ii = 0; ii < 9; ii++)
  {
    Serial.print(read_data[ii], HEX); 
  }
	Serial.println("");

}

