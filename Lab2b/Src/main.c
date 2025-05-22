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

uint8_t debounceButton1(void);

int main(void) {
  uint8_t ledCycle = 0;

  /* Stop watchdog timer */
  WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

  /* Port 1 set to GPIO with P1.1 as input with pull-up resistor */
  P1->SEL0 = 0;
  P1->SEL1 = 0;
  P1->DIR &= ~BIT1;
  P1->OUT |= BIT1;
  P1->REN |= BIT1;

  /* Port 2 set to GPIO with P2.0-2 as output, initialize all off */
  P2->SEL0 = 0;
  P2->SEL1 = 0;
  P2->DIR |= (BIT0 | BIT1 | BIT2);
  P2->OUT &= ~(BIT0 | BIT1 | BIT2); // RGB off

  while (1) {
    /* ledCycle cycles 1-3 increasing after each button press */
    if (debounceButton1()) {
      ledCycle++;
      ledCycle = ledCycle == 4 ? 1 : ledCycle;
    }

    /* follow the LED on/off sequence described in title block */
    if (ledCycle == 1) {
      P2->OUT &= ~BIT2; // Blue off
      P2->OUT |= BIT0;  // Red on
    }

    if (ledCycle == 2) {
      P2->OUT &= ~BIT0; // Red off
      P2->OUT |= BIT1;  // Green on
    }

    if (ledCycle == 3) {
      P2->OUT &= ~BIT1; // Green off
      P2->OUT |= BIT2;  // Blue on
    }
  }
}

/// @brief This function is made to debounce the button (S1) MSP432 Launchpad on
/// PORT1 PIN1.
/// @return 1 if a button press occurred. 0 if false bounce or no press
/// occurred.
uint8_t debounceButton1(void) {
  static uint16_t lBounceState = 0x0000;
  lBounceState = (lBounceState << 1) | !(P1->IN & BIT1) | 0xE000;
  if (lBounceState == 0xF000) {
    return 1;
  }
  return 0;
}

/* EOF */
