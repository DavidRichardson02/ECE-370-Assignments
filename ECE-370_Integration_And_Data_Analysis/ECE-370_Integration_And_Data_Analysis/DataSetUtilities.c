//  DataSetUtilities.c
//  ECE-370_Integration_And_Data_Analysis


#include "DataSetUtilities.h"
#include "GeneralUtilities.h"
#include "StringUtilities.h"
#include "FileUtilities.h"
#include <ctype.h>






/**
 * parse_particle_data
 *
 * Parses a string containing particle data into a Particle structure.
 * This function tokenizes a string using commas as delimiters. Each token represents a different attribute of the Particle structure.
 * It checks and handles potential conversion errors for numerical fields and ensures correct assignment of string values.
 * The function is designed to robustly handle input data and report any inconsistencies or conversion issues.
 * The function assumes that the input string 'data' is well-formed and contains
 * fields in the order defined in the WeatherMeasurement struct.
 *
 * @param data Constant character pointer to the comma-separated string containing particle data.
 * @return A Particle structure populated with the parsed data.
 */
Particle parse_particle_data(char *data, const char *delimiter)
{
    // Initialize a Particle struct to store the parsed data
    Particle p;

    
    // Variables for string tokenization and parsing
    char *token;
    char *endptr;
    size_t length = strlen(data);
    
    
    // Create a temporary copy of the data to modify and parse
    char *temp_data = allocate_memory_char_ptr(length + 1);
    memcpy(temp_data, data, length + 1);

    
    // Replace any non-digit negative signs with zero to prevent parsing errors, i.e., double commas with a space to handle missing values
    // Singular '-' signs for a data entry's value is not compatible with parsing model
    for(int i = 0; i < length+1;i++)
    {
        if(char_is_sign(temp_data[i]) && (isdigit((unsigned char)temp_data[i+1] != 0) || temp_data[i+1] == ',')) // If this char is a sign, ensure it is not preceding some numerical value by including a condition for either the next character not being a digit or as being a comma
        {
            temp_data[i] = '0';
        }
    }
    
    
    // Parse the data using tokenization, converting string representations to appropriate types
    
    // PDG ID
    token = strtok(temp_data, delimiter);
    if (token != NULL)
    {
        p.pdg_id = (int)strtol(token, &endptr, 10);
        // Check if the conversion was successful
        if (*endptr != '\0')
        {
            fprintf(stderr, "Conversion error for pdg_id with value: %s\n", token);
        }
    }

    
    // PDG Name
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strncpy(p.pdg_name, token, sizeof(p.pdg_name) - 1);
    }


    // Name
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strncpy(p.name, token, sizeof(p.name) - 1);
    }

    
    
    // Charge
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        p.charge = strtod(token, &endptr);
        
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for charge with value: %s\n", token);
        }
    }
    

    // Rank
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        p.rank = atoi(token);
    }

    
    // Quarks
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strncpy(p.quarks, token, sizeof(p.quarks) - 1);
    }

    

    // Mass
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        p.mass = strtod(token, &endptr);
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for mass with value: %s\n", token);
            p.mass = 0;
        }
    }
    
    
    // Mass Lower Uncertainty
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        p.mass_lower_uncertainty = strtod(token, &endptr);
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for mass_lower_uncertainty with value: %s\n", token);
            p.mass_lower_uncertainty = 0;
        }
    }

    
    // Mass Upper Uncertainty
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        p.mass_upper_uncertainty = strtod(token, &endptr);
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for mass_upper_uncertainty with value: %s\n", token);
            p.mass_upper_uncertainty = 0;
        }
    }

    
    
    // Decay Width
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        p.decay_width = strtod(token, &endptr);
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for decay_width with value: %s\n", token);
            p.decay_width = 0;
        }
    }

    
    // Decay Width Lower
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        p.decay_width_lower = strtod(token, &endptr);
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for decay_width_lower with value: %s\n", token);
            p.decay_width_lower = 0;
        }
    }

    
    // Decay Width Upper
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        p.decay_width_upper = strtod(token, &endptr);
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for decay_width_upper with value: %s\n", token);
            p.decay_width_upper = 0;
        }
    }

    
    
    // Ensure strings are null-terminated after using strncpy
    p.pdg_name[sizeof(p.pdg_name) - 1] = '\0';
    p.name[sizeof(p.name) - 1] = '\0';
    p.quarks[sizeof(p.quarks) - 1] = '\0';
    free(temp_data); // Free the duplicated string

    return p;
}


/**
 * print_particle
 *
 * Displays the details of a Particle instance.
 * This function prints all the attributes of a Particle to the standard output in a readable format.
 *
 * @param ptrcle The Particle instance to be printed.
 */
