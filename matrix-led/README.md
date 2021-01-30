# Drive a matrix LED using ATtiny2313.

```bash
avr-gcc -mmcu=attiny2313 -O main.c -o main.o
avr-objcopy -j .text -j .data -O ihex main.o main.hex
avrdude -p attiny2313 -c avrisp2 -U flash:w:main.hex:i -F -P usb
```

![view.jpg](https://raw.githubusercontent.com/akawashiro/AVR-experiment/master/matrix-led/view.jpg)
