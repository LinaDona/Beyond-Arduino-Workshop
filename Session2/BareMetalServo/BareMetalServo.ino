#define PINMASK(x) (1U << x)
#define CPU_F 16000000L
uint16_t pwm_DC = 500; // pwm duty cycle to specify angle, in us
volatile uint8_t delay_count = 0; // counts nbr of Timer 1 OVF interrupts  

void setup(){
  // Set pin 10 as output
  DDRB |= PINMASK(2);
  //config TIMER1 in fast PWM mode (MODE 15)
  // Fast PWM output at pin OC1B 
  // set pin OC1B (PB2/PIN10) at BOTTOM (TCNT1 = 0) and clear it at match with TOP (TCNT0 = OCR1A)
  TCCR1A |= (1 << COM1B1) | (1 << WGM11) | (1 << WGM10); 
  TIMSK1 |= (1 << TOIE1);  //enable  timer0 output OVF interrupt
  TCCR1B |= (1 << WGM12) | (1 << WGM13);
  // Enable Timer1 overflow interrupt
  TIMSK1 |= (1 << TOIE1);  
  OCR1A = 4999; // make output PWM period = 20ms 
  TCNT1 = 0 ; // reset timer count to 0
  OCR1B = (pwm_DC/1000000.0)* CPU_F /64 - 1; // make duty cycle with pwm_DC us
  
  sei();  //enable global interrupts
  // Note: the following line of code starts the timer
  TCCR1B |= (1 << CS11) | (1 << CS10); //config clock source and prescaler value 16MHz/64
}

void loop() {
    //Move servo in steps of 10° clockwize
    for(uint8_t i = 0; i <= 180; i+=10){
      servo_write(i);
      niceDelay(25); // 500ms delay 
    }
    
    //Move servo in steps of 10° counter-clockwize
    for(uint8_t i = 180; i > 0; i-=10){
      servo_write(i);
      niceDelay(25); // 500ms delay
    }
}

void servo_write(int angle) { //update the target angle_pwm
  cli(); // Disable global interrupts
  pwm_DC = map(angle, 0, 180, 500, 2400);
  sei(); // Enable global interrupts
}

ISR(TIMER1_OVF_vect) {
  OCR1B = (pwm_DC / 1000000.0) * CPU_F / 64 - 1;
  delay_count++;
}

void niceDelay(unsigned int n){ // delay = 20ms*n
  cli();
  delay_count = 0;
  sei();
  while(delay_count < n);
}