void print_particle(Particle ptrcle)
{
    // Print all the details of the particle structure
    printf("\n\n\n\n\n\n\n\n print_particle %s =========================================================================================", ptrcle.name);
    printf("\n\npdg_id: %d", ptrcle.pdg_id);
    printf("\npdg_name: %s", ptrcle.pdg_name);
    printf("\n\nname: %s", ptrcle.name);
    printf("\n\ncharge: %.17g", ptrcle.charge);
    printf("\n\nrank: %d", ptrcle.rank);
    printf("\n\nquarks: %s", ptrcle.quarks);
    
    printf("\n\nmass: %lf", ptrcle.mass);
    printf("\nmass_lower_uncertainty: %.17g", ptrcle.mass_lower_uncertainty);
    printf("\nmass_upper_uncertainty: %.17g", ptrcle.mass_upper_uncertainty);
    
    printf("\n\ndecay_width: %.17g", ptrcle.decay_width);
    printf("\ndecay_width_lower: %.17g", ptrcle.decay_width_lower);
    printf("\ndecay_width_upper: %.17g", ptrcle.decay_width_upper);
    
    printf("\n\n\n\n==============================================================================================");
}












/**
 * parse_weather_measurement_data
 *
 * Utility function to parse a string into a WeatherMeasurement struct.
 * This function takes a string containing comma-separated values representing
 * weather measurement data and converts it into a WeatherMeasurement struct.
 * It handles conversion of string data to appropriate data types and validates
 * the conversion process. Any anomalies or conversion errors are reported to stderr.
 * The function assumes that the input string 'data' is well-formed and contains
 * fields in the order defined in the WeatherMeasurement struct.
 *
 * @param data Constant character pointer to the string containing the weather data.
 * @return A WeatherMeasurement struct populated with the parsed data.
 */
WeatherMeasurement parse_weather_measurement_data(const char *data, const char *delimiter)
{
    // Initialize a WeatherMeasurement struct to store the parsed data
    WeatherMeasurement wm;
    
    
    // Variables for string tokenization and parsing
    char *token;
    char *endptr;
    size_t length = strlen(data);
    
    
    // Create a temporary copy of the data to modify and parse
    char *temp_data = allocate_memory_char_ptr(length + 1);
    memcpy(temp_data, data, length + 1);

    // Replace double commas with a space to handle missing values
    // This ensures that empty fields are accounted for during tokenization
    for(int i = 0; i < length+1;i++)
    {
        if(temp_data[i] == ',' && temp_data[i+1] == ',')
        {
            temp_data[i] = ' ';
        }
    }
    


    // Tokenization and parsing: Convert the string data into respective fields of WeatherMeasurement struct
    // Each token represents a different attribute of the struct
    // Parsing is done carefully to convert string representations to appropriate data types
    
    token = strtok(temp_data, delimiter);
    if (token != NULL)
    {
        wm.index = (int)strtol(token, &endptr, 10);
        // Check if the conversion was successful
        if (*endptr != '\0')
        {
            fprintf(stderr, "Conversion error for index with value: %s\n", token);
        }
    }

 
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strncpy(wm.stationName, token, sizeof(wm.stationName) - 1);
    }

    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strncpy(wm.dateTime, token, sizeof(wm.dateTime) - 1);
    }
    
    
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        wm.airTemperature = strtod(token, &endptr);
        
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for airTemperature with value: %s\n", token);
        }
    }
    
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        wm.wetBulbTemperatire = strtod(token, &endptr);
        
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for wetBulbTemperatire with value: %s\n", token);
        }
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        wm.humidity = strtod(token, &endptr);
        
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for humidity with value: %s\n", token);
        }
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        wm.rainIntensity = strtod(token, &endptr);
        
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for rainIntensity with value: %s\n", token);
        }
    }
    
    
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        wm.intervalRain = strtod(token, &endptr);
        
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for intervalRain with value: %s\n", token);
        }
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        wm.totalRain = strtod(token, &endptr);
        
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for totalRain with value: %s\n", token);
        }
    }
    
   
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strncpy(wm.precipitationType, token, sizeof(wm.precipitationType) - 1);
    }

    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strncpy(wm.windDirection, token, sizeof(wm.windDirection) - 1);
    }
    
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        wm.windSpeed = strtod(token, &endptr);
        
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for windSpeed with value: %s\n", token);
        }
    }
    
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        wm.maxWindSpeed = strtod(token, &endptr);
        
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for maxWindSpeed with value: %s\n", token);
        }
    }
    
    
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        wm.barometricPressure = strtod(token, &endptr);
        
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for barometricPressure with value: %s\n", token);
        }
    }
    
    
    
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        wm.solarRadiation = strtod(token, &endptr);
        
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for solarRadiation with value: %s\n", token);
        }
    }
    
    
    
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strncpy(wm.heading, token, sizeof(wm.heading) - 1);
    }
    
    
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        wm.stationBatteryLife = strtod(token, &endptr);
        
        // Check if the conversion was successful
        if (*endptr != '\0' && *endptr != ',')
        {
            fprintf(stderr, "Conversion error for stationBatteryLife with value: %s\n", token);
        }
    }
    
    
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strncpy(wm.measurementTimeStamp, token, sizeof(wm.measurementTimeStamp) - 1);
    }
    
    
    
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strncpy(wm.measurementIdentification, token, sizeof(wm.measurementIdentification) - 1);
    }
    
    
    
    
    // Remember to null-terminate the strings after using strncpy
    wm.stationName[sizeof(wm.stationName) - 1] = '\0';
    wm.dateTime[sizeof(wm.dateTime) - 1] = '\0';
    wm.precipitationType[sizeof(wm.precipitationType) - 1] = '\0';
    wm.windDirection[sizeof(wm.windDirection) - 1] = '\0';
    wm.heading[sizeof(wm.heading) - 1] = '\0';
    wm.measurementTimeStamp[sizeof(wm.measurementTimeStamp) - 1] = '\0';
    wm.measurementIdentification[sizeof(wm.measurementIdentification) - 1] = '\0';
    free(temp_data); // Free the duplicated string

    return wm;
}


