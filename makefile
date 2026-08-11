CC = arm-none-eabi-gcc
CFLAGS = -c -O0 -mcpu=cortex-m3 -mthumb -Wall -fmessage-length=0 -ICore/Inc
LDFLAGS = -mcpu=cortex-m3 -mthumb -Wall --specs=nosys.specs -nostdlib -lgcc -T./Linker/STM32F103.ld

SRCS = $(wildcard Core/Src/*.c)
OBJS = $(SRCS:Core/Src/%.c=%.o) core.o

build:
	$(CC) -x assembler-with-cpp $(CFLAGS) Startup/core.S -o core.o
	$(foreach src, $(SRCS), $(CC) $(CFLAGS) $(src) -o $(notdir $(src:.c=.o));)
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