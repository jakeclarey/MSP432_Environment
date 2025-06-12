/**
 * Author: Jacob Clarey
 * Instructor: Dr. Parikh
 * Date: 6/10/25
 *
 * Description: 
 */

#include "driverlib.h"
#include "msp.h"

/* Removes error squiggles that are false errors from include path settings */
#include "msp432p401r.h"

uint8_t ledColor = 0;

void SysTickISR(void) { ledColor++; }

int main(void) {
  MAP_WDT_A_holdTimer(); /* Stop watchdog timer */

  /* Port 2 set to GPIO with P2.0-2 as output, initialize all off */
  P2->SEL0 = 0;
  P2->SEL1 = 0;
  P2->DIR |= (BIT0 | BIT1 | BIT2);
  P2->OUT &= ~(BIT0 | BIT1 | BIT2); // RGB off

  /* SysTick enable with interrupts for 2Hz LED flash rate */
  SysTick->CTRL |= 0;
  SysTick->VAL = 0;
  SysTick->LOAD = 750000 - 1;
  SysTick->CTRL |= 7;

  MAP_Interrupt_enableMaster();

  while (1) {
    switch (ledColor) {
    case 0:
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
      break;

    case 1:
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2);
      GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
      break;

    case 2:
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);
      GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
      break;

    case 3:
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1);
      GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
      break;

    default:
      ledColor = 1;
      break;
    }
  }
}

/* EOF */
