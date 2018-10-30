#include <stdio.h>
#include <stdlib.h>
#include <p18cxxx.h>
#include <string.h>
#include "basic_serial.h"




// Global variables
// Used for serial
// Add variables to be used in interrupts here
extern unsigned char fromReceiver[BUFFERSIZE];
extern int MsgToSend;// = 0;
// create an array of strings
extern unsigned char string[5][BUFFERSIZE];
// point to the first string
extern int stringPtr;// = 1;
// point to the first character
extern int stringPos;// = 0;
// Buffer overflow flag
extern int overflowFlag;// = 0;
// Create a variable for the LRC
extern unsigned char LRC;
extern i;




// Function definitions

// Sets up the interrupts
void setupInterrupts(void){

    RCON |= (1 << 7);      // Enable interrupt priority
    PIE1 |= (1 << 5);      // USART receive interrupt enable
    PIE1bits.ADIE = 1;     // AD interrupt enable 
    IPR1bits.ADIP = 0;     // AD low priority
    IPR1 |= (1 << 5);      // USART interrupt > high priority 
    INTCON |= (1 << 7);    // Enable high priority interrupts 
    INTCON |= (1 << 6);    // Enable low priority interrupts
}

// Set up the USART in Async mode
void setupSerial(void){
        // Setup for Tx and Rx for Serial
    LATCbits.LATC7 = 1;
    LATCbits.LATC6 = 1;
    RCSTAbits.SPEN = 1;
    
    // Transmit and control
    TXSTAbits.CSRC = 1; // Master mode
    TXSTAbits.TX9  = 0; // 8 bit transmission 
    TXSTAbits.TXEN = 1; // Transmit enabled       
    TXSTAbits.SYNC = 0; // Async mode
    // TXSTAbits.SENDB= // unimplemented
    TXSTAbits.BRGH = 1; // High baud rate
    //TXSTAbits.TRMT =  // Transmit status bit  
    //TXSTAbits.TX9D =  // 9th data transmission bit      

    // Receive and control
    RCSTAbits.SPEN = 1; // Serial port enabled 
    RCSTAbits.RX9  = 0; // 8bit receive
    RCSTAbits.SREN = 0; // Disable single receive
    RCSTAbits.CREN = 1; // Enable receiver
    RCSTAbits.ADDEN= 0; // Disable address detection;
    RCSTAbits.FERR = 0; // No framing error
    RCSTAbits.OERR = 0; // No overrun error
    //RCSTAbits.RX9D =  // 9th bit of received data      
    
    // Baud rate -> 9600
    BAUDCONbits.BRG16 = 0; // 8 bit baud generation
    SPBRG = 64;
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
   
    unsigned char temp;// = "G";
    
    // Save the character to current position in the buffer
    //fromReceiver[stringPos] = (unsigned char) RCREG;    
    temp = (unsigned char) RCREG;
    
    fromReceiver[stringPos] = temp;
    //temp = 'G';
    //sendCharacter('H'); 
    
    
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
    if(stringPos == 17 - 1){
        // point back to the start of the buffer
        stringPos = 0;
    }
        
    
    
    //Compute the LRC
        // compare the current LRC with the incoming byte
        
    
    
}


void empty_receive_buffer(void){

    for(i = 0; i < BUFFERSIZE; i++){
        fromReceiver[i] = '0';
    }
}











