/*
 * File:   main.c
 * Author: Aspen
 *
 * Created on 5 September 2018, 12:18 PM
 */

#include "ConfigRegs18f4520.h"
#include <stdio.h>
#include <stdlib.h>
#include <xlcd.h>
#include <delays.h>
#include <usart.h>
#include <math.h>
#include "basic_lcd.h"
#include "basic_serial.h"
#include "globalVariables.h"
#include "mode_contoller.h"
#include"UI.h"


// Setup board OSC, watchdog and low voltage protect 
//#pragma config OSC = HS
//#pragma config WDT = OFF
//#pragma config LVP = OFF

#define SET_ROW 0
#define SET_POS 1
#define SEND_MSG 2

void highPriorityISR( void );
void lowPriorityISR( void );
void display_count(void);
void set_count(void);
void read_count_input(void);
void intToString(int weight);

// Setup the interrupts 
#pragma code highISR = 0x08
void goToHighISR( void )
{
    _asm 
        goto highPriorityISR
    _endasm 
}
#pragma code lowISR = 0x0018
void goToLowISR( void )
{
    _asm 
        goto lowPriorityISR
    _endasm 
}

 //countFunctions
    int hundreds = 0;
    int tens = 0;
    int ones = 1;
    //char count_message[15];
    char symbol;
    int count_column=0;
    char sym0,sym1,sym2,sym3,sym4, sym5;
    int count_confirmed = 0;
    int numberOunits;
    int weight_grams = 100; // TEST WEIGHT VARIABLE 
    int unit_mode = 0; // TEST PRETEND UNIT MODE IS IN GRAMS
unsigned char test_lcd_str[]= "Hol";
unsigned char stringToOutput[7];
void main( void )
{
   
    int i = 0;
    unsigned char message[] = "Send Input:";
    unsigned char end_msg[] = "\r\n"; 
    unsigned char set_row_msg[] = "Enter R: "; 
    unsigned char set_pos_msg[] = "Enter P: "; 
    unsigned char intro_msg[] = "Start";
    unsigned char debug[] = "DEBUG\n\r";
    unsigned char one[] = "1";
    unsigned char zero[] = "0";
    unsigned char num_arr[][3] = {"0", "1", "2", "3","4","5","6","7","8","9",
                                   "10","11","12","13","14","15","16"};
    // Set the variables for lcd display
    int row = 0;
    int position = 0;
    int state = SET_ROW;
    char lolz[] = "0";
     int count_column=0;
     
    UIsetup(); 
    setupSerial();
    setupInterrupts();
    
    LCDInit();    
 
    functionPicker(1);
    
    while(1)
    {       
        user_interface();            
    }   
    
    while(1){};
 
}
void set_count(void)
{ 
    display_count();
//    while(!count_confirmed)
//    {
//        display_count();
//        read_count_input();
//    }
    
}

void read_count_input(void){
   
        // This function monitors RB0 and RA4 as input buttons
       TRISB = 0b00000001;                    //Configure 1st bit of PORTB as input and 3rd as out
       TRISA = 0b00010000;
         
       while((PORTBbits.RB0) == 0 );
        if((PORTBbits.RB0) != 0)            //If 1st switch is pressed
        {
            if(count_column < 4){
                count_column += 1;
                //display_count();
            }
            else{
                count_column = 0;
                //display_count();
            }
            

        }
       while((PORTBbits.RB0) == 0);
 
}
void display_count (void)
{
   unsigned char count_message[16]; 
    
    if (count_column==0)
        {
            sym0= '|';
            sym1='|';
            sym2= ' ';
            sym3 = ' ';
            sym4 = ' ';
//            sym5 = ' ';
            
            sym5 = '0';
        }
    else if (count_column==1)
        {
            sym1= '|';
            sym2='|';
            sym3= ' ';
            sym4 = ' ';
            sym0 = ' ';
            //sym5 = ' ';

            sym5 = '1';
        }
    else if (count_column==2)
        {
            sym2= '|';
            sym3='|';
            sym1= ' ';
            sym0 = ' ';
            sym4 = ' ';
//            sym5 = ' ';
            
            sym5 = '-';
        }
    else if (count_column==3)
        {
            sym3= '|';
            sym4='|';
            sym2= ' ';
            sym1 = ' ';
            sym0 = ' ';
//            sym5 = ' ';
           
            sym5 = '3';
        }
    else if (count_column==4)
        {
            sym3= ' ';
            sym4='|';
            sym2= ' ';
            sym1 = ' ';
            sym0 = ' ';
//            sym5 = '|';

            sym5 = '4';
        }
    else
        {
             sym0= '|';
            sym1='|';
            sym2= ' ';
            sym3 = ' ';
            sym4 = ' ';
            sym5 = '?';
            count_column = 0;
        }
    count_message[0] = sym0;
    count_message[1] = hundreds+48;
    count_message[2]= sym1;
    count_message[3]=tens+48;
    count_message[4]= sym2;
    count_message [5]= ones+48;
    count_message [6]= sym3;
    count_message [7]='O';
    count_message [8]='K';
    count_message [9]= sym4;
    count_message [10]= 'B';
    count_message [11]= 'A';
    count_message [12]= 'C';
    count_message [13]= 'K';
    count_message [14]= sym5;
    count_message [15]= '\0';
   
    write_string(0,0,count_message);
    
    
   // countMenu();
}

/****************************************************************************
*                                 Interrupt Function                        *
****************************************************************************/


#pragma interrupt highPriorityISR     
void highPriorityISR( void )
{   
    /*
    //call check function
    buttonControl();
    */
    INTCONbits.TMR0IF = 0;  //Resetting flag
    INTCONbits.RBIF =0;// Set the flag to 0
         
}

// Timer based interrupt which activates a check on the button
#pragma interrupt lowPriorityISR  
void lowPriorityISR( void ){
    
    //call check function
    buttonControl();
    
    INTCONbits.TMR0IF = 0;  //Resetting flag
    INTCONbits.RBIF =0;// Set the flag to 0
    
}

void intToString(int weight){
    char hundreds_char,tens_char,ones_char, unitsymbol1, unitsymbol2;
    if(unit_mode == 1){
        unitsymbol1 = 'o';
        unitsymbol2 = 'z';
    }
    else{
        unitsymbol1 = 'g';
        unitsymbol2 = ' ';
    }
    //char stringToOutput[3];
    hundreds_char = (weight/100)+48;
    tens_char = ((weight%100)/10)+48;
    ones_char = ((weight%100)%10)+48;
    stringToOutput[0] = hundreds_char;
    stringToOutput[1] = tens_char;
    stringToOutput[2] = ones_char;
    stringToOutput[3] = ' ';
    stringToOutput[4] = unitsymbol1;
    stringToOutput[5] = unitsymbol2;
    stringToOutput[6] = '\0';
    //return stringToOutput;
}