void print_weather_measurement(WeatherMeasurement weatherMeasurement)
{
    printf("\n\n\n\n\n\n\n\n print_weather_measurement %s =========================================================================================", weatherMeasurement.stationName);
    printf("\n\nWeather Measurement: %d", weatherMeasurement.index);
    
    printf("\n stationName: %s", weatherMeasurement.stationName);
    printf("\n\n dateTime: %s", weatherMeasurement.dateTime);
    
    printf("\n\n airTemperature: %.17g", weatherMeasurement.airTemperature);
    printf("\n\n wetBulbTemperatire: %.17g", weatherMeasurement.wetBulbTemperatire);
    printf("\n\n humidity: %.17g", weatherMeasurement.humidity);
    
    printf("\n\n rainIntensity: %.17g", weatherMeasurement.rainIntensity);
    printf("\n\n intervalRain: %.17g", weatherMeasurement.intervalRain);
    printf("\n\n totalRain: %.17g", weatherMeasurement.totalRain);
    
    printf("\n precipitationType: %s", weatherMeasurement.precipitationType);
    printf("\n\n windDirection: %s", weatherMeasurement.windDirection);
    
    printf("\n\n windSpeed: %.17g", weatherMeasurement.windSpeed);
    printf("\n\n maxWindSpeed: %.17g", weatherMeasurement.maxWindSpeed);
    printf("\n\n barometricPressure: %.17g", weatherMeasurement.barometricPressure);
    printf("\n\n solarRadiation: %.17g", weatherMeasurement.solarRadiation);
    
    
    
    printf("\n\n heading: %s", weatherMeasurement.heading);
    printf("\n\n stationBatteryLife: %.17g", weatherMeasurement.stationBatteryLife);
    printf("\n measurementTimeStamp: %s", weatherMeasurement.measurementTimeStamp);
    printf("\n\n measurementIdentification: %s", weatherMeasurement.measurementIdentification);
    
    printf("\n\n\n\n==============================================================================================");
}





















































































































































































































/**
 * parse_entire_file
 *
 * Function to parse the entire file contents.
 * One of the first major steps for preparing the file contents(data set) for plotting, Function to parse the entirety of a CSV file's contents and capture the results in array of arrays of strings, categorizing and sorting all of the values of each one of the dataset's fields and storing them in their own individual char** as a list of values where the file is named
 *
 * @param fileContents Constant character pointer to the string containing the weather data.
 * @param lineCount Constant character pointer to the string containing the weather data.
 * @param fieldCount Pointer to the integer value representing the number of paramaters a data set has.
 * @return An array of arrays of strings, where each of the ith subarrays of the highest level array is a representation of the ith data set fields and all the entries within it, while the
 */
char*** parse_entire_file(char **fileContents, int lineCount, int* fieldCount, const char *delimiter)
{
    char **fileHeader = capture_data_set_header_for_plotting(fileContents[0], fileContents, delimiter);
    int fieldCountCopy = count_data_fields(fileContents[0]);
    
    
    /*----------- Capture the Data Field Names in a Single String Without the typeDelimiters -----------*/
    const char *fieldNames[fieldCountCopy]; //The string of field names as they appear in the first element of the fileContents array of strings
    for (int i = 0; i < fieldCountCopy; i++)
    {
        const char *typeDelimiter = identify_delimiter(fileHeader, fieldCountCopy);
        
        char* typeDelimiterToken = strtok(fileHeader[i], typeDelimiter); // Split the token by the type delimiter to get the name
        if (typeDelimiterToken)
        {
            fieldNames[i] = strdup(typeDelimiterToken);
        }
        print_string(fieldNames[i]);
    }
    
    
    // Allocate array of string arrays for each member
    char*** separatedData = malloc(fieldCountCopy * sizeof(char**));
    
    // Initialize arrays for each member
    for (int i = 0; i < fieldCountCopy; i++)
    {
        separatedData[i] = malloc((lineCount) * sizeof(char*)); // No need for +1, skipping header
        if (!separatedData[i])
        {
            while (i--)
            {
                free(separatedData[i]);
            }
            free(separatedData);
            *fieldCount = 0;
            return NULL;
        }
        separatedData[i][0] = strdup(fieldNames[i]); // Copy the key name
        free((void*)fieldNames[i]); // Free fieldNames elements
    }
    
    
    
    
    for (int line = 1; line < lineCount; line++) // Start from line 1 to skip header
    {
        char* dataCopy = strdup(fileContents[line]);
        
        char* token = strtok(dataCopy, delimiter);
        for (int i = 0; i < fieldCountCopy && token; i++)
        {
            separatedData[i][line] = strdup(token);
            token = strtok(NULL, delimiter);
        }
        free(dataCopy);
    }

    *fieldCount = fieldCountCopy;
    return separatedData;
}










































































