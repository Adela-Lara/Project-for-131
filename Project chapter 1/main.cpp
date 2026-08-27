// ============================================================================
// main.cpp
// Descriptive Statistics Calculator - Chapter 1
// ============================================================================

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "DescriptiveStatsCalculator.h"
#include "input.h"

using namespace std;

void showMenu(const DescriptiveStatsCalculator& calc);
void showIntro();
void configureMenu(DescriptiveStatsCalculator& calc);
void insertMenu(DescriptiveStatsCalculator& calc);
void deleteMenu(DescriptiveStatsCalculator& calc);
bool checkEmpty(const DescriptiveStatsCalculator& calc, int minRequired = 2);

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    showIntro();

    DescriptiveStatsCalculator calc;

    do
    {
        try
        {
            system("cls");

            if (calc.getSize() == 0) {
                cout << "\n\tAddress of Dynamic array: 0000000000000000";
            }
            else {
                cout << "\n\tAddress of Dynamic array: " << calc.getArrayAddress();
            }

            cout << "\n\tDataset: ("
                << (calc.getDatasetType() == DescriptiveStatsCalculator::DatasetType::SAMPLE ? "Sample" : "Population")
                << ")\n\t";
            calc.displayDataset();
            showMenu(calc);

            char option = toupper(inputChar("\n\tOption: "));

            switch (option)
            {
            case '0':
                exit(0);

            case '1':
                configureMenu(calc);
                break;

            case '2':
                insertMenu(calc);
                break;

            case '3':
                if (checkEmpty(calc, 1)) break;
                deleteMenu(calc);
                break;

            case 'A':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tMinimum \t\t = " << calc.findMinimum();
                break;

            case 'B':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tMaximum \t\t = " << calc.findMaximum();
                break;

            case 'C':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tRange \t\t\t = " << calc.findRange();
                break;

            case 'D':
                cout << "\n\tSize \t\t\t = " << calc.findSize();
                break;

            case 'E':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tSum \t\t\t = " << calc.findSum();
                break;

            case 'F':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tMean \t\t\t = " << calc.findMean();
                break;

            case 'G':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tMedian \t\t\t = " << calc.findMedian();
                break;

            case 'H': {
                if (checkEmpty(calc, 1)) break;
                double* modes = nullptr;
                int count = calc.findModes(modes);
                cout << "\n\tMode(s) \t\t\t = ";
                if (count == 0 || modes == nullptr) {
                    cout << "No mode (all values unique)";
                }
                else {
                    for (int i = 0; i < count; ++i) {
                        if (i > 0) cout << " ";
                        cout << modes[i];
                    }
                }
                if (modes) delete[] modes;
                break;
            }

            case 'I':
                if (checkEmpty(calc, 2)) break;
                cout << "\n\tStandard Deviation = \t" << calc.findStandardDeviation();
                break;

            case 'J':
                if (checkEmpty(calc, 2)) break;
                cout << "\n\tVariance = \t\t" << calc.findVariance();
                break;

            case 'K':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tMidrange = \t\t" << calc.findMidrange();
                break;

            case 'L': {
                if (checkEmpty(calc, 1)) break;
                double q1 = 0, q2 = 0, q3 = 0;
                calc.findQuartiles(q1, q2, q3);
                cout << "\n\tQuartiles  \t\tQuartiles: ";
                cout << "\n\t\t\t\tQ1 --> " << fixed << setprecision(1) << q1;
                cout << "\n\t\t\t\tQ2 --> " << fixed << setprecision(1) << q2;
                cout << "\n\t\t\t\tQ3 --> " << fixed << setprecision(1) << q3;
                cout.unsetf(ios::fixed);
                cout << setprecision(6);
                break;
            }

            case 'M':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tInterquartile Range = \t" << calc.findInterquartileRange();
                break;

            case 'N': {
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tOutlier(s) = ";
                if (calc.getSize() < 4) {
                    cout << "unknown";
                }
                else {
                    double* outliers = nullptr;
                    int count = calc.findOutliers(outliers);
                    if (count == 0 || outliers == nullptr) {
                        cout << "none";
                    }
                    else {
                        for (int i = 0; i < count; ++i) {
                            if (i > 0) cout << " ";
                            cout << outliers[i];
                        }
                    }
                    if (outliers) delete[] outliers;
                }
                break;
            }

            case 'O':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tSum of Square \t\t = " << calc.findSumOfSquares();
                break;

            case 'P':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tMean Absolute Deviation \t = " << calc.findMeanAbsoluteDeviation();
                break;

            case 'Q':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tRoot Mean Square \t\t = " << calc.findRootMeanSquare();
                break;

            case 'R':
                if (checkEmpty(calc, 2)) break;
                cout << "\n\tStandard Error of the Mean \t = " << calc.findStandardErrorOfMean();
                break;

            case 'S':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tSkewness \t\t = " << calc.findSkewness();
                break;

            case 'T':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tKurtosis \t\t = " << setprecision(9);
                if (calc.getSize() < 4) {
                    cout << "unknown";
                }
                else {
                    cout << calc.findKurtosis();
                }
                cout << setprecision(6);
                break;

            case 'U':
                if (checkEmpty(calc, 1)) break;
                cout << "\n\tKurtosis Excess \t\t = " << setprecision(9);
                if (calc.getSize() < 4) {
                    cout << "unknown";
                }
                else {
                    cout << calc.findKurtosisExcess();
                }
                cout << setprecision(6);
                break;

            case 'V':
                if (checkEmpty(calc, 2)) break;
                cout << "\n\tCoefficient of Variation \t = " << calc.findCoefficientOfVariation();
                break;

            case 'W':
                if (checkEmpty(calc, 2)) break;
                cout << "\n\tRelative Standard Deviation \t = " << calc.findRelativeStandardDeviation();
                break;

            case 'X':
                if (checkEmpty(calc, 1)) break;
                calc.displayFrequencyTable();
                break;

            case 'Y':
                if (checkEmpty(calc, 1)) break;
                calc.displayAllStatisticalResults();
                break;

            case 'Z': {
                if (checkEmpty(calc, 1)) break;
                string filename;
                cout << "\n\tSpecify a text file to save results: ";
                cin >> filename;

                if (filename.find(".txt") == string::npos)
                    filename += ".txt";

                if (calc.outputAllStatisticalResultsToFile(filename)) {
                    cout << "\n\tCONFIRMATION: File, " << filename << ", has been generated.\n";
                }
                else {
                    cerr << "\n\t[File Error] Unable to generate file " << filename << endl;
                }
                break;
            }

            default:
                cout << "\t\tERROR - Invalid option.";
                break;
            }
        }
        catch (const exception& e)
        {
            cerr << "\n\tException Error: " << e.what() << endl;
        }

        cout << "\n";
        system("pause");

    } while (true);

    return EXIT_SUCCESS;
}

