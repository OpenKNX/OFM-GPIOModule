#ifdef USE_GPIO_MODULE
#include "GPIOModule.h"

class GPIO_MCU : public iGPIOExpander
{
  public:
    GPIO_MCU();
    virtual int init() override;
    virtual void GPIOpinMode(uint8_t pin, int mode, bool preset, int status) override;
    virtual void GPIOdigitalWrite(uint8_t pin, int status) override;
    virtual bool GPIOdigitalRead(uint8_t pin) override;
    virtual inline const bool getInitState() { return _initialized; }
    virtual inline void setInitState(const bool status) { _initialized = status; }
  private:
    bool _initialized = false;
};
#endif // USE_GPIO_MODULE