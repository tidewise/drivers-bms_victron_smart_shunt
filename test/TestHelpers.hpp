#ifndef BMS_VICTRON_SMART_SHUNT_TESTHELPERS_HPP
#define BMS_VICTRON_SMART_SHUNT_TESTHELPERS_HPP

#include <string>
#include <vector>

namespace bms_victron_smart_shunt {
    /**
     * @brief Read a text file and convert it to a uint8_t buffer
     *
     * @param file_path The path of the text file
     * @return std::vector<uint8_t>
     */
    std::vector<uint8_t> readTextFile(std::string const& file_path);
}

#endif