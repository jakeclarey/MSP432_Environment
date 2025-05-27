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
 * Notes:
 */

#include "msp.h"

/* Removes error squiggles that are false errors from include path settings */
#include "msp432p401r.h"

unsigned short debounceButton1(void);

int main(void) {
  unsigned int ledCycle = 0;

  /* Port 1 set to GPIO with P1.1 as input with pull-up resistor */
  *((unsigned long long *)0x40004C0A) = 0;
  P1->SEL1 = 0;     // cannot get working using memory address writing
  P1->DIR &= ~0x02; // cannot get working using memory address writing
  *((unsigned long long *)0x40004C02) |= 0x02;
  *((unsigned long long *)0x40004C06) |= 0x02;

  /* Port 2 set to GPIO with P2.0-2 as output, initialize all off */
  *((unsigned long long *)0x40004C0B) = 0;
  *((unsigned long long *)0x40004C0D) = 0;
  *((unsigned long long *)0x40004C05) |= (0x01 | 0x02 | 0x04);
  *((unsigned long long *)0x40004C03) &= ~(0x01 | 0x02 | 0x04); // RGB off

  while (1) {
    /* ledCycle cycles 1-3 increasing after each button press */
    if (debounceButton1()) {
      ledCycle++;
      ledCycle = ledCycle == 4 ? 1 : ledCycle;
    }

    /* follow the LED on/off sequence described in title block */
    if (ledCycle == 1) {
      *((unsigned long long *)0x40004C03) &= ~0x04; // Blue off
      *((unsigned long long *)0x40004C03) |= 0x01;  // Red on
    }

    if (ledCycle == 2) {
      *((unsigned long long *)0x40004C03) &= ~0x01; // Red off
      *((unsigned long long *)0x40004C03) |= 0x02;  // Green on
    }

    if (ledCycle == 3) {
      *((unsigned long long *)0x40004C03) &= ~0x02; // Green off
      *((unsigned long long *)0x40004C03) |= 0x04;  // Blue on
    }
  }
}

/// @brief This function is made to debounce the button (S1) MSP432 Launchpad on
/// PORT1 PIN1.
/// @return 1 if a button press occurred. 0 if false bounce or no press
/// occurred.
unsigned short debounceButton1(void) {
  static unsigned short lBounceState = 0x0000;

   /* cannot get working using memory address writing */
  lBounceState = (lBounceState << 1) | !((P1->IN) & 0x02) | 0xE000;
  if (lBounceState == 0xF000) {
    return 1;
  }
  return 0;
}

/* EOF */
