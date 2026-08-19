// ============================================================================
// main.cpp
//  this is the menu loop
// ============================================================================

#include <iostream>
#include "DescriptiveStatsCalculator.h"
#include "input.h"

using std::cout;
using std::endl;
using std::string;

// Every character the menu currently accepts. Passed to inputChar() so it
// rejects anything outside this set before main() ever sees the value.
static const string VALID_MENU_OPTIONS = "0123ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Precondition:  none.
// Postcondition: the main menu text has been printed to standard output.
static void printMenu() {
    cout << "\nDescriptive Statistics Calculator Main Menu\n";
    cout << "========================================================================\n";
    cout << " 0. Exit\n";
    cout << " 1. Configure Dataset to Sample or Population\n";
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
}

// Precondition:  none.
// Postcondition: returns true and prints nothing if calc.getSize() >=
//                requiredSize; otherwise prints an error explaining the
//                shortfall and returns false. Callers must skip the
//                operation when this returns false.
static bool hasEnoughData(const DescriptiveStatsCalculator& calc, int requiredSize, const string& operationName) {
    if (calc.getSize() < requiredSize) {
        cout << "ERROR: " << operationName << " requires at least "
            << requiredSize << " value(s); dataset currently has "
            << calc.getSize() << ".\n";
        return false;
    }
    return true;
}

// Precondition:  none.
// Postcondition: prompts (via inputInteger/inputDouble) for how many
//                values to insert and their values, then inserts each
//                into calc in its correct sorted position.
static void handleInsert(DescriptiveStatsCalculator& calc) {
    int count = inputInteger("How many value(s) would you like to insert? ", true); // true = must be positive
    for (int i = 0; i < count; ++i) {
        string prompt = "  Value " + std::to_string(i + 1) + ": ";
        double value = inputDouble(prompt);
        calc.insertValue(value);
    }
    cout << "Inserted. Dataset is now: ";
    calc.displayDataset();
}

// Precondition:  none.
// Postcondition: prompts (via inputDouble) for a value and removes its
//                first occurrence from calc if present.
static void handleDelete(DescriptiveStatsCalculator& calc) {
    double value = inputDouble("Enter value to delete: ");
    if (calc.deleteValue(value)) {
        cout << "Deleted " << value << ". Dataset is now: ";
        calc.displayDataset();
    }
    else {
        cout << value << " was not found in the dataset.\n";
    }
}

// Precondition:  none.
// Postcondition: prompts (via inputInteger with a fixed range) for
//                Sample(1) or Population(2) and configures calc.
static void handleConfigure(DescriptiveStatsCalculator& calc) {
    int choice = inputInteger("Configure dataset as (1) Sample or (2) Population: ", 1, 2);
    if (choice == 1) {
        calc.configureDatasetType(DescriptiveStatsCalculator::DatasetType::SAMPLE);
        cout << "Dataset configured as Sample.\n";
    }
    else {
        calc.configureDatasetType(DescriptiveStatsCalculator::DatasetType::POPULATION);
        cout << "Dataset configured as Population.\n";
    }
}

