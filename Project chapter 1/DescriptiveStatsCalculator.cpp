#include "DescriptiveStatsCalculator.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

// ---------------------------------------------------------------------
// Construction / Destruction (Rule of Three)
// ---------------------------------------------------------------------

// Precondition:  none
// Postcondition: initializes empty dataset with default capacity and SAMPLE type
DescriptiveStatsCalculator::DescriptiveStatsCalculator()
    : data(nullptr), size(0), capacity(DEFAULT_CAPACITY), datasetType(DatasetType::SAMPLE) {
    data = new double[capacity];
}

// Precondition:  initialCapacity >= 1
// Postcondition: initializes empty dataset with specified initial capacity
DescriptiveStatsCalculator::DescriptiveStatsCalculator(int initialCapacity)
    : data(nullptr), size(0), capacity(initialCapacity > 0 ? initialCapacity : DEFAULT_CAPACITY),
    datasetType(DatasetType::SAMPLE) {
    data = new double[capacity];
}

// Precondition:  other is a valid DescriptiveStatsCalculator object
// Postcondition: creates an independent deep copy of other
DescriptiveStatsCalculator::DescriptiveStatsCalculator(const DescriptiveStatsCalculator& other)
    : data(nullptr), size(other.size), capacity(other.capacity), datasetType(other.datasetType) {
    data = new double[capacity];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

// Precondition:  other is a valid DescriptiveStatsCalculator object
// Postcondition: releases current memory and deep copies other (safe on self-assignment)
DescriptiveStatsCalculator& DescriptiveStatsCalculator::operator=(const DescriptiveStatsCalculator& other) {
    if (this == &other) {
        return *this;
    }
    double* newData = new double[other.capacity];
    for (int i = 0; i < other.size; ++i) {
        newData[i] = other.data[i];
    }
    delete[] data;
    data = newData;
    size = other.size;
    capacity = other.capacity;
    datasetType = other.datasetType;
    return *this;
}

// Precondition:  none
// Postcondition: deallocates all dynamically allocated memory
DescriptiveStatsCalculator::~DescriptiveStatsCalculator() {
    delete[] data;
    data = nullptr;
}

// ---------------------------------------------------------------------
// Configuration & Container Operations (Options 1, 2, 3)
// ---------------------------------------------------------------------

// Precondition:  type is SAMPLE or POPULATION
// Postcondition: sets dataset calculation mode
void DescriptiveStatsCalculator::configureDatasetType(DatasetType type) {
    datasetType = type;
}

// Precondition:  none
// Postcondition: returns the current DatasetType
DescriptiveStatsCalculator::DatasetType DescriptiveStatsCalculator::getDatasetType() const {
    return datasetType;
}

// Precondition:  newCapacity >= size
// Postcondition: reallocates data array to newCapacity preserving elements
void DescriptiveStatsCalculator::resize(int newCapacity) {
    if (newCapacity < size) {
        newCapacity = size;
    }
    double* newData = new double[newCapacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

// Precondition:  none
// Postcondition: returns binary search index for sorted insertion
int DescriptiveStatsCalculator::findInsertPosition(double value) const {
    int low = 0;
    int high = size;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (data[mid] < value) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }
    return low;
}

// Precondition:  none
// Postcondition: inserts value in ascending sorted order, growing capacity if full
void DescriptiveStatsCalculator::insertValue(double value) {
    if (size >= capacity) {
        resize(capacity * 2);
    }
    int pos = findInsertPosition(value);
    for (int i = size; i > pos; --i) {
        data[i] = data[i - 1];
    }
    data[pos] = value;
    ++size;
}

// Precondition:  values != nullptr, count >= 0
// Postcondition: inserts count elements in ascending sorted order
void DescriptiveStatsCalculator::insertValues(const double values[], int count) {
    for (int i = 0; i < count; ++i) {
        insertValue(values[i]);
    }
}

// Precondition:  none
// Postcondition: removes first occurrence of value; returns true if found, false otherwise
bool DescriptiveStatsCalculator::deleteValue(double value) {
    const double EPSILON = 1e-9;
    for (int i = 0; i < size; ++i) {
        if (std::abs(data[i] - value) < EPSILON) {
            for (int j = i; j < size - 1; ++j) {
                data[j] = data[j + 1];
            }
            --size;
            return true;
        }
    }
    return false;
}

// Precondition:  none
// Postcondition: removes all occurrences of value; returns number of elements removed
int DescriptiveStatsCalculator::deleteAllOccurrences(double value) {
    const double EPSILON = 1e-9;
    int removed = 0;
    int writeIndex = 0;
    for (int readIndex = 0; readIndex < size; ++readIndex) {
        if (std::abs(data[readIndex] - value) < EPSILON) {
            ++removed;
        }
        else {
            data[writeIndex++] = data[readIndex];
        }
    }
    size = writeIndex;
    return removed;
}

// Precondition:  start <= end
// Postcondition: removes all values in [start, end]; returns number of elements removed
int DescriptiveStatsCalculator::deleteRange(double start, double end) {
    if (start > end) {
        return 0;
    }
    int newSize = 0;
    int removed = 0;
    for (int i = 0; i < size; ++i) {
        if (data[i] >= start && data[i] <= end) {
            ++removed;
        }
        else {
            data[newSize++] = data[i];
        }
    }
    size = newSize;
    return removed;
}

// Precondition:  none
// Postcondition: empties dataset (size = 0)
void DescriptiveStatsCalculator::clear() {
    size = 0;
}

// Precondition:  none
// Postcondition: returns true if size == 0, false otherwise
bool DescriptiveStatsCalculator::isEmpty() const {
    return size == 0;
}

// Precondition:  none
// Postcondition: returns number of stored elements
int DescriptiveStatsCalculator::getSize() const {
    return size;
}

// Precondition:  none
// Postcondition: displays formatted elements to standard output
void DescriptiveStatsCalculator::displayDataset() const {
    if (size == 0) {
        cout << "(empty)\n";
        return;
    }
    const int perLine = 15;
    cout << "\n\t";
    for (int i = 0; i < size; ++i) {
        cout << std::setw(6) << data[i];
        if ((i + 1) % perLine == 0 && i != size - 1) {
            cout << "\n\t";
        }
    }
    cout << "\n";
}

// Precondition:  none
// Postcondition: returns read-only pointer to internal dynamic array
const double* DescriptiveStatsCalculator::getArrayAddress() const {
    return data;
}

// ---------------------------------------------------------------------
// Statistical Functions (Options A -> Z)
// ---------------------------------------------------------------------

// Precondition:  size >= 1
// Postcondition: returns minimum value in dataset
double DescriptiveStatsCalculator::findMinimum() const {
    if (size < 1) return 0.0;
    return data[0];
}

// Precondition:  size >= 1
// Postcondition: returns maximum value in dataset
double DescriptiveStatsCalculator::findMaximum() const {
    if (size < 1) return 0.0;
    return data[size - 1];
}

// Precondition:  size >= 1
// Postcondition: returns range (max - min)
double DescriptiveStatsCalculator::findRange() const {
    if (size < 1) return 0.0;
    return findMaximum() - findMinimum();
}

// Precondition:  none
// Postcondition: returns size of dataset
int DescriptiveStatsCalculator::findSize() const {
    return size;
}

// Precondition:  size >= 1
// Postcondition: returns sum of all elements
double DescriptiveStatsCalculator::findSum() const {
    if (size < 1) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += data[i];
    }
    return sum;
}

// Precondition:  size >= 1
// Postcondition: returns arithmetic mean
double DescriptiveStatsCalculator::findMean() const {
    if (size < 1) return 0.0;
    return findSum() / size;
}

// Precondition:  size >= 1
// Postcondition: returns median of dataset
double DescriptiveStatsCalculator::findMedian() const {
    if (size < 1) return 0.0;
    if (size % 2 == 1) {
        return data[size / 2];
    }
    return (data[size / 2 - 1] + data[size / 2]) / 2.0;
}

// Precondition:  size >= 1
// Postcondition: allocates modes array with highest frequency values; returns count
int DescriptiveStatsCalculator::findModes(double*& modes) const {
    modes = nullptr;
    if (size < 1) return 0;

    int maxFrequency = 1;
    int currentFrequency = 1;

    for (int i = 1; i < size; ++i) {
        if (std::abs(data[i] - data[i - 1]) < 1e-9) {
            ++currentFrequency;
        }
        else {
            if (currentFrequency > maxFrequency) {
                maxFrequency = currentFrequency;
            }
            currentFrequency = 1;
        }
    }

    if (currentFrequency > maxFrequency) {
        maxFrequency = currentFrequency;
    }

    if (maxFrequency == 1) return 0;

    int modeCount = 0;
    currentFrequency = 1;

    for (int i = 1; i <= size; ++i) {
        if (i < size && std::abs(data[i] - data[i - 1]) < 1e-9) {
            ++currentFrequency;
        }
        else {
            if (currentFrequency == maxFrequency) {
                ++modeCount;
            }
            currentFrequency = 1;
        }
    }

    modes = new double[modeCount];
    int modeIndex = 0;
    currentFrequency = 1;

    for (int i = 1; i <= size; ++i) {
        if (i < size && std::abs(data[i] - data[i - 1]) < 1e-9) {
            ++currentFrequency;
        }
        else {
            if (currentFrequency == maxFrequency) {
                modes[modeIndex++] = data[i - 1];
            }
            currentFrequency = 1;
        }
    }

    return modeCount;
}

// Precondition:  size >= 2
// Postcondition: returns variance (sample or population)
double DescriptiveStatsCalculator::findVariance() const {
    if (size < 2) return 0.0;

    double mean = findMean();
    double sumOfSquaredDifferences = 0.0;

    for (int i = 0; i < size; ++i) {
        double difference = data[i] - mean;
        sumOfSquaredDifferences += difference * difference;
    }

    if (datasetType == DatasetType::SAMPLE) {
        return sumOfSquaredDifferences / (size - 1);
    }

    return sumOfSquaredDifferences / size;
}

// Precondition:  size >= 2
// Postcondition: returns standard deviation (sample or population)
double DescriptiveStatsCalculator::findStandardDeviation() const {
    if (size < 2) return 0.0;
    return std::sqrt(findVariance());
}

// Precondition:  size >= 1
// Postcondition: returns midrange (min + max) / 2
double DescriptiveStatsCalculator::findMidrange() const {
    if (size < 1) return 0.0;
    return (findMinimum() + findMaximum()) / 2.0;
}

// Precondition:  0 <= lo < hi <= size
// Postcondition: returns median of subrange [lo..hi-1]
double DescriptiveStatsCalculator::medianInRange(int lo, int hi) const {
    int len = hi - lo;
    if (len <= 0) return 0.0;
    if (len % 2 == 1) {
        return data[lo + len / 2];
    }
    return (data[lo + len / 2 - 1] + data[lo + len / 2]) / 2.0;
}

// Precondition:  size >= 4
// Postcondition: sets q1, q2, q3 to the 1st, 2nd, and 3rd quartiles
void DescriptiveStatsCalculator::findQuartiles(double& q1, double& q2, double& q3) const {
    if (size == 0) {
        q1 = q2 = q3 = 0.0;
        return;
    }
    q2 = findMedian();
    int mid = size / 2;
    q1 = medianInRange(0, mid);
    if (size % 2 == 0) {
        q3 = medianInRange(mid, size);
    }
    else {
        q3 = medianInRange(mid + 1, size);
    }
}

// Precondition:  size >= 4
// Postcondition: returns interquartile range (Q3 - Q1)
double DescriptiveStatsCalculator::findInterquartileRange() const {
    double q1 = 0.0, q2 = 0.0, q3 = 0.0;
    findQuartiles(q1, q2, q3);
    return q3 - q1;
}

// Precondition:  size >= 4
// Postcondition: allocates outliers array with values outside [Q1-1.5*IQR, Q3+1.5*IQR]; returns count
int DescriptiveStatsCalculator::findOutliers(double*& outliers) const {
    outliers = nullptr;
    if (size < 4) return 0;

    double q1 = 0.0, q2 = 0.0, q3 = 0.0;
    findQuartiles(q1, q2, q3);
    double iqr = q3 - q1;
    double lowerFence = q1 - (1.5 * iqr);
    double upperFence = q3 + (1.5 * iqr);

    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (data[i] < lowerFence || data[i] > upperFence) {
            ++count;
        }
    }

    if (count == 0) return 0;

    outliers = new double[count];
    int index = 0;
    for (int i = 0; i < size; ++i) {
        if (data[i] < lowerFence || data[i] > upperFence) {
            outliers[index++] = data[i];
        }
    }

    return count;
}

