//  DataSetUtilities.h
//  ECE-370_Integration_And_Data_Analysis


#ifndef DataSetUtilities_h
#define DataSetUtilities_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>












































/**
 * Particle Structure: Represents a Particle
 *
 * This struct contains all the information that defines a particle in physics.
 * Each member variable holds a specific characteristic for defining the
 * physical and quantum characteristics of a particle.
 *
 * - pdg_id: The Particle Data Group identification number for the particle.
 * - pdg_name: The PDG name of the particle.
 * - name: The commonly used name for the particle.
 * - charge: The electrical charge of the particle.
 * - rank: The rank or classification index of the particle.
 * - quarks: String representation of the quark composition, applicable for composite particles.
 * - mass: The mass of the particle, fundamental for gravitational interactions.
 * - mass_lower_uncertainty: The lower bound of uncertainty in the mass measurement, indicating precision.
 * - mass_upper_uncertainty: The upper bound of uncertainty in the mass measurement.
 * - decay_width: A measure of the particle's stability; the decay width inversely relates to the particle's lifespan.
 * - decay_width_lower: Lower uncertainty bound of the decay width, reflecting measurement precision.
 * - decay_width_upper: Upper uncertainty bound of the decay width.
 */
typedef struct
{
    int pdg_id;
    char pdg_name[25];
    char name[25];
    double charge;
    int rank;
    char quarks[25];
    double mass;
    double mass_lower_uncertainty;
    double mass_upper_uncertainty;
    double decay_width;
    double decay_width_lower;
    double decay_width_upper;
} Particle;


Particle parse_particle_data(char *dataEntry, const char *delimiter);
void print_particle(Particle ptrcle);








/**
 * WeatherMeasurement Structure: Represents a weather measurement.
 *
 * This structure encapsulates the various attributes of a weather measurement,
 * collected from a monitoring station. Each member variable is associated
 * with a specific meteorological field.
 *
 * - index: The identification number for the data entry.
 * - stationName: The name of the station taking the measurement.
 * - dateTime: The date the measurement was taken.
 * - airTemperature: Temperature of the air.
 * - wetBulbTemperatire: Temperature of the air when it is saturated with water vapor.
 * - humidity: Humidity
 * - rainIntensity: Intensity of the rain. (Float)
 * - intervalRain: Amount of rain in a given interval. (Float)
 * - totalRain: Total amount of rain. (Float)
 * - precipitationType: Type of precipitation. (String)
 * - windDirection: Direction of the wind. (String)
 * - windSpeed: Speed of the wind. (Float)
 * - maxWindSpeed: Maximum speed of the wind. (Float)
 * - barometricPressure: Pressure of the atmosphere. (Float)
 * - solarRadiation: Amount of solar radiation. (Float)
 * - heading: Direction the station is facing. (String)
 * - stationBatteryLife: Remaining battery life of the station. (Float)
 * - measurementTimeStamp: Label for the measurement timestamp. (String)
 * - measurementIdentification: Measurement Id
 */
typedef struct
{
    int index;
    char stationName[50];
    char dateTime[50];
    double airTemperature;
    double wetBulbTemperatire;
    double humidity;
    double rainIntensity;
    double intervalRain;
    double totalRain;
    char precipitationType[50];
    char windDirection[50];
    double windSpeed;
    double maxWindSpeed;
    double barometricPressure;
    double solarRadiation;
    char heading[50];
    double stationBatteryLife;
    char measurementTimeStamp[50];
    char measurementIdentification[100];
} WeatherMeasurement;

WeatherMeasurement parse_weather_measurement_data(const char *data, const char *delimiter);
void print_weather_measurement(WeatherMeasurement weatherMeasurement);
































































































// ------------- Helper Functions for Capturing and Formatting Data from an Existing File/Data Set -------------
/// \{
char*** parse_entire_file(char **fileContents, int lineCount, int* fieldCount, const char *delimiter);
int* count_missing_values(char** fileContents, int lineCount, int fieldCount, const char *delimiter, const char *headerLine);
char** capture_data_set_header_for_plotting(char* headerContents, char** fileContents, const char *delimiter); // Captures and formats header information for plotting purposes.
char** determine_data_entry_types(const char *dataEntry, int fieldCount, const char *delimiter); // Determines the data types of fields in a data entry.
char** capture_plottable_fields(char *headerLine, char* dataEntry, int fieldCount, const char *delimiter); // Captures fields from a data entry suitable for plotting.
char *format_data_entry_for_plotting(char *headerLine, char* dataEntry, int fieldCount, const char *delimiter); // Formats a data entry for plotting, ensuring correct data type for each field.
char** capture_data_set_for_plotting(char** fileContents, int lineCount, const char *delimiter); // Processes a dataset for plotting by extracting and formatting numeric fields.
/// \}






// ------------- Helper Functions for Extracting Plottable Data Fields -------------
/// \{
double *extract_plottable_data_field(char** dataSetContents, int fieldIndex, int fieldCount, const char *delimiter); // Writes the plottable data extracted from the dataset to files.
double **extract_plottable_data(char** dataSetContents, int fieldCount, const char *dataDirectory, const char *delimiter); // Extracts all plottable data fields from the dataset and writes them into separate files.
/// \}






// ------------- Helper Functions for Creating and Populating a Formatted File from a Data Set -------------
/// \{
const char *write_plottable_data(char** dataSetContents, char *headerLine, const char *filePathName, const char *dataDirectory, const char *delimiter); // Writes the plottable data extracted from the dataset to files.
char *write_data_set(char** fileContents, const char *filePathName, const char *delimiter); // Processes and writes a dataset to files, separating plottable and non-plottable data.
/// \}






#endif /* DataSetUtilities_h */
