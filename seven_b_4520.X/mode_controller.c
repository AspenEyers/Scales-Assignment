// This is going to be the c file with the differen mode declarations
#include<stdio.h>
#include "basic_lcd.h"
#include"mode_contoller.h"
#include "p18f452.h"

/*
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

 
 */

void functionPicker(int mode )
{
    char help_lcd[] = "HELP";
    char user_lcd[] = "SET_MODE_USER";
    char weigh_lcd[] = "SET_MODE_WEIGH";
    char tare_lcd[] = "TARE";
    char count_lcd[] = "SET_MODE_COUNT";
    char grams_lcd[] = "TO_GRAM";
    char ounces_lcd[] = "TO_OZ";
    char factory_lcd[] = "FACTORY";
    char err[] = "Error";
   
    switch (mode)
    {
        case 0:
            write_string(0,0,help_lcd);
            break;
        case 1:
            write_string(0,0,user_lcd);
            break;
        case 2: 
            write_string(0,0,weigh_lcd);
            break;
        case 3:
            write_string(0,0,tare_lcd);
            break;
        case 4:
            write_string(0,0,count_lcd);
            break;
        case 5:
            write_string(0,0,grams_lcd);
            break;
        case 6:
            write_string(0,0,ounces_lcd);
            break;
        case 7:
            write_string(0,0,factory_lcd);
            break;
        default:
            write_string(0,0,err);
            break; 
    }
}

/*
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
*/

//////////////////////////////////////////////////////////////////////
/*
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
       
       */
      /*
       if((PORTAbits.RA4) != 1)            //If 1st switch is pressed
        {
            set_mode_count(1);
            read_input();
       
       
             PORTBbits.RB3 = 1;           //3rd LED ON
            wait(1000);              //1 Second Delay
             PORTBbits.RB3 = 0;           //LED OFF

//        }*/
//       while((PORTBbits.RB0) == 0);
// 
//}
   


    