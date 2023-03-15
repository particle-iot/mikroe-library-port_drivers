/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/Erik-Home/Documents/GitHub/mikroe_port/mikroe_port/src/mikroe_port.ino"
/*
 * Project mikroe_port
 * Description:
 * Author:
 * Date:
 */

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

void setup();
void loop();
#line 12 "/Users/Erik-Home/Documents/GitHub/mikroe_port/mikroe_port/src/mikroe_port.ino"
#define AMBIENT7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( MIKROBUS_1, MIKROBUS_1_AN )

  typedef struct
{
 
    uint8_t an_pin;

} ambient7_cfg_t;

//typedef uint8_t bus_selected;
//uint8_t foobar = bus_selected;

mikro_bus s1;
uint8_t foobar = s1.bus_selected;



// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  digital_out_init(D19, OUTPUT);
  digital_in_init(D18,INPUT);
  Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  int value = 0;

  digital_out_toggle(D19);
  delayMicroseconds(500);
  value = digital_in_read(D18);

  Serial.print("Input Value: ");
	Serial.print(value, DEC); 
	Serial.println("");

  delay(1s);


   Serial.print("bus selected: ");
	//Serial.print(temp, DEC); 
  Serial.print(foobar, DEC); 
	Serial.println("");


}