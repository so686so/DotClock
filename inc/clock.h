#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <stdio.h>
#include <time.h>

typedef struct _tCLOCK
{
    int hour;
    int min;
    int sec;
} CLOCK;

CLOCK getCurTime( void );

#endif