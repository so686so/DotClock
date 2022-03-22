#include "clock.h"
#include <string.h>

CLOCK getCurTime( void )
{
    CLOCK       clock;
    time_t      timer;
    struct tm   *t;

    memset( &clock, 0x00, sizeof(CLOCK) );

    timer   = time(NULL);           // 현재 시각을 초 단위로 얻기
    t       = localtime(&timer);    // 초 단위의 시간을 분리하여 구조체에 넣기

    clock.hour  = t->tm_hour;
    clock.min   = t->tm_min;
    clock.sec   = t->tm_sec;

    return clock;
}