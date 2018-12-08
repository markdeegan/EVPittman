/* MD2018072802 MD30CR2 Motor Controller and 
  Pittman GM9236s020-r1 motor with HEDS snesor
  Pin 1: Ground,    Black (Bare?)
  Pin 2: Index,     Green (Black?)
  Pin 3: ChannelA,  Yellow
  Pin 4: Vcc,       Red
  Pin 5: ChannelB,  Blue  
*/
  
const int yellowPin = 2;     // the number of the pushbutton pin
const int greenPin = 3;
// const int ledPin =  13;      // the number of the LED pin

// variables will change:
// volatile int greenState = 0; // variable for reading the green sensor status
volatile int events = 0;      // variable for storing the number of interrupt events observed
volatile boolean PRINT=false;
volatile int maxEvents=490;

void setup() {
  // initialize the LED pin as an output:
  // pinMode(ledPin, OUTPUT);

  // initialize the pushbutton pin as an input
  // and pull it  HIGH by default:
  pinMode(yellowPin, INPUT);
  pinMode(greenPin, INPUT);
  
  // Attach an interrupt to the ISR vector
  attachInterrupt(0, pin_ISR0, FALLING);
  attachInterrupt(1, pin_ISR1, FALLING);

  Serial.begin(9600);
  
}

void loop() {
  // Nothing here!  
  if(PRINT==true)
  {
    Serial.println(maxEvents);
    events=0;
    PRINT=false;
  }
}

void pin_ISR0() {
  events++;
  if(maxEvents<events) maxEvents=events;
}

void pin_ISR1() {
  PRINT=true;
}

