#include <stdio.h>
#include <stdlib.h>
#include <xlcd.h>
#include <delays.h>
#include <usart.h>
#include <math.h>
#include "basic_serial.h"
//#include "globalVariables.h"
#include "function_manager.h"
#include <string.h>
#include "set_mode_count_serial.h"
int entered_count = 1;
int weight_per_unit = 0;
double count_double = 0;
unsigned char endmsg[] = "\r\n";
unsigned char count_serial_intro_msg1[]= "Welcome to count mode.";
unsigned char count_serial_intro_msg2[] = "'BACK' to exit\n'SETCOUNT' to change count\n'COUNT' to count.";
unsigned char count_serial_setcount_msg[]= "Enter count number:";
unsigned char count_serial_count_msg[]="Count:";
unsigned char invalid_command_msg[] = "Invalid input";
int weight_grams = 0;
unsigned char string_count_output[20];
int count_int = 0;
void set_mode_count_serial(void){
    
    
    
    
    tx232C(count_serial_intro_msg1);
    while(1)
    {
        tx232C(count_serial_intro_msg2);
        tx232C(endmsg);
        while(!MsgToSend); // wait for user to press enter
        MsgToSend = 0;
        if(strcmp(fromReceiver,"SETCOUNT"))
        {
            while(1)
            {
                tx232C(count_serial_setcount_msg);
                tx232C(endmsg);
                while(!MsgToSend); // wait for user to press enter
                MsgToSend = 0;
                if(!isDigit(fromReceiver)) // check if entered string is digit
                {
                    tx232C(invalid_command_msg);
                    tx232C(endmsg);
                    continue;
                }
                entered_count = str2int(fromReceiver); // convert entered number into int
                if(entered_count <1 || entered_count>500)
                {
                    tx232C(invalid_command_msg);
                    tx232C(endmsg);
                    entered_count = 1;
                    continue;
                }
                else
                {   
                    filter_raw_weight();
                    //callibrate_weight();
                    //ounce_or_grams();


                    weight_per_unit = weight_grams / entered_count; // get weight of 1 unit in g (int)
                    break;
                } 
            }
        }
        else if(strcmp(fromReceiver,"COUNT"))
        {
            filter_raw_weight();
            //callibrate_weight();
            //ounce_or_grams();

            
            
            if(unit_mode!=1)
            {
                count_double = weight_grams/(double)weight_per_unit; //perform calc to get count (double float))
                count_int = count_double - floor(count_double)>0.5 ? (int)ceil(count_double) : (int)floor(count_double); // int calculated count
                tx232C(count_serial_count_msg);
                tx232C(endmsg);
                //int2stringcount();               
                tx232C(string_count_output);
                tx232C(endmsg);
            }
            else
            {
                count_double = weight_grams/((double)weight_per_unit*28.35); //perform calc to get count (double float))
                count_int = count_double - floor(count_double)>0.5 ? (int)ceil(count_double) : (int)floor(count_double); // int calculated count
                tx232C(count_serial_count_msg);
                tx232C(endmsg);
                //int2stringcount();               
                tx232C(string_count_output);
                tx232C(endmsg);
            }
            
        }
        else if(strcmp(fromReceiver,"BACK"))
        {
                return;
        }
        else
        {   
            tx232C(invalid_command_msg);
            tx232C(endmsg);
            continue;
        }
    }
}

int isDigit(unsigned char* string1){
    int i = 0;
    int digit_flag = 1;
    int length = (int)strlen(string1);
    for (i=0; i<length;i++)
    {
        if (string1[i]> '9' || string1[i] <'0'){
            digit_flag = 0;
            return 0; //not digit!
        }
        else{
            continue; // check the other characters
        }
    }
    return 1; // if finish whole string and has not found non-digit, string is digits
}

int str2int( unsigned char* string2){
    int num = 0;
    int i = 0;
    int exp = 0 ;
    int output = 0;
    int myvalue = 0;
    int length;
    length = (int)strlen(string2);
    for (i= 0; i< length; i++){
        num = fromReceiver[i] - '0'; // convert char to int
        exp = length - i - 1;
        myvalue = pow(10, exp);
        output = output+ num * myvalue;
        
    }
    return output;
}

 
