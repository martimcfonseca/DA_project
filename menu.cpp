//
// Created by cristiano on 16/03/26.
//

#include <iostream>
#include <ostream>

#include "Menu.h"

void Menu::run() {
    int option;
    showmenu();
    std::cin >> option;
    std::cout << std::endl;
}


void Menu::showmenu() {
    std::cout << "===========================================" << std::endl;
    std::cout << "   Scientific Review Assignment Tool      " << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << " 1. Load data (submissions + reviewers)   " << std::endl;
    std::cout << " 2. Assign reviews (max flow)             " << std::endl;
    std::cout << " 3. Show current assignments              " << std::endl;
    std::cout << " 4. Risk analysis (remove reviewer(s))   " << std::endl;
    std::cout << " 5. Adjust parameters (Min/MaxReviews)   " << std::endl;
    std::cout << " 0. Exit                                  " << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "Option: ";
    return;
}
