#include "ListingManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

ListingManager::ListingManager(const std::string& filePath, const std::string& favPath)
    : path(filePath), favoritesPath(favPath) {}

void ListingManager::addListing(const Listing& l) {
    std::ofstream file(path, std::ios::app);
    if (!file) {
        std::cerr << RED "Unable to open file." RESET << std::endl;
        return;
    }
    file << l.toCSV() << "\n";
    std::cout << GREEN "Listing added successfully!" RESET << std::endl;
}

std::vector<Listing> ListingManager::readListings(bool fromFavorites) {
    std::ifstream file(fromFavorites ? favoritesPath : path);
    std::vector<Listing> listings;
    std::string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            try {
                listings.push_back(Listing::fromCSV(line));
            } catch (...) {}
        }
    }
    return listings;
}

void ListingManager::writeListings(const std::vector<Listing>& listings, bool toFavorites) {
    std::ofstream file(toFavorites ? favoritesPath : path);
    for (const auto& l : listings) {
        file << l.toCSV() << "\n";
    }
}

void ListingManager::displayListings(bool fromFavorites) {
    auto listings = readListings(fromFavorites);
    std::cout << GREEN << (fromFavorites ? "Favorite Listings" : "Current Listings") << RESET << "\n--------------" << std::endl;
    for (size_t i = 0; i < listings.size(); ++i) {
        std::cout << YELLOW "[" << i << "]" RESET << std::endl;
        listings[i].print();
    }
}

void ListingManager::viewDetails(int index, bool fromFavorites) {
    auto listings = readListings(fromFavorites);
    if (index >= 0 && index < listings.size()) {
        listings[index].print();
    } else {
        std::cerr << RED "Invalid listing index." RESET << std::endl;
    }
}

void ListingManager::addToFavorites(int index) {
    auto listings = readListings();
    if (index >= 0 && index < listings.size()) {
        std::ofstream favFile(favoritesPath, std::ios::app);
        favFile << listings[index].toCSV() << "\n";
        std::cout << GREEN "Added to favorites." RESET << std::endl;
    } else {
        std::cerr << RED "Invalid listing index." RESET << std::endl;
    }
}

void ListingManager::purchaseListing(int index) {
    auto listings = readListings();
    if (index >= 0 && index < listings.size()) {
        listings.erase(listings.begin() + index);
        writeListings(listings);
        std::cout << GREEN "Listing purchased and removed." RESET << std::endl;
    } else {
        std::cerr << RED "Invalid listing index." RESET << std::endl;
    }
}

bool ListingManager::deleteByTitle(const std::string& title) {
    auto listings = readListings();
    auto it = std::remove_if(listings.begin(), listings.end(), [&](const Listing& l) {
        return l.title == title;
    });
    bool removed = it != listings.end();
    listings.erase(it, listings.end());
    writeListings(listings);
    return removed;
}

void ListingManager::editListing(int index, const Listing& updated) {
    auto listings = readListings();
    if (index >= 0 && index < listings.size()) {
        listings[index] = updated;
        writeListings(listings);
        std::cout << GREEN "Listing updated successfully." RESET << std::endl;
    } else {
        std::cerr << RED "Invalid listing index." RESET << std::endl;
    }
}
