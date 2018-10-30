#include<stdio.h>
#include"UI.h"
#include"mode_controller.h"
#include "p18f452.h"

// This is called in the main function and controls what buttons do
void user_interface(void){
    
    while(stateChange != newStateChange){
            functionPicker(stateChange);  
            newStateChange = stateChange;  // Update when changed
            stateDepth = -1;
            currentStateDepth = stateDepth; // update when changed
        }
        while(stateDepth != currentStateDepth){
            modeSelector(stateDepth);
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
           if (stateDepth >= 3 ){
                stateDepth = 0; // Resetting to initialize loop
           }
        
        }
        //Reset timer
        TMR0H = 0xF8;
        TMR0L = 0x30;
        
    }
    
}
