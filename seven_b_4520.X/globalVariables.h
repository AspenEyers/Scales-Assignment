/* 
 * File:   globalVariables.h
 * Author: Aspen
 *
 * Created on 13 September 2018, 3:20 PM
 */

#ifndef GLOBALVARIABLES_H
#define	GLOBALVARIABLES_H

#ifdef	__cplusplus
extern "C" {
#endif

    

    #define USER_LOCAL 1
    #define USER_REMOTE 2
    #define FACTORY_REMOTE 3
    // Global variables
    // Used for serial
    // Add variables to be used in interrupts here
    extern unsigned char fromReceiver[BUFFERSIZE];
    extern int MsgToSend;
    // create an array of strings
    extern unsigned char string[5][BUFFERSIZE];
    // point to the first string
    extern int stringPtr;
    // point to the first character
    extern int stringPos;
    // Buffer overflow flag
    extern int overflowFlag;
    // Create a variable for the LRC
    extern unsigned char LRC;
    
    extern int current_mode;
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALVARIABLES_H */

