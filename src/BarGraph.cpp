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
#include "BarGraph.h"
#include <Arduino.h>
static int8_t LevelTab[] = 
{0x00,0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f};//Level 0~7

BarGraph::BarGraph(uint8_t Clk, uint8_t Data)
{
  Clkpin = Clk;
  Datapin = Data;
  pinMode(Clkpin,OUTPUT);
  pinMode(Datapin,OUTPUT);
}

void BarGraph::init()
{
  set(BRIGHT_TYPICAL);
  clearDisplay();
}

void BarGraph::writeByte(int8_t wr_data)
{
  uint8_t i,count1;   
  for(i=0;i<8;i++)        //sent 8bit data
  {
    digitalWrite(Clkpin,LOW);      
    if(wr_data & 0x01)digitalWrite(Datapin,HIGH);//LSB first
    else digitalWrite(Datapin,LOW);
	delayMicroseconds(3);
    wr_data >>= 1;      
    digitalWrite(Clkpin,HIGH);
	delayMicroseconds(3);
      
  }  
  digitalWrite(Clkpin,LOW); //wait for the ACK
  digitalWrite(Datapin,HIGH);
  digitalWrite(Clkpin,HIGH);     
  pinMode(Datapin,INPUT);
  while(digitalRead(Datapin))    
  { 
    count1 +=1;
    if(count1 == 200)//
    {
     pinMode(Datapin,OUTPUT);
     digitalWrite(Datapin,LOW);
     count1 =0;
    }
    pinMode(Datapin,INPUT);
  }
  pinMode(Datapin,OUTPUT);
  
}
//send start signal to BarGraph
void BarGraph::start(void)
{
  digitalWrite(Clkpin,HIGH);//send start signal to BarGraph
  digitalWrite(Datapin,HIGH);
  delayMicroseconds(2);
  digitalWrite(Datapin,LOW); 
  digitalWrite(Clkpin,LOW); 
} 
//End of transmission
void BarGraph::stop(void)
{
  digitalWrite(Clkpin,LOW);
 // delayMicroseconds(2);
  digitalWrite(Datapin,LOW);
//  delayMicroseconds(2);
  digitalWrite(Clkpin,HIGH);
 // delayMicroseconds(2);
  digitalWrite(Datapin,HIGH); 
}
//******************************************
void BarGraph::setLevel(uint8_t Level)
{
  if(Level > 7)return;//Level should be 0~7
  start();          //start signal sent to BarGraph from MCU
  writeByte(ADDR_FIXED);//
  stop();           //
  start();          //
  writeByte(0xc0);//
  writeByte(LevelTab[Level]);//
  stop();            //
  start();          //
  writeByte(Cmd_DispCtrl);//
  stop();           //
}

void BarGraph::setBar(uint8_t value)
{
  start();          //start signal sent to BarGraph from MCU
  writeByte(ADDR_FIXED);//
  stop();           //
  start();          //
  writeByte(0xc0);//
  writeByte(value);//
  stop();            //
  start();          //
  writeByte(Cmd_DispCtrl);//
  stop();           //
}

void BarGraph::setDot(uint8_t level) {
  if(level == 0) setBar(0x00);
  else {
    setBar(0x01<<(level-1));
  }
}

void BarGraph::frame(boolean FrameFlag)
{
  int8_t SegData;
  if (FrameFlag == 1) SegData = 0x40;
  else SegData = 0x00;
  start();          //start signal sent to BarGraph from MCU
  writeByte(ADDR_AUTO);//
  stop();           //
  start();          //
  writeByte(0xc1);//
  for(uint8_t i=0;i < 3;i ++)
  {
    writeByte(SegData);        //
  }
  stop();           //
  start();          //
  writeByte(Cmd_DispCtrl);//
  stop();           //
}

void BarGraph::clearDisplay(void)
{
  setLevel(0);
  frame(FRAME_OFF);
}
//To take effect the next time it displays.
void BarGraph::set(uint8_t brightness,uint8_t SetData,uint8_t SetAddr)
{
  Cmd_SetData = SetData;
  Cmd_SetAddr = SetAddr;
  Cmd_DispCtrl = 0x88 + brightness;//Set the brightness and it takes effect the next time it displays.
}