/**
 * count_missing_values
 *
 * Counts the number of missing or incorrectly formatted values per field in the dataset.
 *
 * @param fileContents Array of strings where each string is a line in the dataset.
 * @param lineCount Number of lines in the dataset.
 * @param fieldCount Number of fields in each line.
 * @param delimiter Delimiter used in the dataset.
 * @param headerLine Header line of the dataset to determine the data types of fields.
 * @return An array of integers where each integer represents the count of missing or incorrectly formatted values for a corresponding field.
 */
int* count_missing_values(char** fileContents, int lineCount, int fieldCount, const char *delimiter, const char *headerLine)
{
    if (!fileContents || lineCount <= 0 || fieldCount <= 0)
    {
        return NULL;
    }

    int *missingDataCount = calloc(fieldCount, sizeof(int)); // Initialize counts to zero
    if (!missingDataCount)
    {
        perror("Memory allocation failed for missingDataCount");
        return NULL;
    }

    // Analyze the data types based on the header line (assuming first line is the header)
    char **dataTypes = determine_data_entry_types(fileContents[1], fieldCount, delimiter);
    printf("\n\nlineCount: %d           fieldCount: %d", lineCount, fieldCount);
    print_string_array(dataTypes, fieldCount, "Data Types");
    
    
    for (int i = 0; i < lineCount; i++) // Start from 1 to skip the header
    {
        char *dataCopy = strdup(fileContents[i]);
        char *token = strtok(dataCopy, delimiter);
        int fieldIndex = 0;

        while (token && fieldIndex < fieldCount)
        {
            while (isspace((unsigned char)*token)) token++; // Trim leading spaces from the token
            
            const char *typeDataEntry = determine_string_representation_type(token);
            
 
            
            /// Here the delimited value is nothing but a hyphen "-". This field is assumed to be a missing value(either N/A or not available)
            /// Furthermore, to ensure the value is not being used as a minus sign, a check is made to ensure the token is nonnumeric
            if (strcmp(token, "-") == 0 && strcmp(dataTypes[fieldIndex], "nonnumeric") == 0 )
            {
                //printf("\n\nThe token at fieldIndex %d on line %d, was N/A ", fieldIndex, i);
                //printf("\ntoken: %s", token);
                missingDataCount[fieldIndex]++;
            }
            else if (strcmp(typeDataEntry, dataTypes[fieldIndex]) != 0) //The determined data type does not match the expected data type
            {
                printf("\n\n\n\nToken's expected and determined data type mismatch at fieldIndex %d on line %d", fieldIndex, i);
                printf("\nToken: %s", token);
                
                printf("\nExpected: %s", typeDataEntry);
                printf("                Determined: %s\n\n", dataTypes[fieldIndex]);

                missingDataCount[fieldIndex]++;
            }
            
        

            //if(string_is_numeric(token) != string_is_numeric(dataTypes[fieldIndex]))
            //{
            //    printf("\n\n token: %s", token);
            //    missingDataCount[fieldIndex]++;
            //}
            
            //if (strcmp(typeDataEntry, dataTypes[fieldIndex]) != 0 )//||
                //(strcmp(token, "-") == 0 && strcmp(dataTypes[fieldIndex], "numeric") == 0))
            //{
            //    missingDataCount[fieldIndex]++;
            //}

            token = strtok(NULL, delimiter);
            fieldIndex++;
        }

        free(dataCopy);
    }

    for (int i = 0; i < fieldCount; i++)
    {
        free(dataTypes[i]);
    }
    free(dataTypes);

    return missingDataCount;
}

/**
 * capture_data_set_header_for_plotting
 *
 * Processes the header line of a dataset to pair each field with its corresponding data type
 * determined from the dataset's contents. Captures and formats the header information for
 * preparing data for plotting by knowing the type of each field.
 *
 *
 * @param headerContents A string containing the header line of the dataset.
 * @param fileContents An array of strings, each representing a line in the dataset.
 * @param delimiter A character used as a delimiter in the dataset.
 * @return An array of strings where each string is a field name from the header paired with its data type.
 */
