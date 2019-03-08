/*
    __magnrotary_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __magnrotary_driver.h
@brief    Magnetic_rotary Driver
@mainpage Magnetic_rotary Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   MAGNROTARY
@brief      Magnetic_rotary Click Driver
@{

| Global Library Prefix | **MAGNROTARY** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Nov 2018.**      |
| Developer             | **Nemanja Medakovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _MAGNROTARY_H_
#define _MAGNROTARY_H_

/** 
 * @macro T_MAGNROTARY_P
 * @brief Driver Abstract type 
 */
#define T_MAGNROTARY_P    const uint8_t*

/** @defgroup MAGNROTARY_COMPILE Compilation Config */              /** @{ */

   #define   __MAGNROTARY_DRV_SPI__                            /**<     @macro __MAGNROTARY_DRV_SPI__  @brief SPI driver selector */
//  #define   __MAGNROTARY_DRV_I2C__                            /**<     @macro __MAGNROTARY_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __MAGNROTARY_DRV_UART__                           /**<     @macro __MAGNROTARY_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup MAGNROTARY_VAR Variables */                           /** @{ */

/** Settings to choose Single-Ended Mode or Pseudo-Differential Mode */
extern const uint8_t _MAGNROTARY_CHA_POS_GND_NEG       ;
extern const uint8_t _MAGNROTARY_CHB_POS_GND_NEG       ;
extern const uint8_t _MAGNROTARY_CHA_POS_CHB_NEG       ;
extern const uint8_t _MAGNROTARY_CHB_POS_CHA_NEG       ;

/** Settings for data order */
extern const uint8_t _MAGNROTARY_MSB_LSB_ORDER         ;
extern const uint8_t _MAGNROTARY_MSB_ZEROS_ORDER       ;

/** Settings to choose VDD value */
extern const uint16_t _MAGNROTARY_VDD_3V3              ;
extern const uint16_t _MAGNROTARY_VDD_5V               ;

                                                                       /** @} */
/** @defgroup MAGNROTARY_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup MAGNROTARY_INIT Driver Initialization */              /** @{ */

#ifdef   __MAGNROTARY_DRV_SPI__
void magnrotary_spiDriverInit(T_MAGNROTARY_P gpioObj, T_MAGNROTARY_P spiObj);
#endif
#ifdef   __MAGNROTARY_DRV_I2C__
void magnrotary_i2cDriverInit(T_MAGNROTARY_P gpioObj, T_MAGNROTARY_P i2cObj, uint8_t slave);
#endif
#ifdef   __MAGNROTARY_DRV_UART__
void magnrotary_uartDriverInit(T_MAGNROTARY_P gpioObj, T_MAGNROTARY_P uartObj);
#endif

                                                                       /** @} */
/** @defgroup MAGNROTARY_FUNC Driver Functions */                   /** @{ */

/**
 * @brief ADC Result Read function
 *
 * @param[in] cmndByte  Settings for AD conversion
 *
 * @returns Result of conversion
 *
 * Function returns a 12bit result of AD conversion.
 */
uint16_t magnrotary_readADC( uint8_t cmndByte );

/**
 * @brief ADC Output Voltage Get function
 *
 * @param[in] cmdByte  Settings for AD conversion
 * @param[in] pwrVolt  Power voltage value selection (millivolts)
 *
 * @returns ADC output voltage value
 *
 * Function returns ADC voltage value calculated to millivolts, depending on the VDD (power) voltage selection.
 */
uint16_t magnrotary_outVoltADC( uint8_t cmdByte, uint16_t pwrVolt );

/**
 * @brief Magnetic Field Angle Get function
 *
 * @param[in] cmdByte  Settings for AD conversion
 *
 * @returns Magnetic field angle
 *
 * Function returns a magnetic field angle calculated to degrees, in the range from -90 to 90 degrees.
 */
double magnrotary_getFieldAngle( uint8_t cmdByte );

                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Magnetic_rotary_STM.c
    @example Click_Magnetic_rotary_TIVA.c
    @example Click_Magnetic_rotary_CEC.c
    @example Click_Magnetic_rotary_KINETIS.c
    @example Click_Magnetic_rotary_MSP.c
    @example Click_Magnetic_rotary_PIC.c
    @example Click_Magnetic_rotary_PIC32.c
    @example Click_Magnetic_rotary_DSPIC.c
    @example Click_Magnetic_rotary_AVR.c
    @example Click_Magnetic_rotary_FT90x.c
    @example Click_Magnetic_rotary_STM.mbas
    @example Click_Magnetic_rotary_TIVA.mbas
    @example Click_Magnetic_rotary_CEC.mbas
    @example Click_Magnetic_rotary_KINETIS.mbas
    @example Click_Magnetic_rotary_MSP.mbas
    @example Click_Magnetic_rotary_PIC.mbas
    @example Click_Magnetic_rotary_PIC32.mbas
    @example Click_Magnetic_rotary_DSPIC.mbas
    @example Click_Magnetic_rotary_AVR.mbas
    @example Click_Magnetic_rotary_FT90x.mbas
    @example Click_Magnetic_rotary_STM.mpas
    @example Click_Magnetic_rotary_TIVA.mpas
    @example Click_Magnetic_rotary_CEC.mpas
    @example Click_Magnetic_rotary_KINETIS.mpas
    @example Click_Magnetic_rotary_MSP.mpas
    @example Click_Magnetic_rotary_PIC.mpas
    @example Click_Magnetic_rotary_PIC32.mpas
    @example Click_Magnetic_rotary_DSPIC.mpas
    @example Click_Magnetic_rotary_AVR.mpas
    @example Click_Magnetic_rotary_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __magnrotary_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */