/**
 * Author: Jacob Clarey
 * Instructor: Dr. Parikh
 * Date: 5/29/25
 *
 * Description: This is the LED and button code for Lab 3. Upon start up, the
 * RGB LEDs are all off. While S1 is pressed, the blue LED will illuminate.
 * While S2 is pressed, the red LED will illuminate. While both S1 and S2 are
 * pressed, the only the green LED will illuminate. If no buttons are pressed
 * the LEDs will all remain off.
 *
 */
  .syntax unified
  .thumb

  .text
  .align 2

P1IN    .word   0x40004C00  // PORT 1 INPUT
P1OUT   .word   0x40004C02  // PORT 1 OUTPUT
P1DIR   .word   0x40004C04  // PORT 1 DIRECTION
P1REN   .word   0x40004C06  // PORT 1 RESISTOR ENABLE
P1DS    .word   0x40004C08  // PORT 1 DRIVE STRENGTH
P1SEL0  .word   0x40004C0A  // PORT 1 SELECT 0
P1SEL1  .word   0x40004C0C  // PORT 1 SELECT 1

P2IN    .word   0x40004C01  // PORT 2 INPUT
P2OUT   .word   0x40004C03  // PORT 2 OUTPUT
P2DIR   .word   0x40004C05  // PORT 2 DIRECTION
P2REN   .word   0x40004C07  // PORT 2 RESISTOR ENABLE
P2DS    .word   0x40004C09  // PORT 2 DRIVE STRENGTH
P2SEL0  .word   0x40004C0B  // PORT 2 SELECT 0
P2SEL1  .word   0x40004C0D  // PORT 2 SELECT 1

  .global main
  .thumb_func

main:
  BL  GPIO_INIT
Loop
  BL  READ_S1_S2    // Keep S1 and S2 state in R3
  MOV R3, R0        // R0 changes in following subroutines, R3 does not

  CMP R3, #0x12     // True if no buttons are pressed
  IT  EQ
  BLEQ  RGB_OFF

  CMP R3, #0x02     // True if S2 is pressed
  IT  EQ
  BLEQ  RED_ONLY

  CMP R3, #0x10     // True if S1 is pressed
  IT  EQ
  BLEQ  BLUE_ONLY

  CMP R3, #0x00     // True if S1 and S2 are pressed
  IT  EQ
  BLEQ  GREEN_ONLY
  
  B Loop

GPIO_INIT:
  /* The P1XXXX lines are to set P1.1 + P1.4 to input with pull-up resistors */
  LDR   R1, P1SEL0
  MOV   R0, #0x00   
  STRB  R0, [R1]

  LDR   R1, P1SEL1
  MOV   R0, #0x00
  STRB  R0, [R1]

  LDR   R1, P1DIR
  MOV   R0, #0x00
  STRB  R0, [R1]

  LDR   R1, P1OUT
  MOV   R0, #0x12
  STRB  R0, [R1]

  LDR   R1, P1REN
  MOV   R0, #0x12
  STRB  R0, [R1]

  /* The P2XXXX lines are to set P2.0-2 to output */
  LDR   R1, P2SEL0
  MOV   R0, #0x00
  STRB  R0, [R1]

  LDR   R1, P2SEL1
  MOV   R0, #0x00
  STRB  R0, [R1]

  LDR   R1, P2DIR
  MOV   R0, #0x07
  STRB  R0, [R1]

  LDR   R1, P2OUT
  MOV   R0, #0x00
  STRB  R0, [R1]
  BX    LR

RED_ONLY:
  LDR   R1, P2OUT   // Load P2->OUT address into R1
  LDRB  R0, [R1]    // Load the value at the address into R0
  MOV   R0, #0x01   // Modify all bits of value to 0 except bit 0 for Red On
  STRB  R0, [R1]    // Store new value at the peripheral address
  BX    LR          // Branch back to main

GREEN_ONLY:
  LDR   R1, P2OUT   // Load P2->OUT address into R1
  LDRB  R0, [R1]    // Load the value at the address into R0
  MOV   R0, #0x02   // Modify all bits of value to 0 except bit 1 for Green On
  STRB  R0, [R1]
  BX    LR

BLUE_ONLY:
  LDR   R1, P2OUT   // Load P2->OUT address into R1
  LDRB  R0, [R1]    // Load the value at the address into R0
  MOV   R0, #0x04   // Modify all bits of value to 0 except bit 2 for Blue On
  STRB  R0, [R1]    // Store new value at the peripheral address
  BX    LR          // Branch back to main

RGB_OFF:
  LDR   R1, P2OUT   // Load P2->OUT address into R1
  LDRB  R0, [R1]    // Load the value at the address into R0
  MOV   R0, #0x00   // Modify all bits of value to 0 for RGB Off
  STRB  R0, [R1]    // Store new value at the peripheral address
  BX    LR          // Branch back to main

READ_S1_S2:
  LDR   R0, P1IN        // Load P1->IN address into R0
  LDRB  R1, [R0]        // Load the value at the address into R1
  AND   R0, R1, #0x12   // Clear R0, keeping values of bits 4 and 1
  BX    LR              // Branch back to main
  
  .end