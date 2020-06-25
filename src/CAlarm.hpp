//
// Created by Mykhailo Kuvshynov (kuvshmyk@fit.cvut.cz) on 05.05.20.
//
#ifndef CALARM
#define CALARM
#include "CEvent.hpp"

/**
 * Class represents an alarm (sub class of CEvent)
 * Can't be moved to another time/date but can be overlapped
 * */
class CAlarm : public CEvent
{
public:
    explicit CAlarm (std::string name, const CDate & date, const CTime & time)
    : CEvent (std::move(name), date, time, true, false)
    {}

    ~CAlarm() override = default;

    std::string                           SaveEvent       () const override;
    std::string      				      ExportEvent     () const override { return SaveEvent(); }
    std::shared_ptr<CEvent>               Clone           () const override { return std::make_shared<CAlarm>(*this); }
    std::string                           PrintType       () const override { return "   Alarm   "; }
    void                                  GetInfo         () const override;
    bool                                  Advanced        ()       override;
    bool                                  Edit            ()       override { return Advanced(); }
    bool LoadAdvanced    (const std::vector<std::string> & info)   override;
    bool ImportAdvanced  (const std::vector<std::string> & info)   override { return LoadAdvanced(info); }
};

#endif