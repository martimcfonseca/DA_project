/**
 * @file Menu.h
 * @brief Declaration of the main functions responsible for displaying the menu and handling user actions.
 * @note See the implementation in \ref Menu.cpp "Menu.cpp".
 */

#ifndef DA_PROJECT_MENU_H
#define DA_PROJECT_MENU_H

#include "Input.h"
#include "Graph.h"
#include "Parser.h"

using namespace std;


void runMenu(Input& data, Graph<Node>& graph, bool loaded);

#endif