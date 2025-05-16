/**
 * Author: Jacob Clarey
 * Instructor: Dr. Parikh
 * Date: 5/15/25
 * Description: This is the example code from Lab 2. It sets P1 to outputs
 * and toggles them on and off with a delay in between.
 * Notes:
 */

#include "msp.h"
#include "driverlib.h"

/* Removes error squiggles that are false errors from include path settings */
#include "msp432p401r.h"

#define BLINK_DELAY 1000000

int main(void) {
  volatile uint32_t i = 0;
  MAP_WDT_A_holdTimer(); /* Stop watchdog timer */

  P1->SEL0 = 0;
  P1->SEL1 = 0;

  P1->DIR = 255;

  while (1) {
    i++;
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    SysCtlDelay(BLINK_DELAY);
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    SysCtlDelay(BLINK_DELAY);
  }
}
