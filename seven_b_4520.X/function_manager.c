#include "function_manager.h"
#include "basic_serial.h"
#include "set_mode_count_serial.h"
#include "weight_filter.h"
#include "basic_lcd.h"


#define HELP 0            
#define SET_MODE_USER 1
#define SET_MODE_WEIGH 2
#define TARE 3
#define SET_MODE_COUNT 4
#define SET_WEIGHT_GRAMS 5
#define SET_WEIGHT_OUNCES 6
#define SET_MODE_FACTORY 7
#define SHOW_WEIGHT_READINGS 8
#define SHOW_STATISTICS 9
#define SET_SAMPLES_PER_MEASURMENT 10
#define CALIBRATE 11

// mode intro messages
char weigh_intro_msg[] = "You are in weigh mode";
char tare_msg[] = "Taring scales";
char calibrate[] = "calibrating scales:";
char help_message[] = "The following commands are valid:\n\r";
char help_message2[] = "HELP, USER, WEIGH, TARE, COUNT, SET_GRAMS \n\r";
char help_message3[] = "SET_OUNCES, FACTORY, WEIGHT_READINGS, STATISTICS\n\r";
char help_message4[] = "SET_SAMPLES, CALIBRATE";
char count_intro_msg[] = "1";
char set_grams_intro_msg[] = "2";
char set_ounces_intro_msg[] = "3";
char factory_intro_msg[] = "4";
char weight_readings_intro_msg[] = "5";
char statistics_intro_msg[] = "6";
char samples_intro_msg[] = "7";
char msg2[] = "default";
char end_msg2[] = "\r\n";
char return_line[] = "\r";
char grams[] = "grams";
char oz[] = "oz";
char empty[] = "      ";
extern unit_mode;
extern char output[25];
extern filtered_weight;
extern factory_return;
extern int tare_val;
extern int current_mode;

void enter_function(int mode){
    
    switch(mode){
        case HELP:
            tx232C(help_message);
            tx232C(help_message2);            
            tx232C(help_message3);
            tx232C(help_message4);
            tx232C(end_msg2);
            break;
        case SET_MODE_WEIGH:
            tx232C(weigh_intro_msg);
            tx232C(end_msg2);
            weigh();
            break;
        case TARE:
            tx232C(tare_msg);
            tx232C(end_msg2);
            tare();
            break;
        case CALIBRATE:
            if (current_mode == 2)
            {
                tx232C(calibrate);
                tx232C(end_msg2);
                break;    
            }
            else{break;}  
        case SET_MODE_COUNT:
            //tx232C(count_intro_msg);
            //empty_receive_buffer();
            set_mode_count_serial();
            break;
        case SET_WEIGHT_GRAMS:
            tx232C(set_grams_intro_msg);
            set_weight_grams();
            break;
        case SET_WEIGHT_OUNCES:
            tx232C(set_ounces_intro_msg);
            set_weight_ounces();
            break;
        case SET_MODE_FACTORY:
            tx232C(factory_intro_msg);
            break;
        case SET_SAMPLES_PER_MEASURMENT:
            if(current_mode == 2){
                tx232C(samples_intro_msg);
                break;
            }
            else{break;}   
        case SHOW_WEIGHT_READINGS:
            if(current_mode == 2){
                tx232C(weight_readings_intro_msg);
                break;
            }
            else{break;}
        case SHOW_STATISTICS:
            if(current_mode == 2){
                tx232C(statistics_intro_msg);
                break;
            }
            else{break;}
        case SET_MODE_USER:
            break;
        default:
            tx232C(msg2);
            tx232C(end_msg2);
            
            
            

    }
}

void set_weight_grams(){
    unit_mode = 0;
}

void set_weight_ounces(){
    unit_mode = 1;
}

void weigh(void){
    char test_msg[] = "PLZ work";
    
    
    factory_return = 0;
    while(1){
    filter_raw_weight();
        //callibrate_weight();
        //ounce_or_grams();
    
    if(unit_mode == 0){
        num2str(&output,(filtered_weight-tare_val));
        tx232C(output);
        tx232C(grams);
        tx232C(empty);
        tx232C(return_line);
    }    
    if(unit_mode == 1){
        num2str(&output,((filtered_weight-tare_val)*0.035));
        tx232C(output);
        tx232C(oz);
        tx232C(empty);
        tx232C(return_line);
    }
        if(factory_return == 1){
            break;
        }
    }
}


void tare(void){
    tare_val = filtered_weight;
}


// This function takes in a pointer to a string and
// a number. The number will be saved to that string
// The function returns nothing.
// The function tests each character of the number and 
// will return when it reaches 0. therefore a number starting
// with a 0 e.g. 098. will write nothing to the string.
void num2str(char *string, int number){
    
    int length = 0;    
    int rem = number;
    int i = 0;
    
    // ********                     ******** //
    // Determine the length of the input number
    while(rem > 0){
        length++;
        rem = rem/10;
    }
    
    // ********                      ******** //
    // Convert the number into a char array
    rem = number;
    i = length;
    
    while(length > 0){
        
        *(string+length-1) = (rem%10 + 48);
        length--;
        rem = rem/10;
    }
    *(string+i) = ',';
    i++;
    *(string+i) = '\0';
}