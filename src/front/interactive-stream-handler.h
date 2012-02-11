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
 *	@file interactive-stream-handler.h
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
 * Input files: N/A
 * Output files: N/A
 *
 *****************************************************************************/
#include <string>

using namespace std;

/**
 * @class InteractiveStreamHandler
 * @brief Used to format user input.
 *
 *
 * This class will handle formating user input into a structure that
 * the system expects. It also maintains the directory structure and
 * file extensions for the system, so that they only need to be changed
 * in the constants at the top of the main, to affect the whole system.
 *
 * Input files: N/A
 * Output files: N/A
 */
class InteractiveStreamHandler{
	private:

	public:
		/**
		 * @var cba_directory
		 * @brief Directory structure for current bank account files
		 *
		 * This is a string that defines the directory structure to all the
		 * current bank account files.
		 */
		string cba_directory;

		/**
		 * @var current_bank_accounts_file_name
		 * @brief File extension for Current Bank Account Files
		 *
		 * This is a string used to store the file extension that
		 * will be used for current bank account files.
		 */
		string current_bank_accounts_file_name;

		/**
		 * @var tra_directory
		 * @brief Directory structure for transaction files
		 *
		 * This is a string that defines the directory structure to all the
		 * transaction files.
		 */
		string tra_directory;

		/**
		 * @var transaction_file_extension
		 * @brief File extension for Transaction Files
		 *
		 * This is a string used to store the file extension that
		 * will be used for Transaction files.
		 */
		string transaction_file_extension;

		/**
		 * @brief Constructor for InteractiveStreamHandler
		 *
		 * Used to construct an InteractiveStreamHandler. You
		 * must give two strings for the directory structures,
		 * as two strings, one for transaction file extensions,
		 * and the other for the name of the current bank accounts
		 * file.
		 *
		 * @param t_dir
		 *
		 * The directory you wish to write the transaction files to.
		 *
		 * @param t_ext
		 *
		 * The file extension you wish to use for transaction files.
		 *
		 * @param a_dir
		 *
		 * The directory you wish to store the current bank accounts.
		 * file in.
		 *
		 * @param a_name
		 *
		 * The name of the current bank accounts file, with extension.
		 */
		InteractiveStreamHandler(string t_dir, string t_ext, string a_dir, string a_name){
			cba_directory=a_dir;
			tra_directory=t_dir;
			current_bank_accounts_file_name=a_name;
			transaction_file_extension=t_ext;
		}
		~InteractiveStreamHandler(){}

		/**
		 * @brief Used to format a string of Input
		 *
		 * Formats the string of input to remove case sensitivity
		 *
		 * @param s
		 *
		 * The string of input that is being formatted
		 *
		 * @return
		 *
		 * Returns the formatted string
		 */
		string FormatInput(string s);

		/**
		 * @brief Used to format a string into the format of a name
		 *
		 * Formats the input string into a valid name format for the system.
		 * For example, if given "jOHN SmIth", it will return "John_Smith"
		 *
		 * @param s
		 *
		 * The string of input that is being formatted
		 *
		 * @return
		 *
		 * Returns the formatted name
		 */
		string FormatName(string s);

};

