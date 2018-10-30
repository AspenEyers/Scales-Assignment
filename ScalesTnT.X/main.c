/****************************************************************************
*                                                                          *
* This file is the main fie for the scales Assignment.                     *
****************************************************************************/


/*
 * @File:   main.c
 * @Authors: Aspen, James, Tom, Lina, Kwajo, Ty, Richard
 * @date 18 September 2018
 * @ Brief the main file that all others are called from
 *
 * more detailed explanation
 * 
 * 
 I am trying to set an interrupt to use the RB0 button on the pick18452 to act
 *  as a "next" button. From my understanding of TABLE1-2: found on pg 11 of the
 *  PIC18XX datasheet, RBO can be utalised/set to be INT0. Going from this 
 * assumption  onwards, I will attempt to create the desired interrupt
 
 * 
 * Most excellent, there is asection on the INTO interrupt on pg 85 
 * called "8.6 INT0 Interrupt" 
 The following is ke information gleamed from the aforemention section 8.6
 *  Is edge triggered
 * Triggered on rise if INEDG0 =1 in INTCON2
 * Triggered on fall if INTEDG0=0 in INTCON2
 * When (desired edge) appears on INT0
 *          => INT0F=1
 * INT0 interrupt can be disabled by INT0IE=0 (in INTCON register)
 * Must clear INT0F in ISR "BEFORE" re-enabaling the interrupt
 * INT0 is desgined in such a manner that it is ALWAYS A HIGH INTERRUPT
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
#include "UI.h"
/************************************************************************
 Constants
 *************************************************************************/


// Constants
int voltageFor100g;
int functionPicked; //For use in USER_REMOTE and FACTORY_REMOTE
int errorType ;
int first =0 ;

//For use in receiving from PC 
volatile char buffer[16] = {0};
volatile int index = 0;
volatile int indexMask = 15;

// Circular Buffer Parameters 
unsigned char buffer_count = 0; // Keeps track of how many bytes are in the buffer
unsigned char buffer_count_B = 0;

// Global variable 
int currentVoltage;
int weightGrams;
int weightValue;
char weightType;
int selectButton;
int nextButton;
int localType=1;
int number;
int oneAmount;
int result;
int firstIndex;
int lastIndex;
int flag=0;
int stateDepth;
int stateChange;  //variable for picking a new mode
int newStateChange; //condition to stop flickering of constant loop
int maxNStates=11; // maximum number of modes in first state
int maxNless= 9;
int state;
int isPressed;
int currentStateDepth;

/////////////////////////////////////////
// Declares Functions (but does not activate/call them)
void disableInterrupts (void);
void high_interrupt(void);
void _interrupt(void);
void highPriorityIsr(void);


/****************************************************************************
*                                 PIC board setup                           *
****************************************************************************/
// Setup board OSC, watchdog and low voltage protect 
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF
//#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0>


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
void setup(void);
void next (void);
//Declares functions (but does not activate/call them )
void disableInterrupts (void);
void _interrupt(void);
void highPriorityIsr(void);
void rx232Isr (void);
int tx232C(unsigned char *txPTr);
void functionPicker (int);
void enableinterrupts (void);
void modeSelector(int);
void user_interface(void);
void buttonControl(void);

/****************************************************************************
*                                 Main                                      *
*****************************************************************************/
void main(void) 
{
   setup();// Creating a setup sequence to allow for the use of a RB4/RBI interrupt
  
    // Initial menu
  
    stateChange = 0;
    stateDepth = -1;
    currentStateDepth = stateDepth;
    newStateChange = stateChange;
   
    LCDInit();
    
    functionPicker(stateChange);
    
    while(1){
        
        user_interface();
    }
}

/****************************************************************************
*                                 Interrupt Function                        *
****************************************************************************/


//////////////////////////////////////////////////////////////
#pragma code interruptAddress = 0x0008
void _interrupt (void)
{/////NOT BEING TRIGGERED 
    _asm GOTO highPriorityISR _endasm;

}
/************************************************************************************************/
#pragma interrupt highPriorityISR     // or interruptlow    
void highPriorityISR( void )
{
    
    buttonControl();
    
    INTCONbits.TMR0IF = 0;  //Resetting flag
    INTCONbits.RBIF =0;// Set the flag to 0
        // Check to see if data was received
    //if(PIR1 & (1 << 5)){
        //receiveCharacter();         << PART OF SERIAL, ADD THIS BACK IN AFTER INCLUDING SERIAL
    //} 
}