#pragma once

#include "global.h"
#include "interface/gpio/gpio.h"


#ifndef SPI_OPTIMIZE
#define SPI_OPTIMIZE
#endif


namespace SPI
{

    class __attribute__((packed,aligned(4))) Bus
    {
    public:
        virtual int setFrequency(int frequency) const = 0;
        virtual void select() const = 0;
        virtual void deselect() const = 0;
        virtual uint8_t pushByte(uint8_t byte) const = 0;
        virtual void pushBuffer(const void* inbuf, void* outbuf, int len) const = 0;
    };

    class __attribute__((packed,aligned(4))) Device
    {
    public:
        const Bus* bus;
        int frequency;
        uint8_t deselbytes;
        GPIO::Pin cspin;

        Device(const Bus* bus, GPIO::Pin cspin, int frequency);
        void select();
        void deselect();
        void reselect();
        uint8_t pushByte(uint8_t byte);
        void pushBuffer(const void* inbuf, void* outbuf, int len);
        bool stayAwake(bool on);

    private:
        bool keepBusActive;
        bool selected;
#ifdef GPIO_SUPPORT_FAST_MODE
        bool oldGPIOFastState;
#else
        uint32_t : 8;
#endif
        uint32_t : 8;
    };

}
