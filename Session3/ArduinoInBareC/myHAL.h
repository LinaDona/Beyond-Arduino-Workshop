#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>


#define PINMASK(x) (1U << x)
#define F_CPU 16000000UL

void HW_init();
void niceDelay(uint8_t n);
void timer_start();
void enableInterrupts();
void servo_write(int angle);
int map(long x, long in_min, long in_max, long out_min, long out_max);
