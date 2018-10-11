/* 
 * File:   BasicLcd.h
 * Author: Aspen
 *
 * Created on 12 September 2018, 10:38 PM
 */

#ifndef BASICLCD_H
#define	BASICLCD_H

#ifdef	__cplusplus
extern "C" {
#endif


    #define NB_LINES    2                             ///< Number of display lines
    #define NB_COL      16                            ///< Number of characters per line

    #define OUTP        0                             ///< Sets I/Os as outputs
    #define INP         1                             ///< Sets I/Os as inputs

    #define PWR     LATDbits.LATD7                ///< LCD ON/OFF line
    #define EN      LATDbits.LATD6                ///< LCD enable line
    #define RW      LATDbits.LATD5                ///< LCD read/write line
    #define RS      LATDbits.LATD4                ///< LCD register select line
    #define DAT4    LATDbits.LATD0                ///< Data bit 0
    #define DAT5    LATDbits.LATD1                ///< Data bit 1
    #define DAT6    LATDbits.LATD2                ///< Data bit 2
    #define DAT7    LATDbits.LATD3                ///< Data bit 3

    #define PWR_DIR TRISDbits.TRISD7             ///< Direction bit for the power line
    #define EN_DIR  TRISDbits.TRISD6             ///< Direction for EN control line
    #define RW_DIR  TRISDbits.TRISD5             ///< Direction for RW control line
    #define RS_DIR  TRISDbits.TRISD4             ///< Direction for RS control line
    #define D4_DIR  TRISDbits.TRISD0             ///< Direction for data line 0
    #define D5_DIR  TRISDbits.TRISD1             ///< Direction for data line 1
    #define D6_DIR  TRISDbits.TRISD2             ///< Direction for data line 2
    #define D7_DIR  TRISDbits.TRISD3             ///< Direction for data line 3

    #define SET_ON 1
    #define SET_OFF 0
    #define SET_OUT 0
    #define SET_IN 1
    
    #define TRUE  	1                           
    #define FALSE 	0							

    #define ENABLE  1                           
    #define DISABLE 0							

    #define SET  	1                           
    #define CLEAR	0							

    #define READ  	1                           
    #define WRITE	0							

    
    unsigned char read_lcd(void);
    void lcd_wait(void);
    void commandLCD(unsigned char bitsToSet);
    void LCDInit(void);
    void wait(int time);
    void set_lcd_pos(int, int);
    void write_lcd(unsigned char);
    void lcd_clear(void);
    void write_string(int, int, unsigned char msg[]);
    
    
    
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* BASICLCD_H */

