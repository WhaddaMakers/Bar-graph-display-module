/*

  LED BAR GRAPH LIBRARY
  for Whadda WPI471 led bar graph and other TM1561 based LED bar graph modules

  For more information about the example and led bar graph driving library, 
  check the github page README at https://github.com/WhaddaMakers/bar_graph_module
  For more information about the LED bar graph module, consult the manual at the WPI471 product page on whadda.com

  Author: Midas Gossye (Whadda/Velleman)
  Date: 10 March 2021
  URL: https://github.com/WhaddaMakers/bar_graph_module

*/ 
//  Author:Fred.Chu
//  Date:14 August, 2014
//
//
//
//Modified record:
//Autor: 	Detlef Giessmann Germany 
//Mail:	mydiyp@web.de
//Demo for the new 7 LED Battery-Display 2017
//IDE:  	Arduino-1.6.5
//Typ.: 	OPEN-SMART CX10*4RY68  4Color
//Date: 	01.05.2017
/***************************************************************/
/*******************************************************************************/

#ifndef BARGRAPH_H
#define BARGRAPH_H
#include <inttypes.h>
#include <Arduino.h>
	//************definitions for TM1651*********************
#define ADDR_AUTO  0x40
#define ADDR_FIXED 0x44
	
#define STARTADDR  0xc0 
	/**** definitions for the frame of the battery display *******/
#define FRAME_ON   1
#define FRAME_OFF  0
	/**************definitions for brightness***********************/
#define  BRIGHT_DARKEST 0
#define  BRIGHT_TYPICAL 2
#define  BRIGHTEST      7

class BarGraph
{
  public:
	uint8_t Cmd_SetData;
	uint8_t Cmd_SetAddr;
	uint8_t Cmd_DispCtrl;
	BarGraph(uint8_t, uint8_t);
	void init();
	void writeByte(int8_t wr_data);//write 8bit data to BarGraph
	void start(void);//send start bits
	void stop(void); //send stop bits
	void setLevel(uint8_t Level);
	void frame(boolean FrameFlag);
	void clearDisplay(void);
	void set(uint8_t = BRIGHT_TYPICAL,uint8_t = 0x40,uint8_t = 0xc0);//To take effect the next time it displays.
	void setBar(uint8_t);
	void setDot(uint8_t);
  private:
	uint8_t Clkpin;
	uint8_t Datapin;
};
#endif
