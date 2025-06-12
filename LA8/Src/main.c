/**
 * Author: Jacob Clarey
 * Instructor: Dr. Parikh
 * Date: 5/16/25
 *
 * Description: This is the LED cycling code for Lab 2. Upon start up, the RGB
 * LEDs are all off. After pressing S1, the red LED will illuminate and stay on.
 * A second press will turn the red LED off and turn the green LED on. A third
 * press will turn the green LED off and turn the blue LED on. A fourth press
 * will turn the blue LED off and the red LED on. This pattern repeats
 * infinitely.
 *
 * Notes: This code uses the driverlib static library functions. Most likely
 * inefficient
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
