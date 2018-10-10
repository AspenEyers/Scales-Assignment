#include <stdio.h>
#include <stdlib.h>
#include <p18cxxx.h>
#include <string.h>
#include "basic_serial.h"




// Global variables
// Used for serial
// Add variables to be used in interrupts here
extern unsigned char fromReceiver[BUFFERSIZE];
extern int MsgToSend = 0;
// create an array of strings
extern unsigned char string[5][BUFFERSIZE];
// point to the first string
extern int stringPtr = 1;
// point to the first character
extern int stringPos = 0;
// Buffer overflow flag
extern int overflowFlag = 0;
// Create a variable for the LRC
extern unsigned char LRC;





// Function definitions

// Sets up the interrupts
void setupInterrupts(void){

    RCON |= (1 << 7);      // Enable interrupt priority
    PIE1 |= (1 << 5);       // USART receive interrupt enable
    IPR1 |= (1 << 5);      // USART interrupt > high priority 
    INTCON |= (1 << 7);    // Enable high priority interrupts 
    INTCON |= (1 << 6);    // Enable low priority interrupts
}

// Set up the USART in Async mode
void setupSerial(void){
    // Set baud to 9600 on 4Mhz clock
    // async mode
    // 8 bit
    // disable transmit
    // high baud rate
    SPBRG = 9;
    //TXSTA |= (1 << 7);        // clock source select bit
    TXSTA &= ~(1 << 6);         // 9/8 bit select, 8bit = 0
    TXSTA |= (1 << 5);          // Transmit enabled
    TXSTA &= ~(1 << 4);         // USART mode, 0 = Async
    //TXSTA |= (1 << 3);        // unimplimented
    TXSTA |= (1 << 2);          // High speed
    //TXSTA |= (1 << 1);        // transmit shift reg status bit, 1=full
    //TXSTA |= (1 << 0);        // 9th bit for 9bit transmission 

    // set baud rate to 9615
    SPBRG = 25;

    // Set receive status register 
    RCSTA |= (1 << 7);      // Serial port enabled
    RCSTA &= ~(1 << 6);     // 8 bit receive
    RCSTA &= ~(1 << 5);     // Disable single receive
    RCSTA |= (1 << 4);      // Enable receiver  
    RCSTA &= ~(1 << 3);     // Disable address detection
    RCSTA &= ~(1 << 2);     // No framing error      
    RCSTA &= ~(1 << 1);     // No overrun error
    //RCSTA |= (1 << 0);    // Address bit for 9th bit if used
}

// This function takes in the pointer to the beginning of a string
// it returns 0 for success and -1 for an error
int tx232C(unsigned char *txPtr){
    
    while(1){
        // if character is not null
        if(*txPtr != '\0'){
            // send a character
            sendCharacter(txPtr);
        }
        else{
            break;
        }
        txPtr++;

    }
    /**/
    //sendCharacter('\n');
    //sendCharacter('\r');
    return 0;
}

// This function takes in a pointer to a character and sends it
// though the TXSTA serial transmission register
void sendCharacter(unsigned char *msg){
    // turn on transmit
    //TXSTA |= (1 << 5);         // Transmit enabled

    // wait for transmit register to be empty
    while((TXSTA & (1 << 1)) == 0){};

    // place character in transmit register
    TXREG = *msg;

    // turn off transmit
    //TXSTA &= ~(1 << 5);         // Transmit disabled
}

// This function takes in a pointer to a character and sends it
// though the TXSTA serial transmission register
void receiveCharacter(void){
   
    // Save the character to current position in the buffer
    fromReceiver[stringPos] = (unsigned char) RCREG;    
    
    // If enter was pressed
    if(fromReceiver[stringPos] == 0xD){
        MsgToSend = 1;
        fromReceiver[stringPos] = '\0';
        
        // Reset the string position
        stringPos = 0;
        
        // Reset the LRC to 0
        //LRC = 0;
        return;
    }else{
        //Compute the LRC
        // compare the current LRC with the incoming byte
        LRC = LRC ^ fromReceiver[stringPos];
    }
    
    
    // increment the buffer pointer
    stringPos++;
    // If the buffer is full
    if(stringPos == BUFFERSIZE - 1){
        // point back to the start of the buffer
        stringPos = 0;
    }
        
    
    
    //Compute the LRC
        // compare the current LRC with the incoming byte
        
    
    
}















