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
* 	@file main.cpp
* 	@author Koo Beanz 2.1
*	@version 3.1337
*
*	@brief This is the main driver file of the program
*
*	This is the driver file for the KooBeanz 2.1 Back end. The back end is
*	designed to read a merged transaction file, and the current and master
*	bank account files. It will then save the data as a vector of nodes.
*	The system will then loop through the transactions and perform all
*	the changes to these values. Once the changes have been made, updated
*	account files will be written to replace the old ones. The only class
*	in the system is backend, it has all the functions needed to perform 
*	the logic of reading the files to the vectors, changing the vectors
*	and writing them. The main is simply a procedural driver that calls
*	the appropriate functions.
*
*	INPUT: master_bank_account.mba, current_bank_account.cba,
*		merged_transactions.tra
*
*	OUTPUT: master_bank_account.mba, current_bank_account.cba
*****************************************************************************/

#include "BackEnd.h"

//Main method for the system
int main() {
	BackEnd backend("system/transaction/merged_transactions.tra"
			,"system/account/","master_bank_account.mba","current_bank_account.cba");

	//Read in the 2 input files
	backend.readFiles();

	//loop through the transactions
	for(int x=0;x<backend.transactions.size();x++){
		if(backend.transactions[x].code=="01"){//withdrawal
			backend.change_balance(x,true);
		}
		else if(backend.transactions[x].code=="02"){//transfer
			for (int y=0;y<backend.masterAcc.size();y++){
				if (backend.transactions[x].account_number==backend.masterAcc[y].account_number){
					if(backend.transactions[x].misc == "TO"){
						backend.change_balance(x,false);
					}else if (backend.transactions[x].misc == "FR"){//from
						backend.change_balance(x,true);
					}
				}
			}
		}
		else if(backend.transactions[x].code=="03"){ //paybill
			for (int y=0;y<backend.masterAcc.size();y++){
				if (backend.transactions[x].account_number==backend.masterAcc[y].account_number){
					backend.change_balance(x,true);
				}
			}
		}

		else if(backend.transactions[x].code=="04"){ //deposit
			for (int y=0;y<backend.masterAcc.size();y++){
				if (backend.transactions[x].account_number==backend.masterAcc[y].account_number){
					backend.change_balance(x,false);
				}
			}
		}
		else if(backend.transactions[x].code=="05"){ //Create
			//create new account node and add to vector
			MasterAccountNode new_account;
			new_account.account_name = backend.transactions[x].name;
			new_account.account_number = backend.transactions[x].account_number;
			new_account.balance = backend.transactions[x].balance;
			new_account.misc = backend.transactions[x].misc;
			new_account.status = "A";
			new_account.transaction_counter = "0000";
			backend.masterAcc.push_back(new_account);
		}

		else if(backend.transactions[x].code=="06"){ //Delete
			for (int y=0;y<backend.masterAcc.size();y++)
				if (backend.transactions[x].account_number==backend.masterAcc[y].account_number){
					//remove account from vector
					backend.masterAcc.erase(backend.masterAcc.begin()+y);
					break;
				}
		}
		else if(backend.transactions[x].code=="07"){ //Enable
			for (int y=0;y<backend.masterAcc.size();y++)
				if (backend.transactions[x].account_number==backend.masterAcc[y].account_number){
					backend.masterAcc[y].status="A";
					break;
				}
		}
		else if(backend.transactions[x].code=="08"){ //Disable
			for (int y=0;y<backend.masterAcc.size();y++)
				if (backend.transactions[x].account_number==backend.masterAcc[y].account_number){
					backend.masterAcc[y].status="D";
					break;
				}
		}
		else if(backend.transactions[x].code=="09"){ //Change plan
			for (int y=0;y<backend.masterAcc.size();y++)
				if (backend.transactions[x].account_number==backend.masterAcc[y].account_number){
					if(backend.masterAcc[y].misc=="NP")
						backend.masterAcc[y].misc="SP";
					else
						backend.masterAcc[y].misc="NP";
					break;
				}
		}
		else{}
	}

	//write out the files
	backend.writeFiles();
	return 0;
}
