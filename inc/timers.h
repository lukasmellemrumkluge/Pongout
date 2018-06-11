
#ifndef _timers_H_
#define _timers_H_
typedef struct {
    int hours;
    int minutes;
    int seconds;
    int centiseconds;
} funTime_t;
uint8_t timerflag = 0;


volatile funTime_t t1;
volatile funTime_t t2;

void startTimer1(int f);
void stopTimer1(void);
void resetTimer1(void);
void setSplitTimeFromTimer1(funTime_t *split);
void startTimer2(int f);
void stopTimer2(void);
void resetTimer2(void);
void setSplitTimeFromTimer2(funTime_t *split);



#endif /* _timers_H_ */
