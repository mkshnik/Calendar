//
// Created by Mykhailo on 08/06/2020.
//

#include "ETimeWrapper.hpp"

auto NowTime = std::chrono::system_clock::to_time_t(
	std::chrono::system_clock::now());

ETimeWrapper::TimeType ETimeWrapper::Check_Time (CTime time, CDate date)
{
	if (NowTime < DateTo_Time_t(date, time))
		return Future;
	return Past;
}

CDate ETimeWrapper::TomorrowDate ()
{
	auto NowDate = std::chrono::system_clock::to_time_t(
					 std::chrono::system_clock::now());
	std::tm * ptm = std::localtime(&NowDate);
	return CDate(ptm->tm_mday + 1, ptm->tm_mon + 1, ptm->tm_year + 1900);
}

CDate ETimeWrapper::CurrentDate ()
{
	return Time_t_ToDate(std::chrono::system_clock::to_time_t(
			std::chrono::system_clock::now()));
}

CTime  ETimeWrapper::CurrentTime      ()
{
	auto NowDate = std::chrono::system_clock::to_time_t(
			std::chrono::system_clock::now());
	std::tm * ptm = std::localtime(&NowDate);
	return CTime(ptm->tm_hour, ptm->tm_min);
}

std::time_t ETimeWrapper::DateTo_Time_t    (const CDate & date, const CTime & time)
{
	std::tm full_date
		{
			0,
			time.t_minute,
			time.t_hour - 1,
			date.d_day,
			date.d_month - 1,
			date.d_year - 1900
		};
	 return mktime(&full_date);
}

CDate  ETimeWrapper::Time_t_ToDate    				(const std::time_t & time)
{
	std::tm * ptm = std::localtime(&time);
	return CDate(ptm->tm_mday, ptm->tm_mon + 1, ptm->tm_year + 1900);
}

void   ETimeWrapper::AddDays        (CDate & date, const CTime & time, int days)
{
	auto date_time_point = std::chrono::system_clock::from_time_t(DateTo_Time_t(date, time));
	date_time_point += std::chrono::hours{days * 24};
	date = Time_t_ToDate(std::chrono::system_clock::to_time_t(date_time_point));
}

CDate  ETimeWrapper::StrToDate	    (const std::string & sdate)
{
	int d, m, y;
	if (sscanf(sdate.c_str(), "%d.%d.%d", &d, &m, &y) != 3)
		throw std::logic_error("Wrong date format");
	return CDate(d, m, y);
}

int    ETimeWrapper::GetWeekday       ()
{
	time_t nw = std::chrono::system_clock::to_time_t(
				  std::chrono::system_clock::now());
	std::tm * ptm = std::localtime(&nw);
	return ptm->tm_wday;
}

