#ifndef MODE_CONTROLLER_H
#define	MODE_CONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif


void IO_setup(void);
void reset(void);
void TTS_cmd_word(char cmd);
void TTS_cmd_byte(char cmd);
void send_string(char*);
void TTS_cmd_special(char cmd);

void tts_run(char* st);
void tts_init(void);
void delay(void);



#ifdef	__cplusplus
}
#endif

#endif
