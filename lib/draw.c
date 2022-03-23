#include "draw.h"
#include "clock_panel.h"

char arrMatch[PANEL_MAX][PANEL_HEIGHT][PANEL_WIDTH] = {0, };

void cleanAllClockPanel( void )
{
    PPANEL totalPanel = getTotalPanel();
    char** curPanel = NULL;

    if( totalPanel == NULL ) return;

    for( int i = 0; i < PANEL_MAX; i++ ) {
        curPanel = totalPanel[i].panel;

        for( int j = 0; j < totalPanel[i].height; j++ ) {
            memset( curPanel[j], 0x00, totalPanel[i].width );
        }
    }
}

void cleanClockPanel( char** panel )
{
    for( int i = 0; i < PANEL_HEIGHT; i++ ) {
        memset( panel[i], 0x00, PANEL_WIDTH );
    }
}

void setPanel_Line_Row( char** panel, int xPos, int yPos, int len )
{
    for( int i = xPos; i < (len+xPos); i++ ) {
        panel[yPos][i] = 0x01;
    }
}

void setPanel_Line_Col( char** panel, int xPos, int yPos, int len )
{
    for( int i = yPos; i < (len+yPos); i++ ) {
        panel[i][xPos] = 0x01;
    }
}

void setPanel_Dot( char** panel, int xPos, int yPos )
{
    panel[yPos][xPos] = 0x01;
}

void setFlickerSeperate( int idx, BOOL bOn )
{
    PPANEL totalPanel   = getTotalPanel();
    char** curPanel     = NULL;
    int    upperRow     = 2;
    int    underRow     = PANEL_HEIGHT - upperRow - 1;
    int    middleCol    = SEP_WIDTH / 2;

    if( totalPanel == NULL ) return;

    curPanel = totalPanel[idx].panel;

    curPanel[underRow][middleCol] = (bOn) ? 0x01 : 0x00;
    curPanel[upperRow][middleCol] = (bOn) ? 0x01 : 0x00;
}

void setNumber( int idx, int setNum )
{

    char** panel = getClockPanel(idx);

    if( checkChangeNum( idx, setNum ) == FALSE ) {
        return;
    }

    cleanClockPanel( panel );
    
    switch (setNum)
    {
    case 0:
        setPanel_Line_Row( panel, 3, 1, 3 );
        setPanel_Line_Col( panel, 2, 2, 5 );
        setPanel_Line_Row( panel, 3, 7, 3 );
        setPanel_Line_Col( panel, 6, 2, 5 );
        break;

    case 1:
        setPanel_Line_Row( panel, 3, 2, 2 );
        setPanel_Line_Col( panel, 4, 1, 7 );
        setPanel_Line_Row( panel, 3, 7, 3 );
        break;

    case 2:
        setPanel_Line_Row( panel, 2, 1, 5 );
        setPanel_Line_Col( panel, 6, 1, 3 );
        setPanel_Line_Row( panel, 2, 4, 5 );
        setPanel_Line_Col( panel, 2, 4, 3 );
        setPanel_Line_Row( panel, 2, 7, 5 );
        break;

    case 3:
        setPanel_Line_Row( panel, 2, 1, 5 );
        setPanel_Line_Col( panel, 6, 1, 6 );
        setPanel_Line_Row( panel, 2, 4, 5 );
        setPanel_Line_Row( panel, 2, 7, 5 );
        break;

    case 4:
        setPanel_Line_Col( panel, 2, 1, 3 );
        setPanel_Line_Row( panel, 2, 4, 5 );
        setPanel_Line_Col( panel, 5, 1, 7 );
        break;

    case 5:
        setPanel_Line_Row( panel, 2, 1, 5 );
        setPanel_Line_Col( panel, 6, 4, 3 );
        setPanel_Line_Row( panel, 2, 4, 5 );
        setPanel_Line_Col( panel, 2, 1, 3 );
        setPanel_Line_Row( panel, 2, 7, 5 );
        break;

    case 6:
        setPanel_Line_Row( panel, 2, 1, 5 );
        setPanel_Line_Col( panel, 6, 4, 3 );
        setPanel_Line_Row( panel, 2, 4, 5 );
        setPanel_Line_Col( panel, 2, 1, 7 );
        setPanel_Line_Row( panel, 2, 7, 5 );
        break;

    case 7:
        setPanel_Line_Row( panel, 2, 1, 5 );
        setPanel_Line_Col( panel, 6, 1, 7 );
        break;

    case 8:
        setPanel_Line_Row( panel, 2, 1, 5 );
        setPanel_Line_Col( panel, 6, 1, 7 );
        setPanel_Line_Row( panel, 2, 4, 5 );
        setPanel_Line_Col( panel, 2, 1, 7 );
        setPanel_Line_Row( panel, 2, 7, 5 );
        break;

    case 9:
        setPanel_Line_Row( panel, 2, 1, 5 );
        setPanel_Line_Col( panel, 2, 1, 4 );
        setPanel_Line_Row( panel, 2, 4, 5 );
        setPanel_Line_Col( panel, 6, 1, 7 );
        break;
    
    default:
        cleanClockPanel( panel );
        break;
    }

    setPanelNum( idx, setNum );

    setPanelMatchDone( idx, FALSE );
    memset( arrMatch[idx], 0x00, PANEL_WIDTH * PANEL_HEIGHT );
}

static int calcX( int idx )
{
    int res = 0;
    PPANEL totalPanel = getTotalPanel();

    for( int i = 0; i < idx; i++ ) {
        res += totalPanel[i].width;
    }

    return res;
}

static void showAnimationClock( int idx, int row )
{
    PPANEL totalPanel = getTotalPanel();
    char** curPanel   = totalPanel[idx].panel;
    int    curBit     = 0;

    jumpTo( calcX( idx ), row );

    for( int col = 0; col < PANEL_WIDTH; col++ ) {
        if( arrMatch[idx][row][col] ) {
            printf("%s ", (curPanel[row][col]) ? ON_DOT : OFF_DOT);
            continue;
        }

        curBit = rand()%2;
        printf("%s ", (curBit) ? DIM_DOT : OFF_DOT);

        if( curBit == curPanel[row][col] ) {
            arrMatch[idx][row][col] = 0x01;
        }
    }
}

void showClock( void )
{
    PPANEL totalPanel = getTotalPanel();

    if( totalPanel == NULL ) return;

    if( getAllPanelMatchDone() == TRUE ) return;

    for( int row = 0; row < PANEL_HEIGHT; row++ ) {
        for( int idx = 0; idx < PANEL_MAX; idx++ ){
            PANEL  curData  = totalPanel[idx];
            char** curPanel = curData.panel;

            for( int col = 0; col < curData.width; col++ ) {
                printf("%s ", (curPanel[row][col]) ? ON_DOT : OFF_DOT);
            }

            if( getPanelMatchDone( idx ) == TRUE ) 
                continue;

            if( idx == FIRST_SEP || idx == SECOND_SEP )
                continue;

            showAnimationClock( idx, row );
        }
        printf("\n");
    }
}

void jumpTo( int xPos, int yPos )
{
    printf("\033[%d;%df", yPos+1, 2*xPos+1);
}