char** capture_data_set_header_for_plotting(char* headerContents, char** fileContents, const char *delimiter)
{
    // Counts the number of fields in the header.
    int fieldCount = count_data_fields(headerContents);

    // Determines the data types of each field based on the second line of file contents.
    char **dataTypes = determine_data_entry_types(fileContents[1], fieldCount, delimiter);

    // Calculates total length needed for formatted data (field name + data type).
    int formatDataLength = 0;
    for (int i = 0; i < fieldCount; i++)
    {
        formatDataLength += strlen(dataTypes[i]) + 1;
    }
    
    
    // Allocates memory for storing formatted field names and types, indexing each field to capture all plotting relevant fields from the contents file
    char **fieldIndexing = allocate_memory_char_ptr_ptr(formatDataLength, fieldCount);
    
    
    
    // Duplicates the header string for tokenization.
    char* headerCopy = strdup(headerContents);

    
    // Tokenize the header and pair each field with its data type.
    char* token = strtok(headerCopy, delimiter);
    int formatIndex = 0;
    while(token && formatIndex < fieldCount)
    {
        strcpy(fieldIndexing[formatIndex], token); // Copy the token into fieldIndexing
        strcat(fieldIndexing[formatIndex], ":");   // Append the type delimiter.
        strcat(fieldIndexing[formatIndex], dataTypes[formatIndex]); // Append the data type.
        

        // Get the next token
        formatIndex++;
        token = strtok(NULL, delimiter);
    }
    free(headerCopy);

    
    return fieldIndexing; // Returns formatted field names with data types.
}






/**
 * determine_data_entry_types
 *
 * Determines the data types of fields in a data entry.
 * Analyzes a line from the dataset to infer the data type of each field.
 * It helps in understanding the kind of data each field in the dataset holds.
 *
 * @param dataEntry A string containing a line from the dataset.
 * @param fieldCount The number of fields in the data entry.
 * @param delimiter The character used as a delimiter in the dataset.
 * @return An array of strings where each string represents the inferred data type of a field.
 */
char** determine_data_entry_types(const char *dataEntry, int fieldCount, const char *delimiter)
{
    // Increase the buffer size to accommodate additional characters
    size_t characterCount = (strlen(dataEntry) + 1) * 3;
    
    // Allocate memory for storing data types of each field.
    char** dataFields = allocate_memory_char_ptr_ptr(characterCount, fieldCount);

    // Initialize the dataFields array with empty strings.
    for(int i = 0; i < fieldCount; i++)
    {
        strcpy(dataFields[i], "\0");
    }

    
    int fieldIndex = 0;
    char* dataCopy = strdup(dataEntry); // Create a copy of dataEntry to use with strtok (as it modifies the string)
    char* token = strtok(dataCopy, delimiter); // Tokenize and analyze each field
    while(token && fieldIndex < fieldCount)
    {
        // Check if the token is a double to determine the type of the field
        const char* type = determine_string_representation_type(token);
        strncat(dataFields[fieldIndex], type, characterCount - strlen(dataFields[fieldIndex]) - 1);

        // Get the next token
        fieldIndex++;
        token = strtok(NULL, delimiter);
        
    }
    
    
    free(dataCopy);
    return dataFields;
}






/**
 * format_data_entry_for_plotting
 *
 * Formats a data entry for plotting by ensuring each field is of the correct data type.
 * Primarily used for preparing data lines for plotting where data types need to be consistent.
 * The function processes a line from the dataset, converting fields to a default value if they don't match
 * the expected data type (i.e., replacing non-numeric values with '0.0' in numeric fields).
 *
 * @param headerLine The header line of the dataset.
 * @param dataEntry A line from the dataset.
 * @param fieldCount Number of fields in the data entry.
 * @param delimiter The delimiter used in the dataset.
 * @return A new string with the formatted data entry.
 */
