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
// Construction / Destruction / Rule of Three
// ---------------------------------------------------------------------

DescriptiveStatsCalculator::DescriptiveStatsCalculator()
    : data(nullptr), size(0), capacity(DEFAULT_CAPACITY), datasetType(DatasetType::SAMPLE) {
    data = new double[capacity];
}

DescriptiveStatsCalculator::DescriptiveStatsCalculator(int initialCapacity)
    : data(nullptr), size(0), capacity(initialCapacity > 0 ? initialCapacity : DEFAULT_CAPACITY),
    datasetType(DatasetType::SAMPLE) {
    data = new double[capacity];
}

DescriptiveStatsCalculator::DescriptiveStatsCalculator(const DescriptiveStatsCalculator& other)
    : data(nullptr), size(other.size), capacity(other.capacity), datasetType(other.datasetType) {
    data = new double[capacity];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

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

DescriptiveStatsCalculator::~DescriptiveStatsCalculator() {
    delete[] data;
    data = nullptr;
}

// ---------------------------------------------------------------------
// Container / Configuration Operations
// ---------------------------------------------------------------------

void DescriptiveStatsCalculator::configureDatasetType(DatasetType type) {
    datasetType = type;
}

DescriptiveStatsCalculator::DatasetType DescriptiveStatsCalculator::getDatasetType() const {
    return datasetType;
}

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

void DescriptiveStatsCalculator::insertValues(const double values[], int count) {
    for (int i = 0; i < count; ++i) {
        insertValue(values[i]);
    }
}

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

int DescriptiveStatsCalculator::deleteRange(double start, double end) {
    if (start > end) {
        std::swap(start, end);
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

void DescriptiveStatsCalculator::clear() {
    size = 0;
}

bool DescriptiveStatsCalculator::isEmpty() const {
    return size == 0;
}

int DescriptiveStatsCalculator::getSize() const {
    return size;
}

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

const double* DescriptiveStatsCalculator::getArrayAddress() const {
    return data;
}

// ---------------------------------------------------------------------
// Statistical Functions: Fully Implemented (A, B, C, D)
// ---------------------------------------------------------------------

double DescriptiveStatsCalculator::findMinimum() const {
    if (size < 1) return 0.0;
    return data[0];
}

double DescriptiveStatsCalculator::findMaximum() const {
    if (size < 1) return 0.0;
    return data[size - 1];
}

double DescriptiveStatsCalculator::findRange() const {
    if (size < 1) return 0.0;
    return findMaximum() - findMinimum();
}

int DescriptiveStatsCalculator::findSize() const {
    return size;
}

// ---------------------------------------------------------------------
// Statistical Functions: Placeholders for Team Implementation (E -> Z)
// ---------------------------------------------------------------------

double DescriptiveStatsCalculator::findSum() const {
    // TODO: To be implemented by team
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum;
}

double DescriptiveStatsCalculator::findMean() const {
    // TODO: To be implemented by team
    return findSum() / size;
    
}

double DescriptiveStatsCalculator::findMedian() const {
    // TODO: To be implemented by team
    cout << "\n\t[Not yet implemented: findMedian]\n";
    return 0.0;
}

int DescriptiveStatsCalculator::findModes(double*& modes) const {
    // TODO: To be implemented by team
    cout << "\n\t[Not yet implemented: findModes]\n";
    modes = nullptr;
    return 0;
}

double DescriptiveStatsCalculator::findStandardDeviation() const {
    // TODO: To be implemented by team
    double mean = findMean();
    double sum = 0.0;

    for (int i = 0; i < size; i++) {
        double difference = data[i] - mean;
        sum += difference * difference;
    }
    if (datasetType == DatasetType::SAMPLE) {
        double variance = sum / (size - 1);
        double standardDeviationSample = std::sqrt(variance);
        return standardDeviationSample;
    }
    else {
        double variance = sum / size;
        double standardDeviationPop = std::sqrt(variance);
        return standardDeviationPop;
    }
}

double DescriptiveStatsCalculator::findVariance() const {
    // TODO: To be implemented by team
    cout << "\n\t[Not yet implemented: findVariance]\n";
    return 0.0;
}

double DescriptiveStatsCalculator::findMidrange() const {
    // TODO: To be implemented by team
    cout << "\n\t[Not yet implemented: findMidrange]\n";
    return 0.0;
}

void DescriptiveStatsCalculator::findQuartiles(double& q1, double& q2, double& q3) const {
    // TODO: To be implemented by team
    cout << "\n\t[Not yet implemented: findQuartiles]\n";
    q1 = q2 = q3 = 0.0;
}

double DescriptiveStatsCalculator::findInterquartileRange() const {
    // TODO: To be implemented by team
    cout << "\n\t[Not yet implemented: findInterquartileRange]\n";
    return 0.0;
}

int DescriptiveStatsCalculator::findOutliers(double*& outliers) const {
    // TODO: To be implemented by team
    cout << "\n\t[Not yet implemented: findOutliers]\n";
    outliers = nullptr;
    return 0;
}

double DescriptiveStatsCalculator::findSumOfSquares() const {
    // TODO: To be implemented by team
    cout << "\n\t[Not yet implemented: findSumOfSquares]\n";
    return 0.0;
}

double DescriptiveStatsCalculator::findMeanAbsoluteDeviation() const {
    // TODO: To be implemented by team
    cout << "\n\t[Not yet implemented: findMeanAbsoluteDeviation]\n";
    return 0.0;
}

double DescriptiveStatsCalculator::findRootMeanSquare() const {
    // TODO: To be implemented by team
    if (size == 0)
        return 0;
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        double sumOfSquare = data[i] * data[i];
        sum += sumOfSquare;
    }
    return std::sqrt(sum / size);
}

double DescriptiveStatsCalculator::findStandardErrorOfMean() const {
    // TODO: To be implemented by team
    if (size == 0)
        return 0.0;

    return findStandardDeviation() / std::sqrt(size);
}

double DescriptiveStatsCalculator::findSkewness() const {
    // TODO: To be implemented by team
    double mean = findMean();
    double stdDev = findStandardDeviation();
    double sum = 0.0;
    int n = size;
    if (size < 3)
        return 0;
    if (stdDev == 0)
        return 0.0;

    if (datasetType == DatasetType::SAMPLE) {
        for (int i = 0; i < size; i++) {
            double difference = data[i] - mean;
            double division = difference / stdDev;

            sum += division * division * division;
        }

        double numerator = static_cast<double>(n);
        double denominator = static_cast<double>(n - 1) * (n - 2);
        double equationOfN = numerator / denominator;
        return sum * equationOfN;
    }
    else {
        double sum = 0.0;
        for (int i = 0; i < size; i++) {
            double difference = data[i] - mean;
            sum += difference * difference * difference;

        }
        double standardDiviationFourth = stdDev * stdDev * stdDev;
        return (sum / (size * standardDiviationFourth));
    }
}

double DescriptiveStatsCalculator::findKurtosis() const {
    double mean = findMean();
    double stdDev = findStandardDeviation();
    double sum = 0.0;
    int n = size;
    if (size < 4)
        return 0;

    if (datasetType == DatasetType::SAMPLE) {
        for (int i = 0; i < size; i++) {
            double difference = (data[i] - mean);
            double division = difference / stdDev;

            sum += division * division * division * division;
        }
        double numerator = static_cast<double>(n) * (n + 1);
        double denominator = static_cast<double>(n - 1) * (n - 2) * (n - 3);
        double equationOfN = numerator / denominator;
        return  sum * equationOfN;
    }
    else {
        for (int i = 0; i < size; i++) {
            double difference = data[i] - mean;
            sum += (difference * difference * difference * difference);
        }
        double standardDeviationFourth = stdDev * stdDev * stdDev * stdDev;
        return (sum / (size * standardDeviationFourth) );
    }
}

double DescriptiveStatsCalculator::findKurtosisExcess() const {
    // TODO: To be implemented by team
    int n = size;
    if (size > 4)
        return 0;

    if (datasetType == DatasetType::SAMPLE) {
        double numerator = static_cast<double>(3) * (n - 1) * (n - 1);
        double denominator = static_cast<double>(n - 2) * (n - 3);
        double equationOfN = numerator / denominator;

        return findKurtosis() - equationOfN;
    }
    else {
        return findKurtosis() - 3.0;
    }
}

double DescriptiveStatsCalculator::findCoefficientOfVariation() const {
    // TODO: To be implemented by team
    cout << "\n\t[Not yet implemented: findCoefficientOfVariation]\n";
    return 0.0;
}

double DescriptiveStatsCalculator::findRelativeStandardDeviation() const {
    // TODO: To be implemented by team
    cout << "\n\t[Not yet implemented: findRelativeStandardDeviation]\n";
    return 0.0;
}

void DescriptiveStatsCalculator::displayFrequencyTable(std::ostream& out) const {
    // TODO: To be implemented by team
    out << "\n\t[Not yet implemented: displayFrequencyTable]\n";
}

void DescriptiveStatsCalculator::displayAllStatisticalResults(std::ostream& out) const {
    // TODO: To be implemented by team
    out << "\n\t[Not yet implemented: displayAllStatisticalResults]\n";
}

bool DescriptiveStatsCalculator::outputAllStatisticalResultsToFile(const std::string& filename) const {
    // TODO: To be implemented by team
    (void)filename;
    cout << "\n\t[Not yet implemented: outputAllStatisticalResultsToFile]\n";
    return false;
}