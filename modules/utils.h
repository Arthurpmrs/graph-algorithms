#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

#include "graph.h"

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

/**
 * @brief Create a graph from a given input file
 *
 * @param filename input filename
 * @return Graph
 */
Graph createGraphFromFile(string filename);

/**
 * @brief Get the total weight of the minimum spanning tree
 *
 * @param mst reference to the graph that represents the minimum spanning tree
 * @return int
 */
int getTotalWeight(Graph &mst);

/**
 * @brief Prints the minimum spanning tree solution to cout.
 *
 * @param mst reference to the graph that represents the minimum spanning tree
 */
void printMstSolution(Graph &mst);

/**
 * @brief Writes the minimum spanning tree edges to a file.
 *
 * @param mst reference to the graph that represents the minimum spanning tree
 * @param output_filename name of the file to write the edges
 */
void writeMstEdgesToFile(Graph &mst, string output_filename);

#endif // UTILS_H