//
// Created by Mykhailo Kuvshynov (kuvshmyk@fit.cvut.cz) on 05.05.20.
//

#pragma once
#include "CSharedEvent.hpp"

/** Class represents optional event with changeable time/date and information */
class COptionalEvent : public CSharedEvent
{
public:
    COptionalEvent(std::string name, const CDate & date, const CTime & time)
    : CSharedEvent(std::move(name), date, time, true, true)
    {}

    std::shared_ptr<CEvent>           Clone           () const override { return std::make_shared<COptionalEvent>(*this); }
    std::string    					  PrintType       () const override { return "  Optional "; }
    std::string                       SaveEvent       () const override { return "3;" + SaveShared(); }
    std::string 				      ExportEvent     () const override { return "3;" + ExportShared(); }
    bool                              Edit            () 	   override { Advanced(); std::cout << e_name + " was updated.\n"; return true; }
};
