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
 *	@file BackEnd.h
 *	@author Koo Beanz 2.1
 *	@version 3.1337
 *
 *	@brief This is the only class of the program.
 *	
 *	This is the BackEnd class which is used to instantiate the back end
 *	of the system. It will read in the transaction file, and perform all
 *	necessary actions. The input for this program is the current bank 
 *	accounts file, the master bank accounts file, and the transaction files.
 * 	The output of this program is the updated master bank account and 
 * 	current bank accounts files. The old transaction files will be removed.
 *
 *	INPUT: master_bank_account.mba, current_bank_account.cba,
 *		merged_transactions.tra
 *
 *	OUTPUT: master_bank_account.mba, current_bank_account.cba
 *****************************************************************************/

#ifndef BACKEND_H_
#define BACKEND_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

/**
 * @brief A structure used to represent a transaction and store relevant information
 *
 */
typedef struct TransactionNode{
	string code; /** code representing transaction type */
	string name; /** name of account holder **/
	string account_number; /** account number involved in the transaction */
	string balance; /** balance of the account in dollars */
	string misc; /** string to store miscellaneous transaction information */
}tNode;

/**
 * @brief A structure used to represent an entry in the master bank account file
 *
 */
typedef struct MasterAccountNode{
	string account_number; /** account number involved in the transaction */
	string account_name; /** name of account holder */
	string status; /** status; ie. active or disabled */
	string balance; /** balance of the account in dollars */
	string misc; /** string to store miscellaneous account in information */
	string transaction_counter; /** counts transactions with codes 01-04 */
}maNode;

/**
 * @class BackEnd
 * @brief The back end of the banking system updates the end-of-day totals
 * 
 * This class represent the back-end of the banking system. At the end of each
 * day, the back-end system reads in all of the transaction files from the
 * previous day and updates the totals for each account accordingly. It also 
 * applies a banking fee to the appropriate accounts for each withdrawal, 
 * deposit, transfer, and paybill transaction performed.
 *
 * Banking fees depend on account plan, either student or non-student.
 * 
 * INPUT FILES: system/transaction/merged_transactions.tra system/account/master_bank_account.mba
 *
 * OUTPUT FILES: system/account/master_bank_account.mba system/account/current_bank_account.cba
 */
class BackEnd {
private:

public:
	/**
	 * Constructor for the BackEnd class.
	 * @return A new instantiation of BackEnd.
	 * 
	 * @param tra_dir_name
	 *
	 * Directory to the transaction files including the name
	 *
	 * @param acc_dir
	 *
	 * Directory to the account files
	 *
	 * @param mas_acc_nam
	 *
	 * Name for the master account file
	 *
	 * @param cur_acc_nam
	 *
	 * Name for current account name
	 */
	BackEnd(string tra_dir_name,string acc_dir,string mas_acc_nam,string cur_acc_nam){
		transaction_directory_and_name=tra_dir_name;
		current_account_name=cur_acc_nam;
		master_account_name=mas_acc_nam;
		account_directory=acc_dir;
	}
	/**
	 * Destructor for the BackEnd class.
	 */
	virtual ~BackEnd(){}
	string transaction_directory_and_name; /** path of transaction file */
	string account_directory; /** name of account directory */
	string master_account_name; /** name of master account file */
	string current_account_name; /** name of current account file */
	vector<TransactionNode> transactions; /** vector to hold transaction entries */
	vector<MasterAccountNode> masterAcc; /** vector to hold master account entries */
	
	/**
	 * This procedure is used to update the balance of an account.
	 * @param[in] x the index of the transaction in the transaction vector
	 * @param[in] withdraw true for withdrawals; false for deposits
	 */
	void change_balance(int x,bool withdraw);
	
	/**
	 * This procedure is used to update the transaction counter.
	 * @param[in] string current value of the counter
	 * @return the new value of the counter
	 */
	string updateCounter(string);

	/**
	 * A procedure for reading files.
	 */
	void readFiles();
	/**
	 * A procedure for writing to files.
	 */
	void writeFiles();
	/**
	 * A procedure for converting strings to floating point numbers
	 * @param[in[ string the string to be converted
	 */
	float stringToFloat(string);
	/**
	 * A procedure for converting strings to integer numbers
	 * @param[in] string the string to be converted
	 */
	int stringToInt(string);
	/**
	 * A procedure for parsing floating point numbers as strings
	 * @param[in] float the floating point number to be parsed
	 */
	string floatToString(float);
	/**
	 * A procedure for parsing integer numbers as strings
	 * @param[in] float the integer to be parsed
	 */
	string intToString(int);
};

#endif /* BACKEND_H_ */
