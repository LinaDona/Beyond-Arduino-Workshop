default: app.bin
	avr-objcopy -O ihex -R .eeprom app.bin app.hex

flash: app.hex
	avrdude -F -V -c arduino -p ATmega328P -P COM3 -b 115200 -U flash:w:app.hex:i

app.bin: myHAL.o app.o
	avr-gcc -mmcu=atmega328p myHAL.o app.o -o app.bin

myHAL.o: myHAL.c myHAL.h
	avr-gcc -mmcu=atmega328p -c myHAL.c -o myHAL.o

app.o: app.c myHAL.h
	avr-gcc -mmcu=atmega328p -c app.c -o app.o

clean:
	-rm *.o 
	-rm *.hex
	-rm *.bin

	



