/**
 * Author: Jacob Clarey
 * Instructor: Dr. Parikh
 * Date: 
 *
 * Description:
 */

#include "driverlib.h"
#include "msp.h"

/* Removes error squiggles that are false errors from include path settings */
#include "msp432p401r.h"

void UART0_init(void);
void UART_Send(char c);
void UART_MultiSend(char *s, uint8_t l);

int main(void) {
  /* Stop watchdog timer */
  WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

  /* SysTick no interrupts for 2ms delays */
  SysTick->CTRL |= 0;
  SysTick->VAL = 0;
  SysTick->LOAD = 6000 - 1;
  SysTick->CTRL |= 5;

  UART0_init();

  UART_MultiSend("Hello, World!\n\r", 16);

  while (1) {
  }
}

void UART0_init(void) {

  // Configure UART
  EUSCI_A0->CTLW0 |= BIT0; // Put eUSCI in reset

  EUSCI_A0->MCTLW &= BIT0; // disable oversampling
  EUSCI_A0->BRW = 312;     // 3000000/9600 set baudrate to 9600

  /* 8 data bits, no parity, 1 stop bit */
  EUSCI_A0->CTLW0 &= ~(BITF | BITC | BITB | BITA | BIT9 | BIT8 | BIT3);

  EUSCI_A0->CTLW0 |= BIT7; // Configure eUSCI clock source for SMCLK

  P1->SEL0 |= BIT2 | BIT3; // set 2-UART pin as secondary function

  EUSCI_A0->CTLW0 &= ~BIT0; // Initialize eUSCI
}

void UART_Send(char c) {
  while (!(EUSCI_A0->IFG & BIT1)) {
  }
  EUSCI_A0->TXBUF = c;
  SysTick->VAL = 0;
  while (!(SysTick->CTRL & (1 << 16))) {
  }
}

void UART_MultiSend(char *s, uint8_t l) {
  for (uint32_t i = 0; i < l; i++) {
    UART_Send(s[i]);
  }
}

/* EOF */
