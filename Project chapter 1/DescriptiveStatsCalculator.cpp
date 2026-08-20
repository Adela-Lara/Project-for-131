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
// Statistical Functions
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

double DescriptiveStatsCalculator::findSum() const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += data[i];
    }
    return sum;
}

double DescriptiveStatsCalculator::findMean() const {
    if (size == 0) return 0.0;
    return findSum() / size;
}

double DescriptiveStatsCalculator::findMedian() const {
    if (size == 0) return 0.0;
    if (size % 2 == 1) {
        return data[size / 2];
    }
    return (data[size / 2 - 1] + data[size / 2]) / 2.0;
}

int DescriptiveStatsCalculator::findModes(double*& modes) const {
    modes = nullptr;
    if (size == 0) return 0;

    const double EPSILON = 1e-9;
    int maxFreq = 1, currentFreq = 1;
    for (int i = 1; i < size; ++i) {
        if (std::abs(data[i] - data[i - 1]) < EPSILON) {
            currentFreq++;
        }
        else {
            if (currentFreq > maxFreq) maxFreq = currentFreq;
            currentFreq = 1;
        }
    }
    if (currentFreq > maxFreq) maxFreq = currentFreq;

    if (maxFreq == 1) {
        return 0;
    }

    int modeCount = 0;
    currentFreq = 1;
    for (int i = 1; i < size; ++i) {
        if (std::abs(data[i] - data[i - 1]) < EPSILON) {
            currentFreq++;
        }
        else {
            if (currentFreq == maxFreq) modeCount++;
            currentFreq = 1;
        }
    }
    if (currentFreq == maxFreq) modeCount++;

    modes = new double[modeCount];
    int k = 0;
    currentFreq = 1;
    for (int i = 1; i < size; ++i) {
        if (std::abs(data[i] - data[i - 1]) < EPSILON) {
            currentFreq++;
        }
        else {
            if (currentFreq == maxFreq) modes[k++] = data[i - 1];
            currentFreq = 1;
        }
    }
    if (currentFreq == maxFreq) modes[k++] = data[size - 1];

    return modeCount;
}

double DescriptiveStatsCalculator::findVariance() const {
    if (size < 2) return 0.0;
    double mean = findMean();
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        double diff = data[i] - mean;
        sum += diff * diff;
    }
    double denom = (datasetType == DatasetType::SAMPLE) ? (size - 1) : size;
    return sum / denom;
}

double DescriptiveStatsCalculator::findStandardDeviation() const {
    return std::sqrt(findVariance());
}

double DescriptiveStatsCalculator::findMidrange() const {
    if (size == 0) return 0.0;
    return (findMinimum() + findMaximum()) / 2.0;
}

double DescriptiveStatsCalculator::medianInRange(int lo, int hi) const {
    int len = hi - lo;
    if (len <= 0) return 0.0;
    if (len % 2 == 1) {
        return data[lo + len / 2];
    }
    return (data[lo + len / 2 - 1] + data[lo + len / 2]) / 2.0;
}

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

double DescriptiveStatsCalculator::findInterquartileRange() const {
    double q1 = 0, q2 = 0, q3 = 0;
    findQuartiles(q1, q2, q3);
    return q3 - q1;
}

int DescriptiveStatsCalculator::findOutliers(double*& outliers) const {
    outliers = nullptr;
    if (size < 4) return 0;

    double q1 = 0, q2 = 0, q3 = 0;
    findQuartiles(q1, q2, q3);
    double iqr = q3 - q1;
    double lowerFence = q1 - 1.5 * iqr;
    double upperFence = q3 + 1.5 * iqr;

    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (data[i] < lowerFence || data[i] > upperFence) {
            count++;
        }
    }
    if (count == 0) return 0;

    outliers = new double[count];
    int k = 0;
    for (int i = 0; i < size; ++i) {
        if (data[i] < lowerFence || data[i] > upperFence) {
            outliers[k++] = data[i];
        }
    }
    return count;
}

double DescriptiveStatsCalculator::findSumOfSquares() const {
    if (size == 0) return 0.0;
    double mean = findMean();
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        double diff = data[i] - mean;
        sum += diff * diff;
    }
    return sum;
}

double DescriptiveStatsCalculator::findMeanAbsoluteDeviation() const {
    if (size == 0) return 0.0;
    double mean = findMean();
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += std::abs(data[i] - mean);
    }
    return sum / size;
}

double DescriptiveStatsCalculator::findRootMeanSquare() const {
    if (size == 0) return 0.0;
    double sumSq = 0.0;
    for (int i = 0; i < size; ++i) {
        sumSq += data[i] * data[i];
    }
    return std::sqrt(sumSq / size);
}

double DescriptiveStatsCalculator::findStandardErrorOfMean() const {
    if (size == 0) return 0.0;
    return findStandardDeviation() / std::sqrt(size);
}

double DescriptiveStatsCalculator::findSkewness() const {
    if (size < 3) return 0.0;
    double mean = findMean();
    double stdev = findStandardDeviation();
    if (stdev == 0.0) return 0.0;

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        double z = (data[i] - mean) / stdev;
        sum += z * z * z;
    }

    if (datasetType == DatasetType::SAMPLE) {
        return (static_cast<double>(size) / ((size - 1.0) * (size - 2.0))) * sum;
    }
    else {
        return sum / size;
    }
}

