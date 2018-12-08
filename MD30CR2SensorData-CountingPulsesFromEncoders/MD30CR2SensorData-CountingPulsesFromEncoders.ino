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
volatile int maxEvents=490; // this reflects the number of holes in the disc

void setup() {
  // initialize the LED pin as an output:
  // pinMode(ledPin, OUTPUT);

  // initialize the pushbutton pin as an input
  // and pull it  HIGH by default:
  pinMode(yellowPin, INPUT);
  pinMode(greenPin, INPUT);
  
  // Attach an interrupt to the ISR vector
  attachInterrupt(0, pin_ISR0, FALLING); // this will cause the routine pin_ISR0 to be called whenever a pulse is detected on pin 0
  attachInterrupt(1, pin_ISR1, FALLING); // this will cause the routine pin_ISR1 to be called whenever a pulse is detected on pin 0

  Serial.begin(9600);
  
}

void loop() {
  // Nothing here other than printing out the nuumber of events observed and resetting that value
  if(PRINT==true)
  {
    Serial.println(events);
    events=0;
    PRINT=false;
  }
}

//////////////////////////////////////////////////
void pin_ISR0() {
  // This is an Interrupt Service Routine, it gets called whenever an interrupt is fired
  // I called it ISR0 to indicate it is an Interrupt Service Routine, attached to pin0
  // I could have called it anything, but it makes more sense to use a name that means something
  
  events++; // every time this is called, increment the number of events observed
  if(maxEvents<events) maxEvents=events; // if the max number of events observed is < than events, set the maxEvents vaiable to the number of events observed
  // this bit is not really important, so don't spend time trying to figure out my logic in doing it
}
//////////////////////////////////////////////////
void pin_ISR1() {
  // This is also an Interrupt service routine, but is attached to pin 1
  PRINT=true;
}
//////////////////////////////////////////////////
