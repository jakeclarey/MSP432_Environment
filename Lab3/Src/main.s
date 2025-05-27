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
  BL  LED_INIT
Loop
  BL  LED_TOGGLE

  MOV R0, #1000
  BL  Delay
  
  B Loop

LED_INIT:
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
  MOV   R0, #0x02
  STRB  R0, [R1]

  LDR   R1, P1REN
  MOV   R0, #0x02
  STRB  R0, [R1]

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

LED_TOGGLE:
  LDR   R1, P2OUT
  LDRB  R0, [R1]
  EOR   R0, R0, #0x07
  STRB  R0, [R1]
  BX    LR

Delay:
  MOVS  R1, R0
  BNE   L1
  BX    LR
L1
  MOV   R1, #250
L2
  SUBS  R1, #1
  BNE   L2
  SUBS  R0, #1
  BNE   L1
  BX    LR
  .end