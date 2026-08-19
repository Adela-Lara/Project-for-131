#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
using namespace std;
using std::numeric_limits;
using std::streamsize;

//PreCondition: spaces (boolean true or false)
//PostCondition: returns a string including space character(s) or without space character 
inline string inputString(string prompt, bool spaces)
{
	string input = "";

	do
	{
		cout << prompt;
		if (spaces)
		{
			cin.clear(); // ensure stream is in a good state before getline
			getline(cin, input);
			if (input.empty())
			{
				cout << "ERROR: Invalid input string cannot be empty.\n";
				continue;
			}
		}
		else
		{
			cin >> input;
			cin.clear();
			cin.ignore(999, '\n');
		}
		return input;
	} while (true);
}

//PreCondition: valid string of options
//PostCondition: returns an uppercase  of the option (char)
inline char inputChar(string prompt, string options)
{
	char input;
	while (true) {
		cout << prompt;

		if (!(cin >> input)) {
			cout << "ERROR: Invalid input. Must be a character type.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		// always eat the rest of the line from THIS attempt
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// check against allowed set (case-insensitive)
		bool found = false;
		for (int i = 0; i < static_cast<int>(options.length()); ++i) {
			if (toupper(static_cast<unsigned char>(options.at(i)))
				== toupper(static_cast<unsigned char>(input))) {
				found = true; break;
			}
		}

		if (!found) {
			cout << "ERROR: Invalid input. Must be one of '" << options << "' character.\n";
			continue;
		}
		return static_cast<char>(toupper(static_cast<unsigned char>(input)));
	}
}

// Yes/No version, return UPPERCASE yes/no
inline char inputChar(string prompt, char yes, char no)
{
	char input;
	while (true) {
		cout << prompt;

		if (!(cin >> input)) {
			cout << "ERROR: Invalid input. Must be a character type.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		char u = static_cast<char>(toupper(static_cast<unsigned char>(input)));
		char Uyes = static_cast<char>(toupper(static_cast<unsigned char>(yes)));
		char Uno = static_cast<char>(toupper(static_cast<unsigned char>(no)));

		if (u != Uyes && u != Uno) {
			cout << "ERROR: Invalid input. Must be a '" << Uyes
				<< "' or '" << Uno << "' character.\n";
			continue;
		}
		return u;
	}
}

// Alphabet or Digit (alphaOrDigit=true => A..Z; false => 0..9). Returns the char as typed.
inline char inputChar(string prompt, bool alphaOrDigit)
{
	char input;
	while (true) {
		cout << prompt;

		if (!(cin >> input)) {
			cout << "ERROR: Invalid input. Must be a character type.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		unsigned char uc = static_cast<unsigned char>(input);
		if (alphaOrDigit && !isalpha(uc)) {
			cout << "ERROR: Invalid input. Must be an alphabet character.\n";
			continue;
		}
		if (!alphaOrDigit && !isdigit(uc)) {
			cout << "ERROR: Invalid input. Must be a digit character.\n";
			continue;
		}
		return input;
	}
}

// Any character; returns UPPERCASE (to match your current behavior)
inline char inputChar(string prompt)
{
	char input;
	while (true) {
		cout << prompt;

		if (!(cin >> input)) {
			cout << "ERROR: Invalid input. Must be a character type.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return static_cast<char>(toupper(static_cast<unsigned char>(input)));
	}
}

//PreCondition: NA
//PostCondition: returns any integer value
inline int inputInteger(string prompt)
{
	int input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR: Invalid input. Must be an integer type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: posNeg (boolean true or false)
//PostCondition: returns a positive integer value (posNeg = true) or a negative integer value (poseNeg = false)
inline int inputInteger(string prompt, bool posNeg)
{
	int input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR: Invalid input. Must be an integer type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (posNeg && input <= 0)
			cout << "ERROR: Invalid input. Must be a positive number.\n";
		else if (!posNeg && input >= 0)
			cout << "ERROR: Invalid input. Must be a negative number.\n";
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: start (integer) and greater (boolean true or false)
//PostCondition: returns an integer value greater than start or lesser than start
inline int inputInteger(string prompt, int start, bool greater)
{
	int input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR: Invalid input. Must be an integer type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (greater && input < start)
			cout << "ERROR: Invalid input. Must be a greater than or equal to " << start << ".\n";
		else if (!greater && input > start)
			cout << "ERROR: Invalid input. Must be a lesser than or equal to " << start << ".\n";
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: startRange (integer) and endRange (integer)
//PostCondition: returns an integer value within range (startRannge and endRange)
inline int inputInteger(string prompt, int startRange, int endRange)
{
	int input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR: Invalid input. Must be an integer type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (!(input >= min(startRange, endRange) && input <= max(startRange, endRange)))
			cout << "ERROR: Invalid input. Must be from " << startRange << ".." << endRange << ".\n";
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: NA
//PostCondition: returns any double value
inline double inputDouble(string prompt)
{
	double input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR: Invalid input. Must be a double type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: posNeg (boolean true or false)
//PostCondition: returns a positive double value (posNeg = true) or a negative double value (poseNeg = false)
inline double inputDouble(string prompt, bool posNeg)
{
	double input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR: Invalid input. Must be a double type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (posNeg && input <= 0.0)
			cout << "ERROR: Invalid input. Must be a positive number.\n";
		else if (!posNeg && input >= 0.0)
			cout << "ERROR: Invalid input. Must be a negative number.\n";
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: start(integer) and greater(boolean true or false)
//PostCondition: returns an integer value greater than start or lesser than start
inline double inputDouble(string prompt, double start, bool posNeg)
{
	double input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR: Invalid input. Must be a double type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (posNeg && input <= start)
			cout << "ERROR: Invalid input. Must be greater than or equal to " << start << ".\n";
		else if (!posNeg && input >= start)
			cout << "ERROR: Invalid input. Must be lesser than or equal to " << start << ".\n";
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//PreCondition: startRange (integer) and endRange (integer)
//PostCondition: returns an integer value within range (startRannge and endRange)
inline double inputDouble(string prompt, double startRange, double endRange)
{
	double input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR: Invalid input. Must be a double type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (!(input >= min(startRange, endRange) && input <= max(startRange, endRange)))
			cout << "ERROR: Invalid input. Must be from " << startRange << ".." << endRange << ".\n";
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}