double DescriptiveStatsCalculator::findKurtosis() const {
    if (size < 4) return 0.0;
    double mean = findMean();
    double stdev = findStandardDeviation();
    if (stdev == 0.0) return 0.0;

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        double diff = data[i] - mean;
        sum += diff * diff * diff * diff;
    }

    if (datasetType == DatasetType::SAMPLE) {
        double factor = (static_cast<double>(size) * (size + 1.0)) /
                        ((size - 1.0) * (size - 2.0) * (size - 3.0));
        return factor * (sum / std::pow(stdev, 4));
    }
    else {
        return sum / (size * std::pow(stdev, 4));
    }
}

double DescriptiveStatsCalculator::findKurtosisExcess() const {
    if (size < 4) return 0.0;
    double mean = findMean();
    double stdev = findStandardDeviation();
    if (stdev == 0.0) return 0.0;

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        double z = (data[i] - mean) / stdev;
        sum += z * z * z * z;
    }

    if (datasetType == DatasetType::POPULATION) {
        return (sum / size) - 3.0;
    }
    else {
        double numerator = (static_cast<double>(size) * (size + 1.0) /
                           ((size - 1.0) * (size - 2.0) * (size - 3.0))) * sum;
        double correction = 3.0 * std::pow(size - 1.0, 2) / ((size - 2.0) * (size - 3.0));
        return numerator - correction;
    }
}

double DescriptiveStatsCalculator::findCoefficientOfVariation() const {
    double mean = findMean();
    if (std::abs(mean) < 1e-9) return 0.0;
    return findStandardDeviation() / mean;
}

double DescriptiveStatsCalculator::findRelativeStandardDeviation() const {
    return findCoefficientOfVariation() * 100.0;
}

void DescriptiveStatsCalculator::displayFrequencyTable(std::ostream& out) const {
    if (size == 0) {
        out << "\n\tNo data to display.\n";
        return;
    }
    const double EPSILON = 1e-9;
    out << std::right << std::setw(13) << "Value"
        << std::setw(14) << "Frequency"
        << std::setw(14) << "Frequency %" << std::endl;

    int i = 0;
    while (i < size) {
        double val = data[i];
        int count = 1;
        while (i + count < size && std::abs(data[i + count] - val) < EPSILON) {
            count++;
        }
        double percent = (count * 100.0) / size;
        out << std::right << std::setw(13) << val
            << std::setw(14) << count
            << std::setw(14) << std::fixed << std::setprecision(1) << percent << std::endl;
        i += count;
    }
}

void DescriptiveStatsCalculator::displayAllStatisticalResults(std::ostream& out) const {
    if (size == 0) {
        out << "\n\tDataset is empty.\n";
        return;
    }

    out << "\n\tMinimum \t\t\t = " << findMinimum();
    out << "\n\tMaximum \t\t\t = " << findMaximum();
    out << "\n\tRange \t\t\t\t = " << findRange();
    out << "\n\tSize \t\t\t\t = " << getSize();
    out << "\n\tSum \t\t\t\t = " << findSum();
    out << "\n\tMean \t\t\t\t = " << findMean();
    out << "\n\tMedian \t\t\t\t = " << findMedian();

    double* modes = nullptr;
    int modeCount = findModes(modes);
    out << "\n\tMode(s) \t\t\t = ";
    if (modeCount == 0 || modes == nullptr) {
        out << "No mode (all values unique)";
    }
    else {
        for (int i = 0; i < modeCount; ++i) {
            if (i > 0) out << " ";
            out << modes[i];
        }
    }
    if (modes) delete[] modes;

    out << "\n\tStandard Deviation \t\t = " << findStandardDeviation();
    out << "\n\tVariance \t\t\t = " << findVariance();
    out << "\n\tMidrange \t\t\t = " << findMidrange();

    double q1 = 0, q2 = 0, q3 = 0;
    findQuartiles(q1, q2, q3);
    out << "\n\tQuartiles \t\t\t Quartiles:";
    out << "\n\t\t\t\t\t Q1 --> " << std::fixed << std::setprecision(1) << q1;
    out << "\n\t\t\t\t\t Q2 --> " << std::fixed << std::setprecision(1) << q2;
    out << "\n\t\t\t\t\t Q3 --> " << std::fixed << std::setprecision(1) << q3;

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
        for (int i = 0; i < outlierCount; ++i) {
            if (i > 0) out << " ";
            out << outliers[i];
        }
    }
    if (outliers) delete[] outliers;

    out << "\n\tSum of Squares \t\t\t = " << findSumOfSquares();
    out << "\n\tMean Absolute Deviation \t = " << findMeanAbsoluteDeviation();
    out << "\n\tRoot Mean Square \t\t = " << findRootMeanSquare();
    out << "\n\tStandard Error of the Mean \t = " << findStandardErrorOfMean();
    out << "\n\tSkewness \t\t\t = " << findSkewness();
    out << "\n\tKurtosis \t\t\t = " << findKurtosis();
    out << "\n\tKurtosis Excess \t\t = " << findKurtosisExcess();
    out << "\n\tCoefficient of Variation \t = " << findCoefficientOfVariation();
    out << "\n\tRelative Standard Deviation \t = " << findRelativeStandardDeviation();

    out << "\n\n\tFrequency Table\n";
    displayFrequencyTable(out);
}

bool DescriptiveStatsCalculator::outputAllStatisticalResultsToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    displayAllStatisticalResults(file);
    file.close();
    return true;
}