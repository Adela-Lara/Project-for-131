#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include <cctype>

using std::cin;
using std::cout;
using std::string;
using std::min;
using std::max;
using std::numeric_limits;
using std::streamsize;

inline string inputString(string prompt, bool spaces)
{
    string input = "";
    do
    {
        cout << prompt;
        if (spaces)
        {
            cin.clear();
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return input;
    } while (true);
}

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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool found = false;
        for (int i = 0; i < static_cast<int>(options.length()); ++i) {
            if (toupper(static_cast<unsigned char>(options.at(i)))
                == toupper(static_cast<unsigned char>(input))) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "ERROR: Invalid input. Must be one of '" << options << "' character.\n";
            continue;
        }
        return static_cast<char>(toupper(static_cast<unsigned char>(input)));
    }
}

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
            break;
    } while (true);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (posNeg && input <= 0)
            cout << "ERROR: Invalid input. Must be a positive number.\n";
        else if (!posNeg && input >= 0)
            cout << "ERROR: Invalid input. Must be a negative number.\n";
        else
            break;
    } while (true);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (greater && input < start)
            cout << "ERROR: Invalid input. Must be a greater than or equal to " << start << ".\n";
        else if (!greater && input > start)
            cout << "ERROR: Invalid input. Must be a lesser than or equal to " << start << ".\n";
        else
            break;
    } while (true);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (!(input >= min(startRange, endRange) && input <= max(startRange, endRange)))
            cout << "ERROR: Invalid input. Must be from " << startRange << ".." << endRange << ".\n";
        else
            break;
    } while (true);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
            break;
    } while (true);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (posNeg && input <= 0.0)
            cout << "ERROR: Invalid input. Must be a positive number.\n";
        else if (!posNeg && input >= 0.0)
            cout << "ERROR: Invalid input. Must be a negative number.\n";
        else
            break;
    } while (true);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (posNeg && input <= start)
            cout << "ERROR: Invalid input. Must be greater than or equal to " << start << ".\n";
        else if (!posNeg && input >= start)
            cout << "ERROR: Invalid input. Must be lesser than or equal to " << start << ".\n";
        else
            break;
    } while (true);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (!(input >= min(startRange, endRange) && input <= max(startRange, endRange)))
            cout << "ERROR: Invalid input. Must be from " << startRange << ".." << endRange << ".\n";
        else
            break;
    } while (true);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}