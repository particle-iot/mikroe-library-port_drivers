/**
 ******************************************************************************
 * @file    drv_spi_master.h
 * @authors Erik Fasnacht
 * @version V1.0.0
 * @date    16-Mar-2023
 * @brief   SPI Master driver layer to interface with MikroE CLICK libraries
 ******************************************************************************
 **/

#ifndef _DRV_SPI_MASTER_H_
#define _DRV_SPI_MASTER_H_

#include "mikro_pins.h"

//struct for SPI configuration
typedef struct
{
    uint8_t         default_write_data;     //SPI Master default write data
    uint8_t         sck;                    //SCK pin
    uint8_t         miso;                   //MISO pin
    uint8_t         mosi;                   //MOSI pin
    uint32_t        speed;                  //SPI clock speed
    uint8_t         mode;                   //SPI mode
} spi_master_config_t;

//struc for spi master configuration
typedef struct
{
    spi_master_config_t config; //SPI Master Driver configuration structure
} spi_master_t;

//added for library port compatibility
typedef enum {
    SPI_MASTER_MODE_0 = 0,                          //SPI MODE 0
    SPI_MASTER_MODE_1,                              //SPI MODE 1
    SPI_MASTER_MODE_2,                              //SPI MODE 2
    SPI_MASTER_MODE_3,                              //SPI MODE 3
    SPI_MASTER_MODE_DEFAULT = SPI_MASTER_MODE_0     //Default SPI mode - MODE 0
} spi_master_mode_t;

//added for library port compatibility
typedef enum
{
    SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW = 0,                                             //Chip Select Polarity - Active Low
    SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH,                                                //Chip Select Polarity - Active High
    SPI_MASTER_CHIP_SELECT_DEFAULT_POLARITY = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW        //Chip Select Default Polarity - Active Low
} spi_master_chip_select_polarity_t;

//added for library port compatibility
typedef enum
{
    SPI_MASTER_SUCCESS = 0, /*!< Success. */
    SPI_MASTER_ERROR = (-1) /*!< Error. */
} spi_master_err_t;

void spi_master_configure_default(spi_master_config_t *config);                                                                                                              //Configures #spi_master_config_t structure to default initialization values
int8_t spi_master_open(spi_master_t *obj, spi_master_config_t *config);                                                                                                      //Opens the SPI Master driver object on selected pins
void spi_master_select_device(uint8_t chip_select);                                                                                                                 //Sets digital output individual slave pin to logic 0
void spi_master_deselect_device(uint8_t chip_select);                                                                                                               //Sets digital output individual slave pin to logic 1
void spi_master_set_chip_select_polarity(uint8_t polarity);                                                                                                         //sets SPI Master chip select polarity either to active low or active high
int8_t spi_master_set_speed(spi_master_t *obj, uint32_t speed);                                                                                                     //Sets SPI Master module speed to passed value if possible
int8_t spi_master_set_mode(spi_master_t *obj, uint8_t mode);                                                                                                        //Sets SPI Master module mode to passed value if possible
int8_t spi_master_set_default_write_data(spi_master_t *obj, uint8_t default_write_data);                                                                            //Default write data is sent by driver when the data transmit buffer is shorter than data receive buffer
int8_t spi_master_write(spi_master_t *obj, uint8_t *write_data_buffer, size_t write_data_length);                                                                   //Writes byte to SPI bus in blocking mode                                        
int8_t spi_master_read(spi_master_t *obj, uint8_t *read_data_buffer, size_t read_data_length);                                                                      //Reads byte from SPI bus in blocking mode                                             
int8_t spi_master_write_then_read(spi_master_t *obj, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data);     //Writes a sequence of bytes to SPI bus, followed by a corresponding read                                                                                      
void spi_master_close(spi_master_t *obj);                                                                                                                           //Closes SPI Master Driver context object









/**
 * @brief Configure SPI Master configuration structure.
 * @details Configures #spi_master_config_t structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config SPI Master driver configuration settings.
 * See #spi_master_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function                 | Default value             |
 * -------------------------|---------------------------|
 * SPI SCK pin              | 0xFFFFFFFF (invalid pin)  |
 * SPI MISO pin             | 0xFFFFFFFF (invalid pin)  |
 * SPI MOSI pin             | 0xFFFFFFFF (invalid pin)  |
 * SPI Speed                | 100KHz                    |
 * SPI mode                 | 0                         |
 * SPI default write data   | 0                         |
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // SPI Master configuration structure.
 *   spi_master_config_t spi_master_config;
 *
 *   // Populate structure to default init values.
 *   spi_master_configure_default( &spi_master_config );
 * @endcode
 */
//void spi_master_configure_default( spi_master_config_t *config );

