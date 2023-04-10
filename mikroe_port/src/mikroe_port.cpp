/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/Erik-Home/Documents/GitHub/mikroe_port/mikroe_port/src/mikroe_port.ino"

#include "accurrent.h"
#include "eeprom7.h"
#include "temphum13.h"
#include "rs232.h"
#include "pwmdriver.h"
#include "current4.h"


void setup();
void loop();
void ACcurrent_main();
void eeprom7_main();
void temphum13_main();
void rs232_main();
void pwmdriver_main();
void current4_main();
#line 10 "/Users/Erik-Home/Documents/GitHub/mikroe_port/mikroe_port/src/mikroe_port.ino"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

//static tempdefs from libraries
static accurrent_t accurrent;   //from accurrent main.c
static eeprom7_t eeprom7;       //from eeprom7 main.c
static temphum13_t temphum13;   //from temphum13 main.c
static rs232_t rs232;           //from rs232 main.c
static pwmdriver_t pwmdriver;   //from pwmdriver main.c
static current4_t current4;     //from current4 main.c

//defines from rs232 main.c
#define PROCESS_RX_BUFFER_SIZE 500
#define RS232_TRANSMITTER

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
/*
  rs232_cfg_t rs232_cfg;
  rs232_cfg_setup( &rs232_cfg );
  RS232_MAP_MIKROBUS( rs232_cfg, MIKROBUS_1 );
  rs232_init( &rs232, &rs232_cfg );   //includes uart config
*/

  //from pwmdriver
/* 
  pwmdriver_cfg_t pwmdriver_cfg;
  pwmdriver_cfg_setup( &pwmdriver_cfg );
  PWMDRIVER_MAP_MIKROBUS( pwmdriver_cfg, MIKROBUS_1 );
  pwmdriver_init( &pwmdriver, &pwmdriver_cfg );   //inlcudes pwm default config
  pwmdriver_set_duty_cycle( &pwmdriver, 0.0 );
  pwmdriver_pwm_start( &pwmdriver );
*/  

  //from current4
  current4_cfg_t current4_cfg;
  current4_cfg_setup( &current4_cfg );
  CURRENT4_MAP_MIKROBUS( current4_cfg, MIKROBUS_1 );
  current4_init( &current4, &current4_cfg );
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

//rs232_main();
//delay(500);

//pwmdriver_main();
//delay(1000);

current4_main();
delay(5000);


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

//rs232 main.c example
void rs232_main()
{
  static int32_t rsp_size;
  static char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
  char message[ ] = "MikroE";


  rs232_generic_write( &rs232, message, strlen( message ) );
  Delay_ms( 1000 );
}

//pwm testing
void pwmdriver_main()
{
  static int8_t duty_cnt = 1;
  static int8_t duty_inc = 1;
  float duty = duty_cnt / 10.0;



  pwmdriver_set_duty_cycle ( &pwmdriver, duty );
  pwmdriver_pwm_start( &pwmdriver );    //must include to pass new duty cycle value
  Delay_ms( 500 );
    
  if (10 == duty_cnt) 
  {
    duty_inc = -1;
  }
  else if (0 == duty_cnt) 
  {
    duty_inc = 1;
  }
  duty_cnt += duty_inc;

}

// current4 main.c example
void current4_main()
{
  float current4_load_voltage = 0;
  current4_read_an_pin_voltage ( &current4, &current4_load_voltage );
  Serial.print("voltage = ");
	Serial.print(current4_load_voltage, 2); 
	Serial.println("");

}