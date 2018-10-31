
// Included files
//#include <stdio.h>
#include "ConfigRegs18f4520.h"
#include "countFunctions.h"
#include "basic_lcd.h"

int hundreds ;
int tens ;
int ones;
char message[20];
char symbol;
int column=0;
char sym0,sym1,sym2,sym3,sym4, sym5;

void set_count (void)
{
    hundreds=0;
    tens=0;
    ones =1;
    
    if (column==0)
    {
        sym0= '|';
        sym1='|';
        sym2= ' ';
        sym3 = ' ';
        sym4 = ' ';
        sym5 = ' ';
    }
    else if (column==1)
    {
        sym1= '|';
        sym2='|';
        sym3= ' ';
        sym4 = ' ';
        sym0 = ' ';
        sym5 = ' ';
    }
    else if (column==2)
    {
        sym2= '|';
        sym3='|';
        sym1= ' ';
        sym0 = ' ';
        sym4 = ' ';
        sym5 = ' ';
    }
    else if (column==3)
    {
        sym3= '|';
        sym4='|';
        sym2= ' ';
        sym1 = ' ';
        sym0 = ' ';
        sym5 = ' ';
    }
    else if (column==4)
    {
        sym3= ' ';
        sym4='|';
        sym2= ' ';
        sym1 = ' ';
        sym0 = ' ';
        sym5 = '|';
    }
    message[0] = sym0;
    message[1] = hundreds+48;
    message[2]= sym1;
    message[3]=tens+48;
    message[4]= sym2;
    message [5]= ones+48;
    message [6]= sym3;
    message [7]='E';
    message [8]='N';
    message [9]='T';
    message [10]='E';
    message [11]= 'R';
    message [12]= sym4;
    message [13]= 'B';
    message [14]= 'A';
    message [15]= 'C';
    message [16]= 'K';
    message [17]= sym5;
    write_string(0,0,message);
    
    
   // countMenu();
}

/*void countMenu();
{
    
}
*/



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