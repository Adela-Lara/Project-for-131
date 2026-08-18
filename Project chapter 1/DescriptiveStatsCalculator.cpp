// ============================================================================
// DescriptiveStatsCalculator.cpp
//
// Container logic (constructors, insert, delete, resize) is fully
// implemented below. Statistical functions (findMinimum ... 
// outputAllStatisticalResultsToFile) are intentionally left as stubs that
// print "[Not yet implemented]" so the menu compiles and runs end-to-end
// while those pieces are filled in one at a time.
// ============================================================================

#include "DescriptiveStatsCalculator.h"
#include <iostream>
#include <fstream>

using std::cout;
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
        return *this; // guard against self-assignment
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
// Container / configuration operations
// ---------------------------------------------------------------------

void DescriptiveStatsCalculator::configureDatasetType(DatasetType type) {
    datasetType = type;
}

DescriptiveStatsCalculator::DatasetType DescriptiveStatsCalculator::getDatasetType() const {
    return datasetType;
}

void DescriptiveStatsCalculator::resize(int newCapacity) {
    if (newCapacity < size) {
        newCapacity = size; // never shrink below current element count
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
    int high = size; // upper bound is one-past-the-end
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (data[mid] < value) {
            low = mid + 1;
        } else {
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
    for (int i = 0; i < size; ++i) {
        if (data[i] == value) {
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
    int removed = 0;
    int writeIndex = 0;
    for (int readIndex = 0; readIndex < size; ++readIndex) {
        if (data[readIndex] == value) {
            ++removed;
        } else {
            data[writeIndex++] = data[readIndex];
        }
    }
    size = writeIndex;
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
        cout << "(Dataset is empty)" << endl;
        return;
    }
    cout << "[ ";
    for (int i = 0; i < size; ++i) {
        cout << data[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

const double* DescriptiveStatsCalculator::getArrayAddress() const {
    return data;
}

// ---------------------------------------------------------------------
// Statistical functions -- STUBS (prototypes only, to be implemented)
//
// Each stub reports that it is not yet implemented and returns a
// harmless default value so the program compiles and the menu can be
// exercised end-to-end before the math is filled in.
// ---------------------------------------------------------------------

double DescriptiveStatsCalculator::findMinimum() const {
    cout << "[Not yet implemented: findMinimum]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findMaximum() const {
    cout << "[Not yet implemented: findMaximum]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findRange() const {
    cout << "[Not yet implemented: findRange]" << endl;
    return 0.0;
}

int DescriptiveStatsCalculator::findSize() const {
    return size; // trivial pass-through, safe to leave implemented
}

double DescriptiveStatsCalculator::findSum() const {
    cout << "[Not yet implemented: findSum]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findMean() const {
    cout << "[Not yet implemented: findMean]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findMedian() const {
    cout << "[Not yet implemented: findMedian]" << endl;
    return 0.0;
}

int DescriptiveStatsCalculator::findModes(double*& modes) const {
    cout << "[Not yet implemented: findModes]" << endl;
    modes = nullptr;
    return 0;
}

double DescriptiveStatsCalculator::findStandardDeviation() const {
    cout << "[Not yet implemented: findStandardDeviation]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findVariance() const {
    cout << "[Not yet implemented: findVariance]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findMidrange() const {
    cout << "[Not yet implemented: findMidrange]" << endl;
    return 0.0;
}

void DescriptiveStatsCalculator::findQuartiles(double& q1, double& q2, double& q3) const {
    cout << "[Not yet implemented: findQuartiles]" << endl;
    q1 = q2 = q3 = 0.0;
}

double DescriptiveStatsCalculator::findInterquartileRange() const {
    cout << "[Not yet implemented: findInterquartileRange]" << endl;
    return 0.0;
}

int DescriptiveStatsCalculator::findOutliers(double*& outliers) const {
    cout << "[Not yet implemented: findOutliers]" << endl;
    outliers = nullptr;
    return 0;
}

double DescriptiveStatsCalculator::findSumOfSquares() const {
    cout << "[Not yet implemented: findSumOfSquares]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findMeanAbsoluteDeviation() const {
    cout << "[Not yet implemented: findMeanAbsoluteDeviation]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findRootMeanSquare() const {
    cout << "[Not yet implemented: findRootMeanSquare]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findStandardErrorOfMean() const {
    cout << "[Not yet implemented: findStandardErrorOfMean]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findSkewness() const {
    cout << "[Not yet implemented: findSkewness]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findKurtosis() const {
    cout << "[Not yet implemented: findKurtosis]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findKurtosisExcess() const {
    cout << "[Not yet implemented: findKurtosisExcess]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findCoefficientOfVariation() const {
    cout << "[Not yet implemented: findCoefficientOfVariation]" << endl;
    return 0.0;
}

double DescriptiveStatsCalculator::findRelativeStandardDeviation() const {
    cout << "[Not yet implemented: findRelativeStandardDeviation]" << endl;
    return 0.0;
}

void DescriptiveStatsCalculator::displayFrequencyTable() const {
    cout << "[Not yet implemented: displayFrequencyTable]" << endl;
}

void DescriptiveStatsCalculator::displayAllStatisticalResults() const {
    cout << "[Not yet implemented: displayAllStatisticalResults]" << endl;
}

bool DescriptiveStatsCalculator::outputAllStatisticalResultsToFile(const string& filename) const {
    cout << "[Not yet implemented: outputAllStatisticalResultsToFile]" << endl;
    (void)filename;
    return false;
}
