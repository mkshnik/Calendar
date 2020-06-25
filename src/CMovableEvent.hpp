//
// Created by Mykhailo Kuvshynov (kuvshmyk@fit.cvut.cz) on 05.05.20.
//

#pragma once
#include "CSharedEvent.hpp"

/** Class represents an event that could be moved to another time/date or location (sub class of CEvent) */
class CMovableEvent : public CSharedEvent
{
public:
    CMovableEvent(std::string name, const CDate & date, const CTime & time)
    : CSharedEvent(std::move(name), date, time, false, true)
    {}

    std::shared_ptr<CEvent>           Clone           () const override { return std::make_shared<CMovableEvent>(*this); }
    std::string                       SaveEvent       () const override { return "1;" + SaveShared(); }
    std::string 				      ExportEvent     () const override { return "1;" + SaveEvent(); }
    std::string 					  PrintType       () const override { return "  Movable  "; }
    bool                              Edit            ()       override;
};
