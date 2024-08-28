#ifndef BMS_VICTRON_SMART_SHUNT_PROTOCOL_HPP
#define BMS_VICTRON_SMART_SHUNT_PROTOCOL_HPP

#include <base/Time.hpp>
#include <bms_victron_smart_shunt/SmartShuntFeedback.hpp>
#include <cstdint>

namespace bms_victron_smart_shunt {
    namespace protocol {
        static constexpr char PACKET_START_MARKER = 0x0d;
        static constexpr char LINE_DELIMITER = 0x0a;
        static constexpr char FIELD_DELIMITER = 0x09;
        static constexpr char CHECKSUM_STR[] = {'C', 'h', 'e', 'c', 'k', 's', 'u', 'm'};
        static constexpr size_t CHECKSUM_STR_LEN = sizeof(CHECKSUM_STR);
        static constexpr size_t MIN_PACKET_SIZE = 17;

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
        void parseSmartShuntFeedback(uint8_t const* buffer,
            int buffer_size,
            SmartShuntFeedback& feedback);
    }
}

#endif