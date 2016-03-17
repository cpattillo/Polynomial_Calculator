/*
*  cbp53P4.cpp
*
*  COSC 052 Spring 2015
*  Project #4
*
*  Due on: March 31, 2015
*  Author: Caroline Pattillo
*
*
*  In accordance with the class policies and Georgetown's
*  Honor Code, I certify that, with the exception of the
*  class resources and those items noted below, I have neither
*  given nor received any assistance on this project.
*
*  References not otherwise commented within the program source code.
*  Note that you should not mention any help from the TAs, the professor,
*  or any code taken from the class textbooks.
*/

#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "LL.h"
#include "Stack.h"

/*using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::istream;
using std::cin;*/

using namespace std;

//using namespace std;

/*
Loads data from the data file into a vector of MineRecords
*/
void loadMineData(string = "");

int main(int argc, const char *argv[])
{
	try
	{

		string badArgMessage = "";

		//Checks to make command line has an argument 
		if (argc < 2)
		{
			badArgMessage = "There is no argument for the file";
			throw badArgMessage;
		}
		else
		{

			string inputDataFileName(argv[1]);//Declaring first command argument as a string

			//string to store name and path of output file
			string outputFileName = "";

			//output file stream object
			std::ofstream outFile;

			//this statement makes the input file name and the output file name exactly the same
			outputFileName = inputDataFileName;

			//this statement adds an extension to the output file name so it is no longer 
			//exactly the same as the input file
			outputFileName += ".out";


			cout << "The name of the file is: " << inputDataFileName << endl;//printing out file name 

			loadMineData(inputDataFileName);//calling method to load data into MineRecord vector vMr

			cout << "Displayed exe report for terminal:";//Checking to make sure displayed report

			//************* File stuff*************
			//open the output data file
			outFile.open(outputFileName.c_str());

			//test to make sure the file opened successfully
			if (!outFile)
			{
				//output file failed to open
				string errMessage = "Inside function main()\nThe file named: ";
				errMessage += outputFileName;
				errMessage += " failed to open, cannot call the report function :-(";

				throw errMessage;
			}
			else
			{
				//call the report function and have the output go to a file
				cout << "Calling function to send report to a file, output file name is:\n";
				cout << outputFileName << endl;

				//myLog.displayExecReport1(outFile);

				cout << "Output to file is complete.\n";

				outFile.close();
			}
		}
	}

	catch (string errorMessage)
	{
		cout << errorMessage << endl;
	}

	system("pause"); //keeps window open
	return 0;
}

//Populating MineRecord vector with data from the data file. 
void loadMineData(string mFileName)
{
	cout << "Inside function loadMineData() " << endl;
	try
	{
		int recordCount = 0;
		int recordsAccordingToFile = 0;
		string commentsToIgnore = "";
		string oneLine = "";
		string fileOpenError = "";
		ifstream inFile(mFileName.c_str()); //opening file
		

		//If file does not open
		if (!inFile)
		{
			inFile.close();
			fileOpenError = "Input file containing mine data: ";
			fileOpenError += mFileName;
			fileOpenError += " failed to open.";
			throw fileOpenError;
		}
		else
		{

			string find = "";
			int coef;
			int degree;

			/***********DECLARING STACK STUFF*********************/
			stack<LL<int>> myStack(10);
			LL<int> myLL;

			//While Loop that traverses through the file and computers polynomials 
			while (getline(inFile, find))
			{
				cout << "printing out find" << find << endl;

				std::stringstream iss(find);

				if (find[0] == '+')
				{
					cout << "Testing the + operator\n";
					LL<int> temp1(myStack.getTop());
					myStack.pop();
					LL<int> temp2(myStack.getTop());
					myStack.pop();

					cout << "Printing the addition operator\n";
					LL<int> newL(temp1 + temp2);
					newL.print();
					cout << "End addition print\n";
				}
				else if (find[0] == '*')
				{

					cout << "Testing the * operator\n";
					LL<int> temp3(myStack.getTop());
					myStack.pop();
					LL<int> temp4(myStack.getTop());
					myStack.pop();

					cout << "Printing multiplication\n";
					LL<int> nLL(temp3*temp4);
					nLL.print();
					myStack.push(nLL);
					cout << "Finishd printing multiplication\n";
				}
				else if (find[0] == '-')
				{

					cout << "Testing the - operator\n";
					LL<int> temp5(myStack.getTop());
					myStack.pop();
					LL<int> temp6(myStack.getTop());
					myStack.pop();

					cout << "Printing subtraction\n";
					LL<int> subLL(temp5 - temp6);
					subLL.print();
					myStack.push(subLL);
					cout << "Finished Printing subtraction\n";
				}
				else
				{
					

					while (iss >> coef)
					{
						iss >> degree;
						myLL.Insert_rear(coef, degree);
					}

			
					myStack.push(myLL);
					/*
					cout << "******************Printing Stack elements" << endl;
					myStack.getTop().print();

					cout << "*************************Printed elelments***************" << endl;
					*/
					myLL.clear();

				}

			}



			/*int count = 0;
			//fills vMr with data from data file
			while (getline(inFile, oneLine))
			{
			recordCount++;
			cout<<oneLine<<endl;
			count++;
			//cout << count << endl;
			}
			*/
			cout << "finished reading file data..." << recordCount << " lines read." << endl;

			cout << "finished loading all data\n";
			///cout << vMR.size() << " total MineRecord objects added to the vector.\n";

			cout << endl;

			inFile.close();
		}

		cout << "Exiting function loadMineData() " << endl;
	}

	catch (string sErr)
	{
		cout << "error in loadMineData function\n";
		cout << sErr << endl;

		//throw sErr; //do not rethrow for P1
	}


} //END function loadMineData


