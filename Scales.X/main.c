/****************************************************************************
*                                                                          *
* This file is the main fie for the scales assignemnt.                     *
****************************************************************************/


/*
 * @File:   main.c
 * @Authors: Aspen, James, Tom, Lina, Kwajo, Ty, Richard
 * @date 18 September 2018
 * @ Brief the main file that all others are called from
 *
 * more detailed explination
 */



#include <stdio.h>
#include <stdlib.h>
#include "include/mode_controller.h"
#include "include/set_mode_count.h"

// Function declarations


/****************************************************************************
*                                   Definitions                             *
****************************************************************************/
#define USER_LOCAL 0    /**< Local user mode */
#define USER_REMOTE 1   /**< Remote user mode */
#define FACTORY 2       /**< Some documentation for first. */

/****************************************************************************
*                                 functions                                 *
*****************************************************************************/
void setup_pic(void);

/*
 *
 */
void main(void) {

  // Define variables
  // The default mode for the board is user local
  //int mode = user_local();
  int mode = 0;
  // Call setup functions
  // Initialise the basic functionality of the board
  // Interrupts and other things maybe as well
  setup_pic();

  // Tesintg some of the I/O atm
  // Calliong the counter working function from the set_mode_count
  count_working();

  // main program
  switch(mode){
    case 0:
        mode = user_local();
      break;
    case 1:
        mode = user_remote();
      break;
    case 3:
       mode = factory();
      break;
  }


}

void setup_pic( void){

  // Pic setup_
  // What will we need as a general set up? do we need to include the SCI, serial etc as soon as we launch our program?
  
}
