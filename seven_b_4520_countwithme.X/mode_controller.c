// This is going to be the c file with the differen mode declarations
#include<stdio.h>
#include "basic_lcd.h"
#include"mode_controller.h"
#include "p18f452.h"

void functionPicker(int mode )
{ 
    unsigned char help_str[] = "help";          
    unsigned char set_mode_user[] = "set mode user";
    unsigned char set_mode_weigh[]="Set mode weigh";
    unsigned char tare_str[]="Tare";
    unsigned char set_mode_count[] = "Set Mode Count";
    unsigned char set_weight_grams[] = "Set weight grams";
    unsigned char set_weight_ounces[] = "Set Weight Ounces";
    unsigned char set_mode_factory[]="Set Mode Factory";
    unsigned char show_weight_readings[] = "Show Weight readings";
    unsigned char show_stats[] = "Show Statistics";
    unsigned char set_samples_per_measurement[] = "Set Samples";
    unsigned char calibrate_str[] = "Calibrate";    
      unsigned char error_str[] = "Error";  

    switch (mode)
    {
        case 0:
            string_to_LCD(help_str);
            break;
        case 1:
            string_to_LCD(set_mode_user);
            break;
        case 2: 
           string_to_LCD(set_mode_weigh);
            break;
        case 3:
            string_to_LCD(tare_str);
            break;
        case 4:
            string_to_LCD(set_mode_count);
            break;
        case 5:
             string_to_LCD(set_weight_grams);
            break;
        case 6:
           string_to_LCD(set_weight_ounces);
            break;
        case 7:
            string_to_LCD(set_mode_factory);
            break;
        case 8:
            string_to_LCD(show_weight_readings);
            break;
        case 9:
            string_to_LCD(show_stats);
            break;
        case 10:
            string_to_LCD(set_samples_per_measurement);
            break;
        case 11:
            string_to_LCD(calibrate_str);
            break;
        default:
           // errorType =1; //Invalid input
            string_to_LCD(error_str);
            break; 
    }
}

void Entered1(void)
{
    int count;
    /* I am thinking, it will display a guide with all the available functions  */
     //Write to LCD that it's working
    unsigned char str[] = "Entered 1";
    string_to_LCD(str);
}
void Entered2(void)
{
    int count;
    /* I am thinking, it will display a guide with all the available functions  */
     //Write to LCD that it's working
    unsigned char str[] = "Entered 2";
    string_to_LCD(str);
}
void Entered3(void)
{
    int count;
    /* I am thinking, it will display a guide with all the available functions  */
     //Write to LCD that it's working
    unsigned char str[] = "Entered 3";
    string_to_LCD(str);
}


void modeSelector(int depth,int mode){
    
    switch(depth){
        case 0:
            functionPicker(mode);
            break;
        case 1:
           Entered1();
           break;
        case 2:
            Entered2();
            break;
        case 3:
            Entered3();
            break;
        default:
           // errorType =1; //Invalid input
            ERROR() ;
            break; 
    }
    
    
}


//////////////////////////////////////////////////////////////////////
void read_input(void){
   
        // This function monitors RB0 and RA4 as input buttons
       TRISB = 0b00000001;                    //Configure 1st bit of PORTB as input and 3rd as out
       TRISA = 0b00010000;
         
       while((PORTBbits.RB0) == 1 );
        if((PORTBbits.RB0) != 1)            //If 1st switch is pressed
        {
             PORTBbits.RB2 = 1;           //3rd LED ON
            wait(1000);              //1 Second Delay
             PORTBbits.RB2 = 0;           //LED OFF

        }
      /*
       if((PORTAbits.RA4) != 1)            //If 1st switch is pressed
        {
            set_mode_count(1);
            read_input();
       
       
             PORTBbits.RB3 = 1;           //3rd LED ON
            wait(1000);              //1 Second Delay
             PORTBbits.RB3 = 0;           //LED OFF

        }*/
       while((PORTBbits.RB0) == 0);
 
}
   



    