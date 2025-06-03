#pragma once
#include "Listing.h"
#include <vector>
#include <string>

class ListingManager {
private:
    std::string path;
    std::string favoritesPath;

public:
    ListingManager(const std::string& filePath, const std::string& favPath = "favorites.txt");

    void addListing(const Listing& l);
    std::vector<Listing> readListings(bool fromFavorites = false);
    void writeListings(const std::vector<Listing>& listings, bool toFavorites = false);
    void displayListings(bool fromFavorites = false);
    void viewDetails(int index, bool fromFavorites = false);
    void addToFavorites(int index);
    void purchaseListing(int index);
    bool deleteByTitle(const std::string& title);
    void editListing(int index, const Listing& updated);
};
