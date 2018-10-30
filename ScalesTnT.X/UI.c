#include<stdio.h>
#include"UI.h"
#include"mode_controller.h"
#include "p18f452.h"

// Function declarations
void modeSelector(int,int);
void user_interface(void);
void buttonControl(void);

// 'Gloabal' declarations
int stateChange;  //variable for picking a new mode
int newStateChange; //condition to stop flickering of constant loop
int maxNStates=11; // maximum number of modes in first state
int stateDepth;
int currentStateDepth;

void UIsetup(void){
    
    stateChange = 0;
    stateDepth = -1;
    currentStateDepth = stateDepth;
    newStateChange = stateChange;
    
    
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
    if((PORTBbits.RB4) == 1)       
    {
        // debounce here
        wait(1000);
        if((PORTBbits.RB4) != 1){
            
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
    if((PORTBbits.RB5) == 1)       
    {
        // debounce here
        wait(1000);
        if((PORTBbits.RB5) != 1){
            
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
