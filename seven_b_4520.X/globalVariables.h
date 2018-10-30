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
    unsigned char fromReceiver[BUFFERSIZE];
    int MsgToSend = 0;
    // create an array of strings
    unsigned char string[5][BUFFERSIZE];
    // point to the first string
    int stringPtr = 1;
    // point to the first character
    int stringPos = 0;
    // Buffer overflow flag
    int overflowFlag = 0;
    // Create a variable for the LRC
    unsigned char LRC;
    
    int current_mode = USER_LOCAL;
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALVARIABLES_H */

