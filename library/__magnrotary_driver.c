/*
    __magnrotary_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__magnrotary_driver.h"
#include "__magnrotary_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __MAGNROTARY_DRV_I2C__
static uint8_t _slaveAddress;
#endif

const uint8_t _MAGNROTARY_START_BYTE                 = 0x01;
const uint8_t _MAGNROTARY_DUMMY_BYTE                 = 0x00;
const uint8_t _MAGNROTARY_CMD_MASK                   = 0xE0;
const uint16_t _MAGNROTARY_ADC_RESOLUTION            = 4096;
const uint16_t _MAGNROTARY_SIGN_BIT                  = 0x0800;

const uint8_t _MAGNROTARY_CHA_POS_GND_NEG            = 0x80;
const uint8_t _MAGNROTARY_CHB_POS_GND_NEG            = 0xC0;
const uint8_t _MAGNROTARY_CHA_POS_CHB_NEG            = 0x00;
const uint8_t _MAGNROTARY_CHB_POS_CHA_NEG            = 0x40;

const uint8_t _MAGNROTARY_MSB_LSB_ORDER              = 0x00;
const uint8_t _MAGNROTARY_MSB_ZEROS_ORDER            = 0x20;

const uint16_t _MAGNROTARY_VDD_3V3                   = 3298;
const uint16_t _MAGNROTARY_VDD_5V                    = 4960;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __MAGNROTARY_DRV_SPI__

void magnrotary_spiDriverInit(T_MAGNROTARY_P gpioObj, T_MAGNROTARY_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    hal_gpio_csSet( 1 );
}

#endif
#ifdef   __MAGNROTARY_DRV_I2C__

void magnrotary_i2cDriverInit(T_MAGNROTARY_P gpioObj, T_MAGNROTARY_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __MAGNROTARY_DRV_UART__

void magnrotary_uartDriverInit(T_MAGNROTARY_P gpioObj, T_MAGNROTARY_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

uint16_t magnrotary_readADC( uint8_t cmndByte )
{
    uint8_t dataIn[ 3 ];
    uint8_t dataOut[ 3 ];
    uint16_t retVal;
    
    dataIn[ 0 ] = _MAGNROTARY_START_BYTE;
    dataIn[ 1 ] = cmndByte & _MAGNROTARY_CMD_MASK;
    dataIn[ 2 ] = _MAGNROTARY_DUMMY_BYTE;
    
    hal_gpio_csSet( 0 );
    hal_spiTransfer( dataIn, dataOut, 3 );
    hal_gpio_csSet( 1 );
    
    retVal = dataOut[ 1 ] & 0x0F;
    retVal <<= 8;
    retVal |= dataOut[ 2 ];
    
    return retVal;
}

uint16_t magnrotary_outVoltADC( uint8_t cmdByte, uint16_t pwrVolt )
{
    uint16_t temp;
    double res;
    
    temp = magnrotary_readADC( cmdByte );
    
    res = (double)temp / _MAGNROTARY_ADC_RESOLUTION;
    res *= pwrVolt;
    
    return (uint16_t)res;
}

double magnrotary_getFieldAngle( uint8_t cmdByte )
{
    int16_t temp;
    double res;
    
    temp = magnrotary_readADC( cmdByte );
    
    if (temp & _MAGNROTARY_SIGN_BIT)
    {
        temp |= 0xF000;
    }
    
    res = (double)_MAGNROTARY_ADC_RESOLUTION / 180.0;
    res = (double)temp / res;
    
    return res;
}

/* -------------------------------------------------------------------------- */
/*
  __magnrotary_driver.c

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