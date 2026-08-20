#ifndef DESCRIPTIVE_STATS_CALCULATOR_H
#define DESCRIPTIVE_STATS_CALCULATOR_H

#include <string>
#include <iostream>

class DescriptiveStatsCalculator {
public:
    enum class DatasetType { SAMPLE, POPULATION };

    // Constructors / Destructor (Rule of Three)
    DescriptiveStatsCalculator();
    explicit DescriptiveStatsCalculator(int initialCapacity);
    DescriptiveStatsCalculator(const DescriptiveStatsCalculator& other);
    DescriptiveStatsCalculator& operator=(const DescriptiveStatsCalculator& other);
    ~DescriptiveStatsCalculator();

    // Configuration & Container operations
    void configureDatasetType(DatasetType type);
    DatasetType getDatasetType() const;

    void insertValue(double value);
    void insertValues(const double values[], int count);
    bool deleteValue(double value);
    int deleteAllOccurrences(double value);
    int deleteRange(double start, double end);
    void clear();
    bool isEmpty() const;
    int getSize() const;
    void displayDataset() const;
    const double* getArrayAddress() const;

    // Statistical functions
    double findMinimum() const;
    double findMaximum() const;
    double findRange() const;
    int findSize() const;
    double findSum() const;
    double findMean() const;
    double findMedian() const;
    int findModes(double*& modes) const;
    double findStandardDeviation() const;
    double findVariance() const;
    double findMidrange() const;
    void findQuartiles(double& q1, double& q2, double& q3) const;
    double findInterquartileRange() const;
    int findOutliers(double*& outliers) const;
    double findSumOfSquares() const;
    double findMeanAbsoluteDeviation() const;
    double findRootMeanSquare() const;
    double findStandardErrorOfMean() const;
    double findSkewness() const;
    double findKurtosis() const;
    double findKurtosisExcess() const;
    double findCoefficientOfVariation() const;
    double findRelativeStandardDeviation() const;

    // Display and file output
    void displayFrequencyTable(std::ostream& out = std::cout) const;
    void displayAllStatisticalResults(std::ostream& out = std::cout) const;
    bool outputAllStatisticalResultsToFile(const std::string& filename) const;

private:
    static const int DEFAULT_CAPACITY = 8;

    double* data;
    int size;
    int capacity;
    DatasetType datasetType;

    void resize(int newCapacity);
    int findInsertPosition(double value) const;
    double medianInRange(int lo, int hi) const;
};

#endif // DESCRIPTIVE_STATS_CALCULATOR_H