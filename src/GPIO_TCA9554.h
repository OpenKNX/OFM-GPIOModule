#include "GPIOModule.h"
#include "TCA9554.h"

class GPIO_TCA9554 : public iGPIOExpander
{
  private:
    TCA9554* _tca = nullptr;
  public:
    GPIO_TCA9554(uint16_t i2cAddr, TwoWire* wire);
    virtual int init() override;
    virtual void GPIOpinMode(uint8_t pin, int mode, bool preset, int status) override;
    virtual void GPIOdigitalWrite(uint8_t pin, int status) override;
    virtual bool GPIOdigitalRead(uint8_t pin) override;
};