/* 
  @@@@@@@@@@@@@@@@@@@@@@                                                                                                                               
  @@@@@@@@@@@@@@@@@@@@@@             @@@.    @@@    @@@.     @@@@    @@@@        @@@@@@@@@        @@@@@@@@@@@@@.     .@@@@@@@@@@@@@        @@@@@@@@@  
  @@@@@%%@@@%%@@@%%@@@@@             @@@@    @@@    @@@@     @@@@    @@@@       @@@@@@@@@@        @@@@@@@@@@@@@@     @@@@@@@@@@@@@@        @@@@@@@@@  
  @@@@@  @@@  @@@  @@@@@             @@@@    @@@    @@@@     @@@@    @@@@       @@@@   @@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@   @@@@ 
  @@@@@            @@@@@             @@@@   @@@@    @@@@     @@@@@@@@@@@@       @@@@   @@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@   @@@@ 
  @@@@@   @    @   @@@@@             @@@@   @@@@    @@@@     @@@@@@@@@@@@       @@@@@@@@@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@@@@@@@@ 
  @@@@@            @@@@@             @@@@###@@@@@##@@@@@     @@@@    @@@@      @@@@@@@@@@@@       #@@@@@###@@@@@     ##@@@@@###@@@@       @@@@@@@@@@@
  @@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@     @@@@    @@@@      @@@@    @@@@@      @@@@@@@@@@@@@@     @@@@@@@@@@@@@@      @@@@     @@@@
  @@@@@@@@@@@@@@@@@@@@@@

  Whadda WPI471 LED BAR GRAPH MODULE example

  This example 

  For more information about the example and GPS library, check the github page README at https://github.com/WhaddaMakers/bar_graph_module
  For more information about the LED bar graph module, consult the manual at the WPI471 product page on whadda.com

  This example is based on the demo program for the Battery Display by Catalex
  Distributed under MIT license
  URL: https://github.com/freekode/TM1651
  Autor: 	Detlef Giessmann Germany 
  Mail:	mydiyp@web.de
  Date: 	01.05.2017

*/

#include "TM1651.h"
#define CLK 3 //pins definitions for TM1651 and can be changed to other ports       
#define DIO 2

TM1651 bargraphDisplay(CLK,DIO);

void setup()
{
  bargraphDisplay.init();
  bargraphDisplay.set(BRIGHTEST); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}
void loop()
{
  dot_display();
  bar_display();
  custom_display();
}

void dot_display()
{
  for(int i=0; i<8; i++) {
    bargraphDisplay.setDot(i);
    delay(500);
  }
}

void bar_display()
{
  for(int i=0; i<8; i++) {
    bargraphDisplay.displayLevel(i);
    delay(500);
  }
}

void custom_display()
{
  uint8_t custom = 0b00101010;

  for(int i=0; i<4; i++) {

    bargraphDisplay.setBar(custom);
    custom = (~custom) & 0b01111111;
    delay(500);
  }
}
