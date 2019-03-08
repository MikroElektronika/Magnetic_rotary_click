![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Magnetic_rotary Click

- **CIC Prefix**  : MAGNROTARY
- **Author**      : Nemanja Medakovic
- **Verison**     : 1.0.0
- **Date**        : Nov 2018.

---

### Software Support

We provide a library for the Magnetic_rotary Click on our [LibStock](https://libstock.mikroe.com/projects/view/2655/magnetic-rotary-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library performs a magnetic field angle measurement and calculates angle value to degrees.
The library also performs the all necessary settings for the AD conversion, for example channel selection and mode setting.
For more details check documentation.

Key functions :

- ``` uint16_t magnrotary_readADC( uint8_t cmndByte ) ``` - Function returns a 12bit result of AD conversion.
- ``` uint16_t magnrotary_outVoltADC( uint8_t cmdByte, uint16_t pwrVolt ) ``` - Function returns ADC voltage value calculated to millivolts, depending on the VDD (power) voltage selection.
- ``` double magnrotary_getFieldAngle( uint8_t cmdByte ) ``` - Function returns a magnetic field angle calculated to degrees, in the range from -90 to 90 degrees.

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes peripherals and pins.
- Application Initialization - Initializes SPI interface for communication with the device.
- Application Task - (code snippet) - Reads a magnetic field angle calculated to degrees for channel A
  in Single-Ended Mode and logs results on uart terminal.
  Repeats operation every 300 milliseconds.
Note : The angle can be measured in the range from -90 to 90 degrees.


```.c
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
```

Additional Functions :

- void floatCut() - Makes the float values to be rounded on two decimal places.
- void plotAngle() - Sends results of angle on serial plotter.

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2655/magnetic-rotary-click) page.

Other mikroE Libraries used in the example:

- Conversions
- SPI
- UART

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
