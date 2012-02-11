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
 * @file main.cpp
 * @author Koo Beanz 2.1
 * @version 1.337
 *
 * @brief This is the main driver file that will run
 *
 * This file defines the main method, and is procedural. It will use all
 * three of the classes to handle different input and output for the system.
 *****************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include "interactive-stream-handler.h"
#include "transaction-file-writer.h"
#include "bank-account-reader.h"

using namespace std;

//Constants used to define directories and file extensions
string kTransactionDirectory="system/transaction/";
string kCurrentBankAccountDirectory="system/account/";
string kTransactionFileExtension=".tra";
string kCurrentBankAccountFileName="current_bank_account.cba";

//Instantiate the three classes for I/O
InteractiveStreamHandler interact(kTransactionDirectory,kTransactionFileExtension,kCurrentBankAccountDirectory,kCurrentBankAccountFileName);
TransactionFileWriter writer(interact.tra_directory,interact.transaction_file_extension);
BankAccountReader reader(interact.cba_directory,interact.current_bank_accounts_file_name);

/*
 * This method contains the interaction a logged in user can have with the
 * system when attempting to withdraw money from their accounts. It will
 * call the BankAccount reader to read in information from the CBA and use
 * it to determine validity of the user and the amount input. It will also
 * use the writer to call the WriteFile function to generate the
 * transaction file.
 * It accepts a string containing the user name and a boolean which determines
 * whether the user is an admin or not.
 */
void withdrawal(string user_name,bool privileged){
	string user_input;		//stores the users input for commands
	float money_amount;		//Used to store int values of strings representing money

	cout<<"Which account would you like to withdraw from?\n";
	cin>>user_input;
	if(user_input=="cancel"){
		cout<<"Cancelled\n";
	}else{
		//If the user's account exists in the system
		if (reader.IsValid(user_name,user_input)){

			//read in the account info to ensure no money issues
			reader.ReadFile(user_name,user_input);

			//Ask how much the user wishes to withdraw and check if its valid
			cout<<"What amount would you like to withdraw? [In Canadian dollars]\n";
			cin>>user_input;
			stringstream string_to_float(user_input);

			//Was given a non number input
			if((string_to_float>>money_amount).fail())
				cout<<"Error: Invalid Data type.\n";

			//Only the admin can withdraw > $500
			else if(money_amount>500&&!privileged){
				cout<<"Error: Withdrawal limit of $500\n";

			//Must withdraw a positive amount
			}else if (money_amount<=0){
				cout<<"Error: Must withdraw positive amount\n";
			}else{
				if (reader.get_money()<money_amount){
					cout<<"Error: Insufficient funds\n";
				}else{
					writer.WriteFile("01",user_name,reader.get_acc_number(),user_input,"MM");
					cout<<"Dispensing money.\n";
				}
			}
		}else{
			cout<<"Error: Invalid Account.\n";
		}
	}
}

/*
* This method contains the interaction a logged in user can have with the
* system when attempting to deposit money to an account. It will
* call the BankAccount reader to read in information from the CBA and use
* it to determine validity of the user. It will also
* use the writer to call the WriteFile function to generate the
* transaction file with the appropriate data.
* It takes a string that contains the users name.
*/
void deposit(string user_name){
	string user_input;		//stores the users input for commands
	int money_amount;		//Used to store int values of strings representing money

	cout<<"Which account would you like to deposit from?\n";
	cin>>user_input;
	if(user_input=="cancel"){
		cout<<"Cancelled\n";
	}else{
		//Check that the account exists
		if (reader.IsValid(user_name,user_input)){

			//Read in the account information
			reader.ReadFile(user_name,user_input);

			//Ask how much they wish to deposit and stop any errors
			cout<<"What amount would you like to deposit? [In Canadian dollars]\n";
			cin>>user_input;
			stringstream string_to_float(user_input);
			if((string_to_float>>money_amount).fail())
				cout<<"Error: Invalid Data type.\n";
			else if(money_amount>99999.99){
				cout<<"Error: Deposit limit reached\n";
			}else if (money_amount<=0){
				cout<<"Error: Must deposit positive amount\n";
			}else{
				writer.WriteFile("04",user_name,reader.get_acc_number(),user_input,"MM");
				cout<<"Depositing money\n";
			}
		}else{
			cout<<"Error: Invalid Account.\n";
		}
	}
}

