/* 
 * File:   basic_serial.h
 * Author: Aspen
 *
 * Created on 13 September 2018, 12:35 AM
 */

#ifndef BASIC_SERIAL_H
#define	BASIC_SERIAL_H

#ifdef	__cplusplus
extern "C" {
#endif

    
    // Useful definitions
    #define ERROR -1
    #define BUFFERSIZE 17


    // function declarations
    int tx232C(unsigned char *txPtr);
    void setupSerial(void);
    void sendCharacter(unsigned char *msg);
    void highPriorityIsr( void );
    void lowPriorityIsr( void );
    void receiveCharacter(void);
    void setupInterrupts(void);


#ifdef	__cplusplus
}
#endif

#endif	/* BASIC_SERIAL_H */

