/*
Example for Magnetic_rotary Click

    Date          : Nov 2018.
    Author        : Nemanja Medakovic

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes peripherals and pins.
- Application Initialization - Initializes SPI interface for communication with the device.
- Application Task - (code snippet) - Reads a magnetic field angle calculated to degrees for channel A
  in Single-Ended Mode and logs results on uart terminal.
  Repeats operation every 300 milliseconds.
Note : The angle can be measured in the range from -90 to 90 degrees.

Additional Functions :

- void floatCut() - Makes the float values to be rounded on two decimal places.
- void plotAngle() - Sends results of angle on serial plotter.

*/

#include "Click_Magnetic_rotary_types.h"
#include "Click_Magnetic_rotary_config.h"

double magnAngle;
char text[ 50 ];
char logDeg[ 2 ];
uint32_t plotTime;

void floatCut()
{
    uint8_t count;
    uint8_t conCnt = 0;
    uint8_t conVar = 0;

    for (count = 0; count < 50; count++)
    {
        if (text[ count ] == '.')
        {
            conVar = 1;
        }
        if (conVar == 1)
        {
            conCnt++;
        }
        if (conCnt > 3)
        {
            if ((text[ count ] == 'e') || (conVar == 2))
            {
                text[ count - (conCnt - 4) ] = text[ count ];
                text[ count ] = 0;
                conVar = 2;
            }
            else
            {
                text[ count ] = 0;
            }
        }
    }
}

void plotAngle()
{
    int16_t plotData = magnAngle;
    
    IntToStr( plotData, text );
    mikrobus_logWrite( text, _LOG_TEXT );
    mikrobus_logWrite( ",", _LOG_TEXT );
    LongWordToStr( plotTime, text );
    mikrobus_logWrite( text, _LOG_LINE );
    
    if (plotTime == 0xFFFFFFFF)
    {
        plotTime = 0;
    }
    else
    {
        plotTime++;
    }
}

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );

    mikrobus_spiInit( _MIKROBUS1, &_MAGNROTARY_SPI_CFG[0] );

    mikrobus_logInit( _MIKROBUS2, 9600 );
    mikrobus_logWrite( "*** Initializing... ***", _LOG_LINE );

    Delay_ms( 100 );
}

void applicationInit()
{
    magnrotary_spiDriverInit( (T_MAGNROTARY_P)&_MIKROBUS1_GPIO, (T_MAGNROTARY_P)&_MIKROBUS1_SPI );
    Delay_ms( 500 );
    
    logDeg[ 0 ] = 176;
    logDeg[ 1 ] = 0;
    plotTime = 0;
    
    mikrobus_logWrite( "** Magnetic rotary is initialized **", _LOG_LINE );
    mikrobus_logWrite( "", _LOG_LINE );
}

void applicationTask()
{
    magnAngle = magnrotary_getFieldAngle( _MAGNROTARY_CHA_POS_GND_NEG | _MAGNROTARY_MSB_ZEROS_ORDER );
    
    FloatToStr( magnAngle, text );
    floatCut();
    mikrobus_logWrite( "Angle is : ", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_TEXT );
    mikrobus_logWrite( logDeg, _LOG_LINE );
    
    Delay_ms( 300 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
        applicationTask();
    }
}
