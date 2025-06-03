#include "Listing.h"
#include <sstream>
#include <vector>
#include <iostream>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

Listing::Listing() = default;

Listing::Listing(std::string t, float p, std::string d, float s, int r, int b, bool park)
    : title(std::move(t)), price(p), description(std::move(d)), size(s), rooms(r), bathrooms(b), hasParking(park) {}

std::string Listing::toCSV() const {
    std::ostringstream oss;
    oss << title << "," << price << "," << description << ","
        << size << "," << rooms << "," << bathrooms << "," << hasParking;
    return oss.str();
}

Listing Listing::fromCSV(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string item;
    while (getline(ss, item, ',')) {
        fields.push_back(item);
    }
    if (fields.size() != 7 || fields[0].empty()) {
        throw std::runtime_error("Invalid CSV line: " + line);
    }

    return Listing(
        fields[0],
        std::stof(fields[1]),
        fields[2],
        std::stof(fields[3]),
        std::stoi(fields[4]),
        std::stoi(fields[5]),
        std::stoi(fields[6])
    );
}

void Listing::print() const {
    std::cout << YELLOW "Title:" RESET " " << CYAN << title << RESET << "\n"
              << YELLOW "Price:" RESET " " << GREEN << "$" << price << RESET << "\n"
              << YELLOW "Description:" RESET " " << CYAN << description << RESET << "\n"
              << YELLOW "Size:" RESET " " << size << " sqm\n"
              << YELLOW "Rooms:" RESET " " << rooms << "\n"
              << YELLOW "Bathrooms:" RESET " " << bathrooms << "\n"
              << YELLOW "Parking:" RESET " " << (hasParking ? "Yes" : "No") << "\n"
              << "--------------" << std::endl;
}
