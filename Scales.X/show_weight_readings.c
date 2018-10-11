/****************************************************************************
*                                                                          *
* This file is to be used to display the Weight Readings              *
****************************************************************************/

#include <stdio.h>
//#include <stepin.h>
#include "show_weight_readings.h"
#include "LCD_head.h"
// @SHOW_WEIGHT_READINGS.c
//@Thomas McCabe
// @19 September 2018
//@ file containing a weigh mode working trival output


void show_weight_seiral(int weight){
    
    // Printing we can output over serial
   //printf("Output weight to Serial\n");
    
    
}
char show_weight_lcd(char *string){
    
    
    // Printing we can output to the LCD
   //printf("Output weight to LCD\n");
    // Creating string
    
    
   
    
       
    
    // writing something to the LCD to see if it's working
    // First;y we will establish a connections
    lcd_wait();
    write_string(0,0,string);
    
}