void showMenu(const DescriptiveStatsCalculator& calc)
{
    if (calc.getSize() == 0)
    {
        cout << "\n\tERROR: Data Set requires at least 2 values.\n";
    }

    cout << "\n\tDescriptive Statistics Calculator Main Menu\n";
    cout << "\n\t" << string(85, char(205));
    cout << "\n\t0. Exit";
    cout << "\n\t1. Configure Dataset to Sample or Population";
    cout << "\n\t2. Insert sort value(s) to the Dataset";
    cout << "\n\t3. Delete value(s) from the Dataset";
    cout << "\n\t" << string(85, char(196));
    cout << "\n\tA. Find Minimum \t\t\tN. Find Outliers";
    cout << "\n\tB. Find Maximum \t\t\tO. Find Sum of Squares";
    cout << "\n\tC. Find Range \t\t\t\tP. Find Mean Absolute Deviation";
    cout << "\n\tD. Find Size \t\t\t\tQ. Find Root Mean Square";
    cout << "\n\tE. Find Sum \t\t\t\tR. Find Standard Error of Mean";
    cout << "\n\tF. Find Mean \t\t\t\tS. Find Skewness";
    cout << "\n\tG. Find Median \t\t\t\tT. Find Kurtosis";
    cout << "\n\tH. Find Mode(s) \t\t\tU. Find Kurtosis Excess";
    cout << "\n\tI. Find Standard Deviation \t\tV. Find Coefficient of Variation";
    cout << "\n\tJ. Find Variance \t\t\tW. Find Relative Standard Deviation";
    cout << "\n\tK. Find Midrange \t\t\tX. Display Frequency Table";
    cout << "\n\tL. Find Quartiles \t\t\tY. Display ALL statical results";
    cout << "\n\tM. Find Interquartile Range \t\tZ. Output ALL statical results to text file";
    cout << "\n\t" << string(85, char(205)) << "\n";
}