/*
* This method takes a users' name as a parameter in order to display
* all the information pertaining to the account the user specifies in it.
* It can only be used if a user is logged in.
*/
void view(string user_name){
	string user_input;		//stores the users input for commands
	cout<<"Which account would you like to view?\n";
	cin>>user_input;
	if(user_input=="cancel"){
		cout<<"Cancelled\n";
	}else{
		//Ensure that the account exists
		if (reader.IsValid(user_name,user_input)){

			//Read in the account and display all the information
			reader.ReadFile(user_name,user_input);
			cout<<"Name: "<<reader.get_name()<<endl;
			cout<<"Account #: "<<reader.get_acc_number()<<endl;
			cout<<"Status: "<<reader.get_status()<<endl;

			//Transform the transaction number to a string
			stringstream float_to_string;
			float_to_string<<reader.get_money();
			cout<<"Money: "<<float_to_string.str()<<endl;

		}else
			cout<<"Error: Invalid Account\n";
	}
}

/*
* Enable will accept a users' name and a boolean variable which specifies whether
* the account is to be disabled or enabled. According to which was selected,
* a transaction file will be generated with the command for either disabling
* or enabling an account.
*/
void enable(string user_name,bool enable){
	string user_input;		//stores the users input for commands
	cout<<"Which account would you like to change?\n";
	cin>>user_input;

	if(user_input=="cancel"){
		cout<<"Cancelled\n";
	}else{
		//Check to ensure the account exists
		if (reader.IsValid(user_name,user_input)){
			reader.ReadFile(user_name,user_input);
			//Enable the account
			if (enable){
				writer.WriteFile("07",user_name,reader.get_acc_number(),"00000.00","MM");
				cout<<"Account enabled\n";
			}

			//Disable the account
			else{
				writer.WriteFile("08",user_name,reader.get_acc_number(),"00000.00","MM");
				cout<<"Account disabled\n";
			}
		}else
				cout<<"Error: Invalid Account\n";
	}
}

/*
* The changeplan function takes in a user name which it uses along with
* an account number input by the user to check for the validity of a user
* and proceed to output a transaction file with the SP or NP tag attached
* to the end specifying what the plan has been changed to as well as the
* user name and his account.
*/
void changeplan(string user_name){
	string user_input;		//stores the users input for commands
	cout<<"Which account would you like to change?\n";
	cin>>user_input;
	if(user_input=="cancel"){
		cout<<"Cancelled\n";
	}else{
		//Check that the account is valid
		if (reader.IsValid(user_name,user_input)){
			reader.ReadFile(user_name,user_input);
			cout<<"Student plan or non-Student? [SP|NP]\n";
			cin>>user_input;

			//Change to a student plan
			if (user_input=="SP")
				writer.WriteFile("09",user_name,reader.get_acc_number(),"00000.00","SP");

			//Change to a non student plan
			else
				writer.WriteFile("09",user_name,reader.get_acc_number(),"00000.00","NP");
			cout<<"Plan changed\n";
		}else
				cout<<"Error: Invalid Account\n";
	}
}

/*
* This function takes in a user name as a parameter which it uses along
* with an account number input by the user to check his validity and
* then proceeds to output a transaction file containing the code for
* deleting an account along with the user name and account number.
*/
void deleteAcc(string user_name){
	string user_input;		//stores the users input for commands
	cout<<"Which account would you like to delete?\n";
	cin>>user_input;
	if(user_input=="cancel"){
		cout<<"Cancelled\n";
	}else{
		//Check that the account exists and then delete it
		if (reader.IsValid(user_name,user_input)){
			reader.ReadFile(user_name,user_input);
			writer.WriteFile("06",user_name,reader.get_acc_number(),"00000.00","MM");
			cout<<"Account deleted\n";
		}else
				cout<<"Error: Invalid Account\n";
	}
}

