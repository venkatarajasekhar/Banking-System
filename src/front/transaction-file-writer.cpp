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
 * @file transaction-file-writer.cpp
 * @author Koo Beanz 2.1
 * @version 1.337
 *
 * @brief This is a class used to write transaction files
 *
 * This class is used to write all the transaction files for the system.
 * It should handle the naming of the files and placing them in the
 * specified directory, given on creation.
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "transaction-file-writer.h"

using namespace std;


/*
 * Constructor for the TransactionFileWriter class
 * Assigns the directory and extension
 * Initalizes the transaction number
 */
TransactionFileWriter::TransactionFileWriter(string directory,string extension){
	file_directory=directory;
	file_extension=extension;
	//transaction_number=1;
	trans_counter_file = file_directory+"trans_counter.txt";
}

/*
 * Destructor for TransactionFile Writer
 */
TransactionFileWriter::~TransactionFileWriter(){}

//OLD FUNCTIONALITY, NO LONGER NEEDED.
/*
 * FormatTime used to format a string of the time
 * into a format that can be used for file names.
 * EXAMPLES
 * Wed Feb 23 12:33:02 2011\n
 * becomes
 * Feb_23_12:33:02_2011
 */
/*
string TransactionFileWriter::FormatTime(string input){
	string output="";

	//Loop starts at 4 to remove day ie. wed
	for(int x=4;x<input.size()-1;x++){

		//if a space is found, replace with _
		if (isspace(input[x]))
			output+="_";
		else
			output+=input[x];
	}stringstream string_to_int(examine_info);
		string_to_int >> accNum;
		accNum++;
	return output;
}
*/

/*
 * WriteFile will deal with writing the file in the correct directory
 * with the correct name. It does this by working with each string to
 * ensure they are the correct size, and format. Once all the data is
 * formated correctly we create a file in the given directory, which
 * is named after the current system time followed by the transaction
 * number, and then the file extension. The file will contain a single
 * line showing the data.
 */
void TransactionFileWriter::WriteFile(string transaction_code,string name,string account_number,string money,string misc){
	string file_data;
	//Add the transaction code to the file data
	file_data+=transaction_code+" ";

	//Format the user name, so that it will be the correct size
	for(int x=0;x<20;x++){
		if (x<name.size())
			file_data+=name[x];
		else
			file_data+=" ";
	}

	//Add the account number to the file data
	file_data+= " " + account_number+" ";

	/*
	 * Add the money to the file data. It must pre-append 0s
	 * as well as ensuring that if the money is not in decimal
	 * format, it will add .00 to the end of it.
	 */
	int counter=0;
	if (money[money.size()-3]=='.')			//Already in Decimal format
		for(int x=0;x<8;x++){
			if (x<8-money.size())
				file_data+="0";
			else{
				file_data+=money[counter];
				counter++;
			}
		}
	else{									//Convert to decimal format
		for(int x=0;x<5;x++){
			if (x<5-money.size())
				file_data+="0";
			else{
				file_data+=money[counter];
				counter++;
			}
		}
		file_data+=".00";
	}
	file_data+=" ";

	//Add the plan to the file data
	file_data+=misc + "\n";

	/*
	 * The file data should now be finished and we must
	 * generate a file name. This is done by asking the
	 * system for the time, formating it. Then we pre-append
	 * the directory structure to ensure it will be created
	 * in the correct folder. Then we convert the transaction
	 * number to a string and append it. Finally the file
	 * extension is added.
	 *
	 * File name structure
	 * Directory + Time + transaction number+ file extension
	 */
	 
	/*
	//Calculate the time according to the system.
	time_t current_time;
	time(&current_time);
	string file_name=ctime(&current_time);
	*/
	//OLD METHOD OF NAMING TRANSACTION FILES
	//Add the file directory structure
	//file_name=file_directory+FormatTime(file_name);
	//Read the transaction counter file to get the number of the transaction.
	
	string file_name=file_directory+"transaction";
	
	//This block of code will read the trans file counter file and get the number for the transaction.
	string trans_counter;
	ifstream reader;
	reader.open(trans_counter_file.c_str());
	//cin.ignore();
	getline(reader,trans_counter);
	reader.close();
	//Transform the transaction number to a string and add it
	//stringstream int_to_string;
	//int_to_string<<transaction_number;
	//Add the file extension
	file_name+=trans_counter+file_extension;
	
	//)
	
	//Write the file data to the calculated file name
	ofstream write;
	write.open(file_name.c_str());
	write<<file_data;
	write.close();

	//Increment the transaction number and write it into the file
	//Transform the string with the number into an int
	int accNum;
	stringstream string_to_int(trans_counter);
        string_to_int >> accNum;
        //Increment the number
        accNum++;
        //Transform the number back to a string and write it in the file.
        ofstream writer;
        writer.open(trans_counter_file.c_str());
        stringstream int_to_str;
        int_to_str << accNum;
	int x=0;
	while((int_to_str.str().length()+x)<5){x++;writer <<"0";}
        writer << int_to_str.str();
        writer.close();

	//transaction_number++;
}