char *format_data_entry_for_plotting(char *headerLine, char* dataEntry, int fieldCount, const char *delimiter)
{
    // Create a buffer for the formatted data entry, making it larger to accommodate potential changes
    size_t bufferSize = strlen(dataEntry) + fieldCount * 3; // Extra space for "0.0" and commas
    char* formattedDataEntry = allocate_memory_char_ptr(bufferSize);
    strcpy(&formattedDataEntry[0], "\0"); // Initialize the string empty
    char* dataCopy = strdup(dataEntry);
    
    
    char* token;
    char* saveptr;
    token = strtok_r(dataCopy, delimiter, &saveptr);
    int formatIndex = 0;

    
    // Determine the data types for each field in the header.
    char** dataTypes = determine_data_entry_types(headerLine, fieldCount, delimiter);

    
    // Process each field based on its data type.
    while (token && formatIndex < fieldCount)
    {
        // Trim leading spaces from the token
        while (isspace((unsigned char)*token)) token++;

        // Determine the type of data in the token.
        const char* typeDataEntry = determine_string_representation_type(token);

        
        
        // Handling non-numeric or incorrectly formatted fields.
        if (strcmp(token, "-") == 0 && strcmp(dataTypes[formatIndex], "numeric") == 0 )
        {
            strcat(formattedDataEntry, "0.0"); // Replace with default numeric value.
        }
        else if (strcmp(typeDataEntry, dataTypes[formatIndex]) != 0) //The determined data type does not match the expected data type
        {
            if (strcmp(dataTypes[formatIndex], "numeric") == 0)
            {
                strcat(formattedDataEntry, "0.0"); // Replace non-numeric values in numeric fields.
            }
            // If it is expected to be a string but is not, we remove it (by doing nothing here)
        }
        else
        {
            strcat(formattedDataEntry, token); // Append correct token.
        }
        
        
        // Append delimiter except for the last token
        if (formatIndex < fieldCount - 1)
        {
            strcat(formattedDataEntry, delimiter);
        }
        
        formatIndex++;
        token = strtok_r(NULL, delimiter, &saveptr);
    }

    
    
    free(dataCopy);
    for (int i = 0; i < fieldCount; i++)
    {
        free(dataTypes[i]);
    }
    free(dataTypes);
    return formattedDataEntry;
}






/**
 * capture_plottable_fields
 *
 * Captures and formats fields from a data entry that are suitable for plotting.
 * This function processes a line from the dataset and extracts numeric fields,
 * which are typically the ones used in plotting.
 *
 * @param headerLine The header line of the dataset.
 * @param dataEntry A line from the dataset.
 * @param fieldCount Number of fields in the data entry.
 * @param delimiter The delimiter used in the dataset.
 * @return An array of strings containing only the numeric fields from the data entry.
 */
char** capture_plottable_fields(char *headerLine, char* dataEntry, int fieldCount, const char *delimiter)
{
    // Format the data entry for plotting.
    char *formattedData = format_data_entry_for_plotting(headerLine, dataEntry, fieldCount, delimiter);

    // Allocate memory for plottable fields.
    char** plottableFields = allocate_memory_char_ptr_ptr(0, fieldCount);

    // Duplicate formatted data for processing.
    char* dataCopy = strdup(formattedData);
    char* token = strtok(dataCopy, delimiter);
    int plottableIndex = 0;

    // Extract numeric fields for plotting.
    while (token)
    {
        if (string_is_numeric(token))  // Check if the field is numeric.
        {
            plottableFields[plottableIndex] = allocate_memory_char_ptr(strlen(token) + 1);      // Allocate memory for the plottable field
            strcpy(plottableFields[plottableIndex], token); // Copy the token to the plottable field
            plottableIndex++;
        }
        // Get the next token
        token = strtok(NULL, delimiter);
    }
    free(dataCopy);
    free(formattedData); // Free the formatted data, which is no longer needed


    return plottableFields;
}




/**
 * capture_data_set_for_plotting
 *
 * Processes a dataset for plotting by extracting and formatting numeric fields.
 * Goes through each line in the dataset, capturing only the numeric fields, and formats them for plotting.
 *
 * @param fileContents Array of strings representing the dataset.
 * @param lineCount The number of lines in the dataset.
 * @param delimiter The delimiter used in the dataset.
 * @return An array of strings, each representing a line in the dataset with only plottable fields.
 */
char** capture_data_set_for_plotting(char** fileContents, int lineCount, const char *delimiter)
{
    // Assume the first line is the header to determine the format
    char *headerLine = fileContents[1];
    int fieldCount = count_data_fields(headerLine);
    
    
    
    // Allocate memory for the new dataset
    char** processedDataSet = allocate_memory_char_ptr_ptr(MAX_STRING_SIZE, lineCount); // Assuming max length of processed line

    for (int i = 0; i < lineCount; i++)
    {
        // Extract plottable fields from each line of the dataset.
        char** plottableFields = capture_plottable_fields(headerLine, fileContents[i], fieldCount, delimiter);

        // Concatenate plottable fields into a single string for each line.
        char* concatenatedFields = concatenate_string_array(plottableFields, fieldCount, delimiter);

        // Store the concatenated string in the processed dataset.
        processedDataSet[i] = concatenatedFields;

        
        
        // Free the array of plottable fields
        for (int j = 0; j < fieldCount && plottableFields[j] != NULL; j++)
        {
            free(plottableFields[j]);
        }
        free(plottableFields);
    }

    
    return processedDataSet;
}












