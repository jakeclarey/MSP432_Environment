/**
 * Author: Jacob Clarey
 * Instructor: Dr. Parikh
 * Date: 5/29/25
 * Description: This is the example code from Lab 2. It sets P1 to outputs
 * and toggles them on and off with a delay in between.
 *
 * Notes:
 */

#include "driverlib.h"
#include "msp.h"

/* Removes error squiggles that are false errors from include path settings */
#include "msp432p401r.h"

#define BLINK_DELAY 1000000

#define LED_DIR (*((volatile unsigned char *)0x42098080))
#define LED_OUT (*((volatile unsigned char *)0x42098040))
// #define LED_OUT_TI_METHOD (*((volatile unsigned long long*)0x40004C04))

int main(void) {
  volatile uint32_t watchReg = P1->OUT;
  MAP_WDT_A_holdTimer(); /* Stop watchdog timer */

  P1->SEL0 = 0;
  P1->SEL1 = 0;

  LED_DIR |= 1;

  while (1) {
    watchReg = P1->OUT;
    LED_OUT = 1;
    SysCtlDelay(BLINK_DELAY);
    LED_OUT = 0;
    SysCtlDelay(BLINK_DELAY);
  }
}
