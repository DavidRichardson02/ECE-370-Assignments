//  main.c
//  ECE-370_Integration_And_Data_Analysis


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "GeneralUtilities.h"
#include "StringUtilities.h"
#include "FileUtilities.h"
#include "DataSetUtilities.h"
#include "StatisticalMethods.h"
#include "PlottingMethods.h"
#include "DataAnalysis.h"




int main(int argc, const char * argv[])
{
    const char* particleDataSetFilePathName = "/Users/98dav/Desktop/Xcode/C-Programs/ECE-370_Integration_And_Data_Analysis/physics_particles.txt";
    const char *weatherDataSetFilePathName = "/Users/98dav/Desktop/Xcode/C-Programs/ECE-370_Integration_And_Data_Analysis/weather_measurements.csv"; // "/Users/98dav/Desktop/Xcode /C-Programs/ECE-370_Assignment_Two_Integration_And_Data_Analysis/beach-weather-stations-automated-sensors-1.csv";
    
    /*-----------   Capture File Contents in an Array of Strings   -----------*/
    //int lineCount = count_file_lines(particleDataSetFilePathName, MAX_NUM_FILE_LINES);
    //char **fileContents = read_file_contents(particleDataSetFilePathName, lineCount);
    //const char *delimiter = identify_delimiter(fileContents, lineCount);

    
    //run_data_set(particleDataSetFilePathName, fileContents, lineCount, delimiter);
    //run_data_set(weatherDataSetFilePathName);
    
    
    
    //DataSetAnalysis particleDataSet = configure_data_set_analysis(particleDataSetFilePathName);
    
    
    //char *testString = allocate_memory_char_ptr(strlen("-") + 1);//string_is_hyphen_else_is_minus_sign
    //testString = "-";
    //printf("\n\n%d", string_is_hyphen_else_is_minus_sign(testString));
    
    
    ///
    /*
    /*-----------   Capture File Contents in an Array of Strings   -----------*
    int lineCount = count_file_lines(weatherDataSetFilePathName, MAX_NUM_FILE_LINES);
    char **fileContents = read_file_contents(weatherDataSetFilePathName, lineCount);
    //print_file_contents(fileContents, lineCount);
    
    const char *dataDelimiter = identify_delimiter(fileContents, lineCount);
    
    //const char *dataSetDelimiter;//dataDelimiter;
    
    int fieldCount = count_data_fields(fileContents[0]);
    
    char **formattedFileContents = fileContents;
    //char **formattedFileContents = allocate_memory_char_ptr_ptr(size_t strSize, lineCount);
    
    
    
    for(int i = 1; i < lineCount; i++)
    {
        formattedFileContents[i] = prune_and_trim_problematic_characters_from_string(fileContents[i], dataDelimiter, fieldCount);
        
    }
    print_file_contents(formattedFileContents, lineCount);
    //*/
    
    
   
    //char *repeatedDelimiterPruning = "-13,mu,anti_muon,1.0,,0,-,105.6583755,2.3e-06,2.3e-06,2.9959836e-16,3e-22,3e-22";
    //printf("\n\n\n%s: ", repeatedDelimiterPruning);
    //printf("\n%lu: ", strlen(repeatedDelimiterPruning));
    //repeatedDelimiterPruning = prune_and_trim_problematic_characters_from_string(repeatedDelimiterPruning, ',');
    //printf("\n\n\n%s: ", testString);
    //printf("\n\n\n%s: ", repeatedDelimiterPruning);
    //printf("\n%lu: ", strlen(repeatedDelimiterPruning));

    
    
    //
    /*double *unsortedData = allocate_memory_double_ptr(100);
    for(int i = 0; i < 100; i++) { unsortedData[i] = 25 + rand() % (2500 - 25 + 1); }
    double *unsortedDataMerge = unsortedData;
    print_array(100, unsortedData, "Unsorted Data");  print_array(100, unsortedDataMerge, "Unsorted Data Merge");
    radix_sort_doubles(unsortedData, 100);  merge_sort(unsortedDataMerge, 100);
    print_array(100, unsortedData, "Radix Sorted Data");  print_array(100, unsortedDataMerge, "Merge Sorted Data");//*/
    
    return 0;
}



