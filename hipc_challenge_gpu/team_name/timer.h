/* High Resolution Timer
 * =====================
 *
 * Based on timer by Song Ho Ahn (song.ahn@gmail.com)
 * Copyright (c) 2003 Song Ho Ahn
 */

#ifndef TIMER_H
#define TIMER_H

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace util
{
    class Timer
    {
    public:
        Timer();
        ~Timer();

        void   start();
        void   stop();
        double getElapsedTime();
        double getElapsedTimeInSec();
        double getElapsedTimeInMilliSec();
        double getElapsedTimeInMicroSec();

    private:
        double m_startTimeInMicroSec;
        double m_endTimeInMicroSec;
        bool   m_stopped;
#ifdef WIN32
        LARGE_INTEGER m_frequency;
        LARGE_INTEGER m_startCount;
        LARGE_INTEGER m_endCount;
#else
        timeval m_startCount;
        timeval m_endCount;
#endif
    };

}
#endif // TIMER_H

