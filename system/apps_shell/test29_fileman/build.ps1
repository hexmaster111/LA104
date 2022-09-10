md build
cd build
rm output.elf
arm-none-eabi-g++ -Wall -Os -Werror -fno-common -mcpu=cortex-m3 -mthumb -msoft-float -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-psabi -DLA104 -MD -I ../ -I ../../../os_host/source/ -c ../source/main.cpp ../source/Manager.cpp ../../../os_host/source/framework/Wnd.cpp -I../../../os_library/include/ 
arm-none-eabi-gcc -fPIC -mcpu=cortex-m3 -mthumb -o output.elf -nostartfiles -T ../app.lds ./main.o ./Manager.o ./Wnd.o -lbios_la104 -L../../../os_library/build
arm-none-eabi-objdump -d -S output.elf > output.asm
../../../../tools/elfstrip/elfstrip output.elf 29fileman_la104.elf
cd ..
# Remove all the files in the build directory
Remove-Item build
