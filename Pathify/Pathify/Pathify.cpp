#include <iostream>
#include <string>
#include <cstdlib>
#include "Pathenator.h"
#include "Lister.h"

int choice;
bool modifySystem;

int main() {
    std::cout << "Select an option:\n";
    std::cout << "1. Edit PATH (Add to PATH)\n";
    std::cout << "2. List all PATH variables\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    if (choice == 1) {
        system("cls"); // Clears the console
        std::string folderPath;
        std::cout << "Enter the folder to add to PATH: ";
        std::cin.ignore();
        std::getline(std::cin, folderPath);
        std::cout << "Modify system PATH? (1 = Yes, 0 = No): ";
        std::cin >> modifySystem;

        AddToPath(folderPath, modifySystem);
    }
    else if (choice == 2) {
        ListPathVariables();
    }
    else {
        std::cout << "Exiting...\n";
    }

    return 0;
}
