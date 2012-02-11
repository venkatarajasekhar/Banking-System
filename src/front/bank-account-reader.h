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
 * @file bank-account-reader.h
 * @author Koo Beanz 2.1
 * @version 1.337
 *
 * @brief This class will handle managing the bank account file
 *
 * This class is used to handle reading in the current bank accounts file.
 * It also has the ability to check if a user exists in the system, or
 * if a user with a specific account number exists in the system. Once a
 * file has been read, get methods can be used to access its variables.
 *
 * Input files: current bank account file
 * Output files: N/A
 *****************************************************************************/
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/**
 * @class BankAccountReader
 * @brief Used to handle reading the current bank accounts file
 *
 * This class is used to handle reading in the current bank accounts file.
 * It also has the ability to check if a user exists in the system, or
 * if a user with a specific account number exists in the system. Once a
 * file has been read, get methods can be used to access its variables.
 *
 * Input files: current bank account file
 * Output files: N/A
 */
class BankAccountReader{
	private:
		/**
		 * @var directory_structure
		 *
		 * @brief Used to store the directory structure to the bank accounts file
		 *
		 * Used to store the directory structure to the bank accounts file. This
		 * Is important for all methods. If you wish to change the directory structure
		 * change the constant at the top of the main.
		 */
		string directory_structure;

		/**
		 * @var file_name
		 *
		 * @brief Used to store the file name of the bank accounts file
		 *
		 * Used to store the file name of the bank accounts file. This
		 * Is important for all methods. If you wish to change the file name
		 * change the constant at the top of the main.
		 */
		string file_name;

		/**
		 * @var account_number
		 *
		 * @brief Used to store the account number from the file
		 *
		 * Used to store the account number from the file
		 */
		string account_number;

		/**
		 * @var user_name
		 *
		 * @brief Used to store the account holders name from the file
		 *
		 * Used to store the account holders name from the file
		 */
		string user_name;

		/**
		 * @var status
		 *
		 * @brief Used to store the account holders status from the file
		 *
		 * Used to store the account holders status from the file
		 */
		char status;

		/**
		 * @var money
		 *
		 * @brief Used to store the account holders money from the file
		 *
		 * Used to store the account holders money from the file
		 */
		float money;

		int next_account;
	public:
		/**
		 * @brief Constructor for BankAccountReader
		 *
		 * Used to construct a BankAccountReader. Requires the directory to
		 * list where the current bank accounts folder, as well as the name
		 * of this file. These can be changed in the constants at the top
		 * of main.cpp
		 *
		 * @param directory
		 *
		 * The directory you wish to read from.
		 *
		 * @param name
		 *
		 * The name of the current bank accounts file with extension.
		 */
		BankAccountReader(string directory, string name){
			next_account=1;
			file_name=name;
			directory_structure=directory;
			ifstream reader;
			string file=directory_structure+file_name;
			reader.open(file.c_str());
			string file_data="";
			string examine_info="";
			while(getline(reader,file_data)){
				examine_info=file_data.substr(0,5);
				int accNum;
				stringstream string_to_int(examine_info);
				string_to_int >> accNum;
				if (accNum>=next_account)
					next_account=accNum+1;
			}
		}
		~BankAccountReader(){}

		/**
		 * @brief Reads the account given by a name and account #
		 *
		 * Reads current bank accounts file, and searches for the name and account number
		 * given as parameters. Once found it will save these values, so that get methods
		 * can be used.
		 *
		 * @param name
		 *
		 * The name of the account you are searching for.
		 *
		 * @param account
		 *
		 * The account number of the account you are searching for
		 */
		void ReadFile(string name, string account);

		/**
		 * @brief Checks to see if a user is valid in the system
		 *
		 * This will open the current bank accounts file, and search through
		 * to see if the account holder specified exists in the system.
		 *
		 * @param name
		 *
		 * The name of the account holder.
		 *
		 * @return
		 *
		 * Returns true if they exist, and false if they do not.
		 */
		bool IsValid(string name);

		/**
		 * @brief Checks to see if a user is valid in the system
		 *
		 * This will open the current bank accounts file, and search through
		 * to see if the account holder specified exists in the system,
		 * based on both name and account number.
		 *
		 * @param name
		 *
		 * The name of the account holder.
		 *
		 * @param account
		 *
		 * The account number of the account
		 *
		 * @return
		 *
		 * Returns true if they exist, and false if they do not.
		 */
		bool IsValid(string name, string account);

		/**
		 * @brief Returns the status of the account
		 *
		 * Returns the status of the account from the file. This will be overwritten
		 * if you read a different account.
		 *
		 * @return
		 *
		 * Returns a char indicating the status of the account
		 */
		char get_status(){return status;}
		/**
		 * @brief Returns the money in the account
		 *
		 * Returns the money in the account from the file. This will be overwritten
		 * if you read a different account.
		 *
		 * @return
		 *
		 * Returns a float indicating the money in the account
		 */
		float get_money(){return money;}

		/**
		 * @brief Returns the name of the account holder
		 *
		 * Returns the name of the account holder from the file. This will be overwritten
		 * if you read a different account.
		 *
		 * @return
		 *
		 * Returns a string indicating the name of the account holder
		 */
		string get_name(){return user_name;}

		/**
		 * @brief Returns the account number
		 *
		 * Returns the account number from the file. This will be overwritten
		 * if you read a different account.
		 *
		 * @return
		 *
		 * Returns a string indicating the account number
		 */
		string get_acc_number(){return account_number;}

		/**
		 * @brief Returns a new account number, 1 greater than largest account number in the system
		 *
		 * Returns a new account number, 1 greater than the largest account number currently in the system. 
		 * This is to ensure that the account numbers for the system are all valid, and contiguous.
		 *
		 * @return
		 *
		 * Returns an int representing the a new account number, 1 greater than the current largest.
		 */
		string NewAccNumber();

		string assign_plan(string);
};
