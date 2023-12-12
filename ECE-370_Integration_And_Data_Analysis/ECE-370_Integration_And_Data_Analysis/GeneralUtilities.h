//  GeneralUtilities.h
//  ECE-370_Integration_And_Data_Analysis
/**
 * GeneralUtilities code: Provides a collection of general utility functions that support various computational
 * and data manipulation tasks across various contexts. Encompasses functions for safe memory allocation for different data types, including basic and derived types,
 * and functions for handling date/time conversions, particularly focusing on Unix time conversions.
 *
 * Additionally, it includes utilities for bitwise operations on numerical data, useful in scenarios requiring
 * direct manipulation of the binary representation of data. It also provides robust sorting algorithms, including
 * merge sort and radix sort, optimized for handling large datasets, especially useful for sorting double precision
 * floating-point numbers.
 */


#ifndef GeneralUtilities_h
#define GeneralUtilities_h


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>




// ------------------ Global Constants and Macros -------------------
// \{
// Macro to compute the number of elements in a statically-allocated array
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Preprocessor macro that creates a string representation of its argument, the name of the variable
#define VAR_NAME_AS_STRING(var) #var


/**
 * 'months' array: This array contains the names of the twelve months of the year.
 * It is useful for converting numeric month representations into their corresponding
 * textual names.
 */
extern const char *months[12];

/**
 * 'weekDays' array: This array holds the names of the seven days of the week.
 * It can be used to map numeric day representations to
 * their corresponding day names.
 */
extern const char *weekDays[7];

/**
 * 'commonDateTimeFormats' array: An array of string literals representing commonly used date/time formats.
 * These formats are crucial in parsing and standardizing date/time strings from diverse data sources,
 * and follow the conventions used in 'strftime' and 'strptime' functions for date-time formatting and parsing.
 * Each format specifier adheres to the C standard library conventions for date/time formatting.
 */
extern const char *commonDateTimeFormats[12]; // Used for converting date/time strings from datasets into standardized formats.



static pthread_mutex_t localtime_mutex = PTHREAD_MUTEX_INITIALIZER; //Mutex for Thread Safety protecting access to localtime
// \}






// ------------- Helper Functions for Allocating Memory Safely For Basic Types -------------
/// \{
int *allocate_memory_int_ptr(size_t sizeI);
float *allocate_memory_float_ptr(size_t sizeF);
double *allocate_memory_double_ptr(size_t sizeD);
char *allocate_memory_char_ptr(size_t sizeC);
/// \}




// ------------- Helper Functions for Allocating and Deallocating Memory Safely For Derived Types -------------
/// \{
int **allocate_memory_int_ptr_ptr(size_t sizeI);
float **allocate_memory_float_ptr_ptr(size_t sizeF);
double **allocate_memory_double_ptr_ptr(size_t sizeD);
char **allocate_memory_char_ptr_ptr(size_t strSize, size_t numStrings);

void deallocate_memory_int_ptr_ptr(int **intPtrPtr, size_t numInts);
void deallocate_memory_float_ptr_ptr(float **floatPtrPtr, size_t numFloats);
void deallocate_memory_double_ptr_ptr(double **doublePtrPtr, size_t numDoubles);
void deallocate_memory_char_ptr_ptr(char **charPtrPtr, size_t numStrings);
/// \}








// ------------- Helper Functions for Performing Various Mathematical Operations on Containers -------------
/// \{
double min(double a, double b); // Returns the minimum of two values.
double max(double a, double b);  // Returns the maximum of two values.

double min_element(double *data, int n); // Returns the minimum element in an array of values.
double max_element(double *data, int n); // Returns the maximum element in an array of values.
/// \}






// ------------- Helper Functions for Operations with Time -------------
/// \{
time_t convert_to_unix_time(const char *dateTimeString); // Converts a date/time string into Unix time
struct tm *thread_safe_localtime(const time_t *tim, struct tm *result); // A thread-safe wrapper around localtime.
/// \}






// ------------- Helper Functions for Bitwise Operations(on Binary Numerals?) -------------
/// \{
uint64_t flip_sign_bit(uint64_t value); // Helper function to flip the sign bit of the double's binary representation
uint64_t double_to_uint64(double value); // Helper function to reinterpret a double as an uint64_t
double uint64_to_double(uint64_t value); // Helper function to reinterpret a uint64_t as an double
/// \}






// ------------- Helper Functions for Sorting -------------
/// \{
void merge_data(double *unsortedData, int left, int middle, int right); // Merges two sorted subarrays into a single sorted array.
void merge_sort_data(double *unsortedData, int left, int right); // Recursively divides and sorts an array using the merge sort algorithm.
void merge_sort(double *unsortedData, const int numElements); // Sorts an array of doubles using the merge sort algorithm.



void radix_sort_doubles(double *unsortedData, const int numElements); // Sorts an array of double precision floating-point numbers by interpreting their bit patterns as unsigned 64-bit integers using Radix Sort.
/// \}






#endif /* GeneralUtilities_h */
