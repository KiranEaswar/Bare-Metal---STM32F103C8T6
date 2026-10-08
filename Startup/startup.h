#ifndef STARTUP_H
#define STARTUP_H

void reset_handler(void);
void default_handler(void);

void EXTI0_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void TIM2_IRQHandler(void) __attribute__((weak, alias("default_handler")));

#endif