int main() {
    DescriptiveStatsCalculator calc;
    bool running = true;

    while (running) {
        cout << "Address of Dynamic array: " << calc.getArrayAddress() << "\n";
        cout << "Dataset: (" << (calc.getDatasetType() == DescriptiveStatsCalculator::DatasetType::SAMPLE
            ? "Sample" : "Population") << ")\n";
        if (calc.getSize() < 2) {
            cout << "\nERROR: Data Set requires at least 2 values.\n";
        }

        printMenu();

        char opt = inputChar("Option: ", VALID_MENU_OPTIONS);

        switch (opt) {
        case '0':
            running = false;
            cout << "Goodbye!\n";
            break;

        case '1':
            handleConfigure(calc);
            break;

        case '2':
            handleInsert(calc);
            break;

        case '3':
            handleDelete(calc);
            break;

        case 'A':
            if (hasEnoughData(calc, 1, "Find Minimum")) {
                cout << "Minimum: " << calc.findMinimum() << endl;
            }
            break;

        case 'B':
            if (hasEnoughData(calc, 1, "Find Maximum")) {
                cout << "Maximum: " << calc.findMaximum() << endl;
            }
            break;

        case 'C':
            if (hasEnoughData(calc, 1, "Find Range")) {
                cout << "Range: " << calc.findRange() << endl;
            }
            break;

        case 'D':
            cout << "Size: " << calc.findSize() << endl;
            break;

        case 'E':
            if (hasEnoughData(calc, 1, "Find Sum"))
                cout << "Sum: " << calc.findSum() << endl;
            break;
        case 'F':
            if (hasEnoughData(calc, 1, "Find Mean"))
                cout << "Mean: " << calc.findMean() << endl;
            break;
        case 'G':
            if (hasEnoughData(calc, 1, "Find Median"))
                cout << "Median: " << calc.findMedian() << endl;
            break;
        case 'H': {
            if (hasEnoughData(calc, 1, "Find Modes")) {
                double* modes = nullptr;
                int count = calc.findModes(modes);
                cout << "Mode(s) [" << count << "]: ";
                for (int i = 0; i < count; ++i) {
                    cout << modes[i];
                    if (i < count - 1) cout << ", ";
                }
                cout << endl;
                delete[] modes;
            }
            break;
        }
        case 'I':
            if (hasEnoughData(calc, 2, "Find Standard Deviation"))
                cout << "Standard Deviation: " << calc.findStandardDeviation() << endl;
            break;
        case 'J':
            if (hasEnoughData(calc, 2, "Find Variance"))
                cout << "Variance: " << calc.findVariance() << endl;
            break;
        case 'K':
            if (hasEnoughData(calc, 1, "Find Midrange"))
                cout << "Midrange: " << calc.findMidrange() << endl;
            break;
        case 'L': {
            if (hasEnoughData(calc, 4, "Find Quartiles")) {
                double q1, q2, q3;
                calc.findQuartiles(q1, q2, q3);
                cout << "Q1: " << q1 << "  Q2: " << q2 << "  Q3: " << q3 << endl;
            }
            break;
        }
        case 'M':
            if (hasEnoughData(calc, 4, "Find Interquartile Range"))
                cout << "IQR: " << calc.findInterquartileRange() << endl;
            break;
        case 'N': {
            if (hasEnoughData(calc, 4, "Find Outliers")) {
                double* outliers = nullptr;
                int count = calc.findOutliers(outliers);
                cout << "Outliers [" << count << "]: ";
                for (int i = 0; i < count; ++i) {
                    cout << outliers[i];
                    if (i < count - 1) cout << ", ";
                }
                cout << endl;
                delete[] outliers;
            }
            break;
        }
        case 'O':
            if (hasEnoughData(calc, 1, "Find Sum of Squares"))
                cout << "Sum of Squares: " << calc.findSumOfSquares() << endl;
            break;
        case 'P':
            if (hasEnoughData(calc, 1, "Find Mean Absolute Deviation"))
                cout << "Mean Absolute Deviation: " << calc.findMeanAbsoluteDeviation() << endl;
            break;
        case 'Q':
            if (hasEnoughData(calc, 1, "Find Root Mean Square"))
                cout << "Root Mean Square: " << calc.findRootMeanSquare() << endl;
            break;
        case 'R':
            if (hasEnoughData(calc, 2, "Find Standard Error of Mean"))
                cout << "Standard Error of Mean: " << calc.findStandardErrorOfMean() << endl;
            break;
        case 'S':
            if (hasEnoughData(calc, 3, "Find Skewness"))
                cout << "Skewness: " << calc.findSkewness() << endl;
            break;
        case 'T':
            if (hasEnoughData(calc, 4, "Find Kurtosis"))
                cout << "Kurtosis: " << calc.findKurtosis() << endl;
            break;
        case 'U':
            if (hasEnoughData(calc, 4, "Find Kurtosis Excess"))
                cout << "Kurtosis Excess: " << calc.findKurtosisExcess() << endl;
            break;
        case 'V':
            if (hasEnoughData(calc, 2, "Find Coefficient of Variation"))
                cout << "Coefficient of Variation: " << calc.findCoefficientOfVariation() << endl;
            break;
        case 'W':
            if (hasEnoughData(calc, 2, "Find Relative Standard Deviation"))
                cout << "Relative Standard Deviation: " << calc.findRelativeStandardDeviation() << "%" << endl;
            break;
        case 'X': calc.displayFrequencyTable(); break;
        case 'Y': calc.displayAllStatisticalResults(); break;
        case 'Z': {
            string filename = inputString("Output filename: ", false);
            calc.outputAllStatisticalResultsToFile(filename);
            break;
        }

        default:
            // Unreachable: inputChar() already restricts input to
            // VALID_MENU_OPTIONS before returning, so every valid case
            // above is exhaustive. Kept only as a defensive fallback.
            cout << "Invalid option. Please try again.\n";
            break;
        }
    }

    return 0;
}