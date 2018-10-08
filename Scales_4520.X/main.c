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

/****************************************************************************
*                                 Includes                                  *
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>



/****************************************************************************
*                                 PIC board setup                           *
****************************************************************************/
// Setup board OSC, watchdog and low voltage protect 
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF


/****************************************************************************
*                                 #Defines                                  *
****************************************************************************/
// User mode defines
#define USER_LOCAL 0    /**< Local user mode */
#define USER_REMOTE 1   /**< Remote user mode */
#define FACTORY 2       /**< Some documentation for first. */

// LCD defines
#define SET_ROW 0
#define SET_POS 1
#define SEND_MSG 2



void main(int argc, char** argv) {

    //return (EXIT_SUCCESS);
}

