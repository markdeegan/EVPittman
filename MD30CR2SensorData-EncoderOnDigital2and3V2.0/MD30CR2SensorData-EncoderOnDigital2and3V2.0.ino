/* MD2018072802 MD30CR2 Motor Controller and 
  Pittman GM9236s020-r1 motor with HEDS snesor
  Pin 1: Ground,    Black (Bare?)
  Pin 2: Index,     Green (Black?)
  Pin 3: ChannelA,  Yellow
  Pin 4: Vcc,       Red
  Pin 5: ChannelB,  Blue  
*/

#include <TM1638.h>

// variables that are changed by the interrupt handlers should be defined volatile

volatile long eventsA = 0;      // variable for storing the number of interrupt events observed from Motor A
volatile long eventsB = 0;      // variable for storing the number of interrupt events observed from Motor B

long RPsA = 0;
long RPsB = 0;

float diff = 0.0; // Difference in speed between Motor A and Motor B

int timer1_counter;             // needed for the timer ISR

const int strobe = 7;
const int clock = 6;
const int data = 5;

int dots = 0x0; // display all decimal points, value in hexadecimal
int leds = 0xFF; // mask to display LEDS

byte keys; // key value
double number; // number to display
// define a module
TM1638 module(data, clock, strobe);


void setup() {

  // set up the display
  module.clearDisplay(); // clear the display
  number = 12345678; // decimal number

  // Attach an interrupt to the ISR vector
  attachInterrupt(0, pin_ISR_A, FALLING);
  attachInterrupt(1, pin_ISR_B, FALLING);

  ////////////////////////////////////////////////////////////
  // initialize timer1 
  // we are going to use this to report revs and other counters
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  // Set timer1_counter to the correct value for our interrupt interval
  // timer1_counter = 64911;  // preload timer 65536-16MHz/256/100Hz
  // timer1_counter = 64286;  // preload timer 65536-16MHz/256/50Hz
  timer1_counter = 3036;     // preload timer 65536-16MHz/256/2Hz
                              // 100Hz, (65536 - (16,000,000/256/2)) = 64911
                              // 50Hz,  (65536 - (16,000,000/256/2)) = 64286
                              // 20Hz,  (65536 - (16,000,000/256/2)) = 62411
                              // 10Hz,  (65536 - (16,000,000/256/2)) = 59286
                              // 5Hz,   (65536 - (16,000,000/256/2)) = 53036
                              // 2Hz,   (65536 - (16,000,000/256/2)) = 34286
                              // 1Hz,   (65536 - (16,000,000/256/2)) = 3036
  
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
  ////////////////////////////////////////////////////////////

  Serial.begin(9600);
}

void loop() {
  // Nothing here!  
  delay(100);
}

void pin_ISR_A() {
  eventsA++;
}

void pin_ISR_B() {
  eventsB++;
}

void printEvents(){
  RPsA=eventsA>>10;
  RPsB=eventsB>>10;
  Serial.print("EventsA: ");
  Serial.print(eventsA);
  Serial.print(" RPsA: ");
  Serial.print(RPsA);
  Serial.print(" EventsB: ");
  Serial.print(eventsB);
  Serial.print(" RPsB: ");
  Serial.print(RPsB);
  Serial.print(" DIFF: ");
  Serial.print(abs(eventsA-eventsB));
  if(eventsA==0){
      module.setDisplayToDecNumber(0, dots);
    diff = 0;
  }
  else{
    diff = (100.0 * (abs(eventsA-eventsB))/eventsA); 
  }
  Serial.print(" DIFF%: "); 
  Serial.println(diff);
  
  module.setDisplayToDecNumber(abs(eventsA-eventsB), dots);
  
  eventsA=0;
  eventsB=0;
}  
//////////////////////////////////////////////////////////////  
ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  TCNT1 = timer1_counter;   // preload timer
  printEvents();
}
