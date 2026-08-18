// ============================================================================
// DescriptiveStatsCalculator.h
//
// A container class that stores numeric data in a dynamically allocated,
// sorted (ascending) array and computes descriptive statistics on it.
//
// Container requirements satisfied:
//   - Uses new[] / delete[] directly (no std::vector, no std::array).
//   - Values are kept in sorted (ascending) order at all times, so every
//     insertion places the new value into its correct sorted position.
// ============================================================================

#ifndef DESCRIPTIVE_STATS_CALCULATOR_H
#define DESCRIPTIVE_STATS_CALCULATOR_H

#include <string>

class DescriptiveStatsCalculator {
public:
    // Data set can be treated as a Sample or a Population. This affects
    // which divisor (n-1 vs n) is used by variance / standard deviation /
    // standard error calculations.
    enum class DatasetType { SAMPLE, POPULATION };

    // ------------------------------------------------------------------
    // Construction / Destruction / Rule of Three
    // ------------------------------------------------------------------

    // Precondition:  none.
    // Postcondition: object exists with an empty dataset, capacity of
    //                DEFAULT_CAPACITY, and DatasetType::SAMPLE selected.
    DescriptiveStatsCalculator();

    // Precondition:  initialCapacity >= 1.
    // Postcondition: object exists with an empty dataset and internal
    //                array capacity == initialCapacity.
    explicit DescriptiveStatsCalculator(int initialCapacity);

    // Precondition:  other is a valid, fully constructed object.
    // Postcondition: *this is an independent deep copy of other.
    DescriptiveStatsCalculator(const DescriptiveStatsCalculator& other);

    // Precondition:  other is a valid, fully constructed object.
    // Postcondition: *this releases its previous array and becomes an
    //                independent deep copy of other. Safe on self-assignment.
    DescriptiveStatsCalculator& operator=(const DescriptiveStatsCalculator& other);

    // Precondition:  none.
    // Postcondition: all dynamically allocated memory owned by this object
    //                is released.
    ~DescriptiveStatsCalculator();

    // ------------------------------------------------------------------
    // Container / configuration operations (fully implemented)
    // ------------------------------------------------------------------

    // Precondition:  none.
    // Postcondition: dataset is treated as SAMPLE or POPULATION for all
    //                statistics that distinguish between the two.
    void configureDatasetType(DatasetType type);

    // Precondition:  none.
    // Postcondition: returns the currently configured DatasetType.
    DatasetType getDatasetType() const;

    // Precondition:  none.
    // Postcondition: value is inserted into its correct ascending-sorted
    //                position in the internal array; size increases by 1;
    //                internal array is grown (doubled) first if it was full.
    void insertValue(double value);

    // Precondition:  values != nullptr, count >= 0.
    // Postcondition: all `count` values from values[] have been inserted
    //                (each in sorted position), size increases by count.
    void insertValues(const double values[], int count);

    // Precondition:  none.
    // Postcondition: if value exists in the dataset, the FIRST occurrence
    //                found is removed, size decreases by 1, remaining
    //                elements stay in sorted order, and true is returned.
    //                If value is not found, the dataset is unchanged and
    //                false is returned.
    bool deleteValue(double value);

    // Precondition:  none.
    // Postcondition: all occurrences of value are removed; size decreases
    //                by the number of occurrences removed; returns the
    //                number of occurrences removed (0 if none found).
    int deleteAllOccurrences(double value);

    // Precondition:  none.
    // Postcondition: dataset becomes empty (size == 0); allocated capacity
    //                is unchanged.
    void clear();

    // Precondition:  none.
    // Postcondition: returns true if size == 0, false otherwise.
    bool isEmpty() const;

    // Precondition:  none.
    // Postcondition: returns the number of values currently stored.
    int getSize() const;

    // Precondition:  none.
    // Postcondition: prints every value in the dataset, in ascending
    //                order, to standard output. Does not modify the dataset.
    void displayDataset() const;

    // ------------------------------------------------------------------
    // Statistical functions (PROTOTYPES ONLY — to be implemented later)
    //
    // Every function below:
    //   Precondition:  dataset must contain at least the minimum number
    //                  of values noted per-function (checked at runtime;
    //                  functions that cannot compute a result on an
    //                  under-sized dataset should report an error rather
    //                  than access invalid memory).
    //   Postcondition: dataset itself is NOT modified by any of these
    //                  (all are logically const / read-only operations).
    // ------------------------------------------------------------------

    // Precondition:  size >= 1.
    // Postcondition: returns the smallest value in the dataset.
    double findMinimum() const;

    // Precondition:  size >= 1.
    // Postcondition: returns the largest value in the dataset.
    double findMaximum() const;

    // Precondition:  size >= 1.
    // Postcondition: returns (max - min).
    double findRange() const;

    // Precondition:  none.
    // Postcondition: returns size (number of stored values). Equivalent
    //                to getSize(); provided to match menu option D.
    int findSize() const;

    // Precondition:  size >= 1.
    // Postcondition: returns the sum of all values in the dataset.
    double findSum() const;

