#include "function_manager.h"
#include "basic_serial.h"

// mode intro messages
char weigh_intro_msg[] = "You are in weigh mode";
char tare_msg[] = "Taring scales";
char calibrate[] = "calibrating scales:";
char help_message[] = "The following commands are valid:\n";
char msg2[] = "default";
char end_msg2[] = "\r\n";

void enter_function(int mode){
    
    switch(mode){
        case 0:
            tx232C(help_message);
            tx232C(end_msg2);
            break;
        case 1:
            tx232C(weigh_intro_msg);
            tx232C(end_msg2);
            break;
        case 2:
            tx232C(tare_msg);
            tx232C(end_msg2);
            break;
        case 3:
            tx232C(calibrate);
            tx232C(end_msg2);
            break;
        default:
            tx232C(msg2);
            tx232C(end_msg2);
    }
}
