#include "TestHelpers.hpp"
#include <fstream>
#include <iostream>

using namespace bms_victron_smart_shunt;

std::vector<uint8_t> bms_victron_smart_shunt::readTextFile(std::string const& file_path)
{
    std::ifstream file(file_path);
    if (!file) {
        std::cout << "Error opening file!" << std::endl;
    }
    char ch;
    std::vector<uint8_t> buffer;
    while (file.get(ch)) {
        buffer.push_back(static_cast<uint8_t>(ch));
    }
    file.close();
    return buffer;
}