    // Precondition:  size >= 1.
    // Postcondition: returns sum / size (arithmetic mean).
    double findMean() const;

    // Precondition:  size >= 1.
    // Postcondition: returns the middle value (size odd) or the average
    //                of the two middle values (size even) of the sorted
    //                dataset.
    double findMedian() const;

    // Precondition:  size >= 1.
    // Postcondition: allocates (with new[]) an array containing every
    //                value that occurs most frequently, stores its address
    //                in the output parameter `modes`, and returns the
    //                number of elements written to it. Caller is
    //                responsible for calling delete[] on `modes` when done.
    int findModes(double*& modes) const;

    // Precondition:  size >= 2.
    // Postcondition: returns the standard deviation, using the (n-1)
    //                divisor if DatasetType::SAMPLE or the (n) divisor
    //                if DatasetType::POPULATION.
    double findStandardDeviation() const;

    // Precondition:  size >= 2.
    // Postcondition: returns the variance, using the (n-1) divisor if
    //                DatasetType::SAMPLE or the (n) divisor if
    //                DatasetType::POPULATION.
    double findVariance() const;

    // Precondition:  size >= 1.
    // Postcondition: returns (min + max) / 2.
    double findMidrange() const;

    // Precondition:  size >= 4 (recommended minimum for meaningful quartiles).
    // Postcondition: fills q1, q2, q3 by reference with the first,
    //                second (median), and third quartiles of the sorted
    //                dataset.
    void findQuartiles(double& q1, double& q2, double& q3) const;

    // Precondition:  size >= 4.
    // Postcondition: returns Q3 - Q1.
    double findInterquartileRange() const;

    // Precondition:  size >= 4.
    // Postcondition: allocates (with new[]) an array containing every
    //                value that lies outside [Q1 - 1.5*IQR, Q3 + 1.5*IQR],
    //                stores its address in `outliers`, and returns the
    //                number of elements written. Caller must delete[] it.
    int findOutliers(double*& outliers) const;

    // Precondition:  size >= 1.
    // Postcondition: returns the sum of (value^2) across the dataset.
    double findSumOfSquares() const;

    // Precondition:  size >= 1.
    // Postcondition: returns the mean of |value - mean| across the dataset.
    double findMeanAbsoluteDeviation() const;

    // Precondition:  size >= 1.
    // Postcondition: returns sqrt( (sum of value^2) / size ).
    double findRootMeanSquare() const;

    // Precondition:  size >= 2.
    // Postcondition: returns standardDeviation / sqrt(size).
    double findStandardErrorOfMean() const;

    // Precondition:  size >= 3.
    // Postcondition: returns the (Fisher-Pearson) skewness coefficient
    //                describing the asymmetry of the distribution.
    double findSkewness() const;

    // Precondition:  size >= 4.
    // Postcondition: returns the kurtosis of the distribution.
    double findKurtosis() const;

    // Precondition:  size >= 4.
    // Postcondition: returns (kurtosis - 3), i.e. excess kurtosis
    //                relative to a normal distribution.
    double findKurtosisExcess() const;

    // Precondition:  size >= 2 and mean != 0.
    // Postcondition: returns standardDeviation / mean.
    double findCoefficientOfVariation() const;

    // Precondition:  size >= 2 and mean != 0.
    // Postcondition: returns (standardDeviation / mean) * 100, expressed
    //                as a percentage.
    double findRelativeStandardDeviation() const;

    // Precondition:  size >= 1.
    // Postcondition: prints a frequency table (distinct value -> count)
    //                to standard output. Dataset is unmodified.
    void displayFrequencyTable() const;

    // Precondition:  size >= 1 for statistics that require it; function
    //                should gracefully report which stats could not be
    //                computed if the dataset is too small for them.
    // Postcondition: prints every available statistic to standard output.
    void displayAllStatisticalResults() const;

    // Precondition:  filename is a valid, writable file path.
    // Postcondition: a text file is created/overwritten at `filename`
    //                containing every available statistic; returns true
    //                on success, false if the file could not be opened.
    bool outputAllStatisticalResultsToFile(const std::string& filename) const;

    // Precondition:  none.
    // Postcondition: returns the current address of the internal dynamic
    //                array (used only for diagnostic/menu display).
    const double* getArrayAddress() const;

private:
    static const int DEFAULT_CAPACITY = 8;

    double* data;          // dynamically allocated, kept sorted ascending
    int size;               // number of values currently stored
    int capacity;            // current allocated capacity of data[]
    DatasetType datasetType; // SAMPLE or POPULATION

    // Precondition:  newCapacity >= size.
    // Postcondition: internal array is reallocated to newCapacity,
    //                existing elements are preserved in order, and
    //                the old array is deleted.
    void resize(int newCapacity);

    // Precondition:  size >= 0 (valid dataset state).
    // Postcondition: returns the index at which `value` should be
    //                inserted to keep the array in ascending sorted order.
    int findInsertPosition(double value) const;
};

#endif // DESCRIPTIVE_STATS_CALCULATOR_H
