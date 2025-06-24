#pragma once
#include "StreamHelpers.h"
#include "Vector.hpp"
#include <fstream>

void StreamHelpers::readNWords(size_t n, std::stringstream& ss, String& data)
{
    ss >> std::ws;
    while (ss.good() && n > 0)
    {
        String temp;
        ss >> temp;
        if (temp.getLen() > 0)
        {
            n--;
            data += temp;
        }
    }
}

void StreamHelpers::readRemaining(std::stringstream& ss, String& data)
{
    ss >> std::ws;
    char symb;
    while (ss.get(symb))
    {
        data += symb;
    }
}

void StreamHelpers::splitToVector(std::stringstream& ss, Vector<String>& vector)
{
    ss >> std::ws;
    while (ss.good())
    {
        String temp;
        ss >> temp;
        if (temp.getLen() > 0)
        {
            vector.push_back(temp);
        }
    }
}

void StreamHelpers::splitNToVector(size_t n, std::stringstream& ss, Vector<String>& vector)
{
    ss >> std::ws;
    while (ss.good() && n > 0)
    {
        String temp;
        ss >> temp;
        if (temp.getLen() > 0)
        {
            n--;
            vector.push_back(temp);
        }
    }
}

bool StreamHelpers::fileExists(const String& filename)
{
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open())
    {
        return false;
    }
    ifs.peek();
    bool exists = ifs.good();
    ifs.close();

    return exists;
}

void StreamHelpers::createEmpty(const String& filename)
{
    std::ofstream ofs(filename.c_str());
    if (!ofs.is_open())
    {
        throw std::exception("File could not open!");
    }

    ofs.close();
}