/**
 * @brief Open the SPI Master driver object on selected pins.
 * @details Opens the SPI Master driver object on selected pins.
 * Allocates memory and pin for specified object.
 * @param[in] obj SPI Master driver object.
 * See #spi_master_t structure definition for detailed explanation.
 * @param[in] config SPI Master configuration structure.
 * See #spi_master_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #spi_master_err_t, which is size dependant on the architecture.
 * @note This function needs to be called before other driver functions.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // SPI driver context structure.
 *   spi_master_t spi_master;
 *
 *   // SPI Master configuration structure.
 *   spi_master_config_t  spi_master_config;
 *
 *   // Populate config structure.
 *   spi_master_configure_default( &spi_master_config );
 *
 *   // Specify desired SPI Serial Clock pin.
 *   spi_master_config.sck   = MIKROBUS_1_SCK;
 *
 *   // Specify desired SPI Master-In Slave-Out pin.
 *   spi_master_config.miso  = MIKROBUS_1_MISO;
 *
 *   // Specify desired SPI Master-Out Slave-In pin.
 *   spi_master_config.mosi  = MIKROBUS_1_MOSI;
 *
 *   // Specify desired SPI transfer rate.
 *   spi_master_config.speed = 100000;
 *
 *   // Specify desired SPI mode.
 *   spi_master_config.mode  = SPI_MASTER_MODE_0;
 *
 *   // Specify desired default write (dummy) data.
 *   spi_master_config.default_write_data = 0x00;
 *
 *   // Allocate resources for SPI module.
 *   spi_master_open( &spi_master, &spi_master_config );
 * @endcode
 */
//err_t spi_master_open( spi_master_t *obj, spi_master_config_t *config );

/**
 * @brief Select SPI Slave device.
 * @details Sets digital output individual slave pin to logic 0.
 * @param[in] chip_select Device-specific chip select pin.
 * @return Nothing.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // Select desired device.
 *   spi_master_select_device( MIKROBUS_1_CS );
 * @endcode
 */
//void spi_master_select_device( pin_name_t chip_select );

/**
 * @brief Deselect SPI Slave device.
 * @details Sets digital output individual slave pin to logic 1.
 * @param[in] chip_select Device-specific chip select pin.
 * @return Nothing.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // Deselect desired device.
 *   spi_master_deselect_device( MIKROBUS_1_CS );
 * @endcode
 */
//void spi_master_deselect_device( pin_name_t chip_select );

/**
 * @brief Set desired SPI Master chip select polarity.
 * @details Sets SPI Master chip select polarity either to active low or
 * active high. Chip select polarity shall be active low by default.
 * @param[in] polarity Desired chip select polarity mode. See #spi_master_chip_select_polarity_t for valid values.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // Specify desired chip-select polarity.
 *   spi_master_set_chip_select_polarity( SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW );
 * @endcode
 */
//void spi_master_set_chip_select_polarity( spi_master_chip_select_polarity_t polarity );

/**
 * @brief Set SPI Master driver default ( dummy ) write data.
 * @details Default write data is sent by driver when the data transmit buffer is shorter than data receive buffer.
 * @param[in] obj SPI master driver object.
 * See #spi_master_t structure definition for detailed explanation.
 * @param[in] default_write_data User-defined default write data.
 * @return The function can return one of the values defined by
 * #spi_master_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #spi_master_open function.
 *
 * @b Example
 * @code
 *   // SPI Master driver context structure.
 *   spi_master_t spi_master;
 *
 *   // Specify desired default write (dummy) data.
 *   spi_master_set_default_write_data( &spi_master, 0x00 );
 * @endcode
 */
//err_t spi_master_set_default_write_data( spi_master_t *obj, uint8_t default_write_data );

/**
 * @brief Set SPI Master driver communication speed.
 * @details Sets SPI Master module speed to passed value if possible.
 * If not possible, returns error. Make sure to check for return value.
 * Initializes SPI module on hardware level.
 * @param[in] obj SPI Master driver object.
 * See #spi_master_t structure definition for detailed explanation.
 * @param[in] speed SPI Master communication speed.
 * @return The function can return one of the values defined by
 * #spi_master_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #spi_master_open function.
 *
 * @b Example
 * @code
 *   // SPI Master driver context structure.
 *   spi_master_t spi_master;
 *
 *   // Specify desired SPI transfer rate.
 *   spi_master_set_speed( &spi_master, 100000 );
 * @endcode
 */
//err_t spi_master_set_speed( spi_master_t *obj, uint32_t speed );

/**
 * @brief Set SPI Master driver communication mode.
 * @details Sets SPI Master module mode to passed value if possible.
 * If not possible, returns error. Make sure to check for return value.
 * Initializes SPI module on hardware level.
 * @param[in] obj SPI Master driver object.
 * See #spi_master_t structure definition for detailed explanation.
 * @param[in] mode SPI Master communication mode. See #spi_master_mode_t for valid values.
 * @return The function can return one of the values defined by
 * #spi_master_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #spi_master_open function.
 *
 * @b Example
 * @code
 *   // SPI Master driver context structure.
 *   spi_master_t spi_master;
 *
 *   // Specify desired SPI mode.
 *   spi_master_set_mode( &spi_master, SPI_MASTER_MODE_0 );
 * @endcode
 */
//err_t spi_master_set_mode( spi_master_t *obj, spi_master_mode_t mode );

