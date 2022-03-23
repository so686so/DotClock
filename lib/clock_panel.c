#include "clock_panel.h"

PPANEL g_clock_panel = NULL;

BOOL createClockPanel( void )
{
    g_clock_panel = (PPANEL)malloc(sizeof(PANEL) * PANEL_MAX);

    if( g_clock_panel == NULL ) {
        printf("[%d] g_clock_panel malloc failed.\n", __LINE__);
        return FALSE;
    }

    int    i, j;
    PPANEL curPanel = g_clock_panel;

    for( i = 0; i < PANEL_MAX; i++ ) {
        if( i == FIRST_SEP || i == SECOND_SEP ) {
            curPanel->isSep     = TRUE;
            curPanel->curNum    = -1;
            curPanel->height    = PANEL_HEIGHT;
            curPanel->width     = SEP_WIDTH;
            curPanel->matchDone = TRUE;
        } else {
            curPanel->isSep     = FALSE;
            curPanel->curNum    = -1;
            curPanel->height    = PANEL_HEIGHT;
            curPanel->width     = PANEL_WIDTH;            
            curPanel->matchDone = FALSE;
        }
        curPanel++;
    }

    curPanel = g_clock_panel;

    for( i = 0; i < PANEL_MAX; i++ ) {
        curPanel->panel = (char**)malloc(sizeof(char*) * curPanel->height);

        if( curPanel->panel == NULL ) {
            printf("[%d] curPanel->panel malloc failed.\n", __LINE__);
            return FALSE;
        }

        for( j = 0; j < curPanel->height; j++ ) {
            (curPanel->panel)[j] = (char *)malloc(sizeof(char) * curPanel->width);

            if( (curPanel->panel)[j] == NULL ) {
                printf("[%d] curPanel->panel malloc failed.\n", __LINE__);
                return FALSE;
            }

            memset( (curPanel->panel)[j], 0x00, curPanel->width );
        }
        curPanel++;
    }

    return TRUE;
}

void destroyClockPanel( void )
{
    int i, j;
    PPANEL curPanel = g_clock_panel;
    char   *curLine = NULL;

    if( g_clock_panel != NULL ) {
        for( i = 0; i < PANEL_MAX; i++ ) {
            if( curPanel->panel != NULL ) {
                for( j = 0; j < curPanel->height; j++ ) {
                    curLine = (curPanel->panel)[j];

                    if( curLine != NULL ) {
                        free(curLine);
                        curLine = NULL;
                    }
                }

                free(curPanel->panel);
                curPanel->panel = NULL;
                curPanel++;
            }
        }

        free(g_clock_panel);
        g_clock_panel = NULL;
    }
}

PPANEL getTotalPanel( void )
{
    return g_clock_panel;
}

void setPanelNum( int idx, int num )
{
    g_clock_panel[idx].curNum = num;
}

char** getClockPanel( int idx )
{
    return g_clock_panel[idx].panel;
}

void setPanelMatchDone( int idx, BOOL bOn )
{
    g_clock_panel[idx].matchDone = bOn;
}

BOOL getAllPanelMatchDone( void )
{
    for( int idx = 0; idx < PANEL_MAX; idx++ ) {
        if( g_clock_panel[idx].matchDone == FALSE )
            return FALSE;
    }
    return TRUE;
}


BOOL checkChangeNum( int idx, int num )
{
    return g_clock_panel[idx].curNum != num;
}

BOOL getPanelMatchDone( int idx )
{
    return g_clock_panel[idx].matchDone;
}
