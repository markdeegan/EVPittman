#include <TM1638.h>
// define a module on data pin 5(8), clock pin 9(6) and strobe pin 7(10)
TM1638 module(7, 5, 6);
unsigned long a=1;
double b=48.7;

void setup()
{
}

void loop()
{
for (a=1; a<=100; a++)
{
module.setDisplayToDecNumber(b,0,false);
delay(100);
}
module.setDisplayToString("Complete");
delay(1000);
}

