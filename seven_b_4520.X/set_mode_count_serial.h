/* 
 * File:   set_mode_count_serial.h
 * Author: opha5541
 *
 * Created on 30 October 2018, 10:24 PM
 */

#ifndef SET_MODE_COUNT_SERIAL_H
#define	SET_MODE_COUNT_SERIAL_H

#ifdef	__cplusplus
extern "C" {
#endif
    extern int MsgToSend;
    extern unsigned char fromReceiver[17];
    extern int current_mode;
    extern int unit_mode;
    void set_mode_count_serial(void);
    char* intToStringCount(int inte);
    int isDigit(unsigned char*);
    int str2int( unsigned char*);


#ifdef	__cplusplus
}
#endif

#endif	/* SET_MODE_COUNT_SERIAL_H */