// Precondition:  size >= 1
// Postcondition: returns sum of squared deviations from mean
double DescriptiveStatsCalculator::findSumOfSquares() const {
    if (size < 1) return 0.0;
    double mean = findMean();
    double ss = 0.0;
    for (int i = 0; i < size; ++i) {
        double diff = data[i] - mean;
        ss += diff * diff;
    }
    return ss;
}

// Precondition:  size >= 1
// Postcondition: returns mean absolute deviation (MAD)
double DescriptiveStatsCalculator::findMeanAbsoluteDeviation() const {
    if (size < 1) return 0.0;
    double mean = findMean();
    double deviation = 0.0;
    for (int i = 0; i < size; ++i) {
        deviation += std::abs(data[i] - mean);
    }
    return deviation / size;
}

// Precondition:  size >= 1
// Postcondition: returns root mean square (RMS)
double DescriptiveStatsCalculator::findRootMeanSquare() const {
    if (size < 1) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += data[i] * data[i];
    }
    return std::sqrt(sum / size);
}

// Precondition:  size >= 2
// Postcondition: returns standard error of the mean
double DescriptiveStatsCalculator::findStandardErrorOfMean() const {
    if (size < 2) return 0.0;
    return findStandardDeviation() / std::sqrt(size);
}

// Precondition:  size >= 3
// Postcondition: returns skewness coefficient
double DescriptiveStatsCalculator::findSkewness() const {
    if (size < 3) return 0.0;

    double mean = findMean();
    double stdDev = findStandardDeviation();
    if (stdDev == 0.0) return 0.0;

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        double z = (data[i] - mean) / stdDev;
        sum += z * z * z;
    }

    if (datasetType == DatasetType::SAMPLE) {
        double n = static_cast<double>(size);
        double factor = n / ((n - 1.0) * (n - 2.0));
        return factor * sum;
    }

    return sum / size;
}

