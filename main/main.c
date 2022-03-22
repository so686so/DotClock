#include "clock.h"
#include "clock_panel.h"
#include "draw.h"
#include <unistd.h>

int main()
{
    if( createClockPanel() == FALSE ) {
        printf("createClockPanel() Faile.\n");
        return -1;
    }

    CLOCK curTime;

    cleanAllClockPanel();
    system("clear");

    while( 1 ) {
        // Get Time
        curTime = getCurTime();

        // HOUR
        setNumber( HOUR_TENS,   curTime.hour / 10 );
        setNumber( HOUR_UNITS,  curTime.hour % 10 );

        // :
        setFlickerSeperate( FIRST_SEP, curTime.sec % 2 );

        // MINUTE
        setNumber( MIN_TENS,    curTime.min / 10 );
        setNumber( MIN_UNITS,   curTime.min % 10 );
        
        // :
        setFlickerSeperate( SECOND_SEP, curTime.sec % 2 );
        
        // SECOND
        setNumber( SEC_TENS,    curTime.sec / 10 );
        setNumber( SEC_UNITS,   curTime.sec % 10 );

        // SHOW
        showClock();

        usleep(1000000/FRAME);
        jumpTo( 0, 0 );
    }

    destroyClockPanel();
    return 0;
}