/* MD2018072802 MD30CR2 Motor Controller and 
  Pittman GM9236s020-r1 motor with HEDS snesor
  Pin 1: Ground,    Black (Bare?)
  Pin 2: Index,     Green (Black?)
  Pin 3: ChannelA,  Yellow
  Pin 4: Vcc,       Red
  Pin 5: ChannelB,  Blue  
*/
  
const int yellowPinA = 2;     // the number of the encoder pin from Motor A
const int yellowPinB = 3;     // the number of the encoder pin from Motor B

const int ledPin =  13;      // the number of the LED pin

// variables will change:

volatile int eventsA = 0;      // variable for storing the number of interrupt events observed from Motor A
volatile int eventsB = 0;      // variable for storing the number of interrupt events observed from Motor B

volatile boolean PRINT=false;
volatile int maxEventsA=0;
volatile int maxEventsB=0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);

  // initialize the interrupt pins (may not be necessary)
  pinMode(yellowPinA, INPUT);
  pinMode(yellowPinB, INPUT);
  
  // Attach an interrupt to the ISR vector
  attachInterrupt(0, pin_ISRA, FALLING);
  attachInterrupt(1, pin_ISRB, FALLING);

  Serial.begin(9600);
  
}

void loop() {
  Serial.print("A: ");
  Serial.print(eventsA);
  Serial.print(" B: ");
  Serial.println(eventsB);
  delay(10);
}

void pin_ISRA() {
  eventsA++;
  if(maxEventsA<eventsA) maxEventsA=eventsA;
}

void pin_ISRB() {
  eventsB++;
  if(maxEventsB<eventsB) maxEventsB=eventsB;
}

