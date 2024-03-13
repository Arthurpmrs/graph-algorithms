#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstring>

using namespace std;

/**
 * @brief Gets the value of a parameter from the command line arguments.
 *
 * @param parameter the parameter to look for
 * @param argc number of arguments
 * @param argv array of arguments
 * @param value pointer to a string to store the value of the parameter
 * @return true if the parameter was found, false otherwise
 */
bool getParameterValue(char *parameter, int argc, char *argv[], string *value = NULL);

#endif // UTILS_H