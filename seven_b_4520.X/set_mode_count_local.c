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
#include "set_mode_count_local.h"
#include "set_mode_count_serial.h"
#include "weight_filter.h"
#include "basic_lcd.h"

extern int entered_count;
extern int weight_per_unit;
extern double count_double;
extern int filtered_weight;
extern int tare_val;
extern int count_int;
int still_in_count_local;
int count_column = 0;
int hundreds_c = 0;
int tens_c = 0;
int ones_c = 1;
int numberOunits = 0;
char sym0,sym1,sym2,sym3,sym4, sym5;

void set_mode_count_local(void){
    int still_in_count_local = 1;
    int count_local_options =0;
    while(still_in_count_local)
    {
        displayOptions(count_local_options);
        while(still_in_count_local)
        {
            if(PORTBbits.RB4 == 1)
            {
                wait(10000); // debounce
                while(PORTBbits.RB4 == 1);
                count_local_options++;
                if(count_local_options > 2 )
                {
                    count_local_options = 0;
                }
                break;
            }
            else if(PORTBbits.RB5 == 1)
            {
                wait(1000); // debounce                    
                 // move into the Actual function corresponding to the 'local_state'
                enter_count_options(count_local_options);
                
            }   
        }    
    }
}
void displayOptions(int optionnum){
    char setcount_msg_local[] = "SET COUNT";
    char showcount_msg_local[] = "COUNT";
    char back_msg_local[] = "BACK";
    switch (optionnum)
    {
        case 0:
            write_string(0,0,setcount_msg_local);
            break;
        case 1:
            write_string(0,0,showcount_msg_local);
            break;
        case 2: 
            write_string(0,0,back_msg_local);
            break;
    }
}
void enter_count_options(int selected_option)
{
    switch(selected_option){
        case 0:
            findCount();
            break;
        case 1:
            showCountLocal();
            break;
        case 2:
            still_in_count_local = 0;
            return;
    }
}
void showCountLocal(void){
    char outputlol[12];
    filter_raw_weight();
    if(unit_mode!=1)
            {
                count_double = (filtered_weight-tare_val)/(double)weight_per_unit; //perform calc to get count (double float))
                count_int = count_double - floor(count_double)>0.5 ? (int)ceil(count_double) : (int)floor(count_double); // int calculated count
                
                
//                intToStringCount(count_int);   
                num2str(&outputlol, count_int);
                write_string(0,0,outputlol);
                
            }
            else
            {
                count_double = (filtered_weight-tare_val)/((double)weight_per_unit*28.35); //perform calc to get count (double float))
                count_int = count_double - floor(count_double)>0.5 ? (int)ceil(count_double) : (int)floor(count_double); // int calculated count
                 
                num2str(&outputlol, count_int);
                write_string(0,0,outputlol);
            }
}
void findCount(void){
    int still_in_findCount = 1;
    //char errormsg[]="Invalid";
    //while(still_in_findCount)
    //{
        display_count();
        while(still_in_findCount)
        {
            if(PORTBbits.RB4 == 1)
            {
                wait(10000); // debounce
                while(PORTBbits.RB4 == 1);
                
                if(count_column==4)
                {
                    count_column= 0;               
                }        
                else
                {
                    count_column += 1;                
                }
                display_count();
            }
            else if(PORTBbits.RB5 == 1)
            {
                wait(1000); // debounce                    
                 // move into the Actual function corresponding to the 'local_state'
                if(count_column==0)
                {
                    if(hundreds_c != 9)
                    {
                        hundreds_c++;
                
                    }
                    else
                    {
                    hundreds_c =0;
                    }
                display_count();
                }
        
                else if(count_column==1)
                {
                    if(tens_c != 9)
                    {
                        tens_c++;
                
                    }
                    else
                    {
                        tens_c =0;
                    }
                    display_count();
                }
                else if(count_column==2)
                {
                    if(ones_c != 9)
                    {
                        ones_c++;               
                    }
                    else
                    {
                        ones_c =0;
                    }
                    display_count();
                }
                
                else if(count_column==3) // if ok
                {
                    entered_count = (hundreds_c*100) + (tens_c*10) + ones_c;
                    if(entered_count<1|| entered_count>500)
                    {
                        //write_string(0,0,errormsg);
                        entered_count = 1;
                    }
                }
                else if(count_column==4) // if back
                {
                    still_in_findCount=0;// main menu
                }              
            }   
        }    
    //}
    
}
void display_count(void)
{
   unsigned char count_message[16]; 
    
    if (count_column==0)
        {
            sym0= '|';
            sym1='|';
            sym2= ' ';
            sym3 = ' ';
            sym4 = ' ';
            sym5 = ' ';
            
            //sym5 = '0';
        }
    else if (count_column==1)
        {
            sym1= '|';
            sym2='|';
            sym3= ' ';
            sym4 = ' ';
            sym0 = ' ';
            sym5 = ' ';

            //sym5 = '1';
        }
    else if (count_column==2)
        {
            sym2= '|';
            sym3='|';
            sym1= ' ';
            sym0 = ' ';
            sym4 = ' ';
            sym5 = ' ';
            
            //sym5 = '-';
        }
    else if (count_column==3)
        {
            sym3= '|';
            sym4='|';
            sym2= ' ';
            sym1 = ' ';
            sym0 = ' ';
            sym5 = ' ';
           
            //sym5 = '3';
        }
    else if (count_column==4)
        {
            sym3= ' ';
            sym4='|';
            sym2= ' ';
            sym1 = ' ';
            sym0 = ' ';
            sym5 = '|';

            //sym5 = '4';
        }
    else
        {
             sym0= '|';
            sym1='|';
            sym2= ' ';
            sym3 = ' ';
            sym4 = ' ';
            sym5 = ' ';
            count_column = 0;
        }
    count_message[0] = sym0;
    count_message[1] = hundreds_c+48;
    count_message[2]= sym1;
    count_message[3]=tens_c+48;
    count_message[4]= sym2;
    count_message [5]= ones_c+48;
    count_message [6]= sym3;
    count_message [7]='O';
    count_message [8]='K';
    count_message [9]= sym4;
    count_message [10]= 'B';
    count_message [11]= 'A';
    count_message [12]= 'C';
    count_message [13]= 'K';
    count_message [14]= sym5;
    count_message [15]= '\0';
   
    write_string(0,0,count_message);
    
    
   // countMenu();
}
