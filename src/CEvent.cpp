//
// Created by Mykhailo on 08/06/2020.
//

#include "CEvent.hpp"

bool CEvent::Repeat ()
{
	return true;
}

void CEvent::SetRepeat(int type, CDate date)
{
	CDate wdate = *e_dates.begin();
	switch (type)
	{
		case 1:
			e_repeat = RepeatType::Day;
			for (ETimeWrapper::AddDays(wdate, e_time, 1); wdate <= date; ETimeWrapper::AddDays(wdate, e_time, 1))
				e_dates.insert(e_dates.end(), wdate);
			break;
		case 2:
			e_repeat = RepeatType::Week;
			for (ETimeWrapper::AddDays(wdate, e_time, 7); wdate <= date; ETimeWrapper::AddDays(wdate, e_time, 7))
				e_dates.insert(e_dates.end(), wdate);
			break;
		case 3:
			e_repeat = RepeatType::TwoWeeks;
			for (ETimeWrapper::AddDays(wdate, e_time, 14); wdate <= date; ETimeWrapper::AddDays(wdate, e_time, 14))
				e_dates.insert(e_dates.end(), wdate);
			break;
		case 4:
			e_repeat = RepeatType::Month;
			for (wdate.d_month++; wdate <= date;)
			{
				CDate tmp_date = wdate;
				while (!tmp_date.IsValid())
					tmp_date.d_day--;
				e_dates.insert(e_dates.end(), tmp_date);
				if (++wdate.d_month > 12) { wdate.d_year++; wdate.d_month = 1; }
			}
			break;
		case 5:
			e_repeat = RepeatType::Year;
			for (wdate.d_year++; wdate <= date; wdate.d_year++)
			{
				CDate tmp_date = wdate;
				while (!tmp_date.IsValid())
					tmp_date.d_day--;
				e_dates.insert(e_dates.end(), tmp_date);
			}
			break;
		default:
			break;
	}
}