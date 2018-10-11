// This is going to be the c file with the differen mode declarations
#include<stdio.h>
#include "LCD_head.h"
#include"mode_controller.h"

int user_local(void){

    // Write to LCD that it's working
    unsigned char str[]= "user local";
    string_to_LCD(str);
  

  return 0;
}
int user_remote(void){

    //Write to LCD that it's working
    unsigned char str[]= "user remote";
    string_to_LCD(str);

  return 0;
}

int factory(void){

    //Write to LCD that it's working
    unsigned char str[]= "Factory";
    string_to_LCD(str);
  return 0;

}
