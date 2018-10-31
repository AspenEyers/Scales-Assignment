
extern int raw_weight;
extern int filtered_weight;
extern int samples[20];
extern int pos;
extern long sum;
extern int unit_mode;



void filter_raw_weight(void){
    

    
    // to calculate the average
    int len = sizeof(samples) / sizeof(int);
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