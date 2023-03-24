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
#include "temphum13.h"
#include "rs232.h"



void setup();
void loop();
void ACcurrent_main();
void eeprom7_main();
void temphum13_main();
void rs232_main();
#line 17 "/Users/Erik-Home/Documents/GitHub/mikroe_port/mikroe_port/src/mikroe_port.ino"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

//static tempdefs from libraries
static accurrent_t accurrent;   //from accurrent main.c
static eeprom7_t eeprom7;       //from eeprom7 main.c
static temphum13_t temphum13;   //from temphum13 main.c
static rs232_t rs232;           //from rs232 main.c

//defines from rs232 main.c
#define PROCESS_RX_BUFFER_SIZE 500
#define RS232_TRANSMITTER

//variables from rs232 main.c


void setup() 
{

  Serial.begin(9600);

  Particle.disconnect();
  WiFi.off();

  //from ac current
  /*
  accurrent_cfg_t accurrent_cfg;
  accurrent_cfg_setup( &accurrent_cfg ); 
  ACCURRENT_MAP_MIKROBUS( accurrent_cfg, MIKROBUS_1 );
  accurrent_init( &accurrent, &accurrent_cfg );
  */

  //from eeprom7
  /*
  eeprom7_cfg_t eeprom7_cfg;  //Click config object
  eeprom7_cfg_setup( &eeprom7_cfg );
  EEPROM7_MAP_MIKROBUS( eeprom7_cfg, MIKROBUS_2 );
  eeprom7_init( &eeprom7, &eeprom7_cfg );
  eeprom7_default_cfg ( &eeprom7 );
  */

  //from temphum13
  temphum13_cfg_t temphum13_cfg;
  temphum13_cfg_setup( &temphum13_cfg );
  TEMPHUM13_MAP_MIKROBUS( temphum13_cfg, MIKROBUS_2 );
  temphum13_init( &temphum13, &temphum13_cfg );   
  temphum13_default_cfg( &temphum13 );

  //from rs232
  rs232_cfg_t rs232_cfg;
  rs232_cfg_setup( &rs232_cfg );
  RS232_MAP_MIKROBUS( rs232_cfg, MIKROBUS_1 );
  rs232_init( &rs232, &rs232_cfg );   //includes uart config

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

//  ACcurrent_main();
//  delay(1s);

//commented out as BUS2 is used by temphum13
//  eeprom7_main();
//  delay(3s);

//  temphum13_main();
//  delay (500);

rs232_main();
delay(500);


}

//accurrent main.c example
void ACcurrent_main()
{
  float ac_current;
  ac_current = accurrent_get_ma( &accurrent );
  Serial.print("Current value = ");
	Serial.print(ac_current, DEC); 
	Serial.println("");
}

//eeprom7 main.c example
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

//temphum13 main.c example
void temphum13_main()
{
  static float temperature;
  static float humidity;

  temperature = temphum13_get_temperature( &temphum13 );
  humidity = temphum13_get_humidity( &temphum13 );
    
  if ( temperature != 65536.0 )
  {
    Serial.print("Temp in Celcuis = ");
	  Serial.print(temperature, DEC); 
	  Serial.println("");
  }

  if ( humidity != 65536.0 )
  {       
    Serial.print("Relative Humidity = ");
	  Serial.print(humidity, DEC); 
	  Serial.println("");
  } 
}

/*
//uart test
void uart_test()
{
  
  uart_read(NULL,rx_message, 1);
  
  if(rx_message[0] == tx_AA[0])
  {
    Serial.print(" AA message ACK'd, data =  ");
    Serial.print(rx_message[0],HEX); 
	  Serial.println("");
    rx_message[0] = {0x00};
    delay(1000);
    uart_println(NULL, tx_55);
  }
  else if(rx_message[0] == tx_55[0])
  {
    Serial.print(" 55 message ACK'd, data =  ");
    Serial.print(rx_message[0],HEX); 
	  Serial.println("");
    rx_message[0] = {0x00};
    delay(1000);
    uart_println(NULL, tx_AA);
  }
  else
  {
    Serial.print("Error, data =  ");
    Serial.print(rx_message[0],HEX); 
	  Serial.println("");
   //uart_write(NULL, tx_AA, 1);
  }
}
*/

//rs232 m,ain.c example
void rs232_main()
{
  static int32_t rsp_size;
  static char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
  char message[ ] = "MikroE";


  rs232_generic_write( &rs232, message, strlen( message ) );
  Delay_ms( 1000 );

}