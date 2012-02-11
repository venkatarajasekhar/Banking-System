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
 *	@file BackEnd.cpp
 *  @author Koo Beanz 2.1
 * 	@version 3.1337
 *
 *  @brief This file contains the source for the BackEnd class.
 *****************************************************************************/
 
#include "BackEnd.h"

float BackEnd::stringToFloat(string target){
	float output; // float value to be returned
	stringstream string_to_float(target); // store string in stringstream
	string_to_float>>output; // pipe stringstream to output
	return output; // return output value
}

string BackEnd::floatToString(float target){
	string output; // string value to be returned
	stringstream float_to_string; // instantiate stringstream
	float_to_string<<target; // pipe target to stringstream
	output=float_to_string.str(); // assign output to string representation
	return output; // return output value
}

int BackEnd::stringToInt(string target){
	int output; // int value to be returned
	stringstream string_to_int(target); // store string in stringstream
	string_to_int>>output; // pipe stringstream to return value
	return output; // return output value
}

string BackEnd::intToString(int target){
	string output; // string to be returned
	stringstream int_to_string; // instantiate stringstream
	int_to_string<<target; // pipe integer to stringstream
	output=int_to_string.str(); // assign output to string representation
	return output; // return output value
}

string BackEnd::updateCounter(string count){
	//cout << count << endl;
	int counter = stringToInt(count); // convert counter to integer
	counter++; // increase counter
	//cout << counter << "INT" << endl;
	string finalCounter =intToString(counter); // convert back to string
	// prepend final counter with zeroes
	while(finalCounter.size() < 4)
		finalCounter = '0' + finalCounter;
	//cout << finalCounter << "FINAL" << endl;
	return finalCounter;
}

void BackEnd::readFiles(){
	ifstream reader;
	//string file=directory_structure+file_name;

	/*
	 * Read transaction files start
	 */
	reader.open(transaction_directory_and_name.c_str());

	string tra_data = "";
	
	// read each line and parse the transaction information
	while(getline(reader,tra_data)){
		TransactionNode n;
		n.code = tra_data.substr(0,2);
		//cout << n.code << endl;
		n.name = tra_data.substr(3,20);
		//cout << n.name << endl;
		n.account_number = tra_data.substr(24,5);
		//cout << n.account_number << endl;
		n.balance = tra_data.substr(30,8);
		//cout << n.balance << endl;
		n.misc = tra_data.substr(39,2);
		//cout << n.misc << endl;

		transactions.push_back(n);
	}
	// close the reader
	reader.close();

	/*
	 * Read Master bank accounts file start
	 */
	string filename=account_directory+master_account_name;
	reader.open(filename.c_str());
	string mba_data = "";
	
	// read each line and parse the account information
	while(getline(reader,mba_data)){
		MasterAccountNode n;
		n.account_number = mba_data.substr(0,5);
		//cout << n.account_number << endl;
		n.account_name = mba_data.substr(6,20);
		//cout << n.account_name << endl;
		n.status = mba_data.substr(27,1);
		//cout << n.status << endl;
		n.balance = mba_data.substr(29,8);
		//cout << n.balance << endl;
		n.transaction_counter = mba_data.substr(38,4);
		//cout << n.misc << endl;
		n.misc = mba_data.substr(43,2);
		//cout << n.transaction_counter << endl;

		masterAcc.push_back(n);
	}
	// close the reader
	reader.close();
}

void BackEnd::writeFiles(){
	string file_data="";
	
	// read each entry in the master account vector
	for(int x=0;x<masterAcc.size();x++){
		file_data+=masterAcc[x].account_number+" "+masterAcc[x].account_name+
				" "+masterAcc[x].status+" "+masterAcc[x].balance +" "+
				masterAcc[x].misc+"\n";
		//cout << file_data << endl;
	}
	// Write current bank account file
	ofstream write;
	// open the account file
	write.open((account_directory+current_account_name).c_str());
	// write the file data
	write<<file_data;
	// close the writer
	write.close();
	
	// reset the file data
	file_data="";
	
	for(int x=0;x<masterAcc.size();x++){
		//cout << masterAcc[x].transaction_counter << endl;
	}
	// read each entry in the master account vector
	for(int x=0;x<masterAcc.size();x++){
		file_data+=masterAcc[x].account_number+" "+masterAcc[x].account_name+
				" "+masterAcc[x].status+" "+masterAcc[x].balance +" "+
				   masterAcc[x].transaction_counter+" "+masterAcc[x].misc+"\n";
		//cout << masterAcc[x].transaction_counter << endl;
	}
	
	// Write master bank account file
	// open the master bank account file 
	write.open((account_directory+master_account_name).c_str());
	// write the file data
	write<<file_data;
	// close the writer
	write.close();
}

void BackEnd::change_balance(int x,bool withdraw){
	string output="";
	string balance;
	bool negative=false;
	// read each entry in the master bank account file
	for (int y=0;y<masterAcc.size();y++){
		// cout<<masterAcc[y].transaction_counter<<" "; for debugging
		if (transactions[x].account_number==masterAcc[y].account_number){
			// get monetary amount of transaction
			float money=stringToFloat(transactions[x].balance);
			// get balance of account
			float current_balance=stringToFloat(masterAcc[y].balance);
			if (withdraw)
				current_balance-=money; // if withdrawing, subtract money
			else
				current_balance+=money; // if depositing, add money

			// charge fee, depends on account plan
			if (transactions[x].misc!="TO")
				if (masterAcc[y].misc=="NP")
					current_balance-=0.1;
				else
					current_balance-=0.05;

			//Check to see if the number is negative from overdraft
			if (current_balance<0){
				negative=true;
				current_balance*=-1.0;
			}

			// get balance as string
			balance=floatToString(current_balance);
			
			// initialize counter
			int counter=0;
			
			// check if balance is formatted correctly
			if (balance[balance.size()-3]=='.')			//Already in Decimal format
				for(int x=0;x<8;x++){
					if (x<8-balance.size())
						output+="0";
					else{
						output+=balance[counter];
						counter++;
					}
				}
			else if(balance[balance.size()-2]=='.'){
				for(int x=0;x<7;x++){
					if (x<7-balance.size())
						output+="0";
					else{
						output+=balance[counter];
						counter++;
					}
				}
				output+="0";
			}
			else{									//Convert to decimal format
				for(int x=0;x<5;x++){
					if (x<5-balance.size())
						output+="0";
					else{
						output+=balance[counter];
						counter++;
					}
				}
				output+=".00";
			}

			/*to do check first character is 0, replace with -*/
			if(negative){}
			// update balance
			masterAcc[y].balance=output;
			// update transaction counter
			masterAcc[y].transaction_counter =
						updateCounter(masterAcc[y].transaction_counter);
			
			// exit loop
			break;
		}
	}
}
