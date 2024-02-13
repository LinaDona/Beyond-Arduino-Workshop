#define PINMASK(x) (1U << x)
#define CPU_F 16000000L

void setup() {
  DDRB |= PINMASK(5);
  // Set Timer1 to simply count, no compare no waveform generation
  TCCR1A = 0x00;
  // Timer Interrupt Mask. Sets interrupt for timer overflow
  TIMSK1 = (1 << TOIE1);
  // Make Timer1 start counting from 49910 instead of 0
  TCNT1 = 0xFFFF - (CPU_F/1024);
  sei(); // enable interrupts
  // CS = Clock Select | Timer/Counter Control Register (for timer 1)
  // this line sets prescaler to 1024 | 16MHz/1024 = 15625Hz
  TCCR1B = (1 << CS10) | (1 << CS12);
}
void loop() { 
  while(1); 
}

// Timer 1 automatically resets to 0 after overflow,
// so we force it to start from 49910 instead
ISR(TIMER1_OVF_vect){
    PORTB ^= PINMASK(5);
    TCNT1 = 0xFFFF - (CPU_F/1024);
}
