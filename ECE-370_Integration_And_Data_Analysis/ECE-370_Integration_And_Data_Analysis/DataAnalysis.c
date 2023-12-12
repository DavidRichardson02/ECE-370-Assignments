//  DataAnalysis.c
//  ECE-370_Integration_And_Data_Analysis


#include "DataAnalysis.h"
#include "GeneralUtilities.h"
#include "StringUtilities.h"
#include "StatisticalMethods.h"
#include "FileUtilities.h"
#include "DataSetUtilities.h"
#include "PlottingMethods.h"



// capture data set

// format data set for standardized parsing
// prepare data set


/**
 I. CAPTURE DATA SET CONTENTS AS ARRAY OF STRINGS
 
 
 II. FORMAT DATA SET CONTENTS TO BE COMPATIBLE WITH PROGRAM OPERATIONS
 
 
 II. PREPARE DATA SET CONTENTS TO BE WORK WITH STATISTICAL METHODS AND PLOTTING
 
 
 
 
 I. PREPARE DATA SET CONTENTS TO BE WORK WITH STATISTICAL METHODS AND PLOTTING
    1. Capture the contents of the file in an array of strings
    2. Format the string array contents to be compatible with my CSV file operations to help standardize file's contents for further use and prune the array of strings to remove unwelcome things(things like: double commas,, lone - or + signs, etc.), ensure the file lines are organuzed un the order of header line with parameters, header line with data types, and then all data entries on subsequent lines. If the header line for data types is missing, it can easily be created from examining a data entry, the header line with the data set's parameters however, is commonly a required prerequisite(depends on file contents/data set) and while data can still be plotted without any provided parameters of data entries, it will likely lack key information, such as units, name, magnitude, categorization, etc.
    3. Parse the file contents to independently capture all entries for each of the data set's parameters. For example a data set on particles with the charge, mass, and name will have a main array of strings to capture all contents, which will then be used to create new files to capture the contents  and string/double/int/float/etc. array for each
 Capture any and all plottable data values. First identify the data set's eligible parameters for plotting by using the type descriptions provided in the header and/or the actual contents of the data entry.
    4. Categorize the data paramaters into plottable and unplottable values(ex: string is unplottable and a double value is plottable) and create appropriately named and located directories(based on file pathname) for these new and place them into . The primary purpose of this function is to isolate the numerical data parameters to allow the application of various stochastic methods for plotting things like histograms and theoretical distributions. Additionally, these categorizations will be recorded and indexed to be used later to match things like the title of a graph to the data plotted on it.
 
 
 The entries of the data set will all be defined by the same number of parameters(both numerical and character based parameters are could possibly be NULL)
 The number of parameters defining any given data entry, as read from the header line of the csv data set file
 
 Capture and categorize the contents of .csv data sets, continually refining, streamlining, and formatting data to prepare for plotting. Methodically
 
 
 
 
 II. DATA ANALYSIS
 */



DataSetAnalysis configure_data_set_analysis(const char* dataSetFilePathName)
{
    int lineCount = count_file_lines(dataSetFilePathName, MAX_NUM_FILE_LINES);
    char **fileContents = read_file_contents(dataSetFilePathName, lineCount);
    const char *delimiter = identify_delimiter(fileContents, lineCount);
    
    
    int fieldCount = count_data_fields(fileContents[0]);
    
    //char **formattedFileContents = fileContents;
    //char **formattedFileContents = allocate_memory_char_ptr_ptr(size_t strSize, lineCount);
    

    
    
    
    
    
    DataSetAnalysis configuredDataSet;
    configuredDataSet.lineCount = lineCount;
    configuredDataSet.fieldCount = fieldCount;
    configuredDataSet.delimiter = delimiter;
    configuredDataSet.dataSetHeader = fileContents[0];
    configuredDataSet.fieldNameTypePairs =  capture_data_set_header_for_plotting(fileContents[0], fileContents, delimiter);
    configuredDataSet.dataSetFilePathName = dataSetFilePathName;
    

    
    configuredDataSet.missingDataCount = count_missing_values(fileContents, lineCount, fieldCount, delimiter, fileContents[1]);
    
    
    printf("\n\n\nconfiguredDataSet.missingDataCount: ");
    for (int i = 0; i < lineCount; ++i)
    {
        printf("\n%d", configuredDataSet.missingDataCount[i]);
    }
    
    
    
    configuredDataSet.dataSetFileContents = fileContents;
    
    return configuredDataSet;
}


/**
 * analyze_data_set
 *
 *
 *
 */
const char *analyze_data_set(const char* dataSetFilePathName)
{
    int lineCount = count_file_lines(dataSetFilePathName, MAX_NUM_FILE_LINES);
    char **fileContents = read_file_contents(dataSetFilePathName, lineCount);
    const char *delimiter = identify_delimiter(fileContents, lineCount);
    return delimiter;
}


/**
 * capture_and_prepare_data_set_contents
 *
 * Capture File Contents in an Array of Strings.
 *
 *
 */
char **capture_and_prepare_data_set_contents(const char* dataSetFilePathName)
{
    int lineCount = count_file_lines(dataSetFilePathName, MAX_NUM_FILE_LINES);
    char **fileContents = read_file_contents(dataSetFilePathName, lineCount);
    
    
    int fieldCount = count_data_fields(fileContents[0]);
    char **formattedFileContents = fileContents;
    for(int i = 1; i < lineCount; i++)
    {
        //formattedFileContents[i] = prune_and_trim_problematic_characters_from_string(fileContents[i], delimiter, fieldCount);
        
    }
    print_file_contents(formattedFileContents, lineCount);

    
    return formattedFileContents;
}




