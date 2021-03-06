#pragma once

#include "global.h"
#include "interface/gpio/gpio.h"
#include "device/nrf/nrf_radio.h"


namespace NRF
{

    class __attribute__((packed,aligned(4))) SE8R01 final : public Radio
    {
    public:
        enum Register
        {
            Reg_Config = 0x00,
            Reg_AutoAckCtl = 0x01,
            Reg_RxPipeEnable = 0x02,
            Reg_AddressCtl = 0x03,
            Reg_RetransCtl = 0x04,
            Reg_RfChannel = 0x05,
            Reg_RfSetup = 0x06,
            Reg_Status = 0x07,
            Reg_TxObserve = 0x08,
            Reg_EnergyDetect = 0x09,
            Reg_RxPipeAddress0 = 0x0a,
            Reg_RxPipeAddress1 = 0x0b,
            Reg_RxPipeAddress2 = 0x0c,
            Reg_RxPipeAddress3 = 0x0d,
            Reg_RxPipeAddress4 = 0x0e,
            Reg_RxPipeAddress5 = 0x0f,
            Reg_TxAddress = 0x10,
            Reg_RxDataLength0 = 0x11,
            Reg_RxDataLength1 = 0x12,
            Reg_RxDataLength2 = 0x13,
            Reg_RxDataLength3 = 0x14,
            Reg_RxDataLength4 = 0x15,
            Reg_RxDataLength5 = 0x16,
            Reg_FifoStatus = 0x17,
            Reg_DynLengthCtl = 0x1c,
            Reg_FeatureCtl = 0x1d,
            Reg_Tuning = 0x1e,
            Reg_GuardCtl = 0x1f,
        };

        enum InternalRegister
        {
            IntReg_Line = 0x00,
            IntReg_PllCtl0 = 0x01,
            IntReg_PllCtl1 = 0x02,
            IntReg_CalCtl = 0x03,
            IntReg_ACntReg = 0x04,
            IntReg_BCntReg = 0x05,
            IntReg_Reserved0 = 0x06,
            IntReg_Status = 0x07,
            IntReg_State = 0x08,
            IntReg_Chan = 0x09,
            IntReg_IfFreq = 0x0a,
            IntReg_AfcCor = 0x0b,
            IntReg_FDev = 0x0c,
            IntReg_DacRange = 0x0d,
            IntReg_DacIn = 0x0e,
            IntReg_CTuning = 0x0f,
            IntReg_FTuning = 0x10,
            IntReg_RxCtrl = 0x11,
            IntReg_FAgcCtrl = 0x12,
            IntReg_FAcgCtrl1 = 0x13,
            IntReg_DacCalLow = 0x17,
            IntReg_DacCalHi = 0x18,
            IntReg_Reserved1 = 0x19,
            IntReg_DocDacI = 0x1a,
            IntReg_DocDacQ = 0x1b,
            IntReg_AgcCtrl = 0x1c,
            IntReg_AgcGain = 0x1d,
            IntReg_RfIvGen = 0x1e,
            IntReg_TestPkDet = 0x1f,
        };

        union __attribute__((packed)) AutoAckCtl
        {
            uint8_t d8;
            struct __attribute__((packed)) b
            {
                bool pipe0 : 1;
                bool pipe1 : 1;
                bool pipe2 : 1;
                bool pipe3 : 1;
                bool pipe4 : 1;
                bool pipe5 : 1;
                uint8_t : 2;
            } b;
        };

        union __attribute__((packed)) RxPipeEnable
        {
            uint8_t d8;
            struct __attribute__((packed)) b
            {
                bool pipe0 : 1;
                bool pipe1 : 1;
                bool pipe2 : 1;
                bool pipe3 : 1;
                bool pipe4 : 1;
                bool pipe5 : 1;
                uint8_t : 2;
            } b;
        };

        union __attribute__((packed)) AddressCtl
        {
            uint8_t d8;
            struct __attribute__((packed)) b
            {
                enum Width
                {
                    Width_32Bit = 2,
                    Width_40Bit = 3,
                } width : 2;
                uint8_t : 6;
            } b;
        };