void showIntro()
{
    cout << "\n\tWhat are Descriptive Statistics?";
    cout << "\n\n\tDescriptive statistics summarize certain aspects of a data set (Sample or Population)\n\tusing numeric calculations.";
    cout << "\n\n\thttps://www.calculatorsoup.com/calculators/statistics/descriptivestatistics.php.";
    cout << "\n\nPress any key to continue . . . ";
    cin.get();

    system("cls");
}

void configureMenu(DescriptiveStatsCalculator& calc)
{
    system("cls");

    cout << "\n\n\tIn statistics, Population refers to the entire group of data";
    cout << "\n\tpoints that a study is interested in, while a Sample is a";
    cout << "\n\tsubset of that population that is actually used in the study.";

    cout << "\n\n\tConfigure Dataset Menu";
    cout << "\n\t" << string(80, char(205));
    cout << "\n\t\tA. sample";
    cout << "\n\t\tB. population";
    cout << "\n\t" << string(80, char(196));
    cout << "\n\t\tR. return";
    cout << "\n\t" << string(80, char(205));

    char opt = toupper(inputChar("\n\t\tOption: "));
    switch (opt)
    {
    case 'A':
        cout << "\n\tData Set configured for Sample\n";
        calc.configureDatasetType(DescriptiveStatsCalculator::DatasetType::SAMPLE);
        break;

    case 'B':
        cout << "\n\tData Set configured for Population\n";
        calc.configureDatasetType(DescriptiveStatsCalculator::DatasetType::POPULATION);
        break;

    case 'R':
        break;

    default:
        cout << "\n\tERROR - Invalid option.\n";
        break;
    }
}

void insertMenu(DescriptiveStatsCalculator& calc)
{
    do
    {
        system("cls");
        cout << "\n\n\tInsert (sort) Dataset Menu";
        cout << "\n\t" << string(80, char(205));
        cout << "\n\t\tA. insert a value";
        cout << "\n\t\tB. insert a specified number of random values";
        cout << "\n\t\tC. read data from file and insert values";
        cout << "\n\t" << string(80, char(196));
        cout << "\n\t\tR. return";
        cout << "\n\t" << string(80, char(205));

        switch (toupper(inputChar("\n\n\t\tOption: ")))
        {
        case 'A':
        {
            double val = inputDouble("\n\n\tSpecify a value to be inserted: ");
            calc.insertValue(val);
            cout << "\n\t" << val << " has been inserted...\n";
            break;
        }
        case 'B':
        {
            int count = inputInteger("\n\n\tSpecify a number of values to be randomly generated into the Dataset: ", 1, 1000);
            int maxVal = 100;
            for (int i = 0; i < count; i++)
            {
                int rnd = rand() % (maxVal + 1);
                calc.insertValue(static_cast<double>(rnd));
            }
            cout << "\n\tCONFIRMATION: Inserted " << count << " random values into the Dataset.\n";
            break;
        }
        case 'C':
        {
            ifstream inputFile;
            string fileName;

            cout << "\n\n\tSpecify a data text file name to read: ";
            getline(cin, fileName);

            inputFile.open(fileName);

            if (!inputFile)
            {
                cout << "\n\n\tERROR: File, " << fileName << ", cannot be found.\n";
            }
            else
            {
                double value = 0;
                int count = 0;

                while (inputFile >> value)
                {
                    calc.insertValue(value);
                    count++;
                }

                cout << "\n\tCONFIRMATION: " << count
                    << " element(s) have been read and inserted to the Dataset.\n\n";

                inputFile.close();
            }
            break;
        }
        case 'R':
            return;
        default:
            cout << "\n\tInvalid Option.\n";
            break;
        }

        cout << "\n\t";
        system("pause");

    } while (true);
}

