# OFM-GPIOModule
HAL for GPIOs

# Usage

## hardware.h
```
#define OPENKNX_GPIO_NUM 1
#define OPENKNX_GPIO_TYPES OPENKNX_GPIO_T_TCA9555
#define OPENKNX_GPIO_ADDRS 0x20
#define OPENKNX_GPIO_INTS 0xFF  

#define OPENKNX_GPIO_WIRE Wire
#define OPENKNX_GPIO_CLOCK 400000
#define OPENKNX_GPIO_SDA 28
#define OPENKNX_GPIO_SCL 29

#define OPENKNX_xxx_PINS 0x010D, 0x010B, 0x0102, 0x0104
```

## code
```
#include "GPIOModule.h"
..
openknx.addModule(4, openknxGPIOModule);
..
openknxGPIOModule.pinMode(24, OUTPUT);      // set MCU-GPIO 24 to OUTPUT
openknxGPIOModule.digitalWrite(24, HIGH);   // writes MCU-GPIO 24 to HIGH

if (openknxGPIOModule.initialized(1))           // check the initialized state of the expander 0x01
{
  openknxGPIOModule.pinMode(0x0105, OUTPUT);    // sets the GPIO 5 to OUTPUT expander 0x01.
  openknxGPIOModule.digitalWrite(0x0105, HIGH); // writes digital value HIGH to GPIO 5 of the expander 0x01
}
 openknxGPIOModule.digitalRead(0x0105);         // reads GPIO 5 of expander 0x01.
```

# Supported HW
## Controller
RP2040 (single core)
## MCU GPIOs (Arduino)
wraps the `pinMode`, `digitalWrite`, ... functions
## TCA9555
TCA9555 16bit I2C port expander
## PCA9557
PCA9557 8-bit I2C-bus expander (I2C slave address range 0x18 to 0x1F )


# Features
## Current
`pinMode`, `digitalRead`, `digitalWrite`
## Planned Features
- Interrupt handling
- analogRead/Write
- bulk setting of pins
- access with openknx.GPIO.
## Further improvements
- Multicore
- ESP32
- expanders on different I2C units (e.g. 0x01 on Wire, 0x02 on Wire1)