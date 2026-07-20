.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.global reset_handler
.global default_handler
.global TIM2_IRQHandler
.global EXTI0_IRQHandler

.section .vector_table,"a",%progbits
vector_table:
    .word _estack
    .word reset_handler
    .word default_handler       /* NMI */
    .word default_handler       /* HardFault */
    .word default_handler       /* MemManage */
    .word default_handler       /* BusFault */
    .word default_handler       /* UsageFault */
    .word 0                     /* reserved */
    .word 0                     /* reserved */
    .word 0                     /* reserved */
    .word 0                     /* reserved */
    .word default_handler       /* SVCall */
    .word default_handler       /* DebugMon */
    .word 0                     /* reserved */
    .word default_handler       /* PendSV */
    .word default_handler       /* SysTick */
    .word default_handler       /* IRQ0  WWDG */
    .word default_handler       /* IRQ1  PVD */
    .word default_handler       /* IRQ2  TAMPER */
    .word default_handler       /* IRQ3  RTC */
    .word default_handler       /* IRQ4  FLASH */
    .word default_handler       /* IRQ5  RCC */
    .word EXTI0_IRQHandler      /* IRQ6  EXTI0 */
    .word default_handler       /* IRQ7  EXTI1 */
    .word default_handler       /* IRQ8  EXTI2 */
    .word default_handler       /* IRQ9  EXTI3 */
    .word default_handler       /* IRQ10 EXTI4 */
    .word default_handler       /* IRQ11 DMA1_CH1 */
    .word default_handler       /* IRQ12 DMA1_CH2 */
    .word default_handler       /* IRQ13 DMA1_CH3 */
    .word default_handler       /* IRQ14 DMA1_CH4 */
    .word default_handler       /* IRQ15 DMA1_CH5 */
    .word default_handler       /* IRQ16 DMA1_CH6 */
    .word default_handler       /* IRQ17 DMA1_CH7 */
    .word default_handler       /* IRQ18 ADC1_2 */
    .word default_handler       /* IRQ19 USB_HP_CAN_TX */
    .word default_handler       /* IRQ20 USB_LP_CAN_RX0 */
    .word default_handler       /* IRQ21 CAN_RX1 */
    .word default_handler       /* IRQ22 CAN_SCE */
    .word default_handler       /* IRQ23 EXTI9_5 */
    .word default_handler       /* IRQ24 TIM1_BRK */
    .word default_handler       /* IRQ25 TIM1_UP */
    .word default_handler       /* IRQ26 TIM1_TRG_COM */
    .word default_handler       /* IRQ27 TIM1_CC */
    .word TIM2_IRQHandler       /* IRQ28 TIM2 */

.section .text
.type reset_handler, %function
reset_handler:
    LDR r0, =_sidata
    LDR r1, =_sdata
    LDR r2, =_edata
    B copy_loop
copy:
    LDR r3, [r0], #4
    STR r3, [r1], #4
copy_loop:
    CMP r1, r2
    BCC copy
    LDR r1, =_sbss
    LDR r2, =_ebss
    MOVS r0, #0
    B zero_loop
zero:
    STR r0, [r1], #4
zero_loop:
    CMP r1, r2
    BCC zero
    BL main
hang:
    B hang
.size reset_handler, .-reset_handler

.type default_handler, %function
default_handler:
    B default_handler
.size default_handler, .-default_handler

.type TIM2_IRQHandler, %function
TIM2_IRQHandler:
    B TIM2_IRQHandler
.size TIM2_IRQHandler, .-TIM2_IRQHandler

.type EXTI0_IRQHandler, %function
EXTI0_IRQHandler:
    B EXTI0_IRQHandler
.size EXTI0_IRQHandler, .-EXTI0_IRQHandler