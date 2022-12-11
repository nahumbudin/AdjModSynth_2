/**
* @file		JackConfigurationFile.h
*	@author		Nahum Budin
*	@date		13-Apr-2020
*	@version	1.0
*
*	@brief		Jack Audio configuration handling.
*/

#include <string>
#include <fstream>      // std::ifstream
#include <vector>
#include <unistd.h>

#include "JackConfigurationFile.h"

JackConfigurationFile::JackConfigurationFile(std::string path)
{
	filePath = path;
	fileIsRead = false;
}

int JackConfigurationFile::readConfigurationFile()
{
	std::ifstream configFile;
	char c;
	
	if (filePath == "")
	{
		fprintf(stderr, "Error - missing jack configuration file path");
		return -1;
	}
	else
	{
		configFile.open(filePath, std::ifstream::in);
		int err = errno;
		if (!configFile.is_open())
		{
			fprintf(stderr, "Can't open %s Jack config file for read!\n", filePath.c_str());
			return -2;
		}

		while (configFile.get(c)) fileData += c;
		configFile.close();	
		fileIsRead = true;
		
		return 0;
	}
}

int JackConfigurationFile::getConfigTextLines()
{
	std::string textLine;
	int index;
	char c=0;
	
	if (!fileIsRead || fileData.size() == 0)
	{
		fprintf(stderr, "Error - file not read yet or empty");
		return -1;
	}
	else
	{
		index = 0;
	
		while (index < fileData.size()) 
		{
			// Start collecting configuration file text lines
			c = fileData.c_str()[index++];
			while (c != 10) // <LF>
			{
				if (c != 13) 
				{ 
					// not a <CR>	
					textLine += c;
				}
				c = fileData.c_str()[index++];
			}
			// EOL
			if ((*(textLine.begin()) != _COMMENT_START) && (textLine.size() > 0))
			{
				// not a commented text line - add it
				configTextLines.push_back(textLine);
			}
			
			textLine.clear();
		}
		
		return 0;
	}
}

int JackConfigurationFile::getSectionTextLines(std::vector<std::string> *lines, std::string startHeader, std::string endHeader)
{
	bool sectionStart = false;
	
	if ((lines == NULL) || (startHeader == "") || (endHeader == ""))
	{
		return -1;
	}
	
	for (std::string line : configTextLines)
	{
		// go over al lines
		if (!sectionStart)
		{
			// look for requested section header line
			if (line.compare(startHeader) == 0)
			{
				// start segment header found
				sectionStart = true;
			}
		}
		else
		{
			// section line collection is in progress
			if (line.compare(endHeader) != 0)
			{
				// not end of section yet - add line
				lines->push_back(line);
			}
			else
			{
				// end of section - done.
				sectionStart = false;
				break;
			}
		}		
	}
		
	return 0;
}

int JackConfigurationFile::executeConfiguration(QProcess *processes)
{	
	
	int res;
	std::vector<std::string> configLines;
	int i;
	
	// Read the configuration file text
	res = readConfigurationFile();
	if (res != 0)
	{
		// error reading file
		return res;
	}
	
	// get the configuration file non commented text lines
	res = getConfigTextLines();
	if (res != 0)
	{
		return res;
	}	
	
	// Get the Processes section lines
	res = getSectionTextLines(&configLines, _PROCESSES_SECTION_SRART_HEADER, _PROCESSES_SECTION_END_HEADER);
	if (res != 0)
	{
		return res;
	}
	// Execute the processes comand lines
	for (i = 0; ((i < _MAX_NUM_OF_PROCESSES) && (i < configLines.size())); i++)
	{
		processes[i].start(configLines.at(i).c_str());
		// Let it role...
		usleep(500000);
	}	
	
	configLines.clear();
	// Look for the audio connections command lines
	res = getSectionTextLines(&configLines, _AUDIO_SECTION_SRART_HEADER, _AUDIO_SECTION_END_HEADER);
	if (res != 0)
	{
		return res;
	}
	// Execute the jack_connect commands
	for (i = 0; i < configLines.size(); i++)
	{
		system(("jack_connect " + configLines.at(i)).c_str());
	}
	
	configLines.clear();
	// Look for the ALSA MIDI connections command lines
	res = getSectionTextLines(&configLines, _ALSA_MIDI_SECTION_SRART_HEADER, _ALSA_MIDI_SECTION_END_HEADER);
	if (res != 0)
	{
		return res;
	}
	// Execute the aconnect ALSA MIDI connection command lines
	for (i = 0; i < configLines.size(); i++)
	{
		system(("aconnect " + configLines.at(i)).c_str());
	}	
	// Well done
	return 0;
}
