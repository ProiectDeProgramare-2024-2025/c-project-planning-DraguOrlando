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
        std::cout << RED "Usage: ./user2 <option> <file> [args...]" RESET << std::endl;
        return 1;
    }

    int option = std::stoi(argv[1]);
    std::string path = argv[2];
    if (!fs::exists(path)) {
        std::cerr << RED "File does not exist: " << path << RESET << std::endl;
        return 1;
    }

    ListingManager manager(path);

    switch (option) {
        case 5:
            manager.viewDetails(std::stoi(argv[3]));
        break;
        case 6:
            manager.addToFavorites(std::stoi(argv[3]));
        break;
        case 7:
            manager.purchaseListing(std::stoi(argv[3]));
        break;
        case 8:
            manager.displayListings(true);
        break;
        case 9: {
            if (argc < 11) {
                std::cerr << RED "Missing arguments for edit." RESET << std::endl;
                return 1;
            }
            Listing l(argv[4], std::stof(argv[5]), argv[6], std::stof(argv[7]),
                      std::stoi(argv[8]), std::stoi(argv[9]), std::stoi(argv[10]));
            manager.editListing(std::stoi(argv[3]), l);
            break;
        }
        default:
            std::cerr << RED "Invalid option for user2." RESET << std::endl;
        return 1;
    }

    return 0;
}
