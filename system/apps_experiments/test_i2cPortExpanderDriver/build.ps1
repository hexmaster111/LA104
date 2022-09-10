md build
cd build
rm output.elf


arm-none-eabi-g++ -Os -Werror -fno-common -mcpu=cortex-m3 -mthumb -msoft-float -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-psabi -DLA104 -MD -D _ARM -D STM32F10X_HD -c ../main.cpp ../../../os_host/source/framework/Wnd.cpp -I../../../os_library/include/ -I ../../../os_host/lib/CMSIS/Device/STM32F10x/Include -I ../../../os_host/lib/STM32F10x_StdPeriph_Driver/inc -I ../../../os_host/lib/CMSIS/Include
arm-none-eabi-gcc -fPIC -mcpu=cortex-m3 -mthumb -o output.elf -nostartfiles -T ../app.lds ./main.o ./Wnd.o -lbios_la104 -lm -L../../../os_library/build

../../../../tools/elfstrip/elfstrip output.elf aI2cGPIOExpander.elf


cd ..
Remove-Item build
