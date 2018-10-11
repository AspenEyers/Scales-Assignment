/*
 * File:   main.c
 * Author: Aspen
 *
 * Created on 5 September 2018, 12:18 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xlcd.h>
#include <delays.h>
#include <usart.h>
#include "basic_lcd.h"
#include "basic_serial.h"
#include "globalVariables.h"


// Setup board OSC, watchdog and low voltage protect 
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF


#define SET_ROW 0
#define SET_POS 1
#define SEND_MSG 2



void highPriorityISR( void );
void lowPriorityISR( void );


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
    
    
    setupSerial();
    setupInterrupts();
    
    LCDInit();    
    lcd_wait();
    
    set_lcd_pos(0,0);
    lcd_wait();

    
    
    lcd_clear();    
    write_string(0,0,message);
    tx232C(intro_msg);
    tx232C(end_msg);
    
    
    //if(new_msg_flag == 1){
    //    lcd_clear();
    write_string(0,0,message);
    //    new_msg_flag = 0;
    //}
    
    
    
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
                    for(i=0; i < 17; i++){
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