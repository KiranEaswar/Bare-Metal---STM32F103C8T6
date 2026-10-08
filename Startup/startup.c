#include<stdint.h>
#include "startup.h"

extern uint32_t _estack;

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);

void reset_handler(void){
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;

    while (dst < &_edata)
    {
        *dst++ = *src++;
    }

    dst = &_sbss;

    while (dst < &_ebss)
    {
        *dst++ = 0;
    }

    main();

    while(1){}
}

void default_handler(void){
    while(1);
}


__attribute__((section(".vector_table"), aligned(4)))
const uint32_t vector_table[] =
{
    (uint32_t)&_estack,
    (uint32_t)reset_handler,
    (uint32_t)default_handler, //NMI
    (uint32_t)default_handler, //HardFault Handler
    (uint32_t)default_handler, //MemManage
    (uint32_t)default_handler, //BusFault
    (uint32_t)default_handler, //UsageFault
    0,
    0,
    0,
    0,
    (uint32_t)default_handler, //SVCall
    (uint32_t)default_handler, //Debug Monitor
    0,
    (uint32_t)default_handler, //PendSV
    (uint32_t)default_handler, //SysTick
    (uint32_t)default_handler, //WWDG
    (uint32_t)default_handler, //PVD
    (uint32_t)default_handler, //TAMPER
    (uint32_t)default_handler, //RTC
    (uint32_t)default_handler, //FLASH
    (uint32_t)default_handler, //RCC
    (uint32_t)default_handler, //EXTI0
    (uint32_t)default_handler, //EXTI1
    (uint32_t)default_handler, //EXTI2
    (uint32_t)default_handler, //EXTI3
    (uint32_t)default_handler, //EXTI4
    (uint32_t)default_handler, //DMA1_Channel1
    (uint32_t)default_handler, //DMA1_Channel2
    (uint32_t)default_handler, //DMA1_Channel3
    (uint32_t)default_handler, //DMA1_Channel4
    (uint32_t)default_handler, //DMA1_Channel5
    (uint32_t)default_handler, //DMA1_Channel6
    (uint32_t)default_handler, //DMA1_Channel7
    (uint32_t)default_handler, //ADC1_2
    (uint32_t)default_handler, //USB_HP_CAN_TX
    (uint32_t)default_handler, //USB_LP_CAN_RX0
    (uint32_t)default_handler, //CAN_RX1
    (uint32_t)default_handler, //CAN_SCE
    (uint32_t)default_handler, //EXTI9_5
    (uint32_t)default_handler, //TIM1_BRK
    (uint32_t)default_handler, //TIM1_UP
    (uint32_t)default_handler, //TIM1_TRG_COM
    (uint32_t)default_handler, //TIM1_CC
    (uint32_t)default_handler, //TIM2
    (uint32_t)default_handler, //TIM3
    (uint32_t)default_handler, //TIM4
    (uint32_t)default_handler, //I2C1_EV
    (uint32_t)default_handler, //I2C1_ER
    (uint32_t)default_handler, //I2C2_EV
    (uint32_t)default_handler, //I2C2_ER
    (uint32_t)default_handler, //SPI1
    (uint32_t)default_handler, //SPI2
    (uint32_t)default_handler, //USART1
    (uint32_t)default_handler, //USART2
    (uint32_t)default_handler, //USART3
    (uint32_t)default_handler, //EXTI5_10
    (uint32_t)default_handler, //RTCAlarm
    (uint32_t)default_handler, //USBWakeup
    (uint32_t)default_handler, //TIM8_BRK
    (uint32_t)default_handler, //TIM8_UP
    (uint32_t)default_handler, //TIM8_TRG_COM
    (uint32_t)default_handler, //TIM8_CC
    (uint32_t)default_handler, //ADC3
    (uint32_t)default_handler, //FSMC
    (uint32_t)default_handler, //SDIO
    (uint32_t)default_handler, //TIM5
    (uint32_t)default_handler, //SPI3
    (uint32_t)default_handler, //UART4
    (uint32_t)default_handler, //UART5
    (uint32_t)default_handler, //TIM6
    (uint32_t)default_handler, //TIM7
    (uint32_t)default_handler, //DMA2_Channel1
    (uint32_t)default_handler, //DMA2_Channel2
    (uint32_t)default_handler, //DMA2_Channel3
    (uint32_t)default_handler, //DMA2_Channel4_5
    
};