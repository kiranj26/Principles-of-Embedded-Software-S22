/*****************************************************************************
​ ​*​ ​Copyright​ ​(C)​ 2023 ​by​ Kiran Jojare
​ ​*
​ ​*​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary
​ ​*​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are
​ ​*​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded
​ ​*​ ​software.​ Kiran Jojare​ ​and​ ​the​ ​University​ ​of​ ​Colorado​ ​are​ ​not​ ​liable​ ​for
​ ​*​ ​any​ ​misuse​ ​of​ ​this​ ​material.
​ ​*
*****************************************************************************/

/**
 * @file uart.c
 *
 * @brief C file for UART implementation
 */
#include "uart.h"


// Define the oversample rate for UART communication
#define UART_OVERSAMPLE_RATE 	(16)
// Define the system clock frequency
#define SYS_CLOCK 				(24e6)
// Define the number of stop bits
#define STOP_BIT 				(1)
// Define the parity setting
#define PARITY 					(0)
// Define the bit setting
#define BIT 					(0)


//Initialize UART0
void Init_UART0(uint32_t baud_rate) {
    uint16_t sbr;

    //Enable UART0 and PORTA clocks
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

    //Disable UART0 transmit and receive
    UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

    //Select clock source for UART0
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

    //Set PORTA pins for UART0 transmit and receive
    PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
    PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);

    //Set baud rate
    sbr = (uint16_t) ((SYS_CLOCK) / (baud_rate * UART_OVERSAMPLE_RATE));
    UART0->BDH &= ~UART0_BDH_SBR_MASK;
    UART0->BDH |= UART0_BDH_SBR(sbr >> 8);
    UART0->BDL = UART0_BDL_SBR(sbr);
    UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE - 1);

    //Configure receive and transmit settings
    UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(STOP_BIT) | UART0_BDH_LBKDIE(0);
    UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(BIT) | UART0_C1_PE(PARITY);
    UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0) | UART0_C3_NEIE(0)
        | UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

    //Configure status registers
    UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);
    UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

    //Configure interrupt settings
    NVIC_SetPriority(UART0_IRQn, 2);
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);
    UART0->C2 |= UART_C2_RIE(1);

    //Enable UART0 transmit and receive
    UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);
    UART0->S1 &= ~UART0_S1_RDRF_MASK;
}


void UART0_IRQHandler(void)
{
    uint8_t rec_char;
    uint8_t trans_char;

    // Check for any receiver error flags
    if (UART0->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK |
                     UART_S1_FE_MASK | UART_S1_PF_MASK))
    {
        // Clear error flags and read data register to clear the status
        UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
                     UART0_S1_FE_MASK | UART0_S1_PF_MASK;
        rec_char = UART0->D;
    }

    // Check if a character has been received
    if (UART0->S1 & UART0_S1_RDRF_MASK)
    {
        rec_char = UART0->D;
        if (!(cbfifo_capacity(receiver) == cbfifo_length(receiver)))
        {
            cbfifo_enqueue(&rec_char, 1, receiver);
        }
    }

    // Check if transmitter is ready and if there is data in the transmitter buffer
    if ((UART0->C2 & UART0_C2_TIE_MASK) && (UART0->S1 & UART0_S1_TDRE_MASK))
    {
        if (cbfifo_dequeue(&trans_char, 1, transmitter))
        {
            UART0->D = trans_char;
        }
        else
        {
            // No more data to transmit, disable transmitter interrupt
            UART0->C2 &= ~UART0_C2_TIE_MASK;
        }
    }
}


// Write data to UART
int __sys_write(int handle, char *buf, int size)
{
    if (buf == NULL)
    {
        return -1;
    }

    // Wait until there is enough space in the transmitter buffer
    while (cbfifo_length(transmitter) == cbfifo_capacity(transmitter))
    {
        ;
    }

    // Enqueue data to the transmitter buffer
    if (cbfifo_enqueue(buf, size, transmitter) == 0)
    {
        return -1;
    }
    else
    {
        // Enable transmitter interrupt if not already enabled
        if (!(UART0->C2 & UART0_C2_TIE_MASK))
        {
            UART0->C2 |= UART0_C2_TIE(1);
        }
        return 0;
    }
}

// Read a single character from UART
int __sys_readc(void)
{
    int character;

    // Wait until a character has been received
    while (cbfifo_length(receiver) == 0)
    {
        ;
    }

    // Dequeue a character from the receiver buffer
    if (cbfifo_dequeue(&character, 1, receiver) == 1)
    {
        return character;
    }
    else
    {
        return -1;
    }
}

void print_UI()
{
    PRINTF("\n\r+---------------------------------------+\n\r");
    PRINTF("\n\r|       Welcome to Home-Safe System     |\n\r");
    PRINTF("\n\r+---------------------------------------+\n\r");
    delay_100ms();
    PRINTF("\n\r|                                       |\n\r");
    PRINTF("\n\r|  Please select an option:             |\n\r");
    PRINTF("\n\r|                                       |\n\r");
    delay_100ms();
    delay_100ms();
    delay_100ms();
    PRINTF("\n\r|  +---------------------------------+  |\n\r");
    PRINTF("\n\r|  | 'temp'   : Temperature Reading  |  |\n\r");
    delay_100ms();
    delay_100ms();
    delay_100ms();
    PRINTF("\n\r|  | 'hum'    : Humidity Reading     |  |\n\r");
    delay_100ms();
    delay_100ms();
    delay_100ms();
    PRINTF("\n\r|  | 'start'  : Start State Machine  |  |\n\r");
    delay_100ms();
    delay_100ms();
    delay_100ms();
    PRINTF("\n\r|  | 'test'   : Test Hardware        |  |\n\r");
    delay_100ms();
    delay_100ms();
    delay_100ms();
    PRINTF("\n\r|  | 'help'   : List Options         |  |\n\r");
    delay_100ms();
    delay_100ms();
    delay_100ms();
    PRINTF("\n\r|  | 'author' : Print author        |  |\n\r");
    delay_100ms();
    delay_100ms();
    delay_100ms();
    PRINTF("\n\r|  +---------------------------------+  |\n\r");
    delay_100ms();
    delay_100ms();
    delay_100ms();
    PRINTF("\n\r|                                       |\n\r");
    delay_100ms();
    delay_100ms();
    delay_100ms();
    PRINTF("\n\r+---------------------------------------+\n\r");
    delay_100ms();
    delay_100ms();
    delay_100ms();
}