void run_data_set(const char* dataSetFilePathName, char **fileContents, int lineCount, const char *delimiter)
{
    /*-----------   Capture File Contents in an Array of Strings   -----------*/
    //int lineCount = count_file_lines(dataSetFilePathName, MAX_NUM_FILE_LINES);
    //char **fileContents = read_file_contents(dataSetFilePathName, lineCount);
    
    
    int fieldCount = count_data_fields(fileContents[0]);
    char **formattedFileContents = fileContents;
    for(int i = 1; i < lineCount; i++)
    {
        formattedFileContents[i] = prune_and_trim_problematic_characters_from_string(fileContents[i], delimiter, fieldCount);
        
    }
    print_file_contents(formattedFileContents, lineCount);

    
    
    
    
    
    
    
    /*-----------   Capture Plottable Data from 'fileContents' and write to directory at the same level as the original file. (too long to explain here)   -----------*/
    write_data_set(formattedFileContents, dataSetFilePathName, delimiter);
    
    
    
    
    
    /*-----------   Create the Directory for Parsed Data files to Go Inrto  -----------*/
    //char *dataSetFileDirectory = find_file_directory_path(dataSetFilePathName);
    //char *dataSetFileName = find_name_from_path(dataSetFilePathName);
    //char *dataSetFileExtension = identify_file_extension(dataSetFilePathName);
    //dataSetFileDirectory = combine_char_ptr(dataSetFileDirectory, dataSetFileName);
    //const char *dataSetDirectory = combine_char_ptr(dataSetFileDirectory, "_Parsed");
    //dataSetDirectory = combine_char_ptr(dataSetDirectory, dataSetFileExtension);
    //const char *parsedDataDirectory = create_directory(dataSetDirectory);
    
    
    
    
    
    /*-----------   Parse, Categorize, and Capture the File Contents Array of Strings With a Generalized Parsing Function   -----------*
    int parameterCount = 0; // The number of parameters defining any given data entry, as read from the header line of the csv data set file
    char*** separatedData = parse_entire_file(formattedFileContents, lineCount, &parameterCount, delimiter);
    printf("\n\n\n\n\n\n\nrun_data_set parsed  ==============================================================================================\n\n");
    for (int i = 0; i < parameterCount; i++)
    {
        /// Capture the Current Parameter's Data Entries and Write them to the Parsed Data Directory
        char **dataSetParameter = separatedData[i];
        
        
        if(dataSetParameter[i]) //Check this data set parameter
        {
            
        }
        
        /// Create a Parsed Data Parameter File to Store the Current Parameter's Header and Data Entries
        const char *parsedDataFilePathName = parsedDataDirectory;
        const char *parameterParsed = allocate_memory_char_ptr(parameterCount);
        sprintf(parameterParsed, "_Parsed_Data_Parameter_%d.txt", i);
        parsedDataFilePathName = combine_char_ptr(parsedDataFilePathName, parameterParsed);
        
        FILE *parsedDataFile = fopen(parsedDataFilePathName, "w+");
        write_file_contents(parsedDataFilePathName, dataSetParameter);
        fclose(parsedDataFile);
        
        

        
        
        /// Create a Parsed Data File to Store all the Parsed Data Files, Append File Contents at Each Loop Iteration

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        free(parsedDataFilePathName);
        free(parameterParsed);
   
        
        printf("\n\n\n\n%s\n", separatedData[i][0]); // Print the key, aka the parameter name
        for (int j = 1; j < lineCount; j++)
        {
            printf(" %s\n", separatedData[i][j]); // Print the values
        }
    }
    printf("\n\n\n==============================================================================================");
    
    
    
    //parameterCount = 0;
    
    
    
    //print_string_array(fileContents, lineCount, parsedDataDirectory);
    print_string_array_array(separatedData, parameterCount, lineCount, "separatedData print_string_array_array");
    deallocate_memory_char_ptr_ptr(fileContents, lineCount);
    //deallocate_memory_char_ptr_ptr(formattedFileContents, lineCount);
     //*/
}


/**
 please create a short summary of the DataSetUtilities.h file to be placed at the top of the header file, using the below implementation file as a reference for the purpose of this file:

 please help me to organize and extend my documentation of my plain c code for the 'extern const char *months[12]' array of month names, the
 'extern const char *weekDays[7]' array of weekday names, and the 'extern const char *commonDateTimeFormats[12]' array of commonly used date/time formats, used for detecting and formatting date/time fields from a data set's contents


 please help me to create documentation for my c functions below by providing line by line detailed explanations of the c code below:


 please provide line by line detailed explanations of the entirety of my plain c code in the FileUtilities header and FileUtilities implementation file. For function prototypes, you need only include a short description of what the main purpose of the function is, for example: "char** read_file_contents(const char* filePathName, int lineCount); // Reads the contents of a file into a string array", for the function implementations however(in 'FileUtilities.c'), rigorous, detailed, and informative documentation is required for each function.
 
 please try to scan
 this level of detail is satisfactory for the simpler functions in the FileUtilities.c file, however, for the more complex functions(namely the file reading and writing functions), a higher level of detail would be preferrable. please  proceed with similar documentation for the remaining functions in FileUtilities.c
 */
