#define PINMASK(x) (1U << x); 

void setup() {
  DDRB |= PINMASK(5); // pinMode(13,OUTPUT);
}

void loop() {
  servo_write(90, 1000);
  servo_write(0, 1000);
  servo_write(180, 1000);
}

void servo_write(uint8_t angle, uint16_t iters){
    int pwm  = map(angle, 0, 180, 500, 2400); // map angle to pulse width
    
    for(int i = 0; i < iters; i++){ //generate a PWM signal for a certain nbr of iters
      PORTB |=  PIN_13_Msk;     //pin 13 -> HIGH 
      delayMicroseconds(pwm);   //pulse width delay
      PORTB &= ~PIN_13_Msk;     //pin 13 -> LOW
      delayMicroseconds(20000 - pwm); //delay for getting a 20 ms clock period
    }
}
