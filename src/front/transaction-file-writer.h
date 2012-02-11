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
 * @file transaction-file-writer.h
 * @author Koo Beanz 2.1
 * @version 1.337
 *
 * @brief This is a header file used to write transaction files
 *
 * This file defines the class TransactionFileWriter. A TransactionFileWriter
 * will manage all the creation of transaction files, as well as their naming.
 *
 * Input files: N/A
 * Output files: Transaction files.
 *****************************************************************************/
#include <string>

using namespace std;

/**
 * @class TransactionFileWriter
 * @brief Class used to manage writing transaction files
 *
 * This class will manage creation of the transaction files. When constructed
 * it requires a string to detail which directory to place the files in, as
 * well as a string to list the extension of the files.
 *
 * Input files: N/A
 * Output files: Transaction files.
 */
class TransactionFileWriter{
	private:
		/**
		 * @var file_directory
		 * @brief This stores the directory to create the transaction files in.
		 *
		 * This string stores a directory to where the transaction files should
		 * be created. It is initialized in the constructor to allow for it to
		 * be flexible. It is a private variable and can not be changed once
		 * the class is instantiated.
		 */
		string file_directory;

		/**
		 * @var file_extension
		 * @brief This stores the file extension for all transaction files.
		 *
		 * This string stores the file extension that will end all transaction
		 * files.
		 */
		string file_extension;
		
		 /**
		  * @var trans_counter_file
		  * @brief This stores the name of the file that holds the number of transaction files.
		  *
		  * This string has the name of a file that will hold a number whick keeps track
		  * of which transaction file we are creating. This way, even if the system shuts down,
		  * we will still know what the next transaction file created should be.
		  */
		string trans_counter_file;
		 
		/**
		 * @var transaction_number
		 * @brief DEPRECATED VARIABLE. This is a counter for transactions done in one system activation
		 *
		 * The transaction number increments each time a transaction is created.
		 * Its position in between the name of the file and the extension, is
		 * used to help remove the possibility of duplicate files written at the
		 * same time.
		 */
		 
		//int transaction_number;

		/**
		 * @brief THIS FUNCTION IS DEPRECATED. Formats the time given by the system to a useful string. 
		 *
		 * Formats a given string, to remove the first 4 characters,
		 * remove the last character and replace all white space with
		 * '_'. The purpose of removing the first four characters is to remove
		 * the day section of the time, for example "wed ". This section is
		 * not necessary as we are already given the month date and year.
		 * The last character is removed because it is a end of line character.
		 * All the whitespace is replaced with '_' because it aids in naming the
		 * files.
		 *
		 * @param input
		 *
		 * The string of input, this should be an unedited system time.
		 *
		 * @return
		 *
		 * Returns a string containing the formatted time.
		 */
		//string FormatTime(string input);
	public:
		/**
		 * @brief Constructor for TransactionFileWriter
		 *
		 * Used to construct a TransactionFileWriter. You must give it a
		 * string for the directory structure, as well as a string for
		 * the file extension.
		 *
		 * @param directory
		 *
		 * The directory you wish to write the files to.
		 *
		 * @param extension
		 *
		 * The file extension you wish to use.
		 */
		TransactionFileWriter(string directory,string extension);
		/**
		 * @brief De-constructor for TransactionFileWriter
		 */
		~TransactionFileWriter();

		/**
		 * @brief Writes the transaction file
		 *
		 * This function will write the transaction file into the proper
		 * directory, with the proper name. All it requires is the strings
		 * for all the different fields in the transaction file.
		 *
		 * @param transaction_code
		 *
		 * The transaction code that is written. Example "02" for transfer.
		 *
		 * @param name
		 *
		 * The name of the user, It does not need to be the total 20 characters.
		 * Example "John_Smith" becomes "John_Smith__________"
		 *
		 * @param money
		 *
		 * This string money represents the money that occurs for the given
		 * transaction.
		 *
		 * @param plan
		 *
		 * This string is used to show if they are on a student plan, "SP" or
		 * not "NP"
		 */
		void WriteFile(string transaction_code,string name,string account_number,string money,string plan);
};
