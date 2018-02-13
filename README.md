# Table of Contents
1. [Approach](README.md#approach)
2. [Dependencies](README.md#dependencies)
3. [Run Instructions](README.md#run-instructions)

# Approach
The purpose of this repo/project is to parse campaign contribution data and output some statistics on campaign donors classified as "repeat donors".  As per the requirments from the Insight instructions, data is to be parsed line by line to simulate real-time streaming/processing via some more complex frontend acquiring mechanism and/or backend processing module.  The point of this is to acquire real-time statistics data on repeat donors as the results are streamed. To simulate this streaming process, data is read from an input file and analyzed line by line.

In order to identify repeat donors from a data stream one must be keep track of all donor contributions and check for repeat donors after each contribution is read and processed.  In order to identify "repeat donors", my idea was to use and leverage the efficiency of the STL `unordered_map` data structure.  

## Parsing Individual Contributions
Each campaign contribution is processed and split into 21 tokens accounting for all the fields from the [FEC website](http://classic.fec.gov/finance/disclosure/metadata/DataDictionaryContributionsbyIndividuals.shtml).  Though this project only requires us to keep some of this data, I wrap the data in a class called `CampContrib` (campaign contribution). This class provides Get/Set mechanisms for accessing the FEC data fields.  These objects are stored in an `unordered_map` where keys are built from the donors name and zipcode fields.  The value type is a STL `vector` of campaign contributions which allows one to store multiple contributions per key.

## Repeat Donor Detection
A repeat donor is detected by searching for the donors key (name-zipcode) in the `unordered_map` (O(1) access) and then checking if the value type (a vector of this donors contributions) has multiple elements.  If this is the case, an additional search is performed over the map in order to identify and aggregate other repeat donors with the same campaign contribution number, zipcode, and year.  To do this, I use boost::filter_iterator with a an appropraite matching predicate called *IdentifyRepeat*.  The repeat donors are saved in an aggregate vector.

## Statistics
Statistics such as total number of repeat donors and total dontations are calculated from the repeat donor aggregate vector.  Nearest Rank is used to identify percentiles in the set of donor contributions.  From these statistics a string is assembled and output to a file called *repeat_donors.txt*.

# Dependencies
1. C++11 w/ STL
2. Boost v1.58 (specifically the following header files)
    1. boost/iterator/filter_iterator.hpp
    2. boost/range/iterator_range.hpp
    3. boost/tokenizer.hpp
3. GNU Make

# Run Instructions
The project takes three command line arguments: the input data file, the input percentile file, and the outpute repeat donors file.  The project relies on a Makefile in the top level directory.

1. Compile in the top level by running (defaults to out of source build) `Make` followed by:

    `./donation-analytics ./input/itcont.txt ./input/percentile.txt ./output/repeat_donors.txt`
    where we have assumed that the input/output files/directories exist.  This defaults to an out of source build and symlinks the executable in ./bin/ to the top level directory.

2. Compile and run with the insight_test_suite.  For this method one can navigate to the folder *insight_test_suit* and execute `./run_tests.sh`.  This script calls `./run.sh` in the top level directory.  The Makefile is copied with the source files so that the `dontation-analytics` executable can be built in the correct directory for invoking the tests.
