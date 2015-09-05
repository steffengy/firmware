#pragma once

#define STM32_GPIO_CONFIG \
{ \
    GPIO_CONFIG_PORT( /* PORTA */ \
        /* PA 0 */ MODE_INPUT, TYPE_PUSHPULL, SPEED_2MHZ, PULL_UP, INITCTL_SET, INITVAL_LOW, SPECIAL_SYS, /* Radio IRQ */ \
        /* PA 1 */ MODE_OUTPUT, TYPE_PUSHPULL, SPEED_2MHZ, PULL_NONE, INITCTL_SET, INITVAL_HIGH, SPECIAL_SYS, /* Radio CS */ \
        /* PA 2 */ MODE_SPECIAL, TYPE_PUSHPULL, SPEED_2MHZ, PULL_NONE, INITCTL_SET, INITVAL_LOW, SPECIAL_USART1_PA2, /* UART TX */ \
        /* PA 3 */ MODE_SPECIAL, TYPE_PUSHPULL, SPEED_2MHZ, PULL_NONE, INITCTL_SET, INITVAL_LOW, SPECIAL_USART1_PA3, /* UART RX */ \
        /* PA 4 */ MODE_OUTPUT, TYPE_PUSHPULL, SPEED_2MHZ, PULL_NONE, INITCTL_SET, INITVAL_LOW, SPECIAL_SYS, /* LED */ \
        /* PA 5 */ MODE_SPECIAL, TYPE_PUSHPULL, SPEED_50MHZ, PULL_NONE, INITCTL_SET, INITVAL_LOW, SPECIAL_SPI1, /* SPI SCK */ \
        /* PA 6 */ MODE_SPECIAL, TYPE_PUSHPULL, SPEED_50MHZ, PULL_UP, INITCTL_SET, INITVAL_LOW, SPECIAL_SPI1, /* SPI MISO */ \
        /* PA 7 */ MODE_SPECIAL, TYPE_PUSHPULL, SPEED_50MHZ, PULL_UP, INITCTL_SET, INITVAL_LOW, SPECIAL_SPI1, /* SPI MOSI */ \
        /* PA 8 */ MODE_INPUT, TYPE_PUSHPULL, SPEED_2MHZ, PULL_NONE, INITCTL_SET, INITVAL_LOW, SPECIAL_SYS, /* nonpresent */ \
        /* PA 9 */ MODE_INPUT, TYPE_PUSHPULL, SPEED_2MHZ, PULL_NONE, INITCTL_SET, INITVAL_LOW, SPECIAL_SYS, /* unused */ \
        /* PA10 */ MODE_INPUT, TYPE_PUSHPULL, SPEED_2MHZ, PULL_NONE, INITCTL_SET, INITVAL_LOW, SPECIAL_SYS, /* unused */ \
        /* PA11 */ MODE_INPUT, TYPE_PUSHPULL, SPEED_2MHZ, PULL_NONE, INITCTL_SET, INITVAL_LOW, SPECIAL_SYS, /* nonpresent */ \
        /* PA12 */ MODE_INPUT, TYPE_PUSHPULL, SPEED_2MHZ, PULL_NONE, INITCTL_SET, INITVAL_LOW, SPECIAL_SYS, /* nonpresent */ \
        /* PA13 */ MODE_SPECIAL, TYPE_PUSHPULL, SPEED_50MHZ, PULL_NONE, INITCTL_SET, INITVAL_LOW, SPECIAL_SYS, /* SWDIO */ \
        /* PA14 */ MODE_SPECIAL, TYPE_PUSHPULL, SPEED_50MHZ, PULL_NONE, INITCTL_SET, INITVAL_LOW, SPECIAL_SYS, /* SWCLK */ \
        /* PA15 */ MODE_INPUT, TYPE_PUSHPULL, SPEED_2MHZ, PULL_NONE, INITCTL_SET, INITVAL_LOW, SPECIAL_SYS, /* nonpresent */ \
    ), \
}

#define VERSION "0.1.0"


#define RADIO_FREQ 12000000
#define PIN_RADIO_IRQ PIN_A0
#define PIN_RADIO_CS PIN_A1

#define STACK_SIZE 1024

#define GPIO_SUPPORT_FAST_MODE
#define STM32_ENABLE_SPI
#define STM32_ENABLE_UART
#include "board/flexperiment/nano/target.h"