/*
* This function takes in a user name as a parameter which it uses along
* with an account number input by the user to check his validity and
* then proceeds to output a transaction file containing the code for
* creating an account along with the user name and account number and
* the balance input.
*/
void create(string user_name){
	string user_input;		//stores the users input for commands
	float money_amount;		//Used to store int values of strings representing money
	string new_account_number = reader.NewAccNumber();	//Used to generate a new account number.
	//cout<<"Which account would you like to create?\n";
	//cin>>user_input;

	//Check that the account does not already exist
	if (!reader.IsValid(user_name,new_account_number/*,user_input*/)){
		cout<<"How much money will the account have?\n";
		cin>>user_input;
		stringstream string_to_float(user_input);

		//check that there are no issues with the amount of money
		if((string_to_float>>money_amount).fail())
			cout<<"Error: Invalid Data type.\n";
		else if(money_amount>99999.99)
			cout<<"Error: Account money limit breached\n";
		else if(money_amount<0.00)
			cout<<"Error: Account can not hold a negative amount\n";
		else if(user_name.length() > 20)
			cout<<"Error: Name is more than 20 characters.\n";
		else{
			string misc=reader.assign_plan(user_name);
			writer.WriteFile("05",user_name,new_account_number,user_input,misc);
			cout<<"Account created\n";
		}
	}else
			cout<<"Error: Invalid Account\n";
}

/*
* This function takes in a user name and a boolean as parameters which it
* uses to check his validity and whether it is an admin or a standard user.
* Then it takes a specific company code and money amount input by the user
* which it uses to output a transaction file.
*/
void paybill(string user_name,bool privileged){
	string user_input;		//stores the users input for commands
	string company;
	float money_amount;		//Used to store int values of strings representing money

	cout<<"Which account would you like to pay a bill for?\n";
	cin>>user_input;

	if(user_input=="cancel"){
		cout<<"Cancelled\n";
	}else{
		//Check that the account exists
		if (reader.IsValid(user_name,user_input)){
			reader.ReadFile(user_name,user_input);
			cout<<"Please enter the company you wish to pay? [EC|CQ|TV]\n";
			cin>>company;

			//Check that the company exists
			if (company!="EC"&&company!="CQ"&&company!="TV")
				cout<<"Error: Invalid Company\n";
			else{

				//Check for issues with the money amount
				cout<<"What amount would you like to pay? [In Canadian dollars]\n";
				cin>>user_input;
				stringstream string_to_float(user_input);
				if((string_to_float>>money_amount).fail())
					cout<<"Error: Invalid Data type.\n";
				else if(money_amount>2000&&!privileged){
					cout<<"Error: Bill limit of $2000\n";
				}else if (money_amount<=0){
					cout<<"Error: Must pay positive amount\n";
				}else{
					if (reader.get_money()<money_amount){
						cout<<"Error: Insufficient funds\n";
					}else{
						writer.WriteFile("03",user_name,reader.get_acc_number(),user_input,company);
						cout<<"Paying bill\n";
					}
				}
			}
		}else
			cout<<"Error: Invalid Account.\n";
	}
}

/*
* The transfer function takes in a string with the account holders name
* and a boolean indicating whether it is a standard or admin user. It then
* prompts the user to input which account to transfer the money from and
* which account and user to transfer the money to. It checks for the
* validity of all accounts input and then proceeds to generate two transaction
* files, one which will contain the transferrer with the TO field in the end
* and the relevant amount and another which will contain the person receiving
* with the FR field in the end as well as the relevant amount being transferred.
*/
void transfer(string account_holder, bool privileged){
	string account_holder_number;
	string account_transfer;
	string account_transfer_number;
	string user_input;		//stores the users input for commands
	float money_amount;		//Used to store int values of strings representing money

	//Ask for all the information for both user's accounts
	//Flushing cin is required for taking in the second name
	//cin.ignore();
	cout<<"Which account would you like to transfer from?\n";
	cin>>account_holder_number;
	cin.ignore();
	cout<<"Who would you like to transfer to?\n";
	getline(cin,account_transfer);
	account_transfer=interact.FormatName(account_transfer);
	cout<<"Which account would you like to transfer to?\n";
	cin>>account_transfer_number;

	if(account_holder=="cancel"||account_holder_number=="cancel"||account_transfer=="cancel"||account_transfer_number=="cancel"){
		cout<<"Cancelled\n";
	}else{
		//Check that both users exist
		if (reader.IsValid(account_holder,account_holder_number)&&reader.IsValid(account_transfer,account_transfer_number)){

			//Check the money amounts and write the two transfer files
			cout<<"What amount would you like to pay? [In Canadian dollars]\n";
			cin>>user_input;
			stringstream string_to_float(user_input);
			if((string_to_float>>money_amount).fail())
				cout<<"Error: Invalid Data type.\n";
			else if(money_amount>1000&&!privileged){
				cout<<"Error: Bill limit of $1000\n";
			}else if (money_amount<=0){
				cout<<"Error: Must pay positive amount\n";
			}else if (money_amount>99999.99){
				cout<<"Error: Maximum money amount breached\n";
			}else{
				reader.ReadFile(account_holder,account_holder_number);
				if (reader.get_money()<money_amount){
					cout<<"Error: Insufficient funds\n";
				}else{
					writer.WriteFile("02",account_holder,account_holder_number,user_input,"FR");
					writer.WriteFile("02",account_transfer,account_transfer_number,user_input,"TO");
					cout<<"Transferring money\n";
				}
			}
		}else
			cout<<"Error: Invalid Account.\n";
	}
}

