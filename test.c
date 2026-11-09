#include "test.h"
#include "regx52.h"
#include "lcd.h"
#include "config.h"

#define DATA_PORT P0


sbit RS=P2^6;
sbit RW=P2^5;
sbit E=P2^7;

void DelayMs(uint xms){
	   uint i,j;
     for(i=xms;i>0;i--){
		    for(j=110;j>0;j--);
		 }
}


void lcd_writecmd(unsigned char cmd /*Enter the command that you need here*/){
	   RS=0; //write instruction
	   RW=0;
	   E=1;  //enable storing command
	   DATA_PORT=cmd; 
	   DelayMs(2);
	   E=0;  // finish storing command
}

/*This function is for entering the dat that you need here*/
void lcd_writedata(unsigned char dat /*FORMAT:COMMAND + ADDRESS E.G. 0x80+0x05=0x85*/){
	   RS=1;  //write dat
	   RW=0;
	   E=1;
	   DATA_PORT=dat;
	   DelayMs(2);
	   E=0;
}

void lcd_init(){
     lcd_writecmd(0x38); //function set
	   lcd_writecmd(0x0C); //Display switch
	   lcd_writecmd(0x06); //input set
	   lcd_writecmd(0x01); //screen clear
}

// show text-string
void lcd_textwrite(uint textlength,uchar* text,int position){
     uint a;
	   uint b=0x80+position;
	   lcd_writecmd(b);
	   
	   for(a=0;a<textlength;a++){
		     lcd_writedata(text[a]);
		 }
     

}


