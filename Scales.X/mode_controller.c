// This is going to be the c file with the differen mode declarations
#include<stdio.h>
#include"mode_controller.h"

int user_local(void){

  // DO something
  printf("I am in user_local_mode");

  return 0;
}
int user_remote(void){

  // DO something
  printf("I am in user_remote_mode\n");

  return 0;
}

int factory(void){

  // DO something
  printf("I am in user_remote_mode\n");

  return 0;

}
