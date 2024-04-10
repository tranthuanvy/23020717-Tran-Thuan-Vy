#ifndef TIMER_H
#define TIMER_H_
#include "CommonFunc.h"
class Timer
{
public:
    Timer();
    ~Timer();

    void start();
    void stop();
    void paused();
    void unpaused();

    int get_ticks();

    bool is_started();
    bool is_paused();


private:
    int start_tick_;// start run
    int paused_tick_;//paused stop

    bool is_paused_;
    bool is_started_;

};



#endif
