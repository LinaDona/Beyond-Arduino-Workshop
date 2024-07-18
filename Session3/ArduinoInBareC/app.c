#include "myHAL.h"

void setup(){
  HW_init();
  enableInterrupts();
  timer_start();
}

void loop() {
  uint8_t i;
  //Move servo in steps of 10° counter-clockwize
  for(i = 0; i <= 180; i+=10){
    servo_write(i);
    niceDelay(25); // 500ms delay 
  }
    
  //Move servo in steps of 10° clockwize
  for(i = 180; i > 0; i-=10){
    servo_write(i);
    niceDelay(25); // 500ms delay
  }
}

int main(){
  setup();
  while(1){
    loop();
  }
}

