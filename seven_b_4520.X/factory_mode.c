#include "factory.h"
#include "basic_serial.h"
#include <string.h>
#include "function_manager.h"
#include "set_mode_count_serial.h"
#include "globalVariables.h"

#define NUMBER_OF_MODES 12

//******************************************************************
//* Messages
//******************************************************************
char factory_welcome[] = "Welcome to factory mode.\n\r type 'HELP'\n\r";
int i;
// 
char return_endline[] = "\n\r";
char msg[] = "msg: ";
char string_test[NUMBER_OF_MODES][15] = {"HELP",
                                         "USER",
                                         "WEIGH",
                                         "TARE",
                                         "COUNT",
                                         "SET_GRAMS",
                                         "SET_OUNCES",
                                         "FACTORY",
                                         "WEIGHT_READINGS",
                                         "STATISTICS",
                                         "SET_SAMPLES",
                                         "CALIBRATE"};
char end_msg[] = "\r\n";
extern unsigned char fromReceiver[BUFFERSIZE];
extern factory_return;
extern int MsgToSend;


void factory(void){
    // in factory mode you will be greeted with a welcome message and a prompt to call for help if needed
    // If the help is called it will display all the functions that can be used.
    
    // to get into a mode or change states in the factory mode, the correct string must be entered into the command line
    // followed by an enter.

    // test the recieve string from the serial to determine what mode using a lookup table


    
    int exit_factory = 0;
    factory_return = 0;

    tx232C(factory_welcome);
    tx232C(end_msg);    

    // wait until the user wants to exit factory mode
    while(exit_factory == 0){
        filter_raw_weight();


        if(factory_return == 1){
            //tx232C(factory_welcome);
            //tx232C(end_msg);    
            factory_return = 0;

        }
        
        // check to see if the user has entered a valid state 
        // if they have then enter it.
        for(i = 0; i < NUMBER_OF_MODES; i++){
            if(strcmp(fromReceiver, string_test[i]) == 0){
                enter_function(i);
                empty_receive_buffer();
            }
        }


    }
    
}
void factory_password(void){
    unsigned char factory_pw_msg[] = "Please enter the correct password for access to factory mode.\n\r";
    unsigned char factory_pw[]="123";
    unsigned char incorrect_pw_msg[]="Incorrect. You have been denied access.\n\r";
    int still_in_factory_pw = 1;
    tx232C(factory_pw_msg);
    
    MsgToSend =0;
    while(still_in_factory_pw){
        while(MsgToSend==0);
        if(strcmp(fromReceiver,factory_pw)==0){
            current_mode = 2;
            still_in_factory_pw = 0;
            //factory();
        }
        else{
            tx232C(incorrect_pw_msg);
            still_in_factory_pw = 0;
            return;
        }
    }
}
