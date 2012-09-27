/*
 * fileUtil.cpp
 * This file is part of libespm
 *
 * Copyright (C) 2012 - deaths_soul (MCP)
 *
 * libespm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libespm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libespm. If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include "fileUtil.h"
void util::createMast(parser::fileFormat::file &fileA){
	(unsigned int)fileA.flags |= 0x00000001;
}
void util::createONAM(parser::fileFormat::file &fileA, std::vector<parser::fileFormat::file> masters){
	std::string ids;
	bool test = false;
	for(unsigned int i = 0; i < fileA.groups.length(); ++i){
		for(unsigned int j = 0; j < fileA.groups[i].records.length(); ++j){
			if(common::options::contains("ONAM", fileA.groups[i].records[j].name)){
				for(unsigned int k = 0; k < masters.length(); ++k){
					for(unsigned int l = 0; l < masters[k].groups.length(); ++l){
						for(unsigned int m = 0; m < masters[k].groups[l].records.length(); ++m){
							if(fileA.groups[i].records[j].ID == masters[k].groups[l].records[m].ID){
								ids += fileA.groups[i].records[j].ID;
								test = true;
								break;
							}
						}
						if(test)
							break;
					}
					test = false;
				}
			}
		}
	}
	ids += "00";
	vector<parser::fileFormat::record>::iterator it = fileA.records.begin();
	while(*it.name != "INTV" || *it.name != "INCC" || it != fileA.records.end())
		++it;
	parser::fileFormat::record ONAM;
	ONAM.name = "ONAM";
	ONAM.size = ids.length() + 1;
	ONAM.data = ids.c_str();
	fileA.records.insert(it, ONAM);
}
void util::revCreateMast(parser::fileFormat::file &fileA){
	(unsigned int)fileA.flags ^= 0x00000001;
}
void util::revCreateONAM(parser::fileFormat::file &fileA){
	vector<parser::fileFormat::record>::iterator it = fileA.records.begin();
	while(*it.name != "ONAM" || it != fileA.records.end())
		++it;
	fileA.records.erase(it);
}
/*END OF LINE*/
