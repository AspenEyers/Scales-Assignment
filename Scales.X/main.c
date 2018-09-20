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

// Function declarations


/****************************************************************************
*                                   Definitions                             *
****************************************************************************/
#define USER_LOCAL 0    /**< Local user mode */
#define USER_REMOTE 1   /**< Remote user mode */
#define FACTORY 2       /**< Some documentation for first. */



/*
 *
 */
void main(void) {

  // Define variables
  // The default mode for the board is user local
  int mode = USER_LOCAL;

  // Call setup functions
  // Initialise the basic functionality of the board
  // Interrupts and other things maybe as well
  setup_pic();


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
