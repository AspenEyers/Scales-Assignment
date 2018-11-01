/* 
 * File:   function_manager.h
 * Author: Aspen
 *
 * Created on 30 October 2018, 1:38 PM
 */

#ifndef FUNCTION_MANAGER_H
#define	FUNCTION_MANAGER_H

#ifdef	__cplusplus
extern "C" {
#endif


void enter_function(int);
void set_weight_ounces(void);
void set_weight_grams(void);
void weigh(void);
void num2str(char *string, int number);
void tare(void);
void set_samples(void);

#ifdef	__cplusplus
}
#endif

#endif	/* FUNCTION_MANAGER_H */

