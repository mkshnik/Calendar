//
// Created by Mykhailo Kuvshynov on 10.06.20.
//

#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <memory>

/** Class provides work with saving, exporting, importing and loading event and other calendar's data */
class CSaverLoader
{
private:
	/** Save file to (resp. from) which saving (resp. loading) of calendar's data will be provided */
	static std::fstream s_file;

	/**
	 * Reads event from a file
	 * @param file file to import/load events from
	 * @returns vector that stores string with import/load format of events
	 */
	static std::vector<std::vector<std::string>> 		    ReadEvents 		   (std::fstream & file);
public:
	CSaverLoader () = default;
	~CSaverLoader () = default;

	/** Opens save file for loading (reading) */
	static void 						                    OpenForReading     ();

	/** Opens save file for saving (writing) */
	static void 						                    OpenForWriting     ();

	/** Closes savefile */
	static void 						                    CloseLoader        ();

	/**
	 * Loads locations
	 * @returns locations as vector of strings
	 */
	static std::vector<std::string> 	                    LoadLocations      ();

	/**
	 * Loads participants
	 * @returns them as vector of pair of 2 strings (formatted as <name>:<info>)
	 */
	static std::vector<std::pair<std::string,std::string>> 	LoadParticipants   ();

	/**
	 * Exports string to given path
	 * @param path to save string to
	 * @param str__ to be saved
	 */
	static void 											ExportTo		   (const std::string & path,
																			    const std::string & str__);

	/** Saves given string to save file */
	static void 											SaveStr            (const std::string &);

	/** Loads events from save file */
	static std::vector<std::vector<std::string>>       		LoadEvents		   ();

	/** Imports events from the file
	 * @param path file to scan events from
	 * @return loaded events as vector of strings
	 */
	static std::vector<std::vector<std::string>>            ImportEvents       (const std::string & path);

};
