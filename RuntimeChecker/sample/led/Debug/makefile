all:
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og \
-fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections \
-ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -T mem.ld \
-T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"../ldscripts" -Wl,-Map,"RuntimeChecker.map" \
--specs=nano.specs -o "RuntimeChecker.elf"  \
./system/src/stm32f4-hal/stm32f4xx_hal.o \
./system/src/stm32f4-hal/stm32f4xx_hal_cortex.o \
./system/src/stm32f4-hal/stm32f4xx_hal_dfsdm.o \
./system/src/stm32f4-hal/stm32f4xx_hal_flash.o \
./system/src/stm32f4-hal/stm32f4xx_hal_gpio.o \
./system/src/stm32f4-hal/stm32f4xx_hal_iwdg.o \
./system/src/stm32f4-hal/stm32f4xx_hal_pwr.o \
./system/src/stm32f4-hal/stm32f4xx_hal_rcc.o  \
./system/src/newlib/_cxx.o \
./system/src/newlib/_exit.o \
./system/src/newlib/_sbrk.o \
./system/src/newlib/_startup.o \
./system/src/newlib/_syscalls.o \
./system/src/newlib/assert.o  \
./system/src/diag/Trace.o \
./system/src/diag/trace_impl.o  \
./system/src/cortexm/_initialize_hardware.o \
./system/src/cortexm/_reset_hardware.o \
./system/src/cortexm/exception_handlers.o \
./system/src/cmsis/system_stm32f4xx.o \
./system/src/cmsis/vectors_stm32f407xx.o  \
./src/BlinkLed.o ./src/Timer.o \
./src/_initialize_hardware.o \
./src/_write.o ./src/main.o \
./src/stm32f4xx_hal_msp.o \
./src/test.o ./src/Signal.o

obj:
	arm-none-eabi-objdump -d RuntimeChecker.elf > obj
	arm-none-eabi-objdump -D RuntimeChecker.elf > OBJ

clean:
	rm -f *.elf obj OBJ

elf2hex:
	arm-none-eabi-objcopy -O ihex RuntimeChecker.elf RuntimeChecker.hex