// Precondition:  size >= 4
// Postcondition: returns kurtosis coefficient
double DescriptiveStatsCalculator::findKurtosis() const {
    if (size < 4) return 0.0;

    double mean = findMean();
    double stdDev = findStandardDeviation();
    if (stdDev == 0.0) return 0.0;

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        double z = (data[i] - mean) / stdDev;
        sum += z * z * z * z;
    }

    if (datasetType == DatasetType::SAMPLE) {
        double n = static_cast<double>(size);
        double factor = (n * (n + 1.0)) / ((n - 1.0) * (n - 2.0) * (n - 3.0));
        return factor * sum;
    }

    return sum / size;
}

// Precondition:  size >= 4
// Postcondition: returns excess kurtosis
double DescriptiveStatsCalculator::findKurtosisExcess() const {
    if (size < 4) return 0.0;

    double kurt = findKurtosis();
    if (datasetType == DatasetType::POPULATION) {
        return kurt - 3.0;
    }

    double n = static_cast<double>(size);
    double correction = 3.0 * std::pow(n - 1.0, 2) / ((n - 2.0) * (n - 3.0));
    return kurt - correction;
}

// Precondition:  size >= 2, mean != 0
// Postcondition: returns coefficient of variation (stdev / mean)
double DescriptiveStatsCalculator::findCoefficientOfVariation() const {
    double mean = findMean();
    if (std::abs(mean) < 1e-9) return 0.0;
    return findStandardDeviation() / mean;
}

