//
// Created by mkshnik on 10.06.20.
//

#include "CSaverLoader.hpp"

std::fstream                                        CSaverLoader::s_file             {};

void 					                            CSaverLoader::OpenForReading     ()
{
	s_file.open("examples/saves/savedata.txt", std::ios::in);
	if (!s_file.is_open())
		throw std::logic_error("Missing load file. Create one at ~/Calendar/examples/saves/savedata.txt");
}

void 				                                CSaverLoader::OpenForWriting     ()
{
	s_file.open("examples/saves/savedata.txt", std::ios::out);
	if (!s_file.is_open())
		throw std::logic_error("Missing save file. Create one at ~/Calendar/examples/saves/savedata.txt");
}

void 					                            CSaverLoader::CloseLoader   	 ()
{
	s_file.close();
}

std::vector<std::string>                            CSaverLoader::LoadLocations      ()
{
	char c = 0;
	std::vector<std::string> loaded;
	std::string location;
	for (int i = 0; ; i++)
	{
		s_file.read(&c, sizeof(char));
		if (c == ';')
		{
			loaded.push_back(location);
			location.clear();
			continue;
		}
		if (s_file.eof()) return loaded;
		if (c == '\n') break;
		location += c;
	}
	return loaded;
}

void 					                            CSaverLoader::SaveStr            (const std::string & str_)
{
	for (const auto & i : str_)
		s_file.write(&i, sizeof(char));
	s_file.write("\n", sizeof(char));
}

std::vector<std::pair<std::string,std::string>> 	CSaverLoader::LoadParticipants   ()
{
	char c = 0;
	std::vector<std::pair<std::string,std::string>> loaded;
	std::string name, info;
	bool add_name = true;
	for (int i = 0; ; i++)
	{
		s_file.read(&c, sizeof(char));
		if (c == ';')
		{
			loaded.emplace_back(name,info);
			name.clear();
			info.clear();
			add_name = true;
			continue;
		}
		if (s_file.eof()) return loaded;
		if (c == ':') { add_name = false; continue; }
		if (c == '\n' or c == '\0') break;
		if (add_name) name += c;
		else info += c;
	}
	return loaded;
}

std::vector<std::vector<std::string>>       		CSaverLoader::LoadEvents		 ()
{
	return ReadEvents(s_file);
}

std::vector<std::vector<std::string>>   		    CSaverLoader::ImportEvents       (const std::string & path)
{
	std::fstream from_file;
	from_file.open("examples/imports/" + path, std::ios::in);
	if (!from_file.is_open()) throw std::logic_error("File not found");
	std::vector<std::vector<std::string>> events = ReadEvents(from_file);
	from_file.close();
	return events;
}

std::vector<std::vector<std::string>> 				CSaverLoader::ReadEvents 		 (std::fstream & file)
{
	char c = 0;
	std::vector<std::vector<std::string>> loaded;
	std::vector<std::string> event;
	std::string part_;

		while (true)
		{
			if (file.eof()) return loaded;
			file.read(&c, sizeof(char));
			if (c == ';')
			{
				event.push_back(part_);
				part_.clear();
				continue;
			}
			if (c == '\n' and event.empty())
				return loaded;
			if (c == '\n' )
			{
				loaded.push_back(event);
				event.clear();
				c = 0;
				continue;
			}
			part_ += c;
		}
}

void 											    CSaverLoader::ExportTo		     (const std::string & path,
																				      const std::string & str_)
{
	std::ofstream to_file;
	to_file.open("examples/exports/" + path, std::ios::out);
	for (const auto & i : str_)
		to_file.write(&i, sizeof(char));
	to_file.write("\n", sizeof(char));
	to_file.close();
}
