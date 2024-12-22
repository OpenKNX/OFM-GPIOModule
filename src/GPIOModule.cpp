#include "GPIOModule.h"
#include "OpenKNX.h"
#include "GPIO_TCA9555.h"
#include "GPIO_TCA6408.h"
#include "GPIO_MCU.h"
#include "GPIO_PCA9557.h"

GPIOModule openknxGPIOModule;

const OPENKNX_GPIO_T GPIO_TYPES[OPENKNX_GPIO_NUM+1] = {OPENKNX_GPIO_T_MCU, OPENKNX_GPIO_TYPES};
const uint16_t GPIO_ADDRS[OPENKNX_GPIO_NUM+1] = {0, OPENKNX_GPIO_ADDRS};
const uint8_t GPIO_INTS[OPENKNX_GPIO_NUM+1] = {0, OPENKNX_GPIO_INTS};
iGPIOExpander* GPIOExpanders[OPENKNX_GPIO_NUM+1];

GPIOModule::GPIOModule()
{
}

GPIOModule::~GPIOModule()
{
}

const std::string GPIOModule::name()
{
    return "GPIOModule";
}

const std::string GPIOModule::version()
{
    //ToDo
    return 0;
}



void GPIOModule::init()
{
    OPENKNX_GPIO_WIRE.setSDA(OPENKNX_GPIO_SDA);
    OPENKNX_GPIO_WIRE.setSCL(OPENKNX_GPIO_SCL);
    OPENKNX_GPIO_WIRE.begin();
    OPENKNX_GPIO_WIRE.setClock(OPENKNX_GPIO_CLOCK);

    for(int i = 0; i < OPENKNX_GPIO_NUM+1; i++)
    {
        switch(GPIO_TYPES[i])
        {
            case OPENKNX_GPIO_T_MCU:
            {
                GPIOExpanders[i] = new GPIO_MCU();
                GPIOExpanders[i]->setInitState(GPIOExpanders[i] != nullptr);
            }
            break;
            case OPENKNX_GPIO_T_TCA9555:
            {
                GPIOExpanders[i] = new GPIO_TCA9555(GPIO_ADDRS[i], &OPENKNX_GPIO_WIRE);
                const int statuscode = GPIOExpanders[i]->init();
                if(statuscode)
                {
                    logErrorP("no connection to GPIO Expander %u with address %u (Errorcode: %u)", i, GPIO_ADDRS[i], statuscode);
                }
                else
                {
                    logInfoP("connected to GPIO Expander %u with address %u", i, GPIO_ADDRS[i]);
                    GPIOExpanders[i]->setInitState(true);
                }
            }
            break;
            case OPENKNX_GPIO_T_TCA6408:
            {
                GPIOExpanders[i] = new GPIO_TCA6408(GPIO_ADDRS[i], &OPENKNX_GPIO_WIRE);
                const int statuscode = GPIOExpanders[i]->init();
                if(statuscode)
                {
                    logErrorP("no connection to GPIO Expander %u with address %u (Errorcode: %u)", i, GPIO_ADDRS[i], statuscode);
                }
                else
                {
                    logInfoP("connected to GPIO Expander %u with address %u", i, GPIO_ADDRS[i]);
                    GPIOExpanders[i]->setInitState(true);
                }
            }
            break;
            case OPENKNX_GPIO_T_PCA9557:
            {
                GPIOExpanders[i] = new GPIO_PCA9557(GPIO_ADDRS[i], &OPENKNX_GPIO_WIRE);
                const int statuscode = GPIOExpanders[i]->init();
                if (GPIOExpanders[i]->init())
                {
                    logErrorP("No connection to GPIO Expander %u with address 0x%02X (Errorcode: %u)", i, GPIO_ADDRS[i], statuscode);
                }
                else
                {
                    logInfoP("Connected to GPIO Expander %u with address 0x%02X", i, GPIO_ADDRS[i]);
                    GPIOExpanders[i]->setInitState(true);
                }
            }
            break;
            default:
                ;
                logErrorP("GPIO_TYPE %u not found", GPIO_TYPES[i]);
        }
    }
}

const bool GPIOModule::initialized(uint8_t expander)
{
    return GPIOExpanders[expander]->getInitState();
}

void GPIOModule::loop()
{

}

void GPIOModule::pinMode(uint16_t pin, int mode, bool preset, int status)
{
    int8_t localpin = pin & 0xff;
    uint8_t expander = pin >> 8;
    if(expander > OPENKNX_GPIO_NUM)
    {
        logErrorP("GPIOModule::pinMode: invalid pin id %u", pin);
        return;
    }
    GPIOExpanders[expander]->GPIOpinMode(localpin, mode, preset, status);
}

void GPIOModule::digitalWrite(uint16_t pin, int status)
{
    int8_t localpin = pin & 0xff;
    uint8_t expander = pin >> 8;
    if(expander > OPENKNX_GPIO_NUM)
    {
        logErrorP("GPIOModule::digitalWrite: invalid pin id %u", pin);
        return;
    } 
    GPIOExpanders[expander]->GPIOdigitalWrite(localpin, status);
}

bool GPIOModule::digitalRead(uint16_t pin)
{
    int8_t localpin = pin & 0xff;
    uint8_t expander = pin >> 8;
    if(expander > OPENKNX_GPIO_NUM)
    {
        logErrorP("GPIOModule::digitalRead: invalid pin id %u", pin);
        return 0;
    }
    return GPIOExpanders[expander]->GPIOdigitalRead(localpin);
}

