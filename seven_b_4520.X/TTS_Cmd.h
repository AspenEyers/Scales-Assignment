#ifndef TTS_CMD_H
#define TTS_CMD_H

/******************************************************************************

    File Name: TTS_cmd.h

    #defines for all WTS701 commands needed in an application.

    (C) Winbond Electronics Corporation America, 2003


******************************************************************************/


// Class 0 Commands - Hardware commands, executed regardless of WTS701 state
#define TTS_PWUP        0x02    // wake WTS701 to IDLE state
#define TTS_RDST        0x04    // read status word of WTS701
#define TTS_RINT        0x06    // read status word and clear status interrupt
                                // bits
#define TTS_ENTER_RRSM  0x0C    // swap memory between xdata and code store
#define TTS_RST         0x10    // reset the WTS701 -> enters POWER DOWN state
#define TTS_RVER        0x12    // read software and hardware versions of WTS701
#define TTS_SCLS        0x14    // set the clock (CLC) config register to 0xNN
#define CFG_CLK_24M     0x00

// Class 1 Commands - Command byte followed by data byte only
#define TTS_PWDN        0x40    // put WTS701 in POWER DOWN state
#define TTS_EXIT_RRSM   0x41    // does this command exist?
#define TTS_PAUS        0x49    // pause the TTS conversion process
#define TTS_RES         0x4A    // resume the TTS conversion process if paused
#define TTS_STOP        0x4B    // stop TTS conversion without finishing buffer
#define TTS_FIN         0x4C    // finish TTS conversion at end of current buffer
#define TTS_FINW        0x4D    // finish TTS conversion at end of current word
#define TTS_SCOM        0x4E    // set the interrupt communication (COM) config
                                // register to 0xNN
#define TTS_SCOD        0x4F    // set the CODEC control (COD) config register
                                // to 0xNN
#define TTS_SAUD        0x50    // set the analog audio (AUD) config register
                                // to 0xNN
#define TTS_SVOL        0x51    // set the volume (VOL) config register to 0xNN
#define TTS_SSPD        0x52    // set the speech rate/speed (SPD) config
                                // register to 0xNN
#define TTS_VLUP        0x53    // increment the volume (VOL) register
#define TTS_VLDN        0x54    // decrement the volume (VOL) register
#define TTS_SPUP        0x55    // increase speaking rate (SPD) register
#define TTS_SPDN        0x56    // decrease speaking rate (SPD) register
#define TTS_IDLE        0x57    // put WTS701 in IDLE state
#define TTS_SPTC        0x77    // set the speech pitch parameter to 0xNN

// Class 2 Commands - Command byte, data byte plus additional data
#define TTS_CONV        0x81    // start or continue TTS conversion process
#define TTS_ABBR_DEL    0x83    // delete abbreviation from abbreviation table
#define TTS_ABBR_ADD    0xAF    // add abbreviation to abbreviation table

// Class 3 Commands - These return data
#define TTS_RREG        0xC0    // read configuration register 0xNN
#define TTS_ABBR_MEM    0xC7    // get number of bytes available in
                                // abbreviation table
#define TTS_ABBR_NUM    0xC8    // get number of abbreviations entered in
                                // abbreviation table
#define TTS_ABBR_RD     0xC9    // get entry N from the abbreviation table


#endif  // #ifndef TTS_CMD_H
