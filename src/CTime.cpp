//
// Created by Mykhailo Kuvshynov on 18.06.20.
//

#include "CTime.hpp"

std::string CTime::ExportTime () const
{
	std::string export__;
	if (t_hour < 10) export__ += '0';
	export__ += std::to_string(t_hour) + ':';
	if (t_minute < 10) export__ += '0';
	export__ += std::to_string(t_minute);
	return export__;
}