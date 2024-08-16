#ifndef BMS_VICTRON_SMART_SHUNT_PROTOCOL_HPP
#define BMS_VICTRON_SMART_SHUNT_PROTOCOL_HPP

#include <base/Time.hpp>
#include <bms_victron_smart_shunt/SmartShuntFeedback.hpp>
#include <cstdint>

namespace bms_victron_smart_shunt {
    namespace protocol {
        // Packet start marker
        static const uint8_t PACKET_START_MARKER = 0x0d;
        static const uint8_t LINE_DELIMITER = 0x0a;
        static const uint8_t FIELD_DELIMITER = 0x09;
        static const char* CHECKSUM_STR __attribute__((unused)) = "Checksum";

        // Minimum number of bytes per packet
        // TODO: check
        static const int MIN_PACKET_SIZE = 17;

        /** Implements iodrivers_base's extractPacket protocol
         *
         * See iodrivers_base::extractPacket for detailed information
         */
        int extractPacket(const uint8_t* buffer, int buffer_size);

        /**
         * @brief Parse the Victorn Smart Shunt feedback
         * @param buffer The buffer
         * @param buffer_size The buffer size
         * @return SmartShuntFeedback
         */
        SmartShuntFeedback parseSmartShuntFeedback(uint8_t const* buffer,
            int buffer_size);
    }
}

#endif