/**
 * @brief Write byte to SPI bus.
 * @details Writes byte to SPI bus in blocking mode.
 * Received byte is discarded.
 * @param[in] obj SPI master driver object.
 * See #spi_master_t structure definition for detailed explanation.
 * @param[in] write_data_buffer Data transmit buffer.
 * @param[in] write_data_length Number of bytes to write from data transmit buffer.
 * @return The function can return one of the values defined by
 * #spi_master_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #spi_master_open function.
 * @warning The following example describes only how the function is used.
 * This is not a working example.
 *
 * @b Example
 * @code
 *   // Specify length of data to be written.
 *   #define DATA_LENGTH 150
 *
 *   // Specify data structure for data to be sent.
 *   uint8_t write_sequence[ DATA_LENGTH ];
 *
 *   // Specify i.e. 0th element to be sent.
 *   write_sequence[0] = 0x02;
 *
 *   // Specify i.e. 1st element to be sent.
 *   write_sequence[1] = 0x05;
 *
 *   // SPI Master driver context structure
 *   spi_master_t spi_master;
 *
 *   // Write specified data on SPI bus.
 *   spi_master_write( &spi_master, &write_sequence, DATA_LENGTH );
 * @endcode
 */
//err_t spi_master_write( spi_master_t *obj, uint8_t *write_data_buffer,
 //                                           size_t write_data_length );

/**
 * @brief Read byte from SPI bus.
 * @details Reads byte from SPI bus in blocking mode.
 * Transmitted byte is user-defined default (dummy) write data.
 * @param[in] obj SPI master driver object.
 * See #spi_master_t structure definition for detailed explanation.
 * @param[out] read_data_buffer Data receive buffer.
 * @param[in] read_data_length Number of bytes to be read.
 * @return The function can return one of the values defined by
 * #spi_master_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #spi_master_open function.
 * @warning The following example describes only how the function is used.
 * This is not a working example.
 *
 * @b Example
 * @code
 *   // Specify length of data to be read.
 *   #define DATA_LENGTH 150
 *
 *   // Specify data structure for data to be read.
 *   uint8_t read_sequence[ DATA_LENGTH ];
 *
 *   // SPI Master driver context structure.
 *   spi_master_t spi_master;
 *
 *   // Read specified data on SPI bus.
 *   spi_master_read( &spi_master, &read_sequence, DATA_LENGTH );
 * @endcode
 */
//err_t spi_master_read( spi_master_t *obj, uint8_t *read_data_buffer,
//                                           size_t read_data_length );

/**
 * @brief Perform a sequence of SPI Master writes immediately followed by a SPI Master read.
 * @details Writes a sequence of bytes to SPI bus, followed by a corresponding read.
 * @param[in] obj SPI master driver object.
 * See #spi_master_t structure definition for detailed explanation.
 * @param[in] write_data_buffer Data transmit buffer.
 * @param[in] length_write_data Number of bytes to write from data transmit buffer.
 * @param[out] read_data_buffer Data receive buffer.
 * @param[in] length_read_data Number of bytes to be read.
 * @return The function can return one of the values defined by
 * #spi_master_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #spi_master_open function.
 * Before calling this function.
 * @note If the transmitted data sequence is shorter than the received data sequence, the remaining places in the data transmit buffer will be populated with user-defined data. See #spi_master_set_default_write_data function for more details.
 * @warning The following example describes only how the function is used.
 * This is not a working example.
 *
 * @b Example
 * @code
 *   // Specify length of data to be written and read.
 *   #define DATA_LENGTH 150
 *
 *   // Specify data structure for data to be sent.
 *   uint8_t write_sequence[ DATA_LENGTH ];
 *
 *   // Specify data structure for data to be read.
 *   uint8_t read_sequence[ DATA_LENGTH ];
 *
 *   // Specify i.e. 0th element to be sent.
 *   write_sequence[0] = 0x02;
 *
 *   // Specify i.e. 1st element to be sent.
 *   write_sequence[1] = 0x05;
 *
 *   // SPI Master driver context structure.
 *   spi_master_t spi_master;
 *
 *   // Write then read specified data on SPI bus.
 *   spi_master_write_then_read( &spi_master, &write_sequence,
 *                                            DATA_LENGTH,
 *                                            &read_sequence,
 *                                            DATA_LENGTH );
 * @endcode
 */
//err_t spi_master_write_then_read( spi_master_t *obj, uint8_t *write_data_buffer,
//                                                     size_t length_write_data,
//                                                     uint8_t *read_data_buffer,
//                                                     size_t length_read_data );

/**
 * @brief  Close SPI Master Driver context object.
 * @details Closes SPI Master Driver context object,
 * resets pin AF to default values and
 * clears all buffers used by object.
 * @param[in,out] obj Driver context object handle.
 * See #spi_master_t structure definition for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // SPI Master driver context structure.
 *   spi_master_t spi_master;
 *
 *   // Close the SPI module object handler.
 *   spi_master_close( &spi_master );
 * @endcode
 */
//void spi_master_close( spi_master_t *obj );


#endif // _DRV_SPI_MASTER_H_