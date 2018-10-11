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
#include "set_mode_count.h"
#include "set_weight_unit.h"
#include "tare.h"


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




/****************************************************************************
*                                 Function declarations                     *
****************************************************************************/
void setup_pic(void);
void highPriorityISR(void);
void lowPriorityISR(void);



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

}


/****************************************************************************
*                                 Interrupt Function                        *
****************************************************************************/

#pragma interrupt highPriorityISR     // or interruptlow    
void highPriorityISR( void ){
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