//
// Created by Mykhailo Kuvshynov (kuvshmyk@fit.cvut.cz) on 05.05.20.
//

#pragma once
#include <map>
#include <memory>
#include <set>
#include "CTime.hpp"

class CDate
{
public:
    int d_year;
    int d_month;
    int d_day;

    CDate ( int dd, int mm, int yyyy )
    : d_year (yyyy), d_month (mm), d_day (dd)
    {}

    CDate(const CDate & date) = default;

    bool IsValid () const
    {
        if (d_year  < 2000 or d_year  > 2300 or
            d_month < 1    or d_month > 12   or
            d_day   < 1    or d_day   > 31     ) return false;
        bool leap_year = false;
        if ((!(d_year % 4)   and d_year % 100)
        or   (d_year % 100 == 0 and d_year % 400 == 0)) leap_year = true;
        return  !((d_month == 1  && d_day > 31)
               || (d_month == 3  && d_day > 31)
               || (d_month == 4  && d_day > 30)
               || (d_month == 5  && d_day > 31)
               || (d_month == 6  && d_day > 30)
               || (d_month == 7  && d_day > 31)
               || (d_month == 8  && d_day > 31)
               || (d_month == 9  && d_day > 30)
               || (d_month == 10 && d_day > 31)
               || (d_month == 11 && d_day > 30)
               || (d_month == 12 && d_day > 31)
               || (d_month == 2  && d_day > 28 && !leap_year)
               || (d_month == 2  && d_day > 29 && leap_year));
    }

    std::string ExportDate () const
    {
        std::string export__;
        if (d_day < 10)  export__ += '0';
        export__ += std::to_string(d_day) + '.';
        if (d_month < 10) export__ += '0';
        export__ += std::to_string(d_month) +
              '.' + std::to_string(d_year);
        return export__;
    }

    bool operator < (const CDate & other_time) const
    {
        if (d_year != other_time.d_year) return d_year < other_time.d_year;
        if (d_month != other_time.d_month) return d_month < other_time.d_month;
        else return d_day < other_time.d_day;
    }
    bool operator <= (const CDate & other_time) const
    {
        return ((*this < other_time) || (*this == other_time));
    }

    bool operator == (const CDate & other_time) const
    {
        return d_year  == other_time.d_year  &&
               d_month == other_time.d_month &&
               d_day   == other_time.d_day;
    }

    friend std::ostream& operator << (std::ostream& out, const CDate & date)
    {
        if (date.d_day < 10) out << 0;
        out << date.d_day << '.';
        if (date.d_month < 10) out << 0;
        out << date.d_month << '.' << date.d_year;
        return out;
    }
};

