#include "test.h"
#include "regx52.h"
#include "lcd.h"
#include "config.h"


/*interrupt_service*/
void int_init0(){
	   EA=1;
	   EX0=1;
	   IT0=1;

}

void int_init1(){
	   EA=1;
	   EX1=1;
	   IT1=1;
	   
}

void timer(){
	   TMOD = 0x02;
	   TH0 = 0x0;
	   TL0 = 0x0;
}
void led_on() interrupt 0{
	   P1=0xF0;

}

void led_off() interrupt 2{
     P1=~(0xF0);
}

// PROGRAM 

enum station {
	   Cao_Bao_Road,
	   Xu_Jia_Hui,
	   Shanghai_Railway_Station,
	   People_Square,
	   Minghang_DevZone,
};

enum Door_State{
	   OPENED = 1,
	   OPERATING = 2,
	   CLOSED = 0,

} ;

unsigned char code table1[]={"Next Station : Cao Bao Road.Doors will Cao Bao Road                  "};
unsigned char code table11[]={"Doors will open on the left."};

unsigned char code table2[]={"Next Station :                         Xu Jia Hui.                   "};
unsigned char code table21[]={"Doors will open on the left."}; 

unsigned char code table3[]={"Next Station : Shanghai Railway Station."};//use rolling
unsigned char code table31[]={"Doors will open on the left."};

unsigned char code table4[]={"Next Station :                         People Square.                "};
unsigned char code table41[]={"Doors will open on the left."};

unsigned char code table5[]={"Next Station : Minhang Devlopment Zone.Doors will Cao Bao Road"};//use rolling
unsigned char code table51[]={"Doors will open on the left."};

sbit KEY_DOOR_CONTROL = P3^0;
sbit KEY_PREVIOUS_ITEM = P3^1;
sbit KEY_NEXT_ITEM = P3^2;

sbit Buzzer = P1^7;
sbit DOOR_OPENED = P1^3;
sbit DOOR_CLOSED = P1^5;
sbit WARNING = P1^4;

char val;
	
char button_read(){
	   if(0 == KEY_DOOR_CONTROL || 0 == KEY_PREVIOUS_ITEM || 0 == KEY_NEXT_ITEM ){
		   DelayMs(5);
			 if(0 == KEY_DOOR_CONTROL)
			 {
				 while(0 == KEY_DOOR_CONTROL);
				 DelayMs(5);
				 return 1;
		 }
			 
		  if(0 == KEY_PREVIOUS_ITEM)
			 {
				 while(0 == KEY_PREVIOUS_ITEM);
				 DelayMs(5);
				 return 2;
		 } 
			 
		  if(0 == KEY_NEXT_ITEM)
			 {
				 while(0 == KEY_NEXT_ITEM);
				 DelayMs(5);
				 return 3;
		 } 

   }
			 return 0;	 
}




//freezed show
void radio_LCD1(uint textlength,uchar* text,int position){
  lcd_textwrite(textlength,text,position);
	  DelayMs(5000);
	  lcd_writecmd(0x01);}

//rolling show
void radio_LCD_roll(uint textlength,uchar* text,int position){
	  int i;
	  lcd_textwrite(textlength,text,position);
	  for(i =17;i>0;i--){
			   DelayMs(1000);
		     lcd_writecmd(0x18);
			  
		 }
		 lcd_writecmd(0x01);
	 }

   int a=0;
void radio_operation(){
	
	   if(2 == button_read()){
		  a--;
			 switch(a){
			 case 1:
				 radio_LCD1(60,table1,0x01);
		     radio_LCD_roll(27,table11,0x01);break;
			 case 2:
		     radio_LCD1(60,table2,0x01);
		     radio_LCD_roll(27,table11,0x01);break;
			 case 3:
				 radio_LCD_roll(39,table3,0x01);
		     radio_LCD_roll(27,table11,0x01);break;
			 case 4:
				 radio_LCD1(60,table4,0x01);
		     radio_LCD_roll(27,table11,0x01);break;
			 case 5:
				 radio_LCD_roll(60,table5,0x01);
		     radio_LCD_roll(27,table11,0x01);break;
		 }
		 
		 }
		 else if(3 == button_read()){
		 a++;
		 switch(a){
			 case 1:
				 radio_LCD1(60,table1,0x01);
		     radio_LCD_roll(27,table11,0x01);break;
			 case 2:
		     radio_LCD1(60,table2,0x01);
		     radio_LCD_roll(27,table11,0x01);break;
			 case 3:
				 radio_LCD1(60,table3,0x01);
		     radio_LCD_roll(27,table11,0x01);break;
			 case 4:
				 radio_LCD1(60,table4,0x01);
		     radio_LCD_roll(27,table11,0x01);break;
			 case 5:
				 radio_LCD1(60,table5,0x01);
		     radio_LCD_roll(27,table11,0x01);break;
		 }
		 
		 }
		 

}
	 
//Open or close doors
int i;
void doors_operation(){
	   if(1 == button_read()){
		 DOOR_CLOSED = 1;
		 
		 DOOR_OPENED = 0;
		 for(i = 8;i>0;i--){
		 WARNING = 0;Buzzer = 1;
		 DelayMs(500);
		 WARNING = 1;Buzzer = 0;
		 DelayMs(500);
		 }
		 Buzzer = 1;
		 while(1 != button_read());
		 for(i = 8;i>0;i--){
		 WARNING = 0;Buzzer = 1;
		 DelayMs(500);
		 WARNING = 1;Buzzer = 0;
		 DelayMs(500);
		 }
		 Buzzer = 1;
     DOOR_OPENED = 1;
		 DOOR_CLOSED = 0;
}}
		 
void main(){
	   DOOR_CLOSED = 0;
	   lcd_init();
	   while(1){
		 doors_operation();
	   radio_operation();
	   }
}