/**
 * extract_plottable_data_field
 *
 * Extracts a specific plottable data field from the dataset for plotting purposes.
 * It allocates memory for storing the extracted numeric data and processes each line to capture the specified field.
 *
 * @param dataSetContents Array of strings representing the dataset.
 * @param fieldIndex Index of the field to be extracted.
 * @param fieldCount Number of fields in each data entry.
 * @param delimiter The delimiter used in the dataset.
 * @return An array of doubles representing the extracted data field.
 */
double *extract_plottable_data_field(char** dataSetContents, int fieldIndex, int fieldCount, const char *delimiter)
{
    // Count the number of lines in the dataset and allocate memory for plot data.
    int lineCount = count_array_strings(dataSetContents);
    double *plotData = allocate_memory_double_ptr(lineCount);

    // Process each line to extract the specified field.
    for (int i = 0; i < lineCount; i++)
    {
        char* dataEntry = dataSetContents[i]; // The current line of the data set.
        char* dataCopy = strdup(dataEntry);
        char* saveptr;
        char* token = strtok_r(dataCopy, delimiter, &saveptr);
        int currentIndex = 0;
        double fieldValue = 0.0;

        
        // Extract the field value at the specified index.
        while (token && currentIndex < fieldCount)
        {
            if (currentIndex == fieldIndex) // The field index is passed in to capture the specified data set field only.
            {
                fieldValue = atof(token); // Convert the nonnumeric token to a numeric representation as a double.
                plotData[i] = fieldValue;
                break;
            }
               
            // Not yet at the fieldIndex, iterate the currentIndex and get the next field with token.
            currentIndex++;
            token = strtok_r(NULL, delimiter, &saveptr);
        }

           
        // If after iterating through all field indexes, the specified fieldIndex of the data entry has not been found, set it to NULL 0.0.
        if (!token)
        {
            fieldValue = 0.0;
            plotData[i] = fieldValue;
        }
        free(dataCopy);
    }


    return plotData;
}




/**
 * extract_plottable_data
 *
 * Extracts all plottable data fields from the dataset and writes them into separate files.
 * It processes the dataset to extract and store each plottable field in a dedicated file for easy access and plotting.
 *
 * @param dataSetContents Array of strings representing the dataset.
 * @param fieldCount Number of fields in each data entry.
 * @param dataDirectory Directory where the extracted data will be stored.
 * @param delimiter The delimiter used in the dataset.
 * @return A 2D array of doubles representing the extracted data fields.
 */
double **extract_plottable_data(char** dataSetContents, int fieldCount, const char *dataDirectory, const char *delimiter)
{
    // Count lines and allocate memory for the dataset.
    int lineCount = count_array_strings(dataSetContents);
    double **plottableDataSet = (double**)malloc(sizeof(double*) * lineCount);

    // Extract each plottable field.
    for(int i = 0; i < fieldCount; i++)
    {
        plottableDataSet[i] = extract_plottable_data_field(dataSetContents, i, fieldCount, delimiter);
    }
    
    
    // Write data fields into separate files for each plottable field.
    const char *extractedDataDirectory = dataDirectory;
    for(int i = 0; i < fieldCount; i++)
    {
        // Construct file path name for each field.
        char *plottingDataFilePathName = extractedDataDirectory;
        char *fieldExtracted = allocate_memory_char_ptr(fieldCount);
        sprintf(fieldExtracted, "_%d.txt", i);
        plottingDataFilePathName = combine_char_ptr(plottingDataFilePathName, fieldExtracted);
        
        
        // Write the data to files.
        FILE *file = fopen(plottingDataFilePathName, "w+");
        write_file_numeric_data(plottingDataFilePathName, plottableDataSet[i], lineCount);
        fclose(file);
        
        free(plottingDataFilePathName);
        free(fieldExtracted);
    }
    
    
    
    
    
    /*-----------   Write All Data Set Fields into a Single File   -----------*/
    const char *plottingDataFilePathName = combine_char_ptr(extractedDataDirectory, ".txt");
    FILE *file = fopen(plottingDataFilePathName, "w+");
    for(int i = 0; i < fieldCount; i++)
    {
        write_file_numeric_data(plottingDataFilePathName, plottableDataSet[i], lineCount);
    }
    fclose(file);
    
    
    
    return plottableDataSet;
}








/**
 * write_plottable_data
 *
 * Writes the plottable data extracted from the dataset to files.
 * This function captures the dataset's plottable data and writes it into files for each field,
 * making it easier for later use in plotting or analysis.
 *
 * @param dataSetContents Array of strings representing the dataset.
 * @param headerLine The header line of the dataset.
 * @param filePathName Path of the file where the data will be written.
 * @param dataDirectory Directory where the extracted data will be stored.
 * @param delimiter The delimiter used in the dataset.
 * @return The path name of the file where the plottable data is written.
 */
