# 0. Connect UART
# 1. Boot0 jumper ==> to 1
# 2. Press reset button
# 3. Run this script ( change your /dev/ttyUSB0 for the right one):
	../make
	sudo stm32flash -w ../build/*.elf -v -g 0x0800 /dev/ttyUSB0

# 4. Boot0 jumper ==> to 0
# 5. Press reset button
