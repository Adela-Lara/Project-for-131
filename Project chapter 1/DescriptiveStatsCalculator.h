#ifndef DESCRIPTIVE_STATS_CALCULATOR_H
#define DESCRIPTIVE_STATS_CALCULATOR_H

#include <string>
#include <iostream>

class DescriptiveStatsCalculator {
public:
    enum class DatasetType { SAMPLE, POPULATION };

    // ------------------------------------------------------------------
    // Construction / Destruction (Rule of Three)
    // ------------------------------------------------------------------

    // Precondition:  none
    // Postcondition: initializes empty dataset with default capacity and SAMPLE type
    DescriptiveStatsCalculator();

    // Precondition:  initialCapacity >= 1
    // Postcondition: initializes empty dataset with specified initial capacity
    explicit DescriptiveStatsCalculator(int initialCapacity);

    // Precondition:  other is a valid DescriptiveStatsCalculator object
    // Postcondition: creates an independent deep copy of other
    DescriptiveStatsCalculator(const DescriptiveStatsCalculator& other);

    // Precondition:  other is a valid DescriptiveStatsCalculator object
    // Postcondition: releases current memory and deep copies other (safe on self-assignment)
    DescriptiveStatsCalculator& operator=(const DescriptiveStatsCalculator& other);

    // Precondition:  none
    // Postcondition: deallocates all dynamically allocated memory
    ~DescriptiveStatsCalculator();

    // ------------------------------------------------------------------
    // Configuration & Container Operations (Options 1, 2, 3)
    // ------------------------------------------------------------------

    // Precondition:  type is SAMPLE or POPULATION
    // Postcondition: sets dataset calculation mode
    void configureDatasetType(DatasetType type);

    // Precondition:  none
    // Postcondition: returns the current DatasetType
    DatasetType getDatasetType() const;

    // Precondition:  none
    // Postcondition: inserts value in ascending sorted order, growing capacity if full
    void insertValue(double value);

    // Precondition:  values != nullptr, count >= 0
    // Postcondition: inserts count elements in ascending sorted order
    void insertValues(const double values[], int count);

    // Precondition:  none
    // Postcondition: removes first occurrence of value; returns true if found, false otherwise
    bool deleteValue(double value);

    // Precondition:  none
    // Postcondition: removes all occurrences of value; returns number of elements removed
    int deleteAllOccurrences(double value);

    // Precondition:  start <= end
    // Postcondition: removes all values in [start, end]; returns number of elements removed
    int deleteRange(double start, double end);

    // Precondition:  none
    // Postcondition: empties dataset (size = 0)
    void clear();

    // Precondition:  none
    // Postcondition: returns true if size == 0, false otherwise
    bool isEmpty() const;

    // Precondition:  none
    // Postcondition: returns number of stored elements
    int getSize() const;

    // Precondition:  none
    // Postcondition: displays formatted elements to standard output
    void displayDataset() const;

    // Precondition:  none
    // Postcondition: returns read-only pointer to internal dynamic array
    const double* getArrayAddress() const;

    // ------------------------------------------------------------------
    // Statistical Functions (Options A -> Z)
    // ------------------------------------------------------------------

    // Precondition:  size >= 1
    // Postcondition: returns minimum value in dataset
    double findMinimum() const;

    // Precondition:  size >= 1
    // Postcondition: returns maximum value in dataset
    double findMaximum() const;

    // Precondition:  size >= 1
    // Postcondition: returns range (max - min)
    double findRange() const;

    // Precondition:  none
    // Postcondition: returns size of dataset
    int findSize() const;

    // Precondition:  size >= 1
    // Postcondition: returns sum of all elements
    double findSum() const;

    // Precondition:  size >= 1
    // Postcondition: returns arithmetic mean
    double findMean() const;

    // Precondition:  size >= 1
    // Postcondition: returns median of dataset
    double findMedian() const;

    // Precondition:  size >= 1
    // Postcondition: allocates modes array with highest frequency values; returns count
    int findModes(double*& modes) const;

    // Precondition:  size >= 2
    // Postcondition: returns standard deviation (sample or population)
    double findStandardDeviation() const;

    // Precondition:  size >= 2
    // Postcondition: returns variance (sample or population)
    double findVariance() const;

    // Precondition:  size >= 1
    // Postcondition: returns midrange (min + max) / 2
    double findMidrange() const;

    // Precondition:  size >= 1
    // Postcondition: sets q1, q2, q3 to the 1st, 2nd, and 3rd quartiles
    void findQuartiles(double& q1, double& q2, double& q3) const;

    // Precondition:  size >= 1
    // Postcondition: returns interquartile range (Q3 - Q1)
    double findInterquartileRange() const;

    // Precondition:  size >= 4
    // Postcondition: allocates outliers array with values outside [Q1-1.5*IQR, Q3+1.5*IQR]; returns count
    int findOutliers(double*& outliers) const;

    // Precondition:  size >= 1
    // Postcondition: returns sum of squared deviations from mean
    double findSumOfSquares() const;

    // Precondition:  size >= 1
    // Postcondition: returns mean absolute deviation (MAD)
    double findMeanAbsoluteDeviation() const;

    // Precondition:  size >= 1
    // Postcondition: returns root mean square (RMS)
    double findRootMeanSquare() const;

    // Precondition:  size >= 2
    // Postcondition: returns standard error of the mean
    double findStandardErrorOfMean() const;

    // Precondition:  size >= 3
    // Postcondition: returns skewness coefficient
    double findSkewness() const;

    // Precondition:  size >= 4
    // Postcondition: returns kurtosis coefficient
    double findKurtosis() const;

    // Precondition:  size >= 4
    // Postcondition: returns excess kurtosis
    double findKurtosisExcess() const;

    // Precondition:  size >= 2, mean != 0
    // Postcondition: returns coefficient of variation (stdev / mean)
    double findCoefficientOfVariation() const;

    // Precondition:  size >= 2, mean != 0
    // Postcondition: returns relative standard deviation percentage (CV * 100)
    double findRelativeStandardDeviation() const;

    // ------------------------------------------------------------------
    // Display and File Output
    // ------------------------------------------------------------------

    // Precondition:  out stream is valid
    // Postcondition: prints frequency distribution table to out
    void displayFrequencyTable(std::ostream& out = std::cout) const;

    // Precondition:  out stream is valid
    // Postcondition: prints all statistical metrics and frequency table to out
    void displayAllStatisticalResults(std::ostream& out = std::cout) const;

    // Precondition:  filename is writable
    // Postcondition: writes all statistical results to filename; returns true on success
    bool outputAllStatisticalResultsToFile(const std::string& filename) const;

private:
    static const int DEFAULT_CAPACITY = 8;

    double* data;
    int size;
    int capacity;
    DatasetType datasetType;

    // Precondition:  newCapacity >= size
    // Postcondition: reallocates data array to newCapacity preserving elements
    void resize(int newCapacity);

    // Precondition:  none
    // Postcondition: returns binary search index for sorted insertion
    int findInsertPosition(double value) const;

    // Precondition:  0 <= lo < hi <= size
    // Postcondition: returns median of subrange [lo..hi-1]
    double medianInRange(int lo, int hi) const;
};

#endif // DESCRIPTIVE_STATS_CALCULATOR_H