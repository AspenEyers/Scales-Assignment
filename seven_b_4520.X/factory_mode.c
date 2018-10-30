#include "factory.h"
#include "basic_serial.h"
#include <string.h>

//******************************************************************
//* Messages
//******************************************************************
char factory_welcome[] = "Welcome to factory mode.\n If you need help, type 'help'";
char help_message[] = "The following commands are valid:\n";
char return_endline[] = "\n\r";
extern unsigned char fromReceiver[BUFFERSIZE];

void factory(void){
    // in factory mode you will be greeted with a welcome message and a prompt to call for help if needed
    // If the help is called it will display all the functions that can be used.
    
    // to get into a mode or change states in the factory mode, the correct string must be entered into the command line
    // followed by an enter.

    // test the recieve string from te serial to determine what mode using a lookup table
    //  
    
    if(strcmp(fromReceiver, "hi") == 0){
        welcome_message_factory();
        tx232C(fromReceiver);
        help_message_factory();
    }
    
}

void welcome_message_factory(void){
    tx232C(factory_welcome);
    tx232C(return_endline);
}

void help_message_factory(void){
    tx232C(help_message);
    tx232C(return_endline);
        
}