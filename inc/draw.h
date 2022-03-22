#ifndef __CLOCK_PANEL_H__
#define __CLOCK_PANEL_H__

#include <stdio.h>
#include <stdlib.h>
#include "clock_panel.h"

#define FRAME 20

void cleanAllClockPanel( void );
void cleanClockPanel( char** panel );

void setPanel_Line_Row( char** panel, int xPos, int yPos, int len );
void setPanel_Line_Col( char** panel, int xPos, int yPos, int len );
void setPanel_Dot( char** panel, int xPos, int yPos );
void setNumber( int idx, int setNum );
void setFlickerSeperate( int idx, BOOL bOn );

void showClock( void );

void jumpTo( int xPos, int yPos );

#endif