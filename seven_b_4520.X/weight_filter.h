/* 
 * File:   weight_filter.h
 * Author: Aspen
 *
 * Created on 30 October 2018, 9:27 PM
 */

#ifndef WEIGHT_FILTER_H
#define	WEIGHT_FILTER_H

#ifdef	__cplusplus
extern "C" {
#endif


    void filter_raw_weight(void);
    int movingAvg(int *ptrArrNumbers, long *ptrSum, int pos, int len, int nextNum);

#ifdef	__cplusplus
}
#endif

#endif	/* WEIGHT_FILTER_H */

