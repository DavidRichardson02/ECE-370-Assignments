//  DataAnalysis.h
//  ECE-370_Integration_And_Data_Analysis


#ifndef DataAnalysis_h
#define DataAnalysis_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>



/**
 * DataSetAnalysis Structure: Represents the properties of the data set that are required for data
 * analysis and operations, but not necessarily important for the actual meaning of data. For example, the
 * delimiter a data set uses has basically nothing to do with the contents of the data or their meaning, but
 * analyzing the data in any meaningful way would be impossible without a way to differentiate between various
 * fields and entries.
 *
 * This structure encapsulates the various attributes of a data set's properties that are relevant for
 * the capturing, formatting, and analysis analysis of data, without which, there would be no
 * way to perform operations on data.
 * Each member variable is associated with a specific property of data set analysis.
 *
 *
 * DataSetAnalysis Structure: Represents the properties of a data set required for its analysis, reading, writing, extraction of values,
 * statistical operations, and
 * .
 * This structure encapsulates various attributes that are essential for capturing, formatting, and analyzing
 * the data set. These properties facilitate operations on the data, such as parsing, processing, and interpreting.
 *
 *
 * Struct for data set analysis properties:
 *      - int lineCount: The number of data entries in the data set.
 *      - int fieldCount: The number of fields per data entry.
 *      - const char *delimiter: The delimiter character used to separate fields in the data set.
 *      - char *dataSetHeader: Header line of the data set.
 *      - char **fieldNameTypePairs: Array of strings storing pairs of field names and their corresponding types.
 *      - const char* dataSetFilePathName: Path to the data set file.
 *      - int *missingDataCount: Count of missing values per field.
 *      - char **dataSetFileContents: Full contents of the data set, blindly read in.
 *please help me create a plain c function that parses the full file contents and returns an int* count of missing values per field.
 */
typedef struct
{
    int lineCount;
    int fieldCount;
    const char *delimiter;
    
    char *dataSetHeader;
    char **fieldNameTypePairs;
    const char* dataSetFilePathName;

    int *missingDataCount;
    
    char **dataSetFileContents;
} DataSetAnalysis;


DataSetAnalysis configure_data_set_analysis(const char* dataSetFilePathName);


const char *analyze_data_set(const char* dataSetFilePathName);

char **capture_and_prepare_data_set_contents(const char* dataSetFilePathName);


char **format_data_set(const char* dataSetFilePathName);

void run_data_set(const char* dataSetFilePathName, char **fileContents, int lineCount, const char *delimiter);



#endif /* DataAnalysis_h */

