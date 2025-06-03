#pragma once
#include <string>

class Listing {
public:
    std::string title;
    float price;
    std::string description;
    float size;
    int rooms;
    int bathrooms;
    bool hasParking;

    Listing();
    Listing(std::string t, float p, std::string d, float s, int r, int b, bool park);
    std::string toCSV() const;
    static Listing fromCSV(const std::string& line);
    void print() const;
};
