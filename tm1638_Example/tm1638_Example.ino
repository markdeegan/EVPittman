/*
Library examples for TM1638.

Copyright (C) 2011 Ricardo Batista <rjbatista at gmail dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <TM1638.h>

// define a module
TM1638 module1(5, 6, 7);

String commsMode="s";
String motorDir="f";
char   LEDSMode=0x0005;

void setup() {
  byte values[]={1, 2, 4, 8, 16, 32, 64, 128};
    module1.setDisplay(values);
    module1.setLEDs(0x00FF);
    Serial.begin(9600);
}

void setCommsMode()
{
  int buttons=module1.getButtons();
  switch(buttons)
  {
    case 128:
      commsMode="s";
      module1.setLEDs(0x0080);
      break;
    case 64:
      commsMode="p";
      module1.setLEDs(0x0040);
      break;
    case 32:
      motorDir="f";
      module1.setLEDs(0x0020);
      break;
    case 16:
      motorDir="r";
      module1.setLEDs(0x0010);
      break;
  }
}

void loop() {
  setCommsMode();
  Serial.print(motorDir);
  Serial.println(commsMode);  
}