const char *write_plottable_data(char** dataSetContents, char *headerLine, const char *filePathName, const char *dataDirectory, const char *delimiter)
{
    // Capture and process the dataset to extract plottable data
    int lineCount = count_array_strings(dataSetContents);
    int fieldCount = count_data_fields(dataSetContents[0]);
    double **plottableDataSet = extract_plottable_data(dataSetContents, fieldCount, dataDirectory, delimiter);
    
    
    
    
    
    /// For right now this portion of the code is redundant, does exactly what the second half of 'extract_plottable_data' function does, but also allows me to capture the pathname
    /// as a return value, which is not useful for now because they are all being put in the same directory that was created specifically for plottable values anyways
    /* -----------   Write Plottable Data Set Fields into a File   -----------*/
    char *fileName = find_name_from_path(filePathName);
    const char *plottingDataFilePathName = combine_char_ptr(filePathName, combine_char_ptr("/", fileName));
    plottingDataFilePathName = combine_char_ptr(plottingDataFilePathName, ".txt");
    FILE *file = fopen(plottingDataFilePathName, "w+");
    for(int i = 0; i < fieldCount; i++)
    {
        write_file_numeric_data(plottingDataFilePathName, plottableDataSet[i], lineCount);
    }
    fclose(file);
    //*/
    
    
    
    return plottingDataFilePathName;
}




/**
 * write_data_set
 *
 * Processes and writes a dataset to files, categorizing data into plottable and non-plottable types.
 * The function structures the dataset, creating separate files for plottable fields to aid in analysis
 * and plotting.
 *
 * @param fileContents Array of strings representing the dataset.
 * @param filePathName Path of the original dataset file.
 * @param delimiter The delimiter used in the dataset.
 * @return The directory where the processed dataset files are stored.
 */
char *write_data_set(char** fileContents, const char *filePathName, const char *delimiter)
{
    // Create and capture field name-type pairs from the dataset header
    char *headerLine = fileContents[0]; // Get the header line of the dataset.
    int fieldCount = count_data_fields(fileContents[0]);  // Count the number of fields in the header line.
    
    char **fileHeader = capture_data_set_header_for_plotting(headerLine,  fileContents, delimiter);  // Capture header information for plotting.
    //char *createdFileHeader = create_file_header(filePathName);
    const char *typeDelimiter = identify_delimiter(fileHeader, fieldCount);  // Identify the delimiter used in the fileHeader field name type pairs
    
    
    // Capture the Data Field Names in an array of Strings With Fields Indexed as they appear in the fileContents array of strings
    char *fieldNameTypePairs[fieldCount]; // Array to store field name and type pairs.
    for (int i = 0; i < fieldCount; i++)
    {
        // Call to strtok retrieves the field name and type
        char* nameTypeToken = strtok(fileHeader[i], typeDelimiter); // Split the token by the type delimiter to get the name
        
        if(nameTypeToken)
        {
            fieldNameTypePairs[i] = strdup(nameTypeToken);
        }
    }

    
    
    
    
    
    
    // Process the dataset for plotting
    /*-----------   Write the NON-Plottable Data to Files   -----------*/
    int lineCount = count_file_lines(filePathName, MAX_NUM_FILE_LINES);
    char **plottingData = capture_data_set_for_plotting(fileContents, lineCount, delimiter);  // Capture data suitable for plotting.
    //char** dataTypes = determine_data_entry_types(headerLine, fieldCount, delimiter);
 
    
    
    

    /*-----------   Create the Name of a File for Plotting Data Set in Same Directory as Original File   -----------*/
    char *directoryPathName = find_file_directory_path(filePathName); // Get the directory path of the file.
    char *fileName = find_name_from_path(filePathName); // Extract the filename from the path.
    //char *fileExtension = identify_file_extension(filePathName);
    
    
    
    // Create a directory for plottable data fields
    char *dataDirectory = create_directory(filePathName, "_Plottable_Fields"); // Create a directory for plottable data fields.
    
    
    
    
    //The directory to be created at the same level and location as the passed in file pathname
    directoryPathName = combine_char_ptr(directoryPathName, fileName);
    directoryPathName = combine_char_ptr(directoryPathName, "_Plottable_Fields");

    
    
    
    
    // Path to the directory in which the plottable data fields will be located, the full pathnames of the data fields file's will be this string + the actual name of the file
    char *plottableDataFieldsDirectoryFilePath = combine_char_ptr("/", combine_char_ptr(fileName, "_Plottable_Field"));
    const char *plottableFieldsPathName = combine_char_ptr(dataDirectory, plottableDataFieldsDirectoryFilePath); // Full path for plottable data fields.


    
    // Write plottable fields to files, Populate the Contents of the Plotting File with the Contents of the Array of Strings(i.e., the data entries)
    // Write plottable fields to the directory at 'directoryPathName' with pathnames 'plottableFieldsPathName'(to be followed by the index of the field and the .txt extension)
    write_plottable_data(plottingData, fileContents[0], directoryPathName, plottableFieldsPathName, delimiter);
    

    
    return dataDirectory;
}