int main(){
	bool done=false;		//Used to quit the system
	bool in_use=false;		//Used to show that the system is in use by a user
	bool privileged=false;	//Used to activate privileged mode
	int attempts=0;			//stores the users attempts at inputing a correct command
	int last_account=0;	//used when creating new accounts

	string account_holder;	//Used to store the account holder when admin performs transactions
	string user_input;		//stores the users input for commands
	string user_name;		//stores the users name
	cout<< "System initiating...\n";

	/*
		Find the largest account number in use
	*/
	

	cout<< "Please Login to the System\n";

	//Look for commands from user until they quit the system
	do{

		//Take in user input for a command and formats it
		cin>> user_input;
		user_input=interact.FormatInput(user_input);

		//The user chose the login command
		if (user_input=="login"){

			//Give an error if the system is in use
			if (in_use)
				cout<<"Error: System is in use.\n";

			else{

				//Ask user to input the session type
				cout<<"Please choose the type of session. [standard|admin]\n";
				cin>> user_input;
				user_input=interact.FormatInput(user_input);


				if(user_input=="standard"){

					//Ask for the users name and give 3 chances at a valid name
					cout<<"Please enter your name.\n";
					cin.ignore();
					do{
						getline(cin,user_name);
						user_name=interact.FormatName(user_name);
						if (reader.IsValid(user_name)){
							cout<<"Welcome, "<<user_name<<". Please enter a command.\n";
							in_use=true;
							break;
						}else if(user_name=="Cancel"){
							cout<<"Login cancelled\n";
							break;
						}else{
							attempts++;
							if (attempts==3)
								cout<<"Error: Invalid name. Login denied.\n";
							else
								cout<<"Error: Invalid name. Please try again.\n";
						}
					}while(attempts<3);

				}else if(user_input=="admin"){

					//Login as admin and enable privileged mode
					in_use=true;
					user_name="Admin";
					privileged=true;
					cout<<"Welcome, Admin. Please enter a command.\n";
				}else if(user_input=="cancel"){
					cout<<"Cancelled\n";
				}else
					cout<<"Error: Invalid session type. Login failed\n";
			}

		//The user chose the logout command
		}else if(user_input=="logout"){
			privileged=false;
			if(!in_use)
				cout<<"Error: No user logged in\n";
			else{
				writer.WriteFile("00",user_name,"00000","00000000","MM");
				cout<<"Goodbye, "<<user_name<<".\n";
				in_use=false;
			}

		//The user chose the withdrawal command
		}else if(user_input=="withdrawal"){
			if(!in_use)
				cout<<"Error: No user logged in\n";
			else if (privileged){
				cout<<"What is the name of the account holder?\n";
				cin.ignore();
				getline(cin,account_holder);
				account_holder=interact.FormatName(account_holder);
				withdrawal(account_holder,privileged);
			}else
				withdrawal(user_name,privileged);


		//The user chose the Transfer command
		}else if(user_input=="transfer"){
			if(!in_use)
				cout<<"Error: No user logged in\n";
			else if (privileged){
				cout<<"What is the name of the account holder?\n";
				cin.ignore();
				getline(cin,account_holder);
				account_holder=interact.FormatName(account_holder);
				transfer(account_holder,privileged);
			}else
				transfer(user_name,privileged);

		//The user chose the paybill command
		}else if(user_input=="paybill"){
			if(!in_use)
				cout<<"Error: No user logged in\n";
			else if (privileged){
				cout<<"What is the name of the account holder?\n";
				cin.ignore();
				getline(cin,account_holder);
				account_holder=interact.FormatName(account_holder);
				paybill(account_holder,privileged);
			}else
				paybill(user_name,privileged);

		//The user chose the deposit command
		}else if(user_input=="deposit"){
			if(!in_use)
				cout<<"Error: No user logged in\n";
			else if (privileged){
				cout<<"What is the name of the account holder?\n";
				cin.ignore();
				getline(cin,account_holder);
				account_holder=interact.FormatName(account_holder);
				deposit(account_holder);
			}else
				deposit(user_name);

		//The user chose the create command
		}else if(user_input=="create"){
			if(!in_use)
				cout<<"Error: No user logged in\n";
			else if (privileged){
				cout<<"What is the name of the account holder?\n";
				cin.ignore();
				getline(cin,account_holder);
				account_holder=interact.FormatName(account_holder);
				create(account_holder);
			}else
				cout<<"Error: Requires privileged mode\n";

		//The user chose the delete command
		}else if(user_input=="delete"){
			if(!in_use)
				cout<<"Error: No user logged in\n";
			else if (privileged){
				cout<<"What is the name of the account holder?\n";
				cin.ignore();
				getline(cin,account_holder);
				account_holder=interact.FormatName(account_holder);
				deleteAcc(account_holder);
			}else
				cout<<"Error: Requires privileged mode\n";

		//The user chose the disable command
		}else if(user_input=="disable"){
			if(!in_use)
				cout<<"Error: No user logged in\n";
			else if (privileged){
				cout<<"What is the name of the account holder?\n";
				cin.ignore();
				getline(cin,account_holder);
				account_holder=interact.FormatName(account_holder);
				enable(account_holder,false);
			}else
				cout<<"Error: Requires privileged mode\n";

		//The user chose the changeplan command
		}else if(user_input=="changeplan"){
			if(!in_use)
				cout<<"Error: No user logged in\n";
			else if (privileged){
				cout<<"What is the name of the account holder?\n";
				cin.ignore();
				getline(cin,account_holder);
				account_holder=interact.FormatName(account_holder);
				changeplan(account_holder);
			}else
				cout<<"Error: Requires privileged mode\n";


		//The user chose the enable command
		}else if(user_input=="enable"){
			if(!in_use)
				cout<<"Error: No user logged in\n";
			else if (privileged){
				cout<<"What is the name of the account holder?\n";
				cin.ignore();
				getline(cin,account_holder);
				account_holder=interact.FormatName(account_holder);
				enable(account_holder,true);
			}else
				cout<<"Error: Requires privileged mode\n";

		//The user chose the view command
		}else if(user_input=="view"){
			if(!in_use)
				cout<<"Error: No user logged in\n";
			else if (privileged){
				cout<<"What is the name of the account holder?\n";
				cin.ignore();
				getline(cin,account_holder);
				account_holder=interact.FormatName(account_holder);
				view(account_holder);
			}else
			view(user_name);

		//The user chose the help command
		}else if(user_input=="help"){

			//Display the available commands
			cout<<"AVAILABLE COMMANDS\n";
			cout<<"==================\n";
			if (privileged&&in_use){
				cout<<"Logout\n";
				cout<<"Withdrawal\n";
				cout<<"Transfer\n";
				cout<<"Paybill\n";
				cout<<"Deposit\n";
				cout<<"Create\n";
				cout<<"Delete\n";
				cout<<"Changeplan\n";
				cout<<"Enable\n";
				cout<<"Disable\n";
				cout<<"View\n";
				cout<<"Help\n";
			}else if (in_use){
				cout<<"Logout\n";
				cout<<"Withdrawal\n";
				cout<<"Transfer\n";
				cout<<"Paybill\n";
				cout<<"Deposit\n";
				cout<<"View\n";
				cout<<"Help\n";
			}else{
				cout<<"Login\n";
				cout<<"Help\n";
				cout<<"Quit\n";
			}

		//The user chose the cancel command
		}else if(user_input=="cancel")
			cout<<"Error: No transaction in progress\n";

		//The user chose the quit command
		else if(user_input=="quit"){
			if(!in_use){
				done=true;
			}else{
				cout<<"Error: System in use\n";
			}

		//The user input an invalid command
		}else
			cout<<user_input<<" is an invalid command\n";
		
	}while(!done);
	cout<<"System shutting down\n";
}
