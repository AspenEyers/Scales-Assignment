/****************************************************************************
*                                                                          *
* This file is to be used to set the mode to set_mode_count                *
****************************************************************************/

#include <stdio.h>
//#include <stepin.h>
#include "count_or_weigh_mode.h"
#include "LCD_head.h"
// @set_mode_count.c
//@Thomas McCabe
// @19 September 2018
//@ file containing a weigh mode working trival output

int set_mode_count (int var){

  //Write to LCD that it's working
 unsigned char str[]= "count mode";
 string_to_LCD(str);
    
  return 0;

}

int set_mode_weigh (int var){

  //Write to LCD that it's working
 unsigned char str[]= "weigh mode";
 string_to_LCD(str);
    
  return 0;

}

void count_working(void){

  // This is the seperate function to test if count is responding
 //printf("set_mode_count is responding\n");


}
