#define BAREMETALDELAY 
#ifndef BAREMETALDELAY
/*-----------------Code with Arduino delay()--------------------*/
#define PINMASK(x) (1U << x)
void setup() {
  DDRB |= PINMASK(5); // pinMode(LED_BUILTIN, OUTPUT); 

}

void loop() {
  PORTB |= PINMASK(5); // digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  PORTB &= ~PINMASK(5); // digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

#else
/*-----------------Code with our simple_delay()--------------------*/
#define PINMASK(x) (1U << x)
void simple_delay();

void setup() {
  DDRB |= PINMASK(5); // pinMode(LED_BUILTIN, OUTPUT); 
}

void loop() {
  PORTB |= PINMASK(5); // digitalWrite(LED_BUILTIN, HIGH);
  simple_delay();
  PORTB &= ~PINMASK(5); // digitalWrite(LED_BUILTIN, LOW);
  simple_delay();
}

void simple_delay(){
  for(volatile uint32_t i=0; i<0x0000FFFF; i++);  
}
#endif



// pre-processor is auto copy-paste
// DDRB is not a variable created in memory, it's a macro
// #define myPORTB *((volatile uint8_t*) 0x25)
// #define myDDRB *((volatile uint8_t*) 0x24)