        union __attribute__((packed)) RetransCtl
        {
            uint8_t d8;
            struct __attribute__((packed)) b
            {
                uint8_t count : 4;
                uint8_t delay : 4;
            } b;
        };

        union __attribute__((packed)) RfChannel
        {
            uint8_t d8;
            struct __attribute__((packed)) b
            {
                uint8_t channel : 7;
                uint8_t : 1;
            } b;
        };

        union __attribute__((packed)) RfSetup
        {
            uint8_t d8;
            struct __attribute__((packed)) b
            {
                uint8_t power : 3;
                enum DataRate
                {
                    DataRate_1Mbit = 0,
                    DataRate_2Mbit = 1,
                    DataRate_500Kbit = 5,
                } dataRate : 3;
                bool highPower : 1;
                bool sendContinuousCarrier : 1;
            } b;
        };

        union __attribute__((packed)) TxObserve
        {
            uint8_t d8;
            struct __attribute__((packed)) b
            {
                uint8_t retransCount : 4;
                uint8_t lostPackets : 4;
            } b;
        };

        union __attribute__((packed)) EnergyDetect
        {
            uint8_t d8;
            struct __attribute__((packed)) b
            {
                bool signalLevel : 8;
            } b;
        };

        union __attribute__((packed)) FifoStatus
        {
            uint8_t d8;
            struct __attribute__((packed)) b
            {
                bool rxEmpty : 1;
                bool rxFull : 1;
                uint8_t : 2;
                bool txEmpty : 1;
                bool txFull : 1;
                bool txReuse : 1;
                uint8_t : 1;
            } b;
        };

        union __attribute__((packed)) DynLengthCtl
        {
            uint8_t d8;
            struct __attribute__((packed)) b
            {
                bool pipe0 : 1;
                bool pipe1 : 1;
                bool pipe2 : 1;
                bool pipe3 : 1;
                bool pipe4 : 1;
                bool pipe5 : 1;
                uint8_t : 2;
            } b;
        };

        union __attribute__((packed)) FeatureCtl
        {
            uint8_t d8;
            struct __attribute__((packed)) b
            {
                bool dynAck : 1;
                bool ackPayload : 1;
                bool dynLength : 1;
                uint8_t : 5;
            } b;
        };

        union __attribute__((packed)) Tuning
        {
            uint8_t d8[5];
            struct __attribute__((packed)) b
            {
                uint8_t rxSetupTime : 8;
                uint8_t txSetupTime : 8;
                uint8_t rxTimeout : 8;
                uint8_t bandgapWait : 8;
                uint8_t lnaWait : 8;
            } b;
        };

        union __attribute__((packed)) GuardCtl
        {
            uint8_t d8[2];
            struct __attribute__((packed)) b
            {
                uint8_t preGuardBits : 4;
                uint8_t preGuardEnable : 1;
                uint8_t tailRepeat : 3;
                uint8_t spareReg : 8;
            } b;
        };

        enum Feature
        {
            Feature_SwitchRegisterBank = 0x53,
        };

        struct __attribute__((packed)) Configuration
        {
            union Config config;
            union AutoAckCtl autoAckCtl;
            union RxPipeEnable rxPipeEnable;
            union AddressCtl addressCtl;
            union RetransCtl retransCtl;
            union RfChannel rfChannel;
            union RfSetup rfSetup;
            union DynLengthCtl dynLengthCtl;
            union FeatureCtl featureCtl;
            union Tuning tuning;
            union GuardCtl guardCtl;
        };

        SE8R01(const ::SPI::Bus* bus, GPIO::Pin cspin, int frequency)
            : Radio(bus, cspin, frequency) { init(); }
        SE8R01(const ::SPI::Bus* bus, GPIO::Pin cspin, int frequency,
               void (*receivedHandler)(int pipe, uint8_t* packet, int length),
               void (*transmittedHandler)(bool success, int retransmissions))
            : Radio(bus, cspin, frequency, receivedHandler, transmittedHandler) { init(); }

        void switchBank();
        void init();
        void configure(Configuration* config);
        SPI::Status handleIRQ();

    private:
        static const uint8_t initSequence[];
    };

}
