#pragma once

#include <SparkFun_I2C_Expander_Arduino_Library.h> // Using SparkFun library for PCA9557
#include "GPIOModule.h"

class GPIO_PCA9557 : public iGPIOExpander
{
  private:
    SFE_PCA95XX* _pca = nullptr;
    uint8_t _i2cAddr;
    TwoWire* _wire;
    bool _initialized = false;

  public:
    GPIO_PCA9557(uint8_t i2cAddr, TwoWire* wire);
    virtual ~GPIO_PCA9557();
    virtual int init() override;
    virtual void GPIOpinMode(uint8_t pin, int mode, bool preset, int status) override;
    virtual void GPIOdigitalWrite(uint8_t pin, int status) override;
    virtual bool GPIOdigitalRead(uint8_t pin) override;
    virtual inline const bool getInitState() { return _initialized; }
    virtual inline void setInitState(const bool status) { _initialized = status; }
};