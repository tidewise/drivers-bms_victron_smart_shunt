#ifndef BMS_VICTRON_SMART_SHUNT_PROTOCOL_HPP
#define BMS_VICTRON_SMART_SHUNT_PROTOCOL_HPP

#include <bms_victron_smart_shunt/Fields.hpp>
#include <cstdint>

namespace bms_victron_smart_shunt {
    namespace protocol {
        // Packet start marker
        static const uint8_t PACKET_START_MARKER = 0x0d;
        static const uint8_t LINE_DELIMITER = 0x0a;
        static const uint8_t FIELD_DELIMITER = 0x09;

        // Minimum number of bytes per packet
        // TODO: check
        static const int MIN_PACKET_SIZE = 17;

        /** Implements iodrivers_base's extractPacket protocol
         *
         * See iodrivers_base::extractPacket for detailed information
         */
        int extractPacket(const uint8_t* buffer, int buffer_size);

        /**
         * @brief Parse the smart shunt data fields
         * TODO improve
         * @param buffer
         * @param buffer_size
         * @return Fields
         */
        Fields parseFields(uint8_t const* buffer, int buffer_size);
        /**
         * @brief Unmarshal the DC Monitor Mode
         *
         * @param value The mode as int
         * @return DCMonitorMode
         */
        DCMonitorMode unmarshalMode(int value);
    }
}

#endif