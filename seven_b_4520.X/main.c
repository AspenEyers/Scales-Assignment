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
    int row = 0;
    int position = 0;
    int state = SET_ROW;
    int ten = 11;
    setupSerial();
    setupInterrupts();
    
    // ******** Analog-dig init ******** //
    AdInit();    
    
    
    // ******** LCD INIT ******** //
    LCDInit();    


    
    // ******** Verify the LCD and serial work ******** //
    lcd_clear();    
    write_string(0,0,message);
    tx232C(intro_msg);
    tx232C(end_msg);
    
 
    
    number = 1;
    direction = 1;
    while(1){
    
    length = 0;    
    rem = number;
    
    // ********                     ******** //
    // Determine the length of the input number
    while(rem > 0){
        length++;
        rem = rem/10;
    }
    
    output[0] = (length+48);
    output[1] = '\0';
    
    // ********                      ******** //
    // Convert the number into a char array
    rem = number;
    i = length;
    
    while(length > 0){
        
        output[--length] = (rem%10 + 48);
        rem = rem/10;
        //length--;
    }
    output[i++] = ',';
    output[i++] = '\n';
    output[i++] = '\r';
    output[i++] = '\0';
            
    
    
    // *********** Display the data *********** //
    tx232C(output);
    write_string(0,0,output);
    
    
    // ******** Simulate data changing ******** //
    number = number + direction;
    if(number > 1000){
        
        direction = -1;
        
    }else if(number <= 0){
        direction = 1;
    }
    }    
    // Number has been converted and sent
    
    
    
    /*
    
    while(1){
        // If there was a message received by the serial communications
        if(MsgToSend){
            //lcd_clear();
            //write_string(0,0,fromReceiver);
            tx232C(fromReceiver);
            tx232C(end_msg);
            MsgToSend = 0;
            switch(state){
                case SET_ROW:
                    //tx232C(debug);
                    if(strcmp(fromReceiver, num_arr[1]) == 0){
                        row = 1;
                        //tx232C(fromReceiver);
                        //tx232C(end_msg);
                        state++;
                    }else if(strcmp(fromReceiver, num_arr[0]) == 0){
                        row = 0;
                        //tx232C(fromReceiver);
                        //tx232C(end_msg);
                        state++;
                    }
                    break;
                case SET_POS:
                    
                    // for each string, if equal then set pos and move on
                    for(i=0; i < BUFFERSIZE; i++){
                        if(strcmp(fromReceiver, num_arr[i])==0){
                            position = i;
                            //tx232C(fromReceiver);
                            //tx232C(end_msg);
                            state++;
                        }
                    }
                    
                    
                    
                    break;
                case SEND_MSG:
                    
                    //tx232C(fromReceiver);
                    //tx232C(end_msg);
                    lcd_clear();
                    write_string(row,position,fromReceiver);
                    state = SET_ROW;
                    
                    
                    break;
                    
                default:
                    tx232C(debug);
                    
            }
        }
    }
    */
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
        

    
    // Check to see if data was sent
    //if(PIR1 & (1 << 4)){
    //    receiveCharacter();
    //}
    
} 

void AdInit(void){
    
    ADCON0bits.ADON = 1;    // Enable A/D
    // ADCON0bits.GO_DONE   // AD state, 1 if in progress   
    
    // Choose channel AN0
    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;
    
    // Set all the port A pins to Analog <<<<<<<<<<<<<<<<<<<<<<
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 0; 
    ADCON1bits.PCFG2 = 0;
    ADCON1bits.PCFG3 = 0;
            
    // Voltage reference config bits
            // Might be useful to test this with the DC power supply
    ADCON1bits.VCFG0 = 0;   // 1 = Vref- reference is AN2
    ADCON1bits.VCFG1 = 0;   // 1 = Vref+ reference is AN3 

    // FOSC/8 clock
    ADCON2bits.ADCS0 = 1;
    ADCON2bits.ADCS1 = 0;
    ADCON2bits.ADCS2 = 0;

    // Aquisition time
    ADCON2bits.ACQT0 = 0;
    ADCON2bits.ACQT1 = 0;
    ADCON2bits.ACQT2 = 0;
    // Left justify
    ADCON2bits.ADFM = 0;         

}