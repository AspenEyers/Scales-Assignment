// This is going to be the c file with the differen mode declarations
#include<stdio.h>
#include "LCD_head.h"
#include"mode_controller.h"
#include "p18f452.h"

void setup (void)
{
   /* Most excellent, there is a section on the INTO interrupt on pg 85 
 * called "8.6 INT0 Interrupt" 
 The following is ke information gleamed from the aforemention section 8.6
 *  Is edge triggered
 * Triggered on rise if INEDG0 =1 in INTCON2
 * Triggered on fall if INTEDG0=0 in INTCON2
 * When (desired edge) appears on INT0
 *          => INT0F=1
 * INT0 interrupt can be disabled by INT0IE=0 (in INTCON register)
 * Must clear INT0F in ISR "BEFORE" re-enabaling the interrupt
 * INT0 is desgined in such a manner that it is ALWAYS A HIGH INTERRUPT
 */
    INTCON2bits.INTEDG0= 1;//Trigger on rise 
    INTCONbits.INT0E= 1;// Enable interrupt INT0/RBO
}
/************************************************************************************************/
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
/****************************************************************************************/


void ERROR (int errorType)
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
    unsigned char str[]= "user remote";
    string_to_LCD(str);
     
}

/*
int oneUnit (void)
{
    
    //For the use in PC terminals
    if (localType==0)
    {
    char msg="Place one unit in pan";
      int szB= sizeof(msg);
         int i;
         for(i=0;i<szB;i++)
          {
           TXREG= msg[i];
         }
    }
         
    // else it is in local user mode
     else
    {
    // display message  on LCD "Place one unit in pan"
    }
    //Measures mass
    SET_MODE_WEIGH;
    while (selectButton=0)
    {
        
        //wait for mass value to be accepted
    }
    return SET_MODE_WEIGH;
}
*/
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

int CALIBRATE (int currentVoltage)
{
    //Is a manual claibration process 
    //e.g put on 50g weight, set scale as 50g by equating read voltages as value for 50g
    /* Pseduo code example
       put on weight->voltageFor50g= currentVoltage
       OutputGrams = (currentVoltage)/(voltageFor100g)*(100 )
     Roughly 200mV for each 50g
     Account for offset -> approximatly +175mV
     */ 
     //Write to LCD that it's working
    unsigned char str[]= "Calibrate";
    string_to_LCD(str);
}

int SET_SAMPLES_PER_MEASURMENT (int SSPM)
{
    /*
     if (SSPM > 40)
        error //setting error to be a global function for modularity sake
     else
     return SSPM
     */
}

void SHOW_WEIGHT_READINGS (int raw)
{
    //FACTORY MODE ONLY 
    //Send raw values to transmit register for the terminal 
    //However, unsure how to make it real time , other than to poll or interrupt
   // TXREG=raw;
    // Will need top set up way for system to tell if it is in Terminal or local mode
      
    //  buffer = [weightValue,weightType];
    /*
    int szB= sizeof(buffer);
     int il
     for(i=0;i<szB;i++)
     * {
     *  TXREG= buffer[i];
     * }
     
     */
     //Write to LCD that it's working
    unsigned char str[]= "SHOW WEIGHT READINGS";
    string_to_LCD(str);
}

void SHOW_STATISTICS (void)
{
     //Write to LCD that it's working
    unsigned char str[]= "SHOW STATISTICS";
    string_to_LCD(str);
}

void SET_MODE_USER (void )
{   //Activate User_mode
    //USER_MODE;
     //Write to LCD that it's working
    unsigned char str[]= "SET MODE USER";
    string_to_LCD(str);
}

void USER_LOCAL (void)
{
  //  userlocal=1;
     //Write to LCD that it's working
    unsigned char str[]= "USER LOCAL";
    string_to_LCD(str);
    /*Both USER_REMOTE and FACTORY_MODE useses the PC to enter the function that is desired directly 
     * ASSUMES : Use of ASCII value for down-key and USE of ASCII value for enter-key are used 
     TXREG= "SET_MODE_WEIGH";
     if (nextButton=1); 
       TXREG= "SET_MODE_COUNT"
        if(nextButton=1);
            TXREG="TARE";
            if(nextButton=1)
                TXREG="SET_WEIGH_GRAMS";
               if (RXREG=25)
                   TXREG="SET_WEIGHT_OUNCES;
                       if(nextButton=1)
                           TXREG="SET_FACTORY_MODE";
                                if(nextButton=1)
                                     USER_LOCAL;
                        else if (selectButton=1)
                           SET_MODE_FACTORY;
               else if (selectButton=1)
                   SET_WEIGHT_OUNCES;
           else if (selectButton=1)
               SET_WEIGH_GRAMS;
        else if (selectButton=1)
            TARE;
     else if (selectButton=1)
        SET_MODE_WEIGH';     
     */  
}



/*
int functionNumberPicker(char fP )
{
    switch(fP) //https://stackoverflow.com/questions/3065438/switch-statement-with-returns-code-correctness
    {
        case('SET_MODE_WEIGH'):
            result = 0;
            break;
        case('SET_MODE_COUNT'):
            result = 1;
            break;
        case('TARE') :
            result = 2;
            break;
        case('SET_WEIGHT_GRAMS'):
            result = 3;
            break;
        case('SET_WEIGHT_OUNCES'):
            result = 4;
            break;
        case('SET_MODE_FACTORY'):
            result = 5;
            break;
        case('CALIBRATE'):
            result = 6;
            break;
        case('SET_SAMPLES_PER_MEASUREMENT'):
            result = 7;
            break;
        case('SHOW_WEIGHT_READINGS'):
            result = 8;
            break;
        case('SHOW_STATISTICS'):
            result = 9;
            break;
        case('SET_MODE_USER'):
             result = 10;
             break;
        case('HELP'):
            result = 11;
            break;
        default:
        {
            errorType =1; //Invalid input
            ERROR ;
            return 12;
        } 
    }
    return result;
}
      
 */

void HELP (void)
{
    /* I am thinking, it will display a guide with all the available functions  */
     //Write to LCD that it's working
    unsigned char str[]= "Help";
    string_to_LCD(str);
}

void functionPicker(int N )
{
    switch (N)
    {
        case 0:
            SET_MODE_WEIGH;
            break;
        case 1:
            SET_MODE_COUNT;
            break;
        case 2: 
            TARE;
            break;
        case 3:
            SET_WEIGHT_GRAMS;
            break;
        case 4:
            SET_WEIGHT_OUNCES;
            break;
        case 5:
            SET_MODE_FACTORY;
            break;
        case 6:
            CALIBRATE;
            break;
        case 7:
            SET_SAMPLES_PER_MEASURMENT;
            break;
        case 8:
            SHOW_WEIGHT_READINGS;
            break;
        case 9:
            SHOW_STATISTICS;
            break;
        case 10:
            SET_MODE_USER;
            break;
        case 11:
            HELP;
            break;
        default:
           // errorType =1; //Invalid input
            ERROR ;
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
   

