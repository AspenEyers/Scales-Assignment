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
#include "basic_lcd.h"
#include "basic_serial.h"
#include "globalVariables.h"
#include "ConfigRegs18f4520.h"
#include "include_scales_functionality.h"


// Setup board OSC, watchdog and low voltage protect 
//#pragma config OSC = HS
//#pragma config WDT = OFF
//#pragma config LVP = OFF


#define SET_ROW 0
#define SET_POS 1
#define SEND_MSG 2

 char yes[] = "yes\n\r";
 char no[] = "no\n\r";

 
 
char output[25];
int number;
int length;    
int rem; 
int direction;
     

void highPriorityISR( void );
void lowPriorityISR( void );
void AdInit(void);
void num2str(char *string, int number);

// Setup the interrupts 
#pragma code highISR = 0x08
void goToHighISR( void ){
    _asm 
        goto highPriorityISR
    _endasm 
}
#pragma code lowISR = 0x0018
void goToLowISR( void ){
    _asm 
        goto lowPriorityISR
    _endasm 
}



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
    int state = SET_ROW;
    setupSerial();
    AdInit();    
    LCDInit();    
    // Note: the setup interrupts MUST go after the setup functions
    // otherwise it will break the timing in the setups.
    setupInterrupts();
    
    //SET_MODE_COUNT();
    //while(1){
        //write_string(0,0,message);
        //SET_MODE_COUNT();
    //};
    
    // ******** Verify the LCD and serial work ******** //
    lcd_clear();    
    write_string(0,0,message);
    tx232C(intro_msg);
    tx232C(end_msg);
    //edit
    

    while(1){

    }
         
}



#pragma interrupt highPriorityISR     // or interruptlow    
void highPriorityISR( void ){
        // Check to see if data was received
    if(PIR1 & (1 << 5)){
        receiveCharacter();
    }
}

#pragma interruptlow lowPriorityISR 
void lowPriorityISR( void ){
        

    if(PIR1bits.ADIF == 1){
        number = ADRESH;
        number = (number << 2);
        number = number | ((ADRESL >> 6) && (0b00000011));
        //number = ADRESL;
        ADCON0bits.GO = 1;
        
        num2str(&output,number);
        write_string(0,0,output);
    }
    // Check to see if data was sent
    //if(PIR1 & (1 << 4)){
    //    receiveCharacter();
    //}
    
} 

void AdInit(void){

    // Choose channel AN1
    ADCON0bits.CHS0 = 1;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;
    
    // Set all the port A pins to Analog <<<<<<<<<<<<<<<<<<<<<<
    ADCON1bits.PCFG0 = 1;
    ADCON1bits.PCFG1 = 1; 
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 0;
            
    // Voltage reference config bits
            // Might be useful to test this with the DC power supply
    ADCON1bits.VCFG0 = 0;   // 1 = Vref- reference is AN2
    ADCON1bits.VCFG1 = 0;   // 1 = Vref+ reference is AN3 

    // RC oscilator
    ADCON2bits.ADCS0 = 1;
    ADCON2bits.ADCS1 = 1;
    ADCON2bits.ADCS2 = 1;

    // Aquisition time = 8 T_AD
    // Section 19.1 explains why this is nessiscary
    ADCON2bits.ACQT0 = 0;
    ADCON2bits.ACQT1 = 0;
    ADCON2bits.ACQT2 = 1;
    // Left justify
    ADCON2bits.ADFM = 0;         
    
        ADCON0bits.ADON = 1;    // Enable A/D
    // ADCON0bits.GO_DONE   // AD state, 1 if in progress   
        
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        
        // start the conversion
        // this needs to be done every time
        ADCON0bits.GO = 1;

}



// This function takes in a pointer to a string and
// a number. The number will be saved to that string
// The function returns nothing.
// The function tests each character of the number and 
// will return when it reaches 0. therefore a number starting
// with a 0 e.g. 098. will write nothing to the string.
void num2str(char *string, int number){
    
    int length = 0;    
    int rem = number;
    int i = 0;
    
    // ********                     ******** //
    // Determine the length of the input number
    while(rem > 0){
        length++;
        rem = rem/10;
    }
    
    // ********                      ******** //
    // Convert the number into a char array
    rem = number;
    i = length;
    
    while(length > 0){
        
        *(string+length-1) = (rem%10 + 48);
        length--;
        rem = rem/10;
    }
    *(string+i) = ',';
    i++;
    *(string+i) = '\0';
}