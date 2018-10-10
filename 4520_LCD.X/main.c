/* 
 * File:   main.c
 * Author: Aspen
 *
 * Created on 10 October 2018, 3:09 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "ConfigRegs18f4520.h"
#include <xlcd.h>
#include <delays.h>

 void DelayFor18TCY( void ) {
 Nop();
 Nop();
 Nop();
 Nop();
 Nop();
 Nop();
 Nop();
 Nop();
 Nop();
 Nop();
 Nop();
 Nop();
 }
 
 //------------------------------------------
 void DelayPORXLCD (void) {
 Delay1KTCYx(37);// Delay of 15ms
       // Cycles = (TimeDelay * Fosc) / 4
       // Cycles = (15ms * 12MHz) / 4
       // Cycles = 15,000
 return;
 }
  
//------------------------------------------
 void DelayXLCD (void) {
 Delay1KTCYx(12); // Delay of 5ms
       // Cycles = (TimeDelay * Fosc) / 4
       // Cycles = (5ms * 12MHz) / 4
       // Cycles = 5,000
 return;
 }
 //--------------------------

void main(void) {

    OpenXLCD(FOUR_BIT & LINES_5X7);
    while(BusyXLCD());
    WriteCmdXLCD(CURSOR_OFF);
    while(BusyXLCD());
    putcXLCD('c');
    while(1){
        while(BusyXLCD());
        putrsXLCD("SOMETHING PLEASSE");
        putcXLCD('c');
    }
}