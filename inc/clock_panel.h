#ifndef __CLK_PANEL__
#define __CLK_PANEL__

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "type.h"

typedef struct _tPANEL
{
    char** panel;
    int    width;
    int    height;
    int    curNum;
    BOOL   isSep;
    BOOL   matchDone;
} PANEL, *PPANEL;

#define HOUR_TENS       0
#define HOUR_UNITS      1
#define FIRST_SEP       2
#define MIN_TENS        3
#define MIN_UNITS       4
#define SECOND_SEP      5
#define SEC_TENS        6
#define SEC_UNITS       7
#define PANEL_MAX       8

#define SEP_WIDTH       3
#define PANEL_WIDTH     9
#define PANEL_HEIGHT    9

BOOL createClockPanel( void );
void destroyClockPanel( void );

PPANEL getTotalPanel( void );
char** getClockPanel( int idx );

void setPanelNum( int idx, int num );
void setPanelMatchDone( int idx, BOOL bOn );
BOOL getPanelMatchDone( int idx );
BOOL getAllPanelMatchDone( void );

BOOL checkChangeNum( int idx, int num );

#endif