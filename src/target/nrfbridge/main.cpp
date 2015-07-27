#include "global.h"
#include "app/main.h"
#include "sys/time.h"
#include "sys/util.h"
#include "interface/irq/irq.h"
#include "interface/clockgate/clockgate.h"
#include "cpu/arm/cortexm/cmsis.h"
#include "cpu/arm/cortexm/irq.h"
#include "soc/stm32/f0/clockgates.h"
#include "soc/stm32/spi.h"
#include "soc/stm32/gpio.h"
#include "soc/stm32/uart.h"
#include "device/nrf/nrf24l01p/nrf24l01p.h"


enum Command
{
    RxPacket = 0x00,
    TxPacket = 0x01,
    TxDone = 0x02,
    TxFlush = 0x03,
    TxFlushed = 0x04,
    ConfigRadio = 0x10,
    ConfigAddr = 0x11,
    ConfigSize = 0x12,
    ConfigRole = 0x13,
    ConfigReset = 0x1f,
};


void transmittedHandler(bool success, int retransmissions);
void receivedHandler(int pipe, uint8_t* data, int length);


NRF::NRF24L01P radio(&STM32::SPI::SPI1, PIN_RADIO_CS, RADIO_FREQ, &receivedHandler, &transmittedHandler);
UART::Bytewise* uart = &STM32::UART::UART1;
UART::Buffered<1024, 16> buf(uart);
uint8_t packet[64];
uint8_t packetPos = 0;
uint8_t discardBytes = 0;


void initRadio()
{
    static const uint8_t address[] = { 0xDD, 0x37, 0xC4 };
    radio.setTxAddress(address, sizeof(address));
    NRF::NRF24L01P::Configuration nrfConfig = { 0 };
    nrfConfig.config.b.powerUp = true;
    nrfConfig.config.b.role = nrfConfig.config.b.Role_PRX;
    nrfConfig.config.b.crcMode = nrfConfig.config.b.CrcMode_16Bit;
    nrfConfig.addressCtl.b.width = nrfConfig.addressCtl.b.Width_24Bit;
    nrfConfig.retransCtl.b.count = 0;
    nrfConfig.retransCtl.b.delay = 5;
    nrfConfig.rfChannel.b.channel = 82;
    nrfConfig.rfSetup.b.power = nrfConfig.rfSetup.b.Power_0dBm;
    nrfConfig.rfSetup.b.dataRate = nrfConfig.rfSetup.b.DataRate_1Mbit;
    nrfConfig.featureCtl.b.ackPayload = true;
    nrfConfig.featureCtl.b.dynLength = true;
    nrfConfig.rxPipeEnable.b.pipe0 = true;
    nrfConfig.autoAckCtl.b.pipe0 = true;
    nrfConfig.dynLengthCtl.b.pipe0 = true;
    radio.configure(&nrfConfig);
}


void initUART()
{
    STM32::UART::UART1.configure(1500000, 1000, {STM32::UART::Config::StopBits1_0, STM32::UART::Config::ParityNone, false, false, false});
}


int main()
{
    initRadio();
    initUART();

    while (true)
    {
        if (!GPIO::getLevel(PIN_RADIO_IRQ)) radio.handleIRQ();

        int av;
        if ((av = buf.readAvailable()))
        {
            if (discardBytes) discardBytes--;
            if (!packetPos)
            {
                *packet = buf.read();
                if (*packet > 64)
                {
                    discardBytes = 64;
                    *packet = 0;
                }
                else if (*packet) packetPos++;
                else uart->bwTx(0);
            }
            else if (packetPos < *packet) packetPos += buf.read(&packet[packetPos], MIN(av, *packet - packetPos));
            if (packetPos && packetPos >= *packet)
            {
                packetPos = 0;
                if (*packet >= 2)
                    switch (packet[1])
                    {
                    case TxPacket:
                    {
                        if (*packet < 3 || *packet > 35) break;
                        NRF::SPI::Status status = radio.getStatus();
                        if (status.b.txFull)
                        {
                            radio.flushTx();
                            uart->bwTx(2);
                            uart->bwTx(TxFlushed);
                        }
                        radio.transmit(((int8_t*)packet)[2], &packet[3], *packet - 3);
                        break;
                    }
                    case TxFlush:
                        if (*packet != 2) break;
                        radio.flushTx();
                        uart->bwTx(2);
                        uart->bwTx(TxFlushed);
                        break;
                    case ConfigRadio:
                    {
                        if (*packet != 11) break;
                        NRF::NRF24L01P::Configuration* cfg = (NRF::NRF24L01P::Configuration*)&packet[2];
                        cfg->config.b.maskDataReceived = false;
                        cfg->config.b.maskDataSent = false;
                        cfg->config.b.maskMaxRetrans = false;
                        radio.configure(cfg);
                        break;
                    }
                    case ConfigAddr:
                        if (*packet < 4 || *packet > 8) break;
                        if (packet[2] & 0x80) radio.setTxAddress(&packet[3], *packet - 3);
                        else radio.setRxAddress(packet[2], &packet[3], *packet - 3);
                        break;
                    case ConfigSize:
                        if (*packet != 3) break;
                        radio.setPacketSize(packet[2] >> 5, packet[2] & 0x3f);
                        break;
                    case ConfigRole:
                        if (*packet != 3) break;
                        radio.setMode(packet[2]);
                        break;
                    case ConfigReset:
                        if (*packet != 2) break;
                        initRadio();
                        break;
                    }
            }
        }
    }
}


void transmittedHandler(bool success, int retransmissions)
{
    if (!success)
    {
        radio.flushTx();
        uart->bwTx(2);
        uart->bwTx(TxFlushed);
    }
    uart->bwTx(3);
    uart->bwTx(TxDone);
    uart->bwTx((!success << 7) | retransmissions);
}


void receivedHandler(int pipe, uint8_t* data, int length)
{
    uart->bwTx(length + 3);
    uart->bwTx(RxPacket);
    uart->bwTx(pipe);
    while (length--) uart->bwTx(*data++);
}
