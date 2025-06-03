#include "ListingManager.h"
#include <iostream>
#include <filesystem>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << RED "Usage: ./user1 <option> <file> [args...]" RESET << std::endl;
        return 1;
    }

    int option = std::stoi(argv[1]);
    std::string path = argv[2];
    if ((option != 1) && !fs::exists(path)) {
        std::cerr << RED "File does not exist: " << path << RESET << std::endl;
        return 1;
    }

    ListingManager manager(path);

    switch (option) {
        case 1: {
            if (argc < 10) {
                std::cerr << RED "Missing arguments for add." RESET << std::endl;
                return 1;
            }
            Listing l(argv[3], std::stof(argv[4]), argv[5], std::stof(argv[6]),
                      std::stoi(argv[7]), std::stoi(argv[8]), std::stoi(argv[9]));
            manager.addListing(l);
            break;
        }
        case 2:
            manager.displayListings();
        break;
        case 3:
            if (argc < 4) {
                std::cerr << RED "Missing title for delete." RESET << std::endl;
                return 1;
            }
        if (manager.deleteByTitle(argv[3]))
            std::cout << GREEN "Deleted." RESET << std::endl;
        else
            std::cerr << RED "Not found." RESET << std::endl;
        break;
        case 4:
            manager.displayListings(); // dummy sort
        break;
        default:
            std::cerr << RED "Invalid option for user1." RESET << std::endl;
        return 1;
    }

    return 0;
}
