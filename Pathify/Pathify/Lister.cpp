#include "Lister.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>



void ListPathVariables() {
    system("cls");
    char* pathVar;
    size_t len;
    _dupenv_s(&pathVar, &len, "PATH");

    if (!pathVar) {
        std::cerr << "Error retrieving PATH variable.\n";
        return;
    }

    int choice;
    std::cout << "Select display format:\n";
    std::cout << "1. Regular (inline format)\n";
    std::cout << "2. Ordered (each variable on a new line)\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    if (choice == 1) {
        system("cls");
        // Inline format
        std::cout << "Current PATH Variables:\n" << pathVar << std::endl;
    }
    else if (choice == 2) {
        system("cls");
        // Ordered format (splitting by `;`)
        std::cout << "Current PATH Variables (Ordered):\n";
        std::stringstream ss(pathVar);
        std::string pathEntry;
        while (std::getline(ss, pathEntry, ';')) {
            std::cout << pathEntry << std::endl;
        }
    }
    else {
        std::cout << "Invalid choice. Showing default inline format:\n";
        std::cout << pathVar << std::endl;
    }

    free(pathVar);
}
