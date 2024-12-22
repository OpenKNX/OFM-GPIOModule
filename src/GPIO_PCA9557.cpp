#include "GPIO_PCA9557.h"

GPIO_PCA9557::GPIO_PCA9557(uint8_t i2cAddr, TwoWire* wire)
    : _i2cAddr(i2cAddr), _wire(wire)
{
    _pca = new SFE_PCA95XX();
}

GPIO_PCA9557::~GPIO_PCA9557()
{
    delete _pca;
}

int GPIO_PCA9557::init()
{
    if (_pca->begin(_i2cAddr, *_wire))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void GPIO_PCA9557::GPIOpinMode(uint8_t pin, int mode, bool preset, int status)
{
    if (pin > 7 || (mode != INPUT && mode != OUTPUT))
    {
        return;
    }

    if (preset)
    {
        _pca->digitalWrite(pin, status);
    }

    if (mode == INPUT)
    {
        _pca->pinMode(pin, INPUT);
    }
    else
    {
        _pca->pinMode(pin, OUTPUT);
    }
}

// Writes a digital value (HIGH/LOW) to the specified pin
void GPIO_PCA9557::GPIOdigitalWrite(uint8_t pin, int status)
{
    if (pin > 7)
    {
        return;
    }
    _pca->digitalWrite(pin, status);
}

bool GPIO_PCA9557::GPIOdigitalRead(uint8_t pin)
{
    if (pin > 7)
    {
        return false;
    }
    return _pca->digitalRead(pin);
}