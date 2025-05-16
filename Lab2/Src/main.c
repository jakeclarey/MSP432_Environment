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
 * Notes: This code uses the driverlib static library functions.
 */

#include "driverlib.h"
#include "msp.h"

/* Removes error squiggles that are false errors from include path settings */
#include "msp432p401r.h"

/// @brief This function is made to debounce the button MSP432 Launchpad on
/// PORT1 PIN1.
/// @return 1 if a button press occurred. 0 if false bounce or no press
/// occurred.
bool debounceButton1(void);

int main(void) {
  uint8_t ledCount = 0;

  MAP_WDT_A_holdTimer(); /* Stop watchdog timer */

  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1); // S1
  GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);                  // Red
  GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);                  // Green
  GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);                  // Blue

  while (1) {
    if (debounceButton1()) {
      ledCount++;
      ledCount = ledCount == 4 ? 1 : ledCount;
    }

    switch (ledCount) {
    case 1:
      GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
      break;

    case 2:
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
      GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
      break;

    case 3:
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
      GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
      break;

    default:
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
      break;
    }
  }
}

bool debounceButton1(void) {
  static uint16_t lBounceState = 0x0000;
  lBounceState = (lBounceState << 1) |
                 !GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) | 0xE000;
  if (lBounceState == 0xF000) {
    return true;
  }
  return false;
}

/* EOF */
