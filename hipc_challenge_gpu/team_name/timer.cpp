/* High Resolution Timer
 * =====================
 *
 * Based on timer by Song Ho Ahn (song.ahn@gmail.com)
 * Copyright (c) 2003 Song Ho Ahn
 */

#include "timer.h"
#include <stdlib.h>

using namespace util;

Timer::Timer()
{
#ifdef WIN32
    QueryPerformanceFrequency(&m_frequency);
    m_startCount.QuadPart = 0;
    m_endCount.QuadPart   = 0;
#else
    m_startCount.tv_sec = m_startCount.tv_usec = 0;
    m_endCount.tv_sec   = m_endCount.tv_usec   = 0;
#endif
    m_stopped = true;
    m_startTimeInMicroSec = 0;
    m_endTimeInMicroSec   = 0;
}

Timer::~Timer()
{
}

void Timer::start()
{
    m_stopped = false;
#ifdef WIN32
    QueryPerformanceCounter(&m_startCount);
#else
    gettimeofday(&m_startCount, NULL);
#endif
}

void Timer::stop()
{
#ifdef WIN32
    QueryPerformanceCounter(&m_endCount);
#else
    gettimeofday(&m_endCount, NULL);
#endif
    m_stopped = true;
}

double Timer::getElapsedTimeInMicroSec()
{
#ifdef WIN32
    if(! m_stopped)
        QueryPerformanceCounter(&m_endCount);

    m_startTimeInMicroSec = m_startCount.QuadPart * (1000000.0 / m_frequency.QuadPart);
    m_endTimeInMicroSec   = m_endCount.QuadPart * (1000000.0 / m_frequency.QuadPart);
#else
    if(! m_stopped)
        gettimeofday(&m_endCount, NULL);

    m_startTimeInMicroSec = (m_startCount.tv_sec * 1000000.0) + m_startCount.tv_usec;
    m_endTimeInMicroSec   = (m_endCount.tv_sec * 1000000.0) + m_endCount.tv_usec;
#endif

    return m_endTimeInMicroSec - m_startTimeInMicroSec;
}

double Timer::getElapsedTimeInMilliSec()
{
    return this->getElapsedTimeInMicroSec() * 0.001;
}

double Timer::getElapsedTimeInSec()
{
    return this->getElapsedTimeInMicroSec() * 0.000001;
}

double Timer::getElapsedTime()
{
    return this->getElapsedTimeInSec();
}

