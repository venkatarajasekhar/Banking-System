/*
This file is part of KooBeanz2.1 Banking System.

KooBeanz2.1 Banking System is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KooBeanz2.1 Banking System is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with KooBeanz2.1 Banking System.  If not, see <http://www.gnu.org/licenses/>.
*/
/**************************************************************************//**
 *	@file interactive-stream-handler.cpp
 *	@author Koo Beanz 2.1
 *	@version 1.337
 *
 *	@brief Used to format user input.
 *
 * This class will handle formating user input into a structure that
 * the system expects. It also maintains the directory structure and
 * file extensions for the system, so that they only need to be changed
 * in the constants at the top of the main, to affect the whole system.
 *
 *****************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "interactive-stream-handler.h"

using namespace std;

string InteractiveStreamHandler::FormatInput(string s){
	int input_length=s.size();

	// Make all user input lower case
	for(int x=0; x<input_length;x++)
		s[x]=tolower(s[x]);

	// Return formatted user input
	return (s);
}

string InteractiveStreamHandler::FormatName(string s){
	int name_length=s.size();

	/*This has been removed to aid in integration with KooBeanz2.0 System -Ben*/
	// Capitalize first letter of the first name
	//s[0]=toupper(s[0]);

	// Find the space between the first name and last name
	for(int x=1; x<name_length;x++){
		if(isspace(s[x])){
			// Convert space character to underscore
			s[x]='_';
			// Capitalize first letter of the last name
			s[x+1]=toupper(s[x+1]);
		}
	}

	// Return the formatted name
	return (s);
}
