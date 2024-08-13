#ifndef BMS_VICTRON_SMART_SHUNT_PROTOCOL_HPP
#define BMS_VICTRON_SMART_SHUNT_PROTOCOL_HPP

#include <cstdint>

namespace bms_victron_smart_shunt {
    namespace protocol {
        // Packet start marker
        static const uint8_t PACKET_START_MARKER = 0x0d;

        // Minimum number of bytes per packet
        // TODO: check
        static const int MIN_PACKET_SIZE = 17;

        /** Implements iodrivers_base's extractPacket protocol
         *
         * See iodrivers_base::extractPacket for detailed information
         */
        int extractPacket(const uint8_t* buffer, int buffer_size);
    }
}

#endif