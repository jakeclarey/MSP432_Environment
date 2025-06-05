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

int main(void) {
  MAP_WDT_A_holdTimer(); /* Stop watchdog timer */
  GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

  SysTick->CTRL |= 0;
  SysTick->VAL = 0;
  SysTick->LOAD = 750000 - 1;
  SysTick->CTRL |= 5;

  while (1) {
    if (SysTick->CTRL & (1 << 16)) {
      GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
  }
}

/* EOF */