void deleteMenu(DescriptiveStatsCalculator& calc)
{
    do
    {
        system("cls");
        cout << "\n\tDelete Dataset Menu";
        cout << "\n\t" << string(80, char(205));
        cout << "\n\t\tA. delete a value";
        cout << "\n\t\tB. delete a range of values";
        cout << "\n\t\tC. delete all values";
        cout << "\n\t" << string(80, char(196));
        cout << "\n\t\tR. return";
        cout << "\n\t" << string(80, char(205));

        switch (toupper(inputChar("\n\t\tOption: ", "ABCR")))
        {
        case 'A':
        {
            double val = inputDouble("\n\tSpecify a value to find and be deleted from the Dataset: ");
            cout << "\n\tDelete *-all elements or 1-one element found with value " << val << ": ";
            char option = inputChar(" ");
            switch (option)
            {
            case '1':
            {
                if (calc.deleteValue(val))
                {
                    cout << "\n\tCONFIRMATION: One element " << val << " has been found and deleted.\n";
                }
                else
                {
                    cout << "\n\n\tERROR: No element " << val << " has been found and deleted.\n";
                }
                break;
            }
            case '*':
            {
                int removed = calc.deleteAllOccurrences(val);
                if (removed > 0)
                {
                    cout << "\n\tCONFIRMATION: " << removed << " instance(s) of element: " << val << " have been found and deleted.\n";
                }
                else
                {
                    cout << "\n\n\tERROR: No element " << val << " has been found and deleted.\n";
                }
                break;
            }
            default:
                cout << "\n\tERROR: Invalid input. Must be one of '*1' character.\n";
                break;
            }
            break;
        }
        case 'B':
        {
            double startVal = inputDouble("\n\tSpecify a starting value to be deleted from the Dataset: ");
            double endVal = inputDouble("\n\tSpecify an ending value to be deleted from the Dataset: ");
            if (endVal < startVal)
            {
                cout << "\n\tERROR: The ending value (" << endVal << ") cannot be smaller than the starting value (" << startVal << ").\n";
                break;
            }
            int count = calc.deleteRange(startVal, endVal);
            if (count > 0)
            {
                cout << "\n\tCONFIRMATION: " << count << " element(s) in range(" << startVal << ".." << endVal << ") have been deleted.\n";
            }
            else
            {
                cout << "\n\tNo elements found in range(" << startVal << ".." << endVal << ").\n";
            }
            break;
        }
        case 'C':
            calc.clear();
            cout << "\n\tDataset has been purged of all elements.\n";
            break;
        case 'R':
            return;
        default:
            cout << "\n\tERROR: Invalid input. Must be one of 'ABCR' character.\n";
            break;
        }

        cout << "\n\n\t";
        system("pause");

    } while (true);
}

bool checkEmpty(const DescriptiveStatsCalculator& calc, int minRequired)
{
    if (calc.getSize() == 0)
    {
        cout << "\n\tERROR: Dataset is empty.\n";
        return true;
    }
    if (calc.getSize() < minRequired)
    {
        cout << "\n\tERROR: Requires at least " << minRequired << " data values.\n";
        return true;
    }
    return false;
}