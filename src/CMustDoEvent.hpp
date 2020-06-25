//
// Created by Mykhailo Kuvshynov (kuvshmyk@fit.cvut.cz) on 05.05.20.
//

#pragma once
#include "CSharedEvent.hpp"

/** Class represents unmovable and unchangeable event (sub class of CEvent) */
class CMustDoEvent : public CSharedEvent
{
public:
    CMustDoEvent(std::string name, const CDate & date, const CTime & time)
    : CSharedEvent (std::move(name), date, time, false, false)
    {}

    std::shared_ptr<CEvent>           Clone           () const override { return std::make_shared<CMustDoEvent>(*this); }
    std::string 					  PrintType       () const override { return "   MustDo  "; }
    std::string                       SaveEvent       () const override { return "2;" + SaveShared(); }
    std::string 				      ExportEvent     () const override { return "2;" + ExportShared(); }
};