// Precondition:  size >= 2, mean != 0
// Postcondition: returns relative standard deviation percentage (CV * 100)
double DescriptiveStatsCalculator::findRelativeStandardDeviation() const {
    return findCoefficientOfVariation() * 100.0;
}

// ---------------------------------------------------------------------
// Display and File Output
// ---------------------------------------------------------------------

// Precondition:  out stream is valid
// Postcondition: prints frequency distribution table to out
void DescriptiveStatsCalculator::displayFrequencyTable(std::ostream& out) const {
    if (size == 0) {
        out << "\n\tNo data to display.\n";
        return;
    }

    out << std::right << std::setw(13) << "Value"
        << std::setw(14) << "Frequency"
        << std::setw(14) << "Frequency %" << std::endl;

    int i = 0;
    const double EPSILON = 1e-9;

    while (i < size) {
        double currentValue = data[i];
        int frequency = 1;

        while (i + frequency < size &&
            std::abs(data[i + frequency] - currentValue) < EPSILON) {
            frequency++;
        }

        double frequencyPercent = (static_cast<double>(frequency) * 100.0) / size;

        std::ios::fmtflags oldFlags = out.flags();
        std::streamsize oldPrecision = out.precision();

        out << std::right << std::setw(13) << currentValue
            << std::setw(14) << frequency
            << std::setw(14) << std::fixed << std::setprecision(1) << frequencyPercent << std::endl;

        out.flags(oldFlags);
        out.precision(oldPrecision);

        i += frequency;
    }
}

