// This is going to be the c file with the differen mode declarations
#include<stdio.h>
#include "basic_lcd.h"
#include"mode_contoller.h"
#include "p18f452.h"

int user_local(void)
{
    // Write to LCD that it's working
    unsigned char str[]= "user local";
    string_to_LCD(str);
  return 0;
}

int user_remote(void)
{
    //Write to LCD that it's working
    unsigned char str[]= "user remote";
    string_to_LCD(str);
  return 0;
}

int factory(void)
{
    //Write to LCD that it's working
    unsigned char str[]= "Factory";
    string_to_LCD(str);
  return 0;

}

void ERROR (void)
{
    /*
    if (errorType=1) // Remote user inputed invalid command 
    {  
        char msg="INCORRECT MESSAGE";
        int sZ= sizeof(msg);
        int i=0;
     for (i=0;i<sZ;i++)
        {
            TXREG = msg[i] ;
        }
    }
     */
     //Write to LCD that it's working
    unsigned char str[]= "ERROR";
    string_to_LCD(str);
}

void SET_MODE_WEIGH (void)
{ /*
    if (localType==0)
    {
        //if uses PC terminal, it must use theTXREG to display the characters
         //  buffer = [weightValue,weightType];
       
        int szB= sizeof(buffer);
         int il
         for(i=0;i<szB;i++)
         * {
         *  TXREG= buffer[i];
         * }
              
   *}
   */
     //Write to LCD that it's working
    unsigned char str[]= "SET_MODE_WEIGH";
    string_to_LCD(str);
}
void SET_MODE_COUNT (void)
{
    /*
    oneAmount=oneUnit;
     number=weightGrams/oneAmount;
    */
     //Write to LCD that it's working
    unsigned char str[]= "Set count";
    string_to_LCD(str);
     
}

int TARE (void)
{
//    currentVoltage=0;
      //Write to LCD that it's working
    unsigned char str[]= "TARE";
    string_to_LCD(str);
}

char SET_WEIGHT_GRAMS (void)
{
   
    //weightType="g";
     //Write to LCD that it's working
    unsigned char str[]= "SET_WEIGHT_GRAMS";
    string_to_LCD(str);
}
char SET_WEIGHT_OUNCES (void)
{
    
    //weightType="oz";
     //Write to LCD that it's working
    unsigned char str[]= "SET_WEIGHT_OUNCES";
    string_to_LCD(str);

}

void SET_MODE_FACTORY (void)
{
        //Write to LCD that it's working
    unsigned char str[]= "SET_MODE_FACTORY";
    string_to_LCD(str);
}

int CALIBRATE (void)
{
    unsigned char str[]= "Calibrate";
    string_to_LCD(str);
}

int SET_SAMPLES_PER_MEASURMENT (void)
{
    //Write to LCD that it's working
    unsigned char str[]= "Set Sample N";
    string_to_LCD(str);
}

void SHOW_WEIGHT_READINGS (void)
{
    unsigned char str[]= "SHOW WEIGHT READINGS";
    string_to_LCD(str);
}

void SHOW_STATISTICS (void)
{
    unsigned char str[]= "SHOW STATISTICS";
    string_to_LCD(str);
}

void SET_MODE_USER (void )
{  
    unsigned char str[]= "SET MODE USER";
    string_to_LCD(str);
}

void USER_LOCAL (void)
{
  //
     //Write to LCD that it's working
    unsigned char str[]= "USER LOCAL";
    string_to_LCD(str);
}

void HELP (void)
{
    /* I am thinking, it will display a guide with all the available functions  */
     //Write to LCD that it's working
    unsigned char str[]= "Help";
    string_to_LCD(str);
}

void functionPicker(int mode )
{
    switch (mode)
    {
        case 0:
            SET_MODE_COUNT();
            break;
        case 1:
            SET_MODE_WEIGH();
            break;
        case 2: 
            TARE();
            break;
        case 3:
            SET_WEIGHT_GRAMS();
            break;
        case 4:
            SET_WEIGHT_OUNCES();
            break;
        case 5:
            SET_MODE_FACTORY();
            break;
        case 6:
            CALIBRATE();
            break;
        case 7:
            SET_SAMPLES_PER_MEASURMENT();
            break;
        case 8:
            SHOW_WEIGHT_READINGS();
            break;
        case 9:
            SHOW_STATISTICS();
            break;
        case 10:
            SET_MODE_USER();
            break;
        case 11:
            HELP();
            break;
        default:
           // errorType =1; //Invalid input
            ERROR() ;
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
   



    