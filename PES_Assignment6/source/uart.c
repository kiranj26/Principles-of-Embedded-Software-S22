/*****************************************************************************
​ *​ ​Copyright​ ​(C)​ 2023 ​by​ Kiran Jojare
​ *
​ *​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary
​ *​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are
​ *​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded
​ *​ ​software.​ Kiran Jojare​ ​and​ ​the​ ​University​ ​of​ ​Colorado​ ​are​ ​not​ ​liable​ ​for
​ *​ ​any​ ​misuse​ ​of​ ​this​ ​material.
​ *
*****************************************************************************/

/**
 * @file uart.c
 * @brief C file for SERIAL UART function
 *
 * This C file contains function defianations for initializing UART and performing read and write operations.
 *
 * @author Kiran Jojare
 * @date   April 9 2022
 * @version 1.0
 *
 * @reference
 * The code in the files "UART.c" and "UART.h" that contains the functions "UART_init" and "UART_IRQ handler" has been sourced
 * from Alexander Dean's Github repository. You can find the link to this repository below..
 * https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/UART.c.
 * Code has been twicked little to incorporated use of LLFIFO and issues observed with queue.
 */


#include <MKL25Z4.H>
#include "uart.h"								// Include the header file for UART
#include "llfifo.h"								// Include the header file for linked list FIFO buffer
#include <stdio.h>								// Include standard input/output header file

#define UART_EIGHT_DATA_BIT  	(1)             // For 8 bit mode of UART
#define UART_PARITY_ENABLE 		(1)			  	// For Even Parity, make it 1
#define UART_TWO_STOP_BIT   	(0)				// For one stop bit, change to 0
#define UART_OVERSAMPLE_RATE 	(16)			// Set the oversample rate to 16
#define BUS_CLOCK 				(24e6)			// Set the bus clock to 24MHz
#define SYS_CLOCK				(24e6)			// Set the system clock to 24MHz
#define MASK 					(8)				// Set Mask
#define LIFO_SIZE				(256)			// Set LLIFO Capacti as 256 elements

#define ERROR_CODE				(-1)			// return -1 as error code
#define SUCCESS_CODE			(0)				// return 0 as success code

#define SET						(1)				// Set the register Mask Bit
#define CLEAR					(0)				// Clear the register Mask Bit

llfifo_t * RX_llfifo, * TX_llfifo;				// Declare two pointers for RX and TX FIFO buffers

void Init_UART0(uint32_t baud_rate) {
	// Declare variables
	uint16_t sbr;

	// Enable UART0 and PORTA clocks
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Disable UART0 transmitter and receiver
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Select the UART0 clock source as the FLL clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(SET);

	// Configure UART0 pins
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Calculate baud rate divider
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));

	// Configure baud rate
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>MASK);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	// Enable UART0 interrupts
	UART0->BDH |= UART0_BDH_RXEDGIE(CLEAR) | UART0_BDH_SBNS(UART_TWO_STOP_BIT) | UART0_BDH_LBKDIE(CLEAR);
	UART0->C1 = UART0_C1_LOOPS(CLEAR) | UART0_C1_M(UART_EIGHT_DATA_BIT) | UART0_C1_PE(UART_PARITY_ENABLE);
	UART0->C3 = UART0_C3_TXINV(CLEAR) | UART0_C3_ORIE(CLEAR)| UART0_C3_NEIE(CLEAR) | UART0_C3_FEIE(CLEAR) | UART0_C3_PEIE(CLEAR);

	// Clear UART0 status flags
	UART0->S1 = UART0_S1_OR(SET) | UART0_S1_NF(SET) | UART0_S1_FE(SET) | UART0_S1_PF(SET);
	UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK;
	UART0->S2 = UART0_S2_MSBF(CLEAR) | UART0_S2_RXINV(CLEAR);

	// Create RX and TX FIFOs
	RX_llfifo = llfifo_create(LIFO_SIZE);
	TX_llfifo = llfifo_create(LIFO_SIZE);

	// Enable UART0 interrupts in NVIC
	NVIC_SetPriority(UART0_IRQn, 2);
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable UART0 receiver interrupt and transmitter
	UART0->C2 |= UART_C2_RIE(SET);
	UART0->C2 |= UART0_C2_RE(SET) | UART0_C2_TE(SET);

	// Clear the UART0 receive data register full flag
	UART0->S1 &= ~UART0_S1_RDRF_MASK;
}


void UART0_IRQHandler(void) {
	__disable_irq(); // Disable interrupts globally

	uint8_t ch;

	// Check if an error occurred
	if (UART0->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK)) {
		// Clear the error flags
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK;

		// Read the data register to clear the RDRF flag
		ch = UART0->D;
	}

	// Check if there is data to read
	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		// Read the data register
		ch = UART0->D;

		// Echo the character back to the sender
		UART0->D = ch;

		// Enqueue the received character into the RX FIFO
		llfifo_enqueue(RX_llfifo, ch);

		// Enable TX interrupts if TX FIFO is not empty
		if (!(UART0->C2 & UART0_C2_TIE_MASK))
		{
			UART0->C2 |= UART0_C2_TIE(SET);
		}
	}

	// Check if the TX register is empty and there is data to transmit
	if ((UART0->C2 & UART0_C2_TIE_MASK) && (UART0->S1 & UART0_S1_TDRE_MASK)) {

		// Dequeue the next character to transmit
		if (TX_llfifo->length > 0) {
			UART0->D = llfifo_dequeue(TX_llfifo);
		}
		else {
			// Disable TX interrupts if TX FIFO is empty
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
	}

	__enable_irq(); // Enable interrupts globally
}

int __sys_write(int handle, char *buf, int size)
{
	int ret_val = ERROR_CODE;  // Initialize return value to -1

	// Wait until there is enough space in the TX_llfifo buffer to write the data
	while((TX_llfifo->capacity - TX_llfifo->length) < size );

	// Enqueue each character from the input buffer to the TX_llfifo buffer and update the return value
	while(*buf != '\0')
	{
		llfifo_enqueue(TX_llfifo, *buf++);
		ret_val = SUCCESS_CODE;
	}

	// If the TX buffer is not currently transmitting, enable transmission by setting TIE flag
	if (!(UART0->C2 & UART0_C2_TIE_MASK))
	{
		UART0->C2 |= UART0_C2_TIE(SET);
	}
	return ret_val;  // Return the status of the operation
}

int __sys_readc(void)
{
	while(llfifo_is_empty(RX_llfifo));  // Wait until there is a character in the RX buffer
	return llfifo_dequeue(RX_llfifo);   // Dequeue and return the first character in the RX buffer
}
