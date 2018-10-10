
#include <stdio.h>
#include <stdlib.h>
#include <xlcd.h>
#include <delays.h>
#include <usart.h>
#include "LCD_head.h"



void write_string(int line, int position, unsigned char msg[]){
    int index = 0;
    lcd_clear();
    set_lcd_pos(line,position);
    
    while(msg[index] != '\0'){
        write_lcd(msg[index]);
        lcd_wait();
        index++;
    }
}

void lcd_clear(void){
    commandLCD(0b11000000);       // Clear screen
    commandLCD(0b11000001);       //
    lcd_wait();
}

void write_lcd(unsigned char msg){
    unsigned char upper =0;
    unsigned char lower =0;
    unsigned char temp = 0;
    //commandLCD(0b11010100); // Higher nibble of H
    //commandLCD(0b11011000); // Lower nibble of H  
    upper = 0b11010000 | ((msg >> 4)& 0x0F);
    lower = 0b11010000 | (msg & 0x0F);
    
    commandLCD(upper);
    commandLCD(lower);
}

void set_lcd_pos(int line, int position){
    
    unsigned char upper =0;
    unsigned char lower =0;
    unsigned char temp = 0;   
    
    // Determine which line to print on
    if(line == 0){
        temp = position;
    }else if(line == 1){
        temp = position + 64;
    }else{
        // Do nothing
    }
    
    upper = 0b11001000 | ((temp >> 4) & 0x0F);
    lower = 0b11000000 | (temp & 0x0F);
    //0b11001100
    //0b11000100
    commandLCD(upper); // A goto w/ 3MSB for location
    commandLCD(lower); // 4 LSB of location
}


void LCDInit(void)
{
  int i = 0;
  PWR_DIR = OUTP;             // Power line as output
  EN_DIR  = OUTP;             // LCD enable as output
  RW_DIR  = OUTP;             // LCD R/W as output
  RS_DIR  = OUTP;             // LCD register select as output
  D4_DIR  = OUTP;             // LCD data 0 as output
  D5_DIR  = OUTP;             // LCD data 1 as output
  D6_DIR  = OUTP;             // LCD data 2 as output
  D7_DIR  = OUTP;             // LCD data 3 as output

  PWR = DISABLE;                      // Peace of mind only!
  PWR = ENABLE;                       // Turns the LCD display on
  RS = CLEAR;                 // Set LCD in command mode
  RW = WRITE;                 // LCD receives data on bus => write mode
  EN = DISABLE;               // LCD enable data receive (LCD reads whatever is on the bus
  EN = ENABLE;                // Now LCD sets data when requested

  //WaitLCD();
  //WaitLCD();
  for(i = 0; i < 1000; i++){
  Nop();
  }
  commandLCD(0b11000010);
  //WriteNibble(TRUE,0x02);         // Move cursor to top left position
  lcd_wait();
  commandLCD(0b11000010);
  lcd_wait();
  commandLCD(0b11001000);       // Blank display w/out clearing
  lcd_wait();
  commandLCD(0b11000000);       //
  lcd_wait();
  commandLCD(0b11001100);       // Restore display
  lcd_wait();
  commandLCD(0b11000000);       //
  lcd_wait();
  commandLCD(0b11000001);       // Clear screen
  lcd_wait();
  commandLCD(0b11000000);       //
  lcd_wait();
  commandLCD(0b11000110);       //
  lcd_wait();
  PWR = ENABLE;                         // Turns the LCD display on
    Nop();
    Nop();
    Nop();
    Nop();
}

void wait(int time){
    int i = 0;
    time = time*2;

    while(i < time){
        Nop();
        i++;
    }
}

void commandLCD(unsigned char bitsToSet){

  LATD = bitsToSet;// buf | (Dat & 0x0F);          				// Combine & write back to the data lines
  Nop();                         					// Give the data a small delay to settle
  Nop();
  EN = DISABLE;                            			// Enable LCD => The data is taken now
  Nop();
  Nop();
}

void lcd_wait(void){
    unsigned char temp;

    RS = 0;
    RW = 1;
    D7_DIR = SET_IN;


    while(1){
        temp = read_lcd();
        if(temp & 0b10000000){
            // flag is busy
        }else{
            break;
        }

    }

}




unsigned char read_lcd(void){
    unsigned char data;
    unsigned char result;

    // allow the board to read the PORTD pins
    D7_DIR = SET_IN;
    D6_DIR = SET_IN;
    D5_DIR = SET_IN;
    D4_DIR = SET_IN;

    // Read first 4 bits (MSB))
    EN = 1;
    Nop();
    Nop();
    data = PORTD;
    EN = 0;
    result = (data << 4);

    // Reads second 4 bits (LSB))
    EN = 1;
    Nop();
    Nop();
    data = PORTD;
    EN = 0;
    data = data & 0x0D;
    result = result | data;

    D7_DIR = SET_OUT;
    D6_DIR = SET_OUT;
    D5_DIR = SET_OUT;
    D4_DIR = SET_OUT;

    return result;
}