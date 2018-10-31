/*
 * File:   main.c
 * Authors:   Aspe     James, Ty, Richard, Tom, Lina
 * SIDs:
 *
 * Created on 5 September 2018, 12:18 PM
 */


//*****************************************************************************
//*                          Includes                                         *
//*****************************************************************************
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
#include "factory.h"
#include "weight_filter.h"
#include "function_manager.h"



//*****************************************************************************
//*                          Defines                                          *
//*****************************************************************************
#define SET_ROW 0
#define SET_POS 1
#define SEND_MSG 2


//*****************************************************************************
//*                          Strings for debugging                            *
//*****************************************************************************
char yes[] = "yes\n\r";
char no[] = "no\n\r";

//*****************************************************************************
//*                          Variables for main                               *
//***************************************************************************** 
char output[25];
// variables for data and filtering
int raw_weight;
int filtered_weight;
//int window;
int samples[20] = {0};
int pos;
long sum;
int unit_mode = 0;
int length;    
int rem; 
int direction;
     


//*****************************************************************************
//*                          Function definitions                             *
//*****************************************************************************
void highPriorityISR( void );
void lowPriorityISR( void );
void AdInit(void);
void num2str(char *string, int number);



//*****************************************************************************
//*                          Setup Interrupts                                 *
//*****************************************************************************
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


//*****************************************************************************
//*                          Main function                                    *
//*****************************************************************************
void main( void )
{
    //window = 20;    // default window 
 
     
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
    
    //samples[20] = {0};
    raw_weight = 0;
    filtered_weight = 0;
    pos = 0;
    sum = 0;
    
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
    //lcd_clear();    
    //write_string(0,0,message);
    //tx232C(intro_msg);
    //tx232C(end_msg);
    //edit
    current_mode = 2;
    while(1){
        // choose mode
        switch(current_mode){
            case 0:
                // go into user local function choosers
                
                break;
            case 1:
                // go into user remote function chooser
                break;
            case 2:
                    factory();
                break;
        }
    }         
}



#pragma interrupt highPriorityISR     // or interruptlow    
void highPriorityISR( void ){
        // Check to see if data was received
    if(PIR1 & (1 << 5)){
        receiveCharacter();
        //tx232C(yes);
        //sendCharacter(fromReceiver[0]);
        PIR1bits.RCIF = 0;
    }
}

#pragma interruptlow lowPriorityISR 
void lowPriorityISR( void ){
        

    if(PIR1bits.ADIF == 1){
        raw_weight = ADRESH;
        raw_weight = (raw_weight << 1);
        raw_weight = raw_weight | ((ADRESL >> 6) && (0b00000011));
        //number = ADRESL;
        
        
        filter_raw_weight();
        num2str(&output,filtered_weight);
        write_string(0,0,output);
        
        

        ADCON0bits.GO = 1;
        PIR1bits.ADIF = 0;
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
    ADCON1bits.VCFG0 = 1;   // 1 = Vref- reference is AN2
    ADCON1bits.VCFG1 = 1;   // 1 = Vref+ reference is AN3 

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



