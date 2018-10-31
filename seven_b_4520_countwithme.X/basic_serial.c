#include <stdio.h>
#include <stdlib.h>
#include <p18cxxx.h>
#include <string.h>
#include "basic_serial.h"

// Global variables
// Used for serial
// Add variables to be used in interrupts here
extern unsigned char fromReceiver[BUFFERSIZE];
extern int MsgToSend ;
//extern int MsgToSend = 0;

// create an array of strings
extern unsigned char string[5][BUFFERSIZE];
// point to the first string
extern int stringPtr = 1;
// point to the first character
extern int stringPos;
//extern int stringPos = 0;

// Buffer overflow flag
extern int overflow;
//extern int overflowFlag = 0;
// Create a variable for the LRC
extern unsigned char LRC;


// Function definitions

// Sets up the interrupts
/*
void setupInterrupts(void){

    RCON |= (1 << 7);      // Enable interrupt priority
    PIE1 |= (1 << 5);       // USART receive interrupt enable
    IPR1 |= (1 << 5);      // USART interrupt > high priority 
    INTCON |= (1 << 7);    // Enable high priority interrupts 
    INTCON |= (1 << 6);    // Enable low priority interrupts
}
*/
/////////////////////////////////////////////////////////
void enableInterrupts(void)
{
    //Enable prioritized interrupts (pg 84)
    RCONbits.IPEN = 1;
   // INTCON2bits.RBIP = 1; // Enable port B interrupts
    
    //enable all interrupts /including peripherals , pg 75
    INTCONbits.GIE  = 1; // Global Interrupt Enable bit
    INTCONbits.PEIE  = 1; // Peripheral Interrupt Enable bit
    INTCONbits.PEIE  = 1; // Peripheral Interrupt Enable bit
    INTCON2bits.RBIP = 0; // Port B is low
    INTCON2bits.TMR0IP = 0; // Set timer0 interrupt as Low Priority
    INTCONbits.TMR0IF = 0x0;    // Clear the timer0 flag
   }

void disableInterrupts (void)
{
     //Disable interrupts while they are being set
    INTCONbits.GIEH = 0; // Global interrupt high and low
    INTCONbits.GIEL = 0; // 
     
}
void setupInterrupts (void)
{
   /* Most excellent, there is a section on the INTO interrupt on pg 85 
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
    disableInterrupts();
    INTCONbits.TMR0IE = 1; //Enable timer0 interrupt
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.T0PS2 =1;
    TMR0H = 0xF8;
    TMR0L = 0x30;
        
    //Set interrupts
   TRISBbits.RB3 = 1;
   TRISBbits.RB2 = 1;
   
   PORTBbits.RB3 = 0;
   PORTBbits.RB2 = 0;
   
    ADCON1bits.PCFG = 0b1111; //all ports digital
    INTCONbits.RBIE =1;// Enables the RB port change interrupt
    INTCONbits.RBIF =0;// Set the flag to 0
    
    enableInterrupts();
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
    if(stringPos == 17 - 1){
        // point back to the start of the buffer
        stringPos = 0;
    }
        
    
    
    //Compute the LRC
        // compare the current LRC with the incoming byte
        
    
    
}














