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

  This example program shows how you can use the LED bar graph module to display various patterns.
  The library enables 3 different driving modes: 
    - Dot mode: where only 1 combined segment lights up for a set level amount
    - Bar mode: all segments light up to the set level
    - Custom mode: where an arbitrary pattern can be set

  The following code shows an example of each mode that will display consecutively

  For more information about the example and led bar graph driving library, check the github page README at https://github.com/WhaddaMakers/bar_graph_module
  For more information about the LED bar graph module, consult the manual at the WPI471 product page on whadda.com

  This example is based on the demo program for the Battery Display by Catalex
  Distributed under MIT license
  URL: https://github.com/freekode/TM1651
  Autor: 	Detlef Giessmann Germany 
  Mail:	mydiyp@web.de
  Date: 	01.05.2017

*/

#include <BarGraph.h>

//pins definitions for LED bar graph module (can be changed to other pins)
#define CLK 3 // CLK pin
#define DIO 2 // DIO pin

BarGraph bargraphDisplay(CLK,DIO); // Create BarGraph module object, setup pins

void setup()
{
  bargraphDisplay.init(); // Initialise bar graph module
  bargraphDisplay.set(BRIGHTEST); // Set brightness, BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}
void loop()
{
  dot_display(); // Show dot mode display example
  bar_display(); // Show bar mode display example
  custom_display(); // Show custom mode display example
}

// DOT MODE EXAMPLE
void dot_display()
{
  for(int i=0; i<8; i++) {
    bargraphDisplay.setDot(i); // Set bargraph dot to level i
    delay(500);
  }
}

// BAR MODE EXAMPLE
void bar_display()
{
  for(int i=0; i<8; i++) {
    bargraphDisplay.setLevel(i); // Set bargraph bars up to level i
    delay(500);
  }
}

// CUSTOM MODE EXAMPLE
void custom_display()
{
  uint8_t custom = 0b00101010; // Set initial custom pattern, bits 0-6 represent states of segments, bit 7 is ignored 

  for(int i=0; i<4; i++) {

    bargraphDisplay.setBar(custom); // Set bargraph to custom bit pattern
    custom = (~custom) & 0b01111111; // Invert all bits, and with all 1's except highest bit to make sure bit 7 is always set to zero (and ignored)
    delay(500);
  }
}