// Precondition:  out stream is valid
// Postcondition: prints all statistical metrics and frequency table to out
void DescriptiveStatsCalculator::displayAllStatisticalResults(std::ostream& out) const {
    if (size == 0) {
        out << "\n\tDataset is empty.\n";
        return;
    }

    out << "\n\tMinimum \t\t\t = " << findMinimum();
    out << "\n\tMaximum \t\t\t = " << findMaximum();
    out << "\n\tRange \t\t\t\t = " << findRange();
    out << "\n\tSize \t\t\t\t = " << findSize();
    out << "\n\tSum \t\t\t\t = " << findSum();
    out << "\n\tMean \t\t\t\t = " << findMean();
    out << "\n\tMedian \t\t\t\t = " << findMedian();

    double* modes = nullptr;
    int modeCount = findModes(modes);

    out << "\n\tMode(s) \t\t\t = ";
    if (modeCount > 0 && modes != nullptr) {
        for (int i = 0; i < modeCount; i++) {
            if (i > 0) out << " ";
            out << modes[i];
        }
    }
    else {
        out << "No mode (all values unique)";
    }
    delete[] modes;

    out << "\n\tStandard Deviation \t\t = " << findStandardDeviation();
    out << "\n\tVariance \t\t\t = " << findVariance();
    out << "\n\tMidrange \t\t\t = " << findMidrange();

    double q1 = 0.0, q2 = 0.0, q3 = 0.0;
    findQuartiles(q1, q2, q3);

    std::ios::fmtflags oldFlags = out.flags();
    std::streamsize oldPrecision = out.precision();

    out << "\n\tQuartiles \t\t\t Quartiles:";
    out << "\n\t\t\t\t\t Q1 --> " << std::fixed << std::setprecision(1) << q1;
    out << "\n\t\t\t\t\t Q2 --> " << std::fixed << std::setprecision(1) << q2;
    out << "\n\t\t\t\t\t Q3 --> " << std::fixed << std::setprecision(1) << q3;

    out.flags(oldFlags);
    out.precision(oldPrecision);

    out << "\n\tInterquartile Range \t\t = " << findInterquartileRange();

    double* outliers = nullptr;
    int outlierCount = findOutliers(outliers);

    out << "\n\tOutliers \t\t\t = ";
    if (size < 4) {
        out << "unknown";
    }
    else if (outlierCount == 0 || outliers == nullptr) {
        out << "none";
    }
    else {
        for (int i = 0; i < outlierCount; i++) {
            if (i > 0) out << " ";
            out << outliers[i];
        }
    }
    delete[] outliers;

    out << "\n\tSum of Squares \t\t\t = " << findSumOfSquares();
    out << "\n\tMean Absolute Deviation \t = " << findMeanAbsoluteDeviation();
    out << "\n\tRoot Mean Square \t\t = " << findRootMeanSquare();
    out << "\n\tStandard Error of the Mean \t = " << findStandardErrorOfMean();
    out << "\n\tSkewness \t\t\t = " << findSkewness();

    out << "\n\tKurtosis \t\t\t = ";
    if (size < 4) {
        out << "unknown";
    }
    else {
        out << std::setprecision(9) << findKurtosis();
    }

    out << "\n\tKurtosis Excess \t\t = ";
    if (size < 4) {
        out << "unknown";
    }
    else {
        out << std::setprecision(9) << findKurtosisExcess();
    }

    out.flags(oldFlags);
    out.precision(oldPrecision);

    out << "\n\tCoefficient of Variation \t = " << findCoefficientOfVariation();
    out << "\n\tRelative Standard Deviation \t = " << findRelativeStandardDeviation();

    out << "\n\n\tFrequency Table\n";
    displayFrequencyTable(out);
}

// Precondition:  filename is writable
// Postcondition: writes all statistical results to filename; returns true on success
bool DescriptiveStatsCalculator::outputAllStatisticalResultsToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile) {
        return false;
    }
    displayAllStatisticalResults(outputFile);
    outputFile.close();
    return true;
}