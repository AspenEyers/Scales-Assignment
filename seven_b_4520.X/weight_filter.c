#include <p18cxxx.h>

extern int raw_weight;
extern int filtered_weight;
extern int sampleSize;
extern int samples[];
extern int pos;
extern long sum;
extern int unit_mode;



void filter_raw_weight(void){
    
    // to calculate the average
    int len = sampleSize;
    while(PIR1bits.ADIF == 0);
    raw_weight = ADRESH;
    raw_weight = (raw_weight << 2);
    raw_weight = raw_weight | ((ADRESL >> 6) && (0b00000011));
    
    ADCON0bits.GO = 1;
    

    //filtered_weight = filtered_weight - tare_val;
    
    filtered_weight = movingAvg(samples, &sum, pos, len, raw_weight);
    //printf("The new average is %d\n", newAvg);
    pos++;
    if (pos >= len){
        pos = 0;
    }
    
    
    
}




int movingAvg(int *ptrSamples, long *ptrSum, int pos, int len, int nextNum){
    *ptrSum = *ptrSum - ptrSamples[pos] + nextNum;
    ptrSamples[pos] = nextNum;
    return *ptrSum/len;

}