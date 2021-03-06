/****************************************************************************
*                                                                          *
* This file is the main fie for the scales Assignemnt.                     *
****************************************************************************/


/*
 * @File:   main.c
 * @Authors: Aspen, James, Tom, Lina, Kwajo, Ty, Richard
 * @date 18 September 2018
 * @ Brief the main file that all others are called from
 *
 * more detailed explanation
 */

/****************************************************************************
*                                 Includes                                  *
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "LCD_head.h"
#include "mode_controller.h"
#include "count_or_weigh_mode.h"
#include "set_weight_unit.h"
#include "tare.h"
#include "p18f452.h"


/****************************************************************************
*                                 PIC board setup                           *
****************************************************************************/
// Setup board OSC, watchdog and low voltage protect 
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF


/****************************************************************************
*                                 #Defines                                  *
****************************************************************************/
// User mode defines
#define USER_LOCAL 0    /**< Local user mode */
#define USER_REMOTE 1   /**< Remote user mode */
#define FACTORY 2       /**< Some documentation for first. */

// LCD defines
#define SET_ROW 0
#define SET_POS 1
#define SEND_MSG 2

// Mode layer depth indicator
unsigned int layer_depth;


/****************************************************************************
*                                 Function declarations                     *
****************************************************************************/
void setup_pic(void);
void highPriorityISR(void);
void lowPriorityISR(void);
void read_input(void);

/****************************************************************************
*                                 Interrupt setup                           *
****************************************************************************/

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


/****************************************************************************
*                                 Main                                      *
*****************************************************************************/
void main(void) {
    
    int trigger; //This will be used in count mode to select what mass and how many for setting
    // Initial menu
    
    layer_depth = 1;
    LCDInit();
   
    while(1){
    
        if(layer_depth == 1){
            
        
            // the cycle between the top layer
            user_local();
            read_input();
            user_remote();
            read_input();
            factory();
            read_input();
            
    }
    else {
        
        set_mode_count(1);
        read_input();
        set_mode_weigh(1);
        read_input();
    }
    }
}

void read_input(void){
   
        // This function monitors RB0 and RA4 as input buttons
       TRISB = 0b00000001;                    //Configure 1st bit of PORTB as input and 3rd as out
       TRISA = 0b00010000;
         
       while((PORTBbits.RB0) == 1 );
        if((PORTBbits.RB0) != 1)            //If 1st switch is pressed
        {
             PORTBbits.RB2 = 1;           //3rd LED ON
            wait(1000);              //1 Second Delay
             PORTBbits.RB2 = 0;           //LED OFF

        }
      /*
       if((PORTAbits.RA4) != 1)            //If 1st switch is pressed
        {
            set_mode_count(1);
            read_input();
       
       
             PORTBbits.RB3 = 1;           //3rd LED ON
            wait(1000);              //1 Second Delay
             PORTBbits.RB3 = 0;           //LED OFF

        }*/
       while((PORTBbits.RB0) == 0);
 
}
   


/****************************************************************************
*                                 Interrupt Function                        *
****************************************************************************/

#pragma interrupt highPriorityISR     // or interruptlow    
void highPriorityISR( void ){
    
    
    if((PORTAbits.RA4) != 1)            //If 2nd switch is pressed
    {
        layer_depth = 2;
    }
    
        // Check to see if data was received
    //if(PIR1 & (1 << 5)){
        //receiveCharacter();         << PART OF SERIAL, ADD THIS BACK IN AFTER INCLUDING SERIAL
    //} 
}

#pragma interruptlow lowPriorityISR 
void lowPriorityISR( void ){
        

    
    // Check to see if data was sent
    //if(PIR1 & (1 << 4)){
    //    receiveCharacter();
    //}
    
} 