#ifdef USE_GPIO_MODULE
#include "GPIO_MCU.h"
#include "Arduino.h"

GPIO_MCU::GPIO_MCU()
{
}

int GPIO_MCU::init()
{
    return 0;
}

void GPIO_MCU::GPIOpinMode(uint8_t pin, int mode, bool preset, int status)
{
    pinMode(pin, mode); // Erst den Modus setzen!

    if (preset)
    {
#ifdef ARDUINO_ARCH_ESP32
        if (status)
            gpio_set_level((gpio_num_t)pin, HIGH); // Setze Pin HIGH
        else
            gpio_set_level((gpio_num_t)pin, LOW); // Setze Pin LOW
#else
        digitalWriteFast(pin, status);
#endif
    }
}

void GPIO_MCU::GPIOdigitalWrite(uint8_t pin, int status)
{
    digitalWrite(pin, status);
}

bool GPIO_MCU::GPIOdigitalRead(uint8_t pin)
{
    return digitalRead(pin);
}
#endif // USE_GPIO_MODULE