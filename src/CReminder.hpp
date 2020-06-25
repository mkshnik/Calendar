//
// Created by mkshnik on 05.05.20.
//

#pragma once
#include "CEvent.hpp"

/**
 * Class represents reminder (custom and changeable name and location) (sub class of CEvent)'
 * Can be overlapped but cannot be moved
 * */
class CReminder : public CEvent
{
public:
    CReminder (std::string name, const CDate & date, const CTime & time)
    : CEvent (std::move(name), date, time, true, false)
    {}

	std::shared_ptr<CEvent>         Clone           	() const override { return std::make_shared<CReminder>(*this); }
	std::string 					SaveEvent       	() const override;
	std::string 				   	ExportEvent     	() const override { return SaveEvent(); }
	std::string                     PrintType       	() const override;
    void                            GetInfo         	() const override;
};
