//Use tts_init() to initialize tts
//Pass a string into tts_run() to convert text to speech

#include <stdio.h>
#include <stdlib.h>
#include <p18f4520.h>
#include <spi.h>
#include <delays.h>
//#include "ConfigRegs18f4520.h"
//#include "ConfigRegs.h"
#include "TTS_CMD.h"
#include "tts.h"

void tts_init(void) {

    #define RESET PORTCbits.RC0
    #define RB PORTCbits.RC1
    #define SS PORTCbits.RC2
    #define SCLK PORTCbits.RC3
    #define MISO PORTCbits.RC4
    #define MOSI PORTCbits.RC5

    #define CS PORTBbits.RB3


    unsigned char SPI_status;
    CloseSPI();
    OpenSPI(SPI_FOSC_64, MODE_11, SMPEND);

    //Initialization
    IO_setup();
    reset();

    //Transition to idle state
    TTS_cmd_word(TTS_SCLS);
    Delay1KTCYx(0); //sufficient delay to allow the clock to start up
    TTS_cmd_word(TTS_PWUP);


    TTS_cmd_byte(TTS_RDST);
    SPI_status = SSPBUF;
    while(!(SPI_status & 1)){
        SPI_status = SSPBUF;   //wait for rdy to be set
    }
    while (!RB); //wait for RB to be high
    TTS_cmd_byte(0x00);

    TTS_cmd_special(TTS_SVOL);
    TTS_cmd_special(0x00); //max volume
    SS = 1;

  }

  void tts_run(char* st){
    
      
    unsigned char SPI_status;
    int i = 0;
    
    //convert state
    TTS_cmd_special(TTS_CONV);
    //send string
    send_string(st);
    SS = 1;  //end of transaction
    TTS_cmd_word(TTS_FIN);

    SPI_status = SSPBUF;
    while((SPI_status >> 1) & 1){
            SPI_status = SSPBUF;   //wait for cnvt to clear
    }

    //back to idle state
    TTS_cmd_word(TTS_IDLE);

}


//setup for input/output for spi
void IO_setup(){

    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 1;
    TRISCbits.RC2 = 0;
    TRISCbits.RC3 = 0;
    TRISCbits.RC4 = 1;
    TRISCbits.RC5 = 0;

    TRISBbits.RB3 = 0;

    //PORTBbits.RB3 = 0; //chip select
    SS = 0; //slave select
}

void reset(){

    RESET = 0;
    Delay10TCYx(0);     //delay for > 0.5us
    RESET = 1;
    Delay10TCYx(0);     //delay for > 0.5us
    RESET = 0;

}

//command word
void TTS_cmd_word(char cmd){

    CS = 0;
    SS = 0;
    while (!RB); //wait for RB to be high
    putcSPI(cmd);
    Delay1KTCYx(0);
    while (!RB); //wait for RB to be high
    putcSPI(0x00);
    Delay1KTCYx(0);
    SS = 1;
}

//Command byte
void TTS_cmd_byte(char cmd){

    CS = 0;
    SS = 0;
    while (!RB); //wait for RB to be high
    putcSPI(cmd);
    SS = 1;
}

//Command byte without ss = 1
void TTS_cmd_special(char cmd){

    SS = 0;
    while (!RB); //wait for RB to be high
    putcSPI(cmd);
}

void send_string(char *st){
    int i = 0;
    while(st[i] != '\0'){
        while (!RB);
        putcSPI(st[i]);
        i++;
    }
    putcSPI(0x1A); //EOT character
}

void delay(void){
    int i;
    for(i = 0; i<30; i++){
       Delay1KTCYx(255); 
    }
}