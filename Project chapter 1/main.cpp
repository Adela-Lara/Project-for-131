// ============================================================================
// main.cpp
//
// ============================================================================

#include <iostream>
#include <limits>
#include <string>
#include "DescriptiveStatsCalculator.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

// Precondition:  none.
static void printMenu() {
    cout << "\nDescriptive Statistics Calculator Main Menu\n";
    cout << "========================================================================\n";
    cout << " 0. Exit\n";
    cout << " 1. Configure Dataset to Sample or Polulation\n";
    cout << " 2. Insert sort value(s) to the Dataset\n";
    cout << " 3. Delete value(s) from the Dataset\n";
    cout << "------------------------------------------------------------------------\n";
    cout << " A. Find Minimum                       N. Find Outliers\n";
    cout << " B. Find Maximum                       O. Find Sum of Squares\n";
    cout << " C. Find Range                         P. Find Mean Absolute Deviation\n";
    cout << " D. Find Size                          Q. Find Root Mean Square\n";
    cout << " E. Find Sum                           R. Find Standard Error of Mean\n";
    cout << " F. Find Mean                          S. Find Skewness\n";
    cout << " G. Find Median                        T. Find Kurtosis\n";
    cout << " H. Find Mode(s)                       U. Find Kurtosis Excess\n";
    cout << " I. Find Standard Deviation            V. Find Coefficient of Variation\n";
    cout << " J. Find Variance                      W. Find Relative Standard Deviation\n";
    cout << " K. Find Midrange                      X. Display Frequency Table\n";
    cout << " L. Find Quartiles                     Y. Display ALL statical results\n";
    cout << " M. Find Interquartile Range            Z. Output ALL statical results to text file\n";
    cout << "========================================================================\n\n";
    cout << "Option: ";
}

// Precondition:  none.
// Postcondition: clears any error flags on cin and discards the rest of
//                the current input line, leaving the stream ready for a
//                fresh read.
static void clearInput() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Precondition:  none.
// Postcondition: prompts the user for how many values to insert, reads
//                that many doubles, and inserts each into calc.
static void handleInsert(DescriptiveStatsCalculator& calc) {
    cout << "How many value(s) would you like to insert? ";
    int count;
    if (!(cin >> count) || count <= 0) {
        cout << "Invalid count.\n";
        clearInput();
        return;
    }
    for (int i = 0; i < count; ++i) {
        cout << "  Value " << (i + 1) << ": ";
        double value;
        if (!(cin >> value)) {
            cout << "Invalid value, stopping insertion.\n";
            clearInput();
            return;
        }
        calc.insertValue(value);
    }
    cout << "Inserted. Dataset is now: ";
    calc.displayDataset();
}

// Precondition:  none.
// Postcondition: prompts the user for a value and removes its first
//                occurrence from calc if present.
static void handleDelete(DescriptiveStatsCalculator& calc) {
    cout << "Enter value to delete: ";
    double value;
    if (!(cin >> value)) {
        cout << "Invalid value.\n";
        clearInput();
        return;
    }
    if (calc.deleteValue(value)) {
        cout << "Deleted " << value << ". Dataset is now: ";
        calc.displayDataset();
    }
    else {
        cout << value << " was not found in the dataset.\n";
    }
}

// Precondition:  none.
// Postcondition: prompts the user to choose Sample or Population and
//                configures calc accordingly.
static void handleConfigure(DescriptiveStatsCalculator& calc) {
    cout << "Configure dataset as (1) Sample or (2) Population: ";
    int choice;
    if (!(cin >> choice)) {
        cout << "Invalid choice.\n";
        clearInput();
        return;
    }
    if (choice == 1) {
        calc.configureDatasetType(DescriptiveStatsCalculator::DatasetType::SAMPLE);
        cout << "Dataset configured as Sample.\n";
    }
    else if (choice == 2) {
        calc.configureDatasetType(DescriptiveStatsCalculator::DatasetType::POPULATION);
        cout << "Dataset configured as Population.\n";
    }
    else {
        cout << "Invalid choice, dataset type unchanged.\n";
    }
}

int main() {
    DescriptiveStatsCalculator calc;
    string option;
    bool running = true;

    while (running) {
        cout << "Address of Dynamic array: " << calc.getArrayAddress() << "\n";
        cout << "Dataset: (" << (calc.getDatasetType() == DescriptiveStatsCalculator::DatasetType::SAMPLE
            ? "Sample" : "Population") << ")\n";
        if (calc.getSize() < 2) {
            cout << "\nERROR: Data Set requires at least 2 values.\n";
        }

        printMenu();

        if (!(cin >> option)) {
            break; // EOF or stream failure
        }

        // Normalize a single-character option to uppercase for comparison.
        char opt = option.empty() ? '\0' : static_cast<char>(toupper(option[0]));

        switch (opt) {
        case '0': running = false; cout << "Goodbye!\n"; break;
        case '1': handleConfigure(calc); break;
        case '2': handleInsert(calc); break;
        case '3': handleDelete(calc); break;

        case 'A': calc.findMinimum(); break;
        case 'B': calc.findMaximum(); break;
        case 'C': calc.findRange(); break;
        case 'D': cout << "Size: " << calc.findSize() << endl; break;
        case 'E': calc.findSum(); break;
        case 'F': calc.findMean(); break;
        case 'G': calc.findMedian(); break;
        case 'H': { double* modes = nullptr; calc.findModes(modes); delete[] modes; break; }
        case 'I': calc.findStandardDeviation(); break;
        case 'J': calc.findVariance(); break;
        case 'K': calc.findMidrange(); break;
        case 'L': { double q1, q2, q3; calc.findQuartiles(q1, q2, q3); break; }
        case 'M': calc.findInterquartileRange(); break;
        case 'N': { double* outliers = nullptr; calc.findOutliers(outliers); delete[] outliers; break; }
        case 'O': calc.findSumOfSquares(); break;
        case 'P': calc.findMeanAbsoluteDeviation(); break;
        case 'Q': calc.findRootMeanSquare(); break;
        case 'R': calc.findStandardErrorOfMean(); break;
        case 'S': calc.findSkewness(); break;
        case 'T': calc.findKurtosis(); break;
        case 'U': calc.findKurtosisExcess(); break;
        case 'V': calc.findCoefficientOfVariation(); break;
        case 'W': calc.findRelativeStandardDeviation(); break;
        case 'X': calc.displayFrequencyTable(); break;
        case 'Y': calc.displayAllStatisticalResults(); break;
        case 'Z': {
            cout << "Output filename: ";
            string filename;
            cin >> filename;
            calc.outputAllStatisticalResultsToFile(filename);
            break;
        }

        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
    }

    return 0;
}