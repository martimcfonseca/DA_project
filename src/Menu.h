/**
 *  @file Menu.h
 *  @brief Principal function responsible for displaying the menu and deciding which actions to perform
 */

#ifndef DA_PROJECT_MENU_H
#define DA_PROJECT_MENU_H

#include "Input.h"
#include "Graph.h"
#include "Parser.h"

using namespace std;

/**
 * @brief Initializes the main loop.
 * Displays the menu and available options, processes user input,
 * and chooses the appropriate algorithms.
 * @param data reference to the data where the information is stored
 * @param graph reference to the graph used to execute the algorithms
 * @param loaded flag indicating whether the data is loaded
 */
void runMenu(Input& data, Graph<Node>& graph, bool loaded);

#endif