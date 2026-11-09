#ifndef __TEST_H__
#define __TEST_H__

#include "test.h"
#include "regx52.h"
#include "lcd.h"
#include "config.h"

#define uint unsigned int
#define uchar unsigned char




void DelayMs(uint xms);
void lcd_writecmd(uchar cmd);
void lcd_writedata(uchar dat);
void lcd_init();
void lcd_textwrite(uint textlength,uchar* text,int position);

#endif