/* Author Name: Micaiah Skolnick
Date: 10/01/17               */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <string>
#include <sstream>
using namespace std;
//Declare public variables
ifstream fromFile;
ofstream toFile;
int bytesInMemory;
int bitsInMemory;
string dataFileName;
string dataType;
int dataValue;
string dataStr;
string dataString;
string address;
string memory;
int charCount;
int addressHeaderDec;
int currAddress;

string decToHex(int decimal) {
	char buffer[33];
	_itoa_s(decimal, buffer, 16); //Convert the decimal number to hexadecimal
	return buffer;
}

string dbDialog() {
	fromFile >> dataValue; //Get the data value
	string stringToReturn = "";
	stringToReturn = decToHex(dataValue);
	if (dataValue > 0) {
		return stringToReturn;
	}
	else {
		return stringToReturn.substr(6, 2);
	}
}
string dwDialog() {
	fromFile >> dataValue; //Get the data value
	string stringToReturn = "";
	stringToReturn = decToHex(dataValue);
	if (stringToReturn.length() == 2) {
		stringToReturn.insert(0, "00");
	}
	else if (stringToReturn.length() == 8) {
		stringToReturn = stringToReturn.substr(4, 4);
	}
	return stringToReturn;
}
string hbDialog() {
	fromFile >> dataString; //Get the data value
	return dataString;
}
string hwDialog() {
	fromFile >> dataString; //Get the data value
	if (dataString.length() == 2) {
		dataString.insert(0, "00");
	}
	return dataString;
}
string sDialog() {
	char thisChar;
	int asciiCharInt;
	string newString = "", asciiCharStr;
	fromFile >> ws;
	getline(fromFile, dataString); //Get the string from the data file
	for (int i = 0; i < dataString.length(); i++) {
		thisChar = dataString.at(i); //Get the next character of the string
		asciiCharInt = (int)thisChar; //Convert the character to ascii code
		asciiCharStr = decToHex(asciiCharInt); //Conver the decimal ascii to hex
		newString.append(asciiCharStr);//Append the ascii code to what will be written to memory
	}
	newString.append("00"); //Add a null character to the end of the string
	return newString;
}
void printResults() {
	addressHeaderDec = 0;

	for (int i = 0; i < bitsInMemory; i += 16) {
		string currAddressHex = decToHex(addressHeaderDec);
		int length = 8 - currAddressHex.length();
		for (int z = 0; z < length; z++) {
			cout << 0; //Print out the number of 0s needed to get an 8 digit number
		}
		cout << currAddressHex << ": ";
		cout << memory.substr(i, 16) << endl;;
		addressHeaderDec += 8; //Add 8 to the current memory address
	}
}
void createMemory() {
	for (int i = 0; i < bitsInMemory; i++) { //Pad out the memory for the number of bits needed
		memory.append("0");
	}
}
int main() {
	//Initialize public variables
	bytesInMemory = 0;
	dataFileName = "blank";
	memory = "";
	address = "00000000";
	charCount = 0;
	//Read in the number of bytes in memory, and the file name
	cout << "How many bytes in memory? ";
	cin >> bytesInMemory;
	bitsInMemory = bytesInMemory * 2;
	cout << "Data file name? ";
	cin >> dataFileName;
	createMemory(); //Create the memory where data will be stored
	fromFile.open(dataFileName);

	while (fromFile >> dataType) { //Keep reading instructions until the end of file is reached		
		if (dataType == "s") { //Enter the correct dialog based on the data type entered
			dataStr = sDialog();
		}
		else if (dataType == "db") {
			dataStr = dbDialog();
		}
		else if (dataType == "dw") {
			dataStr = dwDialog();
		}
		else if (dataType == "hb") {
			dataStr = hbDialog();
		}
		else if (dataType == "hw") {
			dataStr = hwDialog();
		}
		//Replace the characters at the correct memory location with the new values
		memory.replace(currAddress, dataStr.length(), dataStr);
		currAddress += dataStr.length(); //Increase the current address location
	}
	printResults();
	cout << endl << endl << "Enter any key to exit ";
	cin >> dataType;
	return 0;
}
