//
// Created by Mykhailo Kuvshynov on 03.05.20.
//

#pragma once
#include <iostream>

/** Class represents time */
class CTime
{
public:
    int t_hour;
    int t_minute;

    CTime (int hh, int min)
    : t_hour (hh), t_minute (min)
    {}

    CTime (const CTime & time)
    : t_hour(time.t_hour), t_minute(time.t_minute)
    {}

    /** @returns true if time is valid */
    bool IsValid () const
    {
        return  !(t_hour   > 23 || t_hour   < 0
               || t_minute < 0  || t_minute > 59);
    }

    /** @returns string in format hh:mm */
    std::string ExportTime () const;

    bool operator < (const CTime & other_time) const
    {
        if (t_hour != other_time.t_hour)
            return t_hour < other_time.t_hour;
        return t_minute < other_time.t_minute;
    }

    friend std::ostream& operator << (std::ostream& out, const CTime & time)
    {
        if (time.t_hour < 10) out << 0;
        out << time.t_hour << ':';
        if (time.t_minute < 10) out << 0;
        out << time.t_minute;
        return out;
    }

    bool operator == (const CTime & time)
    {
        return t_minute == time.t_minute
        and    t_hour   == time.t_hour;
    }

    bool operator <= (const CTime & time)
    {
        return (*this < time) or (*this == time);
    }

    CTime operator + (int min)
    {
        t_minute += min;
        while (t_minute >= 60)
        { t_hour += t_minute/60; t_minute %= 60; }
        return *this;
    }

    CTime operator += (int min)
    { return *this + min; }
};
