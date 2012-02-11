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
 * @file bank-account-reader.cpp
 * @author Koo Beanz 2.1
 * @version 1.337
 *
 * @brief This class will handle managing the bank account file
 *
 * This class is used to handle reading in the current bank accounts file.
 * It also has the ability to check if a user exists in the system, or
 * if a user with a specific account number exists in the system. Once a
 * file has been read, get methods can be used to access its variables.
 *****************************************************************************/
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "bank-account-reader.h"
using namespace std;

void BankAccountReader::ReadFile(string name,string account){
	// String to hold the user's account number and name
	string account_info=account+" "+name;
	string examine_info="";

	// Open the bank account file
	ifstream reader;
	string file=directory_structure+file_name;
	reader.open(file.c_str());

	string file_data="";
	int length=account_info.size();

	// Read each line of the bank account file until the end
	while(getline(reader,file_data)){
		// Extract the name and account number from the line
		examine_info=file_data.substr(0,length);
		// Check if the line is the file is the line expected
		if (examine_info==account_info){
			// Get user's name and account number
			account_number=account;
			user_name=name;
			// Extract account status from file
			status=file_data[26];
			// Extract money amount from file
			stringstream string_to_float(file_data.substr(29,8));
			string_to_float>>money;
		}
	}
	// Close the file reader
	reader.close();
}

bool BankAccountReader::IsValid(string name){
	// Read the bank account file to make sure the user exists
	ifstream reader;
	string file=directory_structure+file_name;
	reader.open(file.c_str());

	// Store a line from file in file data
	string file_data="";
	string examine_name="";
	int length=name.size();
	//Add the required underscores to the name input to match the name field of the 
	//CBA file.
	for(int i = length; i < 20;i++){
		name += " ";
	}
	/* Known error: John_Smith will match John_Smithsonian */
	// Read each line of the bank account file until the end
	while(getline(reader,file_data)){
		// Examine the name portion of the line
		examine_name=file_data.substr(6,20);
		// Check if the name matches the expected name
		if (examine_name==name){
			// Close the file reader
			reader.close();
			// Name found, so it is valid.
			return true;
		}
	}
	// Close the file reader
	reader.close();
	// Name not found, name is not valid.
	return false;
}

bool BankAccountReader::IsValid(string name,string account){
	/* Read the bank account file to make sure the account exists and
		belongs to the specified user */
	string account_info=account+" "+name;
	string examine_info="";
	cout<<account_info<<endl;
	// Open the bank account file
	ifstream reader;
	string file=directory_structure+file_name;
	reader.open(file.c_str());

	string file_data="";
	int length=account_info.size();

	// Read each line of the bank account file until the end
	while(getline(reader,file_data)){
		// Extract the name and account number
		examine_info=file_data.substr(0,length);
		// Check if the line matches the expected line
		if (examine_info==account_info){
			// Close the file reader
			reader.close();
			// Account exists, return true
			return true;
		}
	}
	// Close the file reader
	reader.close();
	// Account not found, name and/or account number is not valid.
	return false;
}

string BankAccountReader::NewAccNumber(){
	stringstream int_to_str;
	int_to_str << next_account;
	string newAcc=int_to_str.str();
	next_account++;
	int numberSize = newAcc.size();
	while (numberSize < 5){
	        newAcc = '0'+newAcc;
	        numberSize++;
	}
	return newAcc;
}

string BankAccountReader::assign_plan(string name){
	ifstream reader;
	string file=directory_structure+file_name;
	reader.open(file.c_str());
	
	string file_data="";
	string examine_name="";
	string plan;
	int length=name.size();
	for(int i = length; i < 20;i++)
		name += " ";

	while(getline(reader,file_data)){
		examine_name=file_data.substr(6,20);
		if (examine_name==name){
			plan=file_data.substr(38,2);
			return plan;
		}
	}
	return "NP";
}
