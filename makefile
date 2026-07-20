CC = arm-none-eabi-gcc
CFLAGS = -c -O0 -mcpu=cortex-m3 -mthumb -Wall -fmessage-length=0
LDFLAGS = -mcpu=cortex-m3 -mthumb -Wall --specs=nosys.specs -nostdlib -lgcc -T./STM32F103.ld
OBJS = core.o main.o rcc.o gpio.o tim.o flash.o

build:
	$(CC) -x assembler-with-cpp $(CFLAGS) core.S -o core.o
	$(CC) $(CFLAGS) main.c -o main.o
	$(CC) $(CFLAGS) rcc.c -o rcc.o
	$(CC) $(CFLAGS) gpio.c -o gpio.o
	$(CC) $(CFLAGS) tim.c -o tim.o
	$(CC) $(CFLAGS) flash.c -o flash.o
	$(CC) $(OBJS) $(LDFLAGS) -o main.elf
	arm-none-eabi-objcopy -O binary main.elf main.bin

flash:
	st-flash write main.bin 0x08000000

run:
	gdb-multiarch main.elf

clean:
	rm -f *.o *.elf *.bin

debug:
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg

debug2:
	openocd -f interface/stlink.cfg -c "set CPUTAPID 0x2ba01477" -f target/stm32f1x.cfg