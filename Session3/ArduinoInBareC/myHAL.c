#include "myHAL.h"

volatile uint8_t delay_count = 0; // counts nbr of Timer 1 OVF interrupts 
uint16_t pwm_DC = 500; // pwm duty cycle to specify angle, in us

ISR(TIMER1_OVF_vect) {
  OCR1B = (pwm_DC / 1000000.0) * F_CPU / 64 - 1;
  delay_count++;
}

void HW_init(){
  // Set pin 10 as output
  DDRB |= PINMASK(2);
  // config TIMER1 in fast PWM mode (MODE 15)
  // Fast PWM output at pin OC1B 
  // set pin OC1B (PB2/PIN10) at BOTTOM (TCNT1 = 0) and clear it at match with TOP (TCNT0 = OCR1A)
  TCCR1A |= (1 << COM1B1) | (1 << WGM11) | (1 << WGM10); 
  TCCR1B |= (1 << WGM12) | (1 << WGM13);
  // Enable Timer1 overflow interrupt
  TIMSK1 |= (1 << TOIE1);  
  OCR1A = 4999; // make output PWM period = 20ms 
  TCNT1 = 0 ; // init timer counter to 0
  OCR1B = (pwm_DC/1000000.0)* F_CPU /64 - 1; // make duty cycle with pwm_DC us
}

void timer_start(){
  // Note: the following line of code starts the timer
  TCCR1B |= (1 << CS11) | (1 << CS10); //config clock source with prescaler value 64
}

void servo_write(int angle) { //update the target angle_pwm
  cli(); // Disable global interrupts
  pwm_DC = map(angle, 0, 180, 500, 2400);
  sei(); // Enable global interrupts
}

void niceDelay(uint8_t n){ // delay = 20ms*n, max delay is 5.1s
  cli();
  delay_count = 0;
  sei();
  while(delay_count < n);
}


void enableInterrupts(){ // Enable global interrupts
    sei(); 
}

int map(long x, long in_min, long in_max, long out_min, long out_max) {
  return ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}