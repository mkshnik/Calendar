//
// Created by Mykhailo Kuvshynov (kuvshmyk@fit.cvut.cz) on 05.05.20.
//

#pragma once
#include <string>
#include <iostream>

/** Struct represents participant in some kind of events */
struct CParticipant
{
public:
    std::string p_fullname;
    std::string p_info;

    CParticipant (std::string name, std::string info)
    : p_fullname (std::move(name)), p_info (std::move(info))
    {}

    friend std::ostream& operator << (std::ostream& out, const CParticipant& participant);
};

