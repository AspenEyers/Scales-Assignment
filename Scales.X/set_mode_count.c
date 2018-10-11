/****************************************************************************
*                                                                          *
* This file is to be used to set the mode to set_mode_count                *
****************************************************************************/

#include <stdio.h>
//#include <stepin.h>
#include "set_mode_count.h"
// @set_mode_count.c
//@Thomas McCabe
// @19 September 2018
//@ file containing a weigh mode working trival output

int set_mode_count (int var){

  // All we wan it to do now is print set_mode_count to screen
  printf("set_mode_count\n");
  printf("on line %d\n", var);
  return 0;

}

void count_working(void){

  // This is the seperate function to test if count is responding
  printf("set_mode_count is responding\n");


}
