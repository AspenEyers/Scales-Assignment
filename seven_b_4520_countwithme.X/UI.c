#include<stdio.h>
#include"UI.h"
#include"mode_contoller.h"
#include "p18f452.h"
#include"basic_lcd.h"

// Function declarations
void user_interface(void);
void buttonControl(void);
void UIsetup(void);

// 'Gloabal' declarations
int stateChange;  //variable for picking a new mode
int newStateChange; //condition to stop flickering of constant loop
int maxNStates=11; // maximum number of modes in first state
int stateDepth;
int currentStateDepth;

void UIsetup(void){
    
    stateChange = 0;        // Initial "mode"
    stateDepth = 0;         // no mode has been selected so depth = 0
    currentStateDepth = stateDepth; // This is for checking if they have been changed
    newStateChange = stateChange; // likewise for current depth
    
    
}
// This is called in the main function and controls what buttons do
void user_interface(void){
    
    while(stateChange != newStateChange){
            functionPicker(stateChange);  
            newStateChange = stateChange;  // Update when changed
            stateDepth = 0;
            currentStateDepth = stateDepth; // update when changed
        }
        while(stateDepth != currentStateDepth){
            modeSelector(stateDepth,stateChange);
            currentStateDepth = stateDepth; // update when changed
        }  

}

// This is called in timer interrupt and controls what each button does
void buttonControl(void){

    // check if the button is pressed
    if((PORTBbits.RB3) == 1)       
    {
        // debounce here
        wait(1000);
        if((PORTBbits.RB3) != 1){
            
            //N &= maxNless;//
           stateChange++;
           PORTB = 0;
           wait(100);

           // ensuring that the it loops through
           if (stateChange > maxNStates ){
                stateChange = 0;
           }
        
        }
        //Reset timer
        TMR0H = 0xF8;
        TMR0L = 0x30;
        
    }
    if((PORTBbits.RB2) == 1)       
    {
        // debounce here
        wait(1000);
        if((PORTBbits.RB2) != 1){
            
            //N &= maxNless;//
           stateDepth++;
           PORTB = 0;
           wait(100);

           // ensuring that it loops through
           if (stateDepth > 3 ){
                stateDepth = 0; // Resetting to initialize loop
           }
        
        }
        //Reset timer
        TMR0H = 0xF8;
        TMR0L = 0x30;
        
    }
    
}
