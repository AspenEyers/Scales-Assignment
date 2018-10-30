#include "factory.h"
#include "basic_serial.h"
#include <string.h>
#include "function_manager.h"

#define NUMBER_OF_MODES 4

//******************************************************************
//* Messages
//******************************************************************
char factory_welcome[] = "Welcome to factory mode.\n\r type 'HELP'\n\r";

int i;
// 
char return_endline[] = "\n\r";
char msg[] = "msg: ";
char string_test[NUMBER_OF_MODES][15] = {"HELP", "WEIGH", "TARE", "CALIBRATE"};
char end_msg[] = "\r\n";
extern unsigned char fromReceiver[BUFFERSIZE];

void factory(void){
    // in factory mode you will be greeted with a welcome message and a prompt to call for help if needed
    // If the help is called it will display all the functions that can be used.
    
    // to get into a mode or change states in the factory mode, the correct string must be entered into the command line
    // followed by an enter.

    // test the recieve string from the serial to determine what mode using a lookup table
    //  
    //tx232C(fromReceiver);
    //tx232C(end_msg);
    
    int exit_factory = 0;
    
    
    // wait until the user wants to exit factory mode
    while(exit_factory == 0){

        
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

