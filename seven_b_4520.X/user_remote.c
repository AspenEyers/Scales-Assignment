/* 
 * File:   user_remote.c
 * Author: opha5541
 *
 * Created on 31 October 2018, 2:59 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "user_remote.h"
#include "basic_serial.h"
#include <string.h>
#include "globalVariables.h"
#include "function_manager.h"
/*
 * 
 */
#define NUMBER_OF_MODES 7

char user_remote_welcome[] = "Welcome to user remote mode.\n\r type 'HELP'\n\r";
char user_remote_options[NUMBER_OF_MODES][10] = {"HELP",             
                                         "WEIGH",
                                         "TARE",
                                         "COUNT",
                                         "SET_GRAMS",
                                         "SET_OUNCES",
                                         "FACTORY",
                                         };
unsigned char end_rem[] = "\r\n";
extern unsigned char fromReceiver[BUFFERSIZE];
extern int current_mode;
void user_remote(){
    int exit_user_remote = 0;
    int ind = 0;
    tx232C(user_remote_welcome);
    tx232C(end_rem);
    
    
    
    
    // wait until the user wants to exit factory mode
    while(exit_user_remote == 0){

        
        // check to see if the user has entered a valid state 
        // if they have then enter it.
        for(ind = 0; ind < NUMBER_OF_MODES; ind++){
            if(strcmp(fromReceiver, user_remote_options[ind]) == 0){
                enter_function(ind);
                empty_receive_buffer();
            }
        }


    }